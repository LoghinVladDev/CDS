//
// Created by loghin on 2/10/24.
//

#ifndef CDS_POLICY_REHASH_POLICY_HPP
#define CDS_POLICY_REHASH_POLICY_HPP
#pragma once

#include <cds/meta/Compiler>

namespace cds {
namespace impl {
template <typename S, bool hasLoadFactor> class RehashPolicy {
public:
  enum class BalanceType : U8 {
    Stable,
    Required,
    Impossible
  };

  struct BalanceResult {
    U64 size;
    BalanceType type;
  };
};

namespace prp {
template <typename T> struct U64PrimeRehashTable {
  static Size const _fts = 35U;
  constexpr static T const _ft[_fts] = {
      13ULL, 29ULL, 59ULL, 127ULL, 257ULL, 521ULL, 1049ULL, 2099ULL,
      4201ULL, 8419ULL, 16843ULL, 33703ULL, 67409ULL, 134837ULL,
      269683ULL, 539389ULL, 1078787ULL, 2157587ULL, 4315183ULL,
      8630387ULL, 17260781ULL, 34521589ULL, 69043189ULL, 138086407ULL,
      276172823ULL, 552345671ULL, 1104691373ULL, 2209382761ULL,
      4418765551ULL, 8837531111ULL, 17675062243ULL, 35350124489ULL,
      70700248981ULL, 141400498003ULL, 282800996033ULL
  };
};

// ODR before cpp17
template <typename T> T const U64PrimeRehashTable<T>::_ft[U64PrimeRehashTable<T>::_fts];

template <typename T> struct PrimeRehashTable {};
template <> struct PrimeRehashTable<U64> : U64PrimeRehashTable<U64> {};

template <Size = sizeof(Size)> class PrimeRehashPolicy {};
template <> class PrimeRehashPolicy<sizeof(U64)> : public RehashPolicy<U64, true>, private PrimeRehashTable<U64> {
public:
  CDS_ATTR(2(explicit, constexpr(11))) PrimeRehashPolicy(U64 lf = 1) noexcept : _lf(lf) {}
  CDS_ATTR(constexpr(11)) PrimeRehashPolicy(PrimeRehashPolicy const&) = default;

  CDS_ATTR(constexpr(14)) auto reset() noexcept -> void {
    _fi = 0;
  }

  CDS_ATTR(2(nodiscard, constexpr(17))) auto current() const noexcept -> U64 {
    return _ft[_fi];
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto load() const noexcept -> U64 {
    return _lf;
  }

  CDS_ATTR(2(nodiscard, constexpr(17))) auto balance(Size bCnt, Size eCnt, Size rCnt) noexcept -> BalanceResult {
    if (_fi + 1 == _fts) {
      return {_ft[_fi], BalanceType::Impossible};
    }

    auto const req = rCnt + eCnt;
    if (bCnt != 0) {
      auto const adj = bCnt * _lf;
      auto const mgf = 2u;
      if (adj >= req) {
        return {current(), BalanceType::Stable};
      }

      if (req <= adj * mgf) {
        return {_ft[++_fi], BalanceType::Required};
      }
    }

    while (_fi + 1 != _fts && req > _ft[_fi] * _lf) {
      ++_fi;
    }
    return {_ft[_fi], BalanceType::Required};
  }

private:
  U64 _lf;
  U64 _fi {0};
};
} // namespace prp

template <typename S = Size> class PrimeRehashPolicy : public prp::PrimeRehashPolicy<sizeof(S)> {
  using prp::PrimeRehashPolicy<sizeof(S)>::PrimeRehashPolicy;
};
} // namespace impl
} // namespace cds

#endif // CDS_POLICY_REHASH_POLICY_HPP
