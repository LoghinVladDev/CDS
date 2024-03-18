//
// Created by loghin on 12/8/23.
//

#ifndef CDS_PRIMITIVE_STRING_PATTERN_HPP
#define CDS_PRIMITIVE_STRING_PATTERN_HPP
#pragma once

#include <cds/functional/Hash>
#include <cds/meta/StdLib>
#include <cds/iterator/AddressIterator>
#include <cds/memory/Allocator>

#include "StringAbstract.hpp"

#include "../../ds/hashTable/HashTableBase.hpp"
#include "../../ds/linkedList/SingleLinkedListBase.hpp"
#include "../../policy/RehashPolicy.hpp"

#if CDS_ATTR(msvc)
#pragma warning(disable: 4244)
#endif

namespace cds {
namespace impl {
using meta::EnableIf;
using meta::Not;
using meta::All;
using meta::IsRef;

using meta::value;

template <typename S, typename A> class KMPBase : private A {
public:
  using Utils = StringAbstract<S>;

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

  CDS_ATTR(2(nodiscard, constexpr(11))) auto isEnd(Size idx) const noexcept -> bool {
    return idx == len();
  }

private:
  S _pat;
  Size* _lps;
};

namespace ahoCorasick {
using meta::Eq;
using meta::EnableIf;
using meta::IsSame;

using functional::Hash;
using functional::Equal;

using impl::TableRehashPolicy;
using impl::FwdNode;

using cds::Allocator;
using cds::AllocatorSet;

template <typename T> struct AhoCorasickU8RehashTable {
  static Size constexpr _fts = 7U;
  static T constexpr _ft[_fts] = { 2U, 5U, 13U, 29U, 59U, 127U, 256U };
};

template <typename T> struct AhoCorasickU16RehashTable {
  static Size constexpr _fts = 14U;
  static T constexpr _ft[_fts] = {
      2U, 5U, 13U, 29U, 59U, 127U, 257U, 521U,
      1049U, 2099U, 4201U, 8419U, 16843U, 32768U
  };
};

template <typename T> struct AhoCorasickU32RehashTable {
  static Size constexpr _fts = 31U;
  static T constexpr _ft[_fts] = {
      2U, 5U, 13U, 29U, 59U, 127U, 257U, 521U, 1049U, 2099U,
      4201U, 8419U, 16843U, 33703U, 67409U, 134837U, 269683U,
      539389U, 1078787U, 2157587U, 4315183U, 8630387U,
      17260781U, 34521589U, 69043189U, 138086407U, 276172823U,
      552345671U, 1104691373U, 2209382761U, 4294967296ULL
  };
};

// ODR before cpp17
template <typename T> T const AhoCorasickU8RehashTable<T>::_ft[_fts];
template <typename T> T const AhoCorasickU16RehashTable<T>::_ft[_fts];
template <typename T> T const AhoCorasickU32RehashTable<T>::_ft[_fts];

template <typename T, Size = sizeof(T)> struct AhoCorasickRehashTable {};
template <typename T> struct AhoCorasickRehashTable<T, 1> : AhoCorasickU8RehashTable<U64> {};
template <typename T> struct AhoCorasickRehashTable<T, 2> : AhoCorasickU16RehashTable<U64> {};
template <typename T> struct AhoCorasickRehashTable<T, 4> : AhoCorasickU32RehashTable<U64> {};

template <typename T, Size = sizeof(T)> struct Link {};
template <typename T> struct Link<T, 1> {
  U64 id: 56;
  T key;

  CDS_ATTR(constexpr(11)) Link(T k, U64 const i) noexcept : id(i), key(k) {}
};

template <typename T> struct Link<T, 2> {
  U64 id: 48;
  T key;

  CDS_ATTR(constexpr(11)) Link(T k, U64 const i) noexcept : id(i), key(k) {}
};

template <typename T> struct Link<T, 4> {
  U64 id : 32;
  T key;

  CDS_ATTR(constexpr(11)) Link(T k, U64 const i) noexcept : id(i), key(k) {}
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

  CDS_ATTR(constexpr(14)) auto setId(U32 const id) noexcept -> void {
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

  CDS_ATTR(constexpr(14)) auto setId(U32 const id) noexcept -> void {
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
    using Base::tryEmplace;
    using Base::at;
  };

  using ParentLink = Link<C>;

  Children children;
  Link<C> parent;

  CDS_ATTR(2(explicit, constexpr(11))) Vertex(Link<C> parentLink, AS const& allocatorSet) noexcept :
      parent{parentLink}, children{allocatorSet} {}
};

enum class PredResultKind : U8 { PRK_feed, PRK_accept };
struct PredResult {
  PredResultKind kind;
  int reverseLen;
  Size state;
};

template <
    typename C,
    typename AS /* = AllocatorSet<Allocator<FwdNode<Size>>, Allocator<int>, Allocator<Vertex<C, ?>>, ...[[Vertex<> required allocators]]> */
> class AhoCorasick : private AS {
public:
  using V = Vertex<C, AS>;
  using ParentLink = typename V::ParentLink;

  template <typename I, typename FAS, EnableIf<Not<IsSame<RemoveCVRef<I>, AhoCorasick>>> = 0>
  CDS_ATTR(2(explicit, constexpr(20)))
  AhoCorasick(I&& stringSet, Size startingSize = 16, FAS&& alloc = FAS()) noexcept(false) :
      AS(cds::forward<FAS>(alloc)),
      _vertices(AS::template get<V>().allocate(startingSize)),
      _lengths(AS::template get<int>().allocate(cds::forward<I>(stringSet).size())),
      _lSize(cds::forward<I>(stringSet).size()),
      _cap(startingSize) {
    construct(&_vertices[0], ParentLink{0, 0}, static_cast<AS const&>(*this));

    U32 wId = 0;
    for (auto i = cds::begin(cds::forward<I>(stringSet)), e = cds::end(cds::forward<I>(stringSet)); i != e; ++i) {
      auto vId = _r;
      auto* v = _vertices + vId;
      auto const& str = *i;
      using U = StringAbstract<RemoveCVRef<decltype(str)>>;
      for (Size idx = 0, len = U::length(str); idx < len; ++idx) {
        auto const* pat = U::data(str);
        auto r = v->children.tryEmplace(pat[idx], _size);
        if (get<0>(r)) {
          addVertex(ParentLink(pat[idx], vId));
        }
        vId = get<1>(r)->id;
        v = _vertices + vId;
      }
      v->setId(wId);
      v->leaf = 1;
      construct(_lengths + wId++, U::length(str));
    }
    traverse();
  }

  CDS_ATTR(constexpr(14)) AhoCorasick(AhoCorasick&& aho) noexcept :
      AS(cds::move(aho)),
      _vertices(cds::exchange(aho._vertices, nullptr)),
      _lengths(cds::exchange(aho._lengths, nullptr)),
      _lSize(cds::exchange(aho._lSize, 0)),
      _cap(cds::exchange(aho._cap, 0)),
      _size(cds::exchange(aho._size, 0)),
      _r(cds::exchange(aho._r, 0)) {}

  AhoCorasick(AhoCorasick const&) = delete;
  auto operator=(AhoCorasick const&) -> AhoCorasick& = delete;
  auto operator=(AhoCorasick&&) -> AhoCorasick& = delete;

  CDS_ATTR(constexpr(20)) ~AhoCorasick() noexcept {
    destruct(_vertices, _vertices + _size);
    destruct(_lengths, _lengths + _lSize);
    AS::template get<V>().deallocate(_vertices, _cap);
    AS::template get<int>().deallocate(_lengths, _lSize);
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto initState() const noexcept -> Size {
    return _r;
  }

  CDS_ATTR(2(nodiscard, constexpr(14))) auto operator()(C c, Size state) const noexcept -> PredResult {
    while (true) {
      auto e = _vertices[state].children.at(c);
      if (e) {
        state = e->id;
        break;
      }
      if (state == _r) {
        break;
      }
      state = _vertices[state].suffixLink;
    }

    if (_vertices[state].endWordLink == _r) {
      return {PredResultKind::PRK_feed, 0, state};
    }

    return {PredResultKind::PRK_accept, _lengths[_vertices[_vertices[state].endWordLink].id()], state};
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto isEnd(Size idx) const noexcept -> bool {
    return _vertices[idx].endWordLink != _r;
  }

private:
  CDS_ATTR(constexpr(20)) auto traverse() noexcept(false) -> void {
    auto& alloc = AS::template get<FwdNode<Size>>();
    using QueueAllocator = RemoveCVRef<decltype(alloc)>;
    class TraversalQueue : public SingleLinkedListBase<Size, Equal<>, QueueAllocator> {
    public:
      using Base = SingleLinkedListBase<Size, Equal<>, QueueAllocator>;
      using SingleLinkedListBase<Size, Equal<>, QueueAllocator>::SingleLinkedListBase;
      using Base::front;
    };

    TraversalQueue queue{alloc};
    queue.emplaceBack(_r);
    while(!queue.empty()) {
      auto v = *queue.front();
      queue.pop();
      computeLink(v);
      for (auto it = begin(_vertices[v].children), e = end(_vertices[v].children); it != e; ++it) {
        queue.emplaceBack(static_cast<Size>(it->id));
      }
    }
  }

  CDS_ATTR(constexpr(14)) auto computeLink(Size vId) noexcept(false) -> void {
    auto* const v = _vertices + vId;
    if (vId == _r) {
      v->suffixLink = _r;
      v->endWordLink = _r;
      return;
    }

    if (v->parent.id == _r) {
      v->suffixLink = _r;
      if (v->leaf) {
        v->endWordLink = vId;
      } else {
        v->endWordLink = _vertices[v->suffixLink].endWordLink;
      }
      return;
    }

    auto cbvId = _vertices[v->parent.id].suffixLink;
    auto c = v->parent.key;

    while(true) {
      auto* const cbv = _vertices + cbvId;
      auto const link = cbv->children.at(c);
      if (link) {
        v->suffixLink = link->id;
        break;
      }
      if (cbvId == _r) {
        v->suffixLink = _r;
        break;
      }
      cbvId = cbv->suffixLink;
    }

    if (v->leaf) {
      v->endWordLink = vId;
    } else {
      v->endWordLink = _vertices[v->suffixLink].endWordLink;
    }
  }

  CDS_ATTR(constexpr(20)) auto addVertex(ParentLink link) noexcept(false) -> void {
    if (_size == _cap) {
      auto nc = _cap * 2;
      auto* nb = AS::template get<V>().allocate(nc);
      moveInitialize(_vertices, _vertices + _cap, nb);
      destruct(_vertices, _vertices + _cap);
      AS::template get<V>().deallocate(
          cds::exchange(_vertices, nb),
          cds::exchange(_cap, nc)
      );
    }

    construct(_vertices + _size++, link, static_cast<AS const&>(*this));
  }

  V* _vertices;
  int* _lengths;
  Size _lSize;
  Size _cap;
  Size _size {1};
  Size _r {0};
};
} // namespace ahoCorasick

namespace matchKind {
struct ByCharacter {};
struct ByErrorIndex {};
struct ByState {};
}

template <typename P, typename = typename P::MatchKind> struct StateContainer {
  CDS_ATTR(2(explicit, constexpr(11))) StateContainer(CDS_ATTR(unused) P const&) noexcept {}
};

template <typename P> struct StateContainer<P, matchKind::ByState> {
  CDS_ATTR(2(explicit, constexpr(11))) StateContainer(P const& sm) noexcept : state(sm.initState()) {}
  Size state;
};
} // namespace impl
} // namespace cds

#if CDS_ATTR(msvc)
#pragma warning(default: 4244)
#endif

#endif // CDS_PRIMITIVE_STRING_PATTERN_HPP
