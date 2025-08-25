//
// Created by loghin on 6/3/25.
//

#ifndef CDS_ITERATOR_PROJECTION_ITERATOR_HPP
#define CDS_ITERATOR_PROJECTION_ITERATOR_HPP
#pragma once

#include <cds/functional/Invoke>
#include <cds/meta/IteratorTraits>

namespace cds {
namespace iterator {
namespace impl {
using meta::AddPointer;
using meta::Conditional;
using meta::EnableIf;
using meta::IteratorType;
using meta::IteratorTypeOf;
using meta::IsDefaultConstructible;
using meta::IsIntegral;
using meta::IsRef;
using meta::IsVoid;
using meta::RemoveRef;
using meta::rvalue;

namespace fn = functional;

template <typename I, typename P> using ProjectionOf = decltype(fn::invoke(rvalue<P>(), *rvalue<I>()));

template <typename I, typename P, IteratorType t = IteratorTypeOf<I>::value, IteratorType = t>
class ProjectionIterator;

template <typename I, typename P> class ProjectionIterator<I, P, IteratorType::UnknownOrSentinel> : private I {
  using I::I;
  using I::operator=;

  [[nodiscard]] constexpr auto base() const noexcept -> I const& {
    return static_cast<I const&>(*this);
  }
};

template <typename I, typename P, IteratorType orig>
class CDS_ATTR(ebo) ProjectionIterator<I, P, IteratorType::Forward, orig> : private P {
public:
  using Reference = ProjectionOf<I, P>;
  using Address = AddPointer<RemoveRef<Reference>>;

  CDS_ATTR(2(explicit, constexpr(11))) ProjectionIterator(I const& it, P const& p) noexcept :
      P{p}, _it{it} {}

  template <typename P0 = P, typename = EnableIf<IsDefaultConstructible<P0>>>
  CDS_ATTR(2(explicit, constexpr(11))) ProjectionIterator(I const& it) noexcept : ProjectionIterator{it, P0{}} {}

  CDS_ATTR(constexpr(11)) ProjectionIterator() noexcept = default;
  CDS_ATTR(constexpr(11)) ProjectionIterator(ProjectionIterator const&) noexcept = default;
  CDS_ATTR(constexpr(11)) ProjectionIterator(ProjectionIterator&&) noexcept = default;
  ~ProjectionIterator() noexcept = default;

  CDS_ATTR(constexpr(14)) auto operator=(ProjectionIterator const&) noexcept -> ProjectionIterator& = default;
  CDS_ATTR(constexpr(14)) auto operator=(ProjectionIterator&&) noexcept -> ProjectionIterator& = default;

  CDS_ATTR(2(nodiscard, constexpr(11))) auto operator*()
      const CDS_ATTR(noexcept(noexcept(fn::invoke(P{}, *rvalue<I>())))) -> Reference {
    return fn::invoke(projector(), *base());
  }

  template <typename I0 = I, typename = EnableIf<IsRef<ProjectionOf<I0, P>>>> CDS_ATTR(2(nodiscard, constexpr(11)))
  auto operator->() const CDS_ATTR(noexcept(noexcept(&fn::invoke(rvalue<P>(), *rvalue<I>())))) -> Address {
    return &fn::invoke(projector(), *base());
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto base() const noexcept -> I const& {
    return _it;
  }

  CDS_ATTR(constexpr(14)) auto operator++() noexcept -> ProjectionIterator<I, P, orig>& {
    ++base();
    return *this;
  }

  CDS_ATTR(constexpr(14)) auto operator++(int) noexcept -> ProjectionIterator<I, P, orig> {
    auto copy = static_cast<ProjectionIterator<I, P, orig> const&>(*this);
    ++base();
    return copy;
  }

protected:
  CDS_ATTR(2(nodiscard, constexpr(11))) auto projector() const noexcept -> P const& {
    return static_cast<P const&>(*this);
  }

  CDS_ATTR(2(nodiscard, constexpr(14))) auto base() noexcept -> I& {
    return _it;
  }

private:
  I _it;
};

template <typename LI, typename LP, typename RI, typename RP> CDS_ATTR(2(nodiscard, constexpr(11)))
auto operator==(ProjectionIterator<LI, LP> const& lhs, ProjectionIterator<RI, RP> const& rhs) noexcept -> bool {
  return lhs.base() == rhs.base();
}

template <typename LI, typename LP, typename RI, typename RP> CDS_ATTR(2(nodiscard, constexpr(11)))
auto operator!=(ProjectionIterator<LI, LP> const& lhs, ProjectionIterator<RI, RP> const& rhs) noexcept -> bool {
  return lhs.base() != rhs.base();
}

template <typename I, typename P, IteratorType orig>
class CDS_ATTR(ebo) ProjectionIterator<I, P, IteratorType::Bidirectional, orig> :
    public ProjectionIterator<I, P, IteratorType::Forward, orig> {
  using Base = ProjectionIterator<I, P, IteratorType::Forward, orig>;

public:
  using Base::Base;
  using Base::operator=;

  CDS_ATTR(constexpr(14)) auto operator--() noexcept -> ProjectionIterator<I, P, orig>& {
    --Base::base();
    return *this;
  }

  CDS_ATTR(constexpr(14)) auto operator--(int) noexcept -> ProjectionIterator<I, P, orig> {
    auto copy = static_cast<ProjectionIterator<I, P, orig> const&>(*this);
    --Base::base();
    return copy;
  }
};

template <typename I, typename P>
class CDS_ATTR(ebo) ProjectionIterator<I, P, IteratorType::RandomAccess> :
    public ProjectionIterator<I, P, IteratorType::Bidirectional, IteratorType::RandomAccess> {
  using Base = ProjectionIterator<I, P, IteratorType::Bidirectional, IteratorType::RandomAccess>;
  using Base::projector;

public:
  using typename Base::Reference;
  using Base::Base;
  using Base::operator=;

  template <typename N, typename I0 = I, typename = EnableIf<IsRef<ProjectionOf<I0, P>>>>
  CDS_ATTR(2(nodiscard, constexpr(11))) auto operator[](N index) const noexcept -> Address {
    return fn::invoke(projector(), Base::base()[index]);
  }

  template <typename N, typename = EnableIf<IsIntegral<N>>> CDS_ATTR(2(nodiscard, constexpr(11)))
  auto operator+(N rhs) const noexcept -> ProjectionIterator {
    return ProjectionIterator{Base::base() + rhs, projector()};
  }

  template <typename N, typename = EnableIf<IsIntegral<N>>> CDS_ATTR(2(nodiscard, constexpr(11)))
  auto operator-(N rhs) const noexcept -> ProjectionIterator {
    return ProjectionIterator{Base::base() - rhs, projector()};
  }
};

template <typename LI, typename LP, typename RI, typename RP> CDS_ATTR(2(nodiscard, constexpr(11))) auto operator<(
    ProjectionIterator<LI, LP, IteratorType::RandomAccess> const& lhs,
    ProjectionIterator<RI, RP, IteratorType::RandomAccess> const& rhs
) noexcept -> bool {
  return lhs.base() < rhs.base();
}

template <typename LI, typename LP, typename RI, typename RP> CDS_ATTR(2(nodiscard, constexpr(11))) auto operator>(
    ProjectionIterator<LI, LP, IteratorType::RandomAccess> const& lhs,
    ProjectionIterator<RI, RP, IteratorType::RandomAccess> const& rhs
) noexcept -> bool {
  return lhs.base() > rhs.base();
}

template <typename LI, typename LP, typename RI, typename RP> CDS_ATTR(2(nodiscard, constexpr(11))) auto operator<=(
    ProjectionIterator<LI, LP, IteratorType::RandomAccess> const& lhs,
    ProjectionIterator<RI, RP, IteratorType::RandomAccess> const& rhs
) noexcept -> bool {
  return lhs.base() <= rhs.base();
}

template <typename LI, typename LP, typename RI, typename RP> CDS_ATTR(2(nodiscard, constexpr(11))) auto operator>=(
    ProjectionIterator<LI, LP, IteratorType::RandomAccess> const& lhs,
    ProjectionIterator<RI, RP, IteratorType::RandomAccess> const& rhs
) noexcept -> bool {
  return lhs.base() >= rhs.base();
}

#if CDS_ATTR(spaceship)
template <typename LI, typename LP, typename RI, typename RP> CDS_ATTR(2(nodiscard, constexpr(11))) auto operator<=>(
    ProjectionIterator<LI, LP, IteratorType::RandomAccess> const& lhs,
    ProjectionIterator<RI, RP, IteratorType::RandomAccess> const& rhs
) noexcept -> decltype(lhs.base() <=> rhs.base()) {
  return lhs.base() <=> rhs.base();
}
#endif

template <typename LI, typename LP, typename RI, typename RP> CDS_ATTR(2(nodiscard, constexpr(11))) auto operator-(
    ProjectionIterator<LI, LP, IteratorType::RandomAccess> const& lhs,
    ProjectionIterator<RI, RP, IteratorType::RandomAccess> const& rhs
) noexcept -> decltype(lhs - rhs) {
  return lhs.base() - rhs.base();
}
} // namespace impl

using impl::ProjectionIterator;
} // namespace iterator
} // namespace cds

#endif // #ifndef CDS_ITERATOR_PROJECTION_ITERATOR_HPP
