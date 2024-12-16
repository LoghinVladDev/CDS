//
// Created by loghin on 12/16/24.
//

#ifndef CDS_COLLECTION_VECTOR_VIEW_CONVERSION_HPP
#define CDS_COLLECTION_VECTOR_VIEW_CONVERSION_HPP

#include <initializer_list>
#include <cds/meta/Base>
#include "VectorViewDecl.hpp"
#include "../vector/VectorDecl.hpp"
#include "../../primitive/string/StringBaseDecl.hpp"
#include "../../primitive/string/StringViewBaseDecl.hpp"
#include "../../stdlib/array.hpp"
#include "../../stdlib/string.hpp"
#include "../../stdlib/string_view.hpp"
#include "../../stdlib/vector.hpp"

namespace cds {
namespace impl {
using meta::False;
using meta::Null;

template <typename T, Size s> struct VectorViewArrayConversion : True {
  using ElementType = T;
  template <typename T0> CDS_ATTR(2(nodiscard, constexpr(11))) static auto begin(T0&& data) noexcept -> T* {
    return fwd<T0>(data);
  }

  template <typename T0> CDS_ATTR(2(nodiscard, constexpr(11))) static auto end(T0&& data) noexcept -> T* {
    return fwd<T0>(data) + s;
  }

  template <Size extent, typename T0> CDS_ATTR(2(nodiscard, constexpr(11))) static auto accepts(T0&&) noexcept -> bool {
    return extent <= s;
  }

  template <Size extent> CDS_ATTR(2(nodiscard, constexpr(11))) static auto ctAccepts() noexcept -> bool {
    return extent <= s;
  }
};

template <typename T> struct VectorViewVectorConversion : True {
  using ElementType = T;
  template <typename T0> CDS_ATTR(2(nodiscard, constexpr(11))) static auto begin(T0&& data) noexcept -> T* {
    return &(fwd<T0>(data)[0]);
  }

  template <typename T0> CDS_ATTR(2(nodiscard, constexpr(11))) static auto end(T0&& data) noexcept -> T* {
    return &(fwd<T0>(data)[fwd<T0>(data).size() - 1]) + 1;
  }

  template <Size extent, typename T0> CDS_ATTR(2(nodiscard, constexpr(11))) static auto accepts(T0&& data) noexcept
      -> bool {
    return extent <= (end(fwd<T0>(data)) - begin(fwd<T0>(data)));
  }

  template <Size extent> CDS_ATTR(2(nodiscard, constexpr(11))) static auto ctAccepts() noexcept -> bool {
    return true;
  }
};

template <typename T> struct VectorViewIListConversion : True {
  using ElementType = T;
  template <typename T0> CDS_ATTR(2(nodiscard, constexpr(11))) static auto begin(T0&& data) noexcept -> T* {
    return &*(fwd<T0>(data).begin());
  }

  template <typename T0> CDS_ATTR(2(nodiscard, constexpr(11))) static auto end(T0&& data) noexcept -> T* {
    return &*(fwd<T0>(data).begin() + fwd<T0>(data).size());
  }

  template <Size extent, typename T0> CDS_ATTR(2(nodiscard, constexpr(11))) static auto accepts(T0&& data) noexcept
      -> bool {
    return extent <= (end(fwd<T0>(data)) - begin(fwd<T0>(data)));
  }

  template <Size extent> CDS_ATTR(2(nodiscard, constexpr(11))) static auto ctAccepts() noexcept -> bool {
    return true;
  }
};

template <typename> struct VectorViewConversion : False {};

template <> struct VectorViewConversion<Null> : True {
  using ElementType = void;
  CDS_ATTR(2(nodiscard, constexpr(11))) static auto begin(Null) noexcept -> Null {
    return nullptr;
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) static auto end(Null) noexcept -> Null {
    return nullptr;
  }

  template <Size extent> CDS_ATTR(2(nodiscard, constexpr(11))) static auto accepts(Null) noexcept -> bool {
    return extent == 0u;
  }

  template <Size extent> CDS_ATTR(2(nodiscard, constexpr(11))) static auto ctAccepts() noexcept -> bool {
    return extent == 0u;
  }
};

template <typename T, Size s> struct VectorViewConversion<T[s]> : VectorViewArrayConversion<T, s> {};
template <typename T, Size s> struct VectorViewConversion<T const[s]> : VectorViewArrayConversion<T const, s> {};
template <typename T, Size s> struct VectorViewConversion<T(&)[s]> : VectorViewArrayConversion<T, s> {};
template <typename T, Size s> struct VectorViewConversion<T const(&)[s]> : VectorViewArrayConversion<T const, s> {};

template <typename T, Size s> struct VectorViewConversion<VectorView<T, s>> :
    VectorViewArrayConversion<T const, s> {};
template <typename T, Size s> struct VectorViewConversion<VectorView<T, s>&> :
    VectorViewArrayConversion<T const, s> {};
template <typename T, Size s> struct VectorViewConversion<VectorView<T, s> const> :
    VectorViewArrayConversion<T const, s> {};
template <typename T, Size s> struct VectorViewConversion<VectorView<T, s> const&> :
    VectorViewArrayConversion<T const, s> {};

template <typename T> struct VectorViewConversion<VectorView<T>> :
    VectorViewVectorConversion<T const> {};
template <typename T> struct VectorViewConversion<VectorView<T>&> :
    VectorViewVectorConversion<T const> {};
template <typename T> struct VectorViewConversion<VectorView<T> const> :
    VectorViewVectorConversion<T const> {};
template <typename T> struct VectorViewConversion<VectorView<T> const&> :
    VectorViewVectorConversion<T const> {};

template <typename T, typename E, typename A, typename S> struct VectorViewConversion<BaseVector<T, E, A, S>> :
    VectorViewVectorConversion<T> {};
template <typename T, typename E, typename A, typename S> struct VectorViewConversion<BaseVector<T, E, A, S>&> :
    VectorViewVectorConversion<T> {};
template <typename T, typename E, typename A, typename S> struct VectorViewConversion<BaseVector<T, E, A, S> const> :
    VectorViewVectorConversion<T const> {};
template <typename T, typename E, typename A, typename S> struct VectorViewConversion<BaseVector<T, E, A, S> const&> :
    VectorViewVectorConversion<T const> {};

template <typename T, typename A> struct VectorViewConversion<std::vector<T, A>> : VectorViewVectorConversion<T> {};
template <typename T, typename A> struct VectorViewConversion<std::vector<T, A>&> : VectorViewVectorConversion<T> {};
template <typename T, typename A> struct VectorViewConversion<std::vector<T, A> const> :
    VectorViewVectorConversion<T const> {};
template <typename T, typename A> struct VectorViewConversion<std::vector<T, A> const&> :
    VectorViewVectorConversion<T const> {};

template <typename T> struct VectorViewConversion<std::initializer_list<T>> : VectorViewIListConversion<T const> {};
template <typename T> struct VectorViewConversion<std::initializer_list<T>&> : VectorViewIListConversion<T const> {};
template <typename T> struct VectorViewConversion<std::initializer_list<T> const> :
    VectorViewIListConversion<T const> {};
template <typename T> struct VectorViewConversion<std::initializer_list<T> const&> :
    VectorViewIListConversion<T const> {};

template <typename T, std::size_t size> struct VectorViewConversion<std::array<T, size>> :
    VectorViewArrayConversion<T, size> {};
template <typename T, std::size_t size> struct VectorViewConversion<std::array<T, size>&> :
    VectorViewArrayConversion<T, size> {};
template <typename T, std::size_t size> struct VectorViewConversion<std::array<T, size> const> :
    VectorViewArrayConversion<T const, size> {};
template <typename T, std::size_t size> struct VectorViewConversion<std::array<T, size> const&> :
    VectorViewArrayConversion<T const, size> {};

template <typename C, typename T, typename A> struct VectorViewConversion<std::basic_string<C, T, A>> :
    VectorViewVectorConversion<C> {};
template <typename C, typename T, typename A> struct VectorViewConversion<std::basic_string<C, T, A>&> :
    VectorViewVectorConversion<C> {};
template <typename C, typename T, typename A> struct VectorViewConversion<std::basic_string<C, T, A> const> :
    VectorViewVectorConversion<C const> {};
template <typename C, typename T, typename A> struct VectorViewConversion<std::basic_string<C, T, A> const&> :
    VectorViewVectorConversion<C const> {};

#if CDS_ATTR(cpp17)
template <typename C, typename T> struct VectorViewConversion<std::basic_string_view<C, T>> :
    VectorViewVectorConversion<C const> {};
template <typename C, typename T> struct VectorViewConversion<std::basic_string_view<C, T>&> :
    VectorViewVectorConversion<C const> {};
template <typename C, typename T> struct VectorViewConversion<std::basic_string_view<C, T> const> :
    VectorViewVectorConversion<C const> {};
template <typename C, typename T> struct VectorViewConversion<std::basic_string_view<C, T> const&> :
    VectorViewVectorConversion<C const> {};
#endif // #if CDS_ATTR(cpp17)
} // namespace impl
} // namespace cds

#endif // CDS_COLLECTION_VECTOR_VIEW_CONVERSION_HPP
