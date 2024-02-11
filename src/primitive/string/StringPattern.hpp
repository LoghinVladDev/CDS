//
// Created by loghin on 12/8/23.
//

#ifndef CDS_PRIMITIVE_STRING_PATTERN_HPP
#define CDS_PRIMITIVE_STRING_PATTERN_HPP
#pragma once

#include <cds/Utility>
#include <cds/functional/Hash>
#include <cds/meta/StdLib>
#include <cds/meta/StringTraits>
#include <cds/iterator/AddressIterator>
#include <cds/memory/Allocator>

#include "StringUtils.hpp"

#include "../../ds/hashTable/HashTableBase.hpp"
#include "../../policy/RehashPolicy.hpp"

#include <ostream>

namespace cds {
namespace impl {
using meta::EnableIf;
using meta::Not;
using meta::Decay;
using meta::All;
using meta::True;
using meta::False;
using meta::IsRef;
using meta::Nullptr;

using meta::lvalue;
using meta::rvalue;
using meta::inConstexpr;

template <typename> struct PatternUtils {};

template <typename C, Size s> struct ArrPatternUtils {
  template <typename T> CDS_ATTR(2(nodiscard, constexpr(11))) static auto length(T&&) noexcept -> Size {
    return s;
  }

  template <typename T> CDS_ATTR(2(nodiscard, constexpr(11))) static auto data(T&& data) noexcept -> C const* {
    return cds::forward<T>(data);
  }
};

template <typename C, Size s> struct PatternUtils<C(&)[s]> : ArrPatternUtils<C, s - 1> {};
template <typename C, Size s> struct PatternUtils<C const(&)[s]> : ArrPatternUtils<C, s - 1> {};

template <typename C> struct PtrPatternUtils {
  using Utils = StringUtils<C, StringTraits<C>>;

  CDS_ATTR(2(nodiscard, constexpr(14))) static auto length(C const* ptr) noexcept -> Size {
    return Utils::length(ptr);
  }

  CDS_ATTR(2(nodiscard, constexpr(14))) static auto data(C const* ptr) noexcept -> C const* {
    return ptr;
  }
};

template <typename C> struct PatternUtils<C*> : PtrPatternUtils<C> {};
template <typename C> struct PatternUtils<C*&> : PtrPatternUtils<C> {};
template <typename C> struct PatternUtils<C const*> : PtrPatternUtils<C> {};
template <typename C> struct PatternUtils<C const*&> : PtrPatternUtils<C> {};

template <typename C> struct BSVPatternUtils {
  template <typename T> CDS_ATTR(2(nodiscard, constexpr(11))) static auto length(T&& sv) noexcept -> Size {
    return cds::forward<T>(sv).length();
  }

  template <typename T> CDS_ATTR(2(nodiscard, constexpr(11))) static auto data(T&& sv) noexcept -> C const* {
    return cds::forward<T>(sv).data();
  }
};

template <typename C, typename U> struct PatternUtils<BaseStringView<C, U>> : BSVPatternUtils<C> {};
template <typename C, typename U> struct PatternUtils<BaseStringView<C, U>&> : BSVPatternUtils<C> {};
template <typename C, typename U> struct PatternUtils<BaseStringView<C, U> const> : BSVPatternUtils<C> {};
template <typename C, typename U> struct PatternUtils<BaseStringView<C, U> const&> : BSVPatternUtils<C> {};

template <typename T> constexpr auto allocate(std::size_t s) -> T* {
  return static_cast<T*>(::operator new(s));
}

template <typename S, typename A> class KMPBase : private A {
public:
  using Utils = PatternUtils<S>;

  template <typename FS, typename FA> CDS_ATTR(constexpr(20)) KMPBase(FS&& needle, FA&& alloc)
      CDS_ATTR(noexcept(noexcept(A(cds::forward<FA>(alloc)).allocate(0)))) :
      A{cds::forward<FA>(alloc)},
      _pat{cds::forward<FS>(needle)},
      _lps{A::allocate(len())} {
    construct(_lps, 0);
    Size idx = 1u;
    Size parseIdx = 0;
    auto const* pattern = Utils::data(cds::forward<FS>(needle));
    while (idx < len()) {
      if (pattern[idx] == pattern[parseIdx]) {
        construct(_lps + idx++, ++parseIdx);
      } else if (parseIdx > 0) {
        parseIdx = _lps[parseIdx - 1];
      } else {
        construct(_lps + idx++, 0);
      }
    }
  }

  template <typename Ref = IsRef<S>, EnableIf<Ref> = 0>
  CDS_ATTR(2(explicit, constexpr(14))) KMPBase(KMPBase&& pred) noexcept :
      A{cds::move(pred)}, _pat{pred._pat}, _lps{cds::exchange(pred._lps, nullptr)} {}

  template <typename Ref = IsRef<S>, EnableIf<Not<Ref>> = 0>
  CDS_ATTR(2(explicit, constexpr(14))) KMPBase(KMPBase&& pred)
      CDS_ATTR(noexcept(noexcept(S(cds::move(pred._pat))))) :
      A{cds::move(pred)}, _pat{cds::move(pred._pat)}, _lps{cds::exchange(pred._lps, nullptr)} {}

  KMPBase(KMPBase const&) noexcept = delete;
  auto operator=(KMPBase const&) noexcept -> KMPBase& = delete;
  auto operator=(KMPBase&&) noexcept -> KMPBase& = delete;

  CDS_ATTR(constexpr(20)) ~KMPBase() noexcept {
    destruct(_lps, _lps + len());
    A::deallocate(_lps, len());
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto len() const
      CDS_ATTR(noexcept(noexcept(Utils::length(value<S>())))) -> Size {
    return Utils::length(_pat);
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto data() const
      CDS_ATTR(noexcept(noexcept(Utils::data(value<S>())))) -> decltype(Utils::data(value<S>())) {
    return Utils::data(_pat);
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto lps() const noexcept -> Size const* {
    return _lps;
  }

private:
  S _pat;
  Size* _lps;
};

namespace ahoCorasick {
using meta::Int;
using meta::Eq;
using meta::EnableIf;
using functional::Hash;
using functional::Equal;
using impl::TableRehashPolicy;
using impl::FwdNode;
using cds::Allocator;
using cds::AllocatorSet;

template <typename T> struct AhoCorasickU8RehashTable {
  static Size const _fts = 7U;
  constexpr static T const _ft[_fts] = { 2U, 5U, 13U, 29U, 59U, 127U, 256U };
};

template <typename T> struct AhoCorasickU16RehashTable {
  static Size const _fts = 14U;
  constexpr static T const _ft[_fts] = {
      2U, 5U, 13U, 29U, 59U, 127U, 257U, 521U,
      1049U, 2099U, 4201U, 8419U, 16843U, 32768U
  };
};

template <typename T> struct AhoCorasickU32RehashTable {
  static Size const _fts = 31U;
  constexpr static T const _ft[_fts] = {
      2U, 5U, 13U, 29U, 59U, 127U, 257U, 521U, 1049U, 2099U,
      4201U, 8419U, 16843U, 33703U, 67409U, 134837U, 269683U,
      539389U, 1078787U, 2157587U, 4315183U, 8630387U,
      17260781U, 34521589U, 69043189U, 138086407U, 276172823U,
      552345671U, 1104691373U, 2209382761U, 4294967296ULL
  };
};

// ODR before cpp17
template <typename T> T const AhoCorasickU8RehashTable<T>::_ft[AhoCorasickU8RehashTable<T>::_fts];
template <typename T> T const AhoCorasickU16RehashTable<T>::_ft[AhoCorasickU16RehashTable<T>::_fts];
template <typename T> T const AhoCorasickU32RehashTable<T>::_ft[AhoCorasickU32RehashTable<T>::_fts];

template <typename T, Size = sizeof(T)> struct AhoCorasickRehashTable {};
template <typename T> struct AhoCorasickRehashTable<T, 1> : AhoCorasickU8RehashTable<U64> {};
template <typename T> struct AhoCorasickRehashTable<T, 2> : AhoCorasickU16RehashTable<U64> {};
template <typename T> struct AhoCorasickRehashTable<T, 4> : AhoCorasickU32RehashTable<U64> {};

template <typename T, Size = sizeof(T)> struct Link {};
template <typename T> struct Link<T, 1> {
  U64 id: 56;
  T key;

  CDS_ATTR(constexpr(11)) Link(U64 i, T k) noexcept : id(i), key(k) {}
};

template <typename T> struct Link<T, 2> {
  U64 id: 48;
  T key;

  CDS_ATTR(constexpr(11)) Link(U64 i, T k) noexcept : id(i), key(k) {}
};

template <typename T> struct Link<T, 4> {
  U64 id : 32;
  T key;

  CDS_ATTR(constexpr(11)) Link(U64 i, T k) noexcept : id(i), key(k) {}
};

struct LinkKeyProjection {
  template <typename T> CDS_ATTR(2(nodiscard, constexpr(11))) auto operator()(Link<T> const& link) const noexcept -> T {
    return link.key;
  }
};

template <typename T, Size = sizeof(T)> struct LinkLeafId {};

struct SplitWordIdLinkLeafId {
  U64 endWordLink : 48;
  U16 lWordId : 16;
  U64 suffixLink : 48;
  U16 hWordId : 15;
  U8 leaf : 1;

  CDS_ATTR(constexpr(11)) SplitWordIdLinkLeafId() noexcept :
      endWordLink(0), lWordId(0), suffixLink(0), hWordId(0), leaf(0) {}

  CDS_ATTR(constexpr(14)) auto setId(U32 id) noexcept -> void {
    lWordId = id & 0xffffU;
    hWordId = id >> 16;
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto id() const noexcept -> U32 {
    return static_cast<U32>(hWordId) << 16 | static_cast<U32>(lWordId);
  }
};

template <typename T> struct LinkLeafId<T, 1> : SplitWordIdLinkLeafId {};
template <typename T> struct LinkLeafId<T, 2> : SplitWordIdLinkLeafId {};
template <typename T> struct LinkLeafId<T, 4> {
  U32 endWordLink : 32;
  U32 suffixLink : 32;
  U32 wordId : 31;
  U8 leaf : 1;

  CDS_ATTR(constexpr(11)) LinkLeafId() noexcept :
      endWordLink(0), suffixLink(0), wordId(0), leaf(0) {}

  CDS_ATTR(constexpr(14)) auto setId(U32 id) noexcept -> void {
    wordId = id;
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto id() const noexcept -> U32 {
    return wordId;
  }
};

template <
    typename C,
    typename AS /* = AllocatorSet<Allocator<FwdNode<L>>, Allocator<FwdNode<L>*>> */,
    typename L = Link<C const>,
    typename T = AhoCorasickRehashTable<C>
> struct Vertex : LinkLeafId<C> {
  class Children : public HashTableBase<L, C const, Hash<>, TableRehashPolicy<T>, LinkKeyProjection, Equal<>, AS> {
  public:
    using HashTableBase<L, C const, Hash<>, TableRehashPolicy<T>, LinkKeyProjection, Equal<>, AS>::HashTableBase;
    using Base = HashTableBase<L, C const, Hash<>, TableRehashPolicy<T>, LinkKeyProjection, Equal<>, AS>;
    using Base::get;
    using Base::at;
  };

  Children children;
  Link<C> parent {0, 0};
};

template <
    typename C,
    typename AS /* = AllocatorSet<Allocator<FwdNode<Size>>, Allocator<int>, Allocator<Vertex<C, ?>>, ...[[Vertex<> required allocators]]> */
> class AhoCorasick : private AS {
public:
  using V = Vertex<C, AS>;

  template <typename I> CDS_ATTR(2(explicit, constexpr(20)))
  AhoCorasick(I&& stringSet, Size startingSize = 16) noexcept(false) :
      _vertices(AS::template get<V>().allocate(startingSize)),
      _lengths(AS::template get<int>().allocate(cds::forward<I>(stringSet).size())),
      _lSize(cds::forward<I>(stringSet).size()),
      _cap(startingSize) {
    construct(&_vertices[0]);

    U32 wId = 0;
    auto v = _r;
    for (auto&& str : cds::forward<I>(stringSet)) {
      using U = PatternUtils<RemoveCVRef<decltype(str)>>;
      for (auto c : str) {
        auto r = _vertices[v].children.get(c);
        if (!r.alive) {
          auto& nv = newVertex();
          // nv.suffixLink = -1; probably not needed
          nv.parent.id = v;
          nv.parent.key = c;
          construct(r.data, _size - 1, c);
        }
        v = r.data->id;
      }
      _vertices[v].leaf = 1;
      _vertices[v].setId(wId);
      construct(_lengths + wId++, U::length(str));
    }

    traverse();
  }

  ~AhoCorasick() noexcept {
    destruct(_vertices, _vertices + _size);
    destruct(_lengths, _lengths + _lSize);
    AS::template get<V>().deallocate(_vertices, _cap);
    AS::template get<int>().deallocate(_lengths, _lSize);
  }

private:
  CDS_ATTR(constexpr(20)) auto traverse() noexcept(false) -> void {
    // replace with SLL
    using N = FwdNode<Size>;
    N* h = nullptr;
    N* b = nullptr;
    auto& a = AS::template get<FwdNode<Size>>();
    auto push = [&h, &b, &a](Size v) {
      auto* n = a.allocate(1);
      construct(n, nullptr, v);
      if (!b) {
        h = n;
        b = n;
      } else {
        b->next = n;
      }
    };

    auto pop = [&b, &h, &a]() {
      auto v = h->data;
      auto* c = h;
      h = h->next;
      destruct(c);
      a.deallocate(c, 1);
      if (h == nullptr) {
        b = nullptr;
      }
      return v;
    };

    auto empty = [&h]() {
      return h == nullptr;
    };

    push(_r);
    while(!empty()) {
      auto v = pop();
      computeLink(v);
      for (auto it = begin(_vertices[v].children), e = end(_vertices[v].children); it != e; ++it) {
        push(it->id);
      }
    }
  }

  CDS_ATTR(constexpr(20)) auto computeLink(Size v) noexcept(false) -> void {
    if (v == _r) {
      _vertices[v].suffixLink = _r;
      _vertices[v].endWordLink = _r;
      return;
    }

    if (_vertices[v].parent.id == _r) {
      _vertices[v].suffixLink = _r;
      if (_vertices[v].leaf) {
        _vertices[v].endWordLink = v;
      } else {
        _vertices[v].endWordLink = _vertices[_vertices[v].suffixLink].endWordLink;
      }
      return;
    }

    auto cbv = _vertices[_vertices[v].parent.id].suffixLink;
    auto c = _vertices[v].parent.key;

    while(true) {
      auto const link = _vertices[cbv].children.at(c);
      if (link) {
        _vertices[v].suffixLink = link->id;
        break;
      }
      if (cbv == _r) {
        _vertices[v].suffixLink = _r;
        break;
      }
      cbv = _vertices[cbv].suffixLink;
    }

    if (_vertices[v].leaf) {
      _vertices[v].endWordLink = v;
    } else {
      _vertices[v].endWordLink = _vertices[_vertices[v].suffixLink].endWordLink;
    }
  }

  CDS_ATTR(2(nodiscard, constexpr(20))) auto newVertex() noexcept(false) -> V& {
    if (_size == _cap) {
      auto nc = _cap * 2;
      auto* nb = AS::template get<V>().allocate(nc);
      moveInitialize(_vertices, _vertices + _cap, nb);
      destruct(_vertices, _vertices + _cap);
      AS::template get<V>().deallocate(cds::exchange(_vertices, nb), cds::exchange(_cap, nc));
    }

    return *construct(_vertices + _size++);
  }

  V* _vertices;
  int* _lengths;
  Size _lSize;
  Size _cap;
  Size _size {1};
  Size _r {0};
};
} // namespace ahoCorasick
} // namespace impl
} // namespace cds

#endif // CDS_PRIMITIVE_STRING_PATTERN_HPP
