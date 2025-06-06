//
// Created by loghin on 6/3/25.
//

#ifndef CDS_DS_SET_PROJECTION_HPP
#define CDS_DS_SET_PROJECTION_HPP
#pragma once

#include <cds/functional/Transformer>
#include <cds/meta/Base>
#include <cds/meta/Semantics>

namespace cds {
namespace impl {
using functional::impl::Identity;
using meta::lvalue;
using meta::False;
using meta::True;

template <typename, typename> struct SetProjectionTraits;
template <typename C, typename P, typename T = SetProjectionTraits<C, P>> class SetProjection;

template <typename T, typename I> class SetProjectionInsertion;

template <typename T> class SetProjectionInsertion<T, False> {};
template <typename C, typename P, typename T> class SetProjectionInsertion<SetProjection<C, P, T>, True> {
public:
  template <typename... Args> CDS_ATTR(constexpr(14)) auto emplace(Args&&... args)
      CDS_ATTR(noexcept(noexcept(lvalue<C>().emplace(fwd<Args>(args)...))))
      -> decltype(lvalue<C>().emplace(fwd<Args>(args)...)) {
    return static_cast<SetProjection<C, P, T>*>(this)->base().emplace(fwd<Args>(args)...);
  }
};

template <typename, typename> class SetProjectionRemoval;

template <typename T> class SetProjectionRemoval<T, False> {};

template <typename C, typename P, typename T> class SetProjectionRemoval<SetProjection<C, P, T>, True> {
public:
  using Key = typename T::Value;

  CDS_ATTR(constexpr(20)) auto remove(Key const& key) noexcept -> bool {
    return static_cast<SetProjection<C, P, T>*>(this)->base().remove(key);
  }
};

template <typename C, typename T> class SetProjectionRemoval<SetProjection<C, Identity<>, T>, True> {
public:
  using Entry = typename T::Value;

  CDS_ATTR(constexpr(20)) auto remove(Entry const& entry) noexcept -> bool {
    return static_cast<SetProjection<C, Identity<>, T>*>(this)->base().remove(entry.key());
  }
};

template <typename T, typename I, typename CI, typename> class SetProjectionIteration {
  CDS_ATTR(2(nodiscard, constexpr(11))) auto refl() const noexcept -> T const* {
    return static_cast<T const*>(this);
  }

  CDS_ATTR(2(nodiscard, constexpr(14))) auto refl() noexcept -> T* {
    return static_cast<T*>(this);
  }

public:
  using Iterator = I;
  using ConstIterator = CI;

  CDS_ATTR(2(nodiscard, constexpr(11))) auto begin() const noexcept -> ConstIterator {
    return ConstIterator{refl()->base().cbegin(), refl()->projector()};
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto end() const noexcept -> ConstIterator {
    return ConstIterator{refl()->base().cend(), refl()->projector()};
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto cbegin() const noexcept -> ConstIterator {
    return ConstIterator{refl()->base().cbegin(), refl()->projector()};
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto cend() const noexcept -> ConstIterator {
    return ConstIterator{refl()->base().cend(), refl()->projector()};
  }

  CDS_ATTR(2(nodiscard, constexpr(14))) auto begin() noexcept -> Iterator {
    return Iterator{refl()->base().begin(), refl()->projector()};
  }

  CDS_ATTR(2(nodiscard, constexpr(14))) auto end() noexcept -> Iterator {
    return Iterator{refl()->base().end(), refl()->projector()};
  }
};

template <typename T, typename I, typename CI> class SetProjectionIteration<T, I, CI, Identity<>> {
  CDS_ATTR(2(nodiscard, constexpr(11))) auto refl() const noexcept -> T const* {
    return static_cast<T const*>(this);
  }

  CDS_ATTR(2(nodiscard, constexpr(14))) auto refl() noexcept -> T* {
    return static_cast<T*>(this);
  }

public:
  using Iterator = I;
  using ConstIterator = CI;

  CDS_ATTR(2(nodiscard, constexpr(11))) auto begin() const noexcept -> ConstIterator {
    return refl()->base().cbegin();
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto end() const noexcept -> ConstIterator {
    return refl()->base().cend();
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto cbegin() const noexcept -> ConstIterator {
    return refl()->base().cbegin();
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto cend() const noexcept -> ConstIterator {
    return refl()->base().cend();
  }

  CDS_ATTR(2(nodiscard, constexpr(14))) auto begin() noexcept -> Iterator {
    return refl()->base().begin();
  }

  CDS_ATTR(2(nodiscard, constexpr(14))) auto end() noexcept -> Iterator {
    return refl()->base().end();
  }
};

template <typename C, typename P, typename T> class SetProjection :
    private P,
    public SetProjectionIteration<SetProjection<C, P, T>, typename T::Iterator, typename T::ConstIterator, P>,
    public SetProjectionInsertion<SetProjection<C, P, T>, typename T::CanInsert>,
    public SetProjectionRemoval<SetProjection<C, P, T>, typename T::CanRemove> {
public:
  using Base = C;
  using Traits = T;
  using Value = typename Traits::Value;
  using Projector = typename Traits::Projector;
  using Iterator = typename Traits::Iterator;
  using ConstIterator = typename Traits::ConstIterator;

  CDS_ATTR(2(explicit, constexpr(11))) SetProjection(C& range, P const& p = {}) noexcept : P{p}, _range{range} {}

  SetProjection() = delete;
  SetProjection(SetProjection const&) = default;
  SetProjection(SetProjection&&) = default;
  ~SetProjection() = default;

  auto operator=(SetProjection const&) -> SetProjection& = default;
  auto operator=(SetProjection&&) -> SetProjection& = default;

  CDS_ATTR(2(nodiscard, constexpr(11))) auto base() const noexcept -> C& {
    return _range;
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto projector() const noexcept -> P const& {
    return static_cast<P const&>(*this);
  }

private:
  C& _range;
};
} // namespace impl

using impl::SetProjection;
} // namespace cds

#include "../../format/SetProjectionFormat.hpp"

#endif // CDS_DS_SET_PROJECTION_HPP
