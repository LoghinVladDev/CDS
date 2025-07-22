//
// Created by loghin on 2/10/24.
//

#ifndef CDS_POLICY_REHASH_POLICY_HPP
#define CDS_POLICY_REHASH_POLICY_HPP
#pragma once

#include <cds/meta/Base>
#include <cds/meta/Compiler>

namespace cds {
namespace impl {
using meta::True;

template <typename, typename> class RehashPolicy {
public:
  enum class BalanceType : U8 {
    Stable,
    Required,
    Impossible
  };

  struct BalanceResult {
    Size size;
    BalanceType type;
  };

  static_assert(sizeof(BalanceResult) == 2 * sizeof(Size), "unexpected BalanceResult size");
};

namespace prp {
template <typename T> struct U64PrimeRehashTable {
  static Size constexpr _fts = 35U;
  static T constexpr _ft[_fts] = {
      13ULL, 29ULL, 59ULL, 127ULL, 257ULL, 521ULL, 1049ULL, 2099ULL,
      4201ULL, 8419ULL, 16843ULL, 33703ULL, 67409ULL, 134837ULL,
      269683ULL, 539389ULL, 1078787ULL, 2157587ULL, 4315183ULL,
      8630387ULL, 17260781ULL, 34521589ULL, 69043189ULL, 138086407ULL,
      276172823ULL, 552345671ULL, 1104691373ULL, 2209382761ULL,
      4418765551ULL, 8837531111ULL, 17675062243ULL, 35350124489ULL,
      70700248981ULL, 141400498003ULL, 282800996033ULL
  };
};

#if !CDS_ATTR(cpp17)
// ODR before cpp17
template <typename T> T const U64PrimeRehashTable<T>::_ft[_fts];
#endif

template <typename T> struct U32PrimeRehashTable {
  static Size constexpr _fts = 28U;
  static T constexpr _ft[_fts] = {
    13ULL, 29ULL, 59ULL, 127ULL, 257ULL, 521ULL, 1049ULL, 2099ULL,
    4201ULL, 8419ULL, 16843ULL, 33703ULL, 67409ULL, 134837ULL,
    269683ULL, 539389ULL, 1078787ULL, 2157587ULL, 4315183ULL,
    8630387ULL, 17260781ULL, 34521589ULL, 69043189ULL, 138086407ULL,
    276172823ULL, 552345671ULL, 1104691373ULL, 2209382761ULL
  };
};

#if !CDS_ATTR(cpp17)
// ODR before cpp17
template <typename T> T const U32PrimeRehashTable<T>::_ft[_fts];
#endif

template <typename = Size> struct PrimeRehashTable {};
template <> struct PrimeRehashTable<U64> : U64PrimeRehashTable<U64> {};
template <> struct PrimeRehashTable<U32> : U32PrimeRehashTable<U32> {};

template <typename Table> class CDS_ATTR(ebo) TableRehashPolicy : public RehashPolicy<Size, True>, private Table {
public:
  CDS_ATTR(2(explicit, constexpr(11))) TableRehashPolicy(U64 const lf = 1) noexcept : _lf(lf) {}
  CDS_ATTR(constexpr(11)) TableRehashPolicy(TableRehashPolicy const&) = default;
  CDS_ATTR(constexpr(14)) auto operator=(TableRehashPolicy const&) -> TableRehashPolicy& = default;

  CDS_ATTR(constexpr(14)) auto reset() noexcept -> void {
    _fi = 0;
  }

  CDS_ATTR(2(nodiscard, constexpr(17))) auto current() const noexcept -> Size {
    return Table::_ft[_fi];
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto load() const noexcept -> Size {
    return _lf;
  }

  CDS_ATTR(2(nodiscard, constexpr(17))) auto balance(
      Size const bCnt, Size const eCnt, Size const rCnt
  ) noexcept -> BalanceResult {
    if (_fi + 1 == Table::_fts) {
      return {Table::_ft[_fi], BalanceType::Impossible};
    }

    auto const req = rCnt + eCnt;
    if (bCnt != 0) {
      auto const adj = bCnt * _lf;
      auto constexpr mgf = 2u;
      if (adj >= req) {
        return {current(), BalanceType::Stable};
      }

      if (req <= adj * mgf) {
        return {Table::_ft[++_fi], BalanceType::Required};
      }
    }

    while (_fi + 1 != Table::_fts && req > Table::_ft[_fi] * _lf) {
      ++_fi;
    }
    return {Table::_ft[_fi], BalanceType::Required};
  }

private:
  Size _lf;
  Size _fi {0};
};
} // namespace prp

using prp::TableRehashPolicy;
using prp::PrimeRehashTable;
} // namespace impl
} // namespace cds

#endif // CDS_POLICY_REHASH_POLICY_HPP
