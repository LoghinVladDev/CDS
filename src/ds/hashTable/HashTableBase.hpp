//
// Created by loghin on 2/7/24.
//

#ifndef CDS_DS_HASH_TABLE_BASE_HPP
#define CDS_DS_HASH_TABLE_BASE_HPP
#pragma once

#include <cds/meta/StdLib>
#include <cds/meta/Semantics>
#include <cds/memory/ByteStorage>
#include <cds/functional/FunctionalInterface>
#include <cds/iterator/HashTableIterator>
#include <cds/Utility>

#include "../node/FwdNode.hpp"

#include <cassert>

namespace cds {
namespace impl {
using meta::RemoveConst;

using meta::rvalue;
using meta::inConstexpr;

template <typename T, typename K, typename H, typename RP, typename KP, typename KC, typename AS>
class CDS_ATTR(inheritsEBOs) HashTableBase : private H, private RP, private AS {
private:
  using Node = FwdNode<T>;

public:
  using Type = T;
  using Key = K;
  using Hasher = H;
  using RehashPolicy = RP;
  using AllocSet = AS;

  using Iterator = iterator::HashTableIterator<T>;
  using ConstIterator = iterator::HashTableIterator<T const>;

  struct UninitializedGetResult {
    Type* data;
    bool alive;
  };

  CDS_ATTR(2(explicit, constexpr(11))) HashTableBase(AllocSet const& alloc = AllocSet())
      CDS_ATTR(noexcept(noexcept(HashTableBase(H(), RP(), alloc)))) : HashTableBase(H(), RP(), alloc) {}

  CDS_ATTR(2(explicit, constexpr(11))) HashTableBase(Hasher const& hasher, AllocSet const& alloc = AllocSet())
      CDS_ATTR(noexcept(noexcept(HashTableBase(hasher, RP(), alloc)))) : HashTableBase(hasher, RP(), alloc) {}

  CDS_ATTR(constexpr(11)) HashTableBase(
      Hasher const& hasher, RehashPolicy const& rehashPolicy, AllocSet const& alloc = AllocSet()
  ) CDS_ATTR(noexcept(noexcept(H(hasher)) && noexcept(RP(rehashPolicy)) && noexcept(AS(alloc)))) :
      H{hasher}, RP{rehashPolicy}, AS{alloc} {}

  CDS_ATTR(2(implicit, constexpr(20)))
  HashTableBase(HashTableBase const& table)
      CDS_ATTR(noexcept(noexcept(copyOnceClean(table)))) {
    copyOnceClean(table);
  }

  CDS_ATTR(constexpr(14)) HashTableBase(HashTableBase&& table) noexcept :
      H(cds::move(table)), RP(cds::move(table)), AS(cds::move(table)),
      _bCnt(cds::exchange(table._bCnt, 0)), _eCnt(cds::exchange(table._eCnt, 0)),
      _bArr(cds::exchange(table._bArr, nullptr)) {}

  CDS_ATTR(constexpr(20)) ~HashTableBase() noexcept {
    clear();
  }

protected:
  CDS_ATTR(nodiscard) auto get(K const& key) CDS_ATTR(noexcept(noexcept(
      noexcept(rvalue<KC>()(rvalue<KP>()(rvalue<Node>().data), key))
      && noexcept(alloc())
      && noexcept(alloc(0))
      && noexcept(rvalue<H>()(key))
  ))) -> UninitializedGetResult {
    KC const comp;
    KP const proj;
    if (!_bArr) {
      alloc(RP::current());
    }

    auto hash = (*this)(key);
    auto*& buck = bucket(hash);
    auto head = buck;
    auto size = 0;

    while (head) {
      if (comp(proj(head->data), key)) {
        return {&head->data, true};
      }
      head = head->next;
      ++size;
    }

    head = alloc();
    head->next = buck;
    buck = head;
    ++_eCnt;

    if (size >= RP::load()) {
      auto const rh = RP::balance(_bCnt, _eCnt, 1);
      if (rh.type == RP::BalanceType::Required) {
        rehash(rh.size, hash, head);
      }
    }

    return {&head->data, false};
  }

  CDS_ATTR(2(nodiscard, constexpr(14))) auto get(K const& key) const CDS_ATTR(noexcept(
      noexcept(rvalue<KC>()(rvalue<KP>()(rvalue<Node>().data), key))
      && noexcept(rvalue<H>()(key))
  )) -> Type const* {
    KC const comp;
    KP const proj;
    if (empty()) {
      return nullptr;
    }

    auto head = bucket((*this)(key));
    while (head) {
      if (comp(proj(head->data), key)) {
        return &head->data;
      }
      head = head->next;
    }

    return nullptr;
  }

  CDS_ATTR(2(nodiscard, constexpr(14))) auto at(K const& key) CDS_ATTR(noexcept(
      noexcept(rvalue<KC>()(rvalue<KP>()(rvalue<Node>().data), key))
      && noexcept(rvalue<H>()(key))
  )) -> Type* {
    KC const comp;
    KP const proj;
    if (empty()) {
      return nullptr;
    }

    auto head = bucket((*this)(key));
    while (head) {
      if (comp(proj(head->data), key)) {
        return &head->data;
      }
      head = head->next;
    }

    return nullptr;
  }

  CDS_ATTR(2(nodiscard, constexpr(14))) auto at(K const& key) const CDS_ATTR(noexcept(
      noexcept(rvalue<KC>()(rvalue<KP>()(rvalue<Node>().data), key))
      && noexcept(rvalue<H>()(key))
  )) -> Type const* {
    KC const comp;
    KP const proj;
    if (empty()) {
      return nullptr;
    }

    auto head = bucket((*this)(key));
    while (head) {
      if (comp(proj(head->data), key)) {
        return &head->data;
      }
      head = head->next;
    }

    return nullptr;
  }

  CDS_ATTR(constexpr(20)) auto copy(HashTableBase const& table)
      CDS_ATTR(noexcept(noexcept(copyOnceClean(table)))) -> void {
    if (this == &table) {
      return;
    }

    clear();
    copyOnceClean(table);
  }

  CDS_ATTR(constexpr(20)) auto copyOnceClean(HashTableBase const& table) CDS_ATTR(noexcept(
      noexcept(alloc(0))
       && noexcept(construct(alloc(), nullptr, rvalue<Node>().data))
  )) -> void {
    if (table.empty()) {
      return;
    }

    _eCnt = table._eCnt;
    alloc(table._bCnt);
    for (decltype(_bCnt) idx = 0; idx < table._bCnt; ++idx) {
      auto*& lb = bucket(idx);
      auto* rb = table.bucket(idx);

      auto* rh = rb;
      Node* le = nullptr;
      while(rh) {
        auto node = construct(alloc(), nullptr, rh->data);
        rh = rh->next;
        if (!le) {
          lb = node;
        } else {
          le->next = node;
        }
        le = node;
      }
    }

    RP::operator=(table);
  }

  CDS_ATTR(constexpr(20)) auto move(HashTableBase&& table) noexcept -> void {
    if (this == &table) {
      return;
    }

    clear();
    moveOnceClean(cds::move(table));
  }

  CDS_ATTR(constexpr(14)) auto moveOnceClean(HashTableBase&& table) noexcept -> void {
    _bArr = cds::exchange(table._bArr, nullptr);
    _bCnt = cds::exchange(table._bCnt, 0);
    _eCnt = cds::exchange(table._eCnt, 0);
    H::operator=(cds::move(table));
    RP::operator=(cds::move(table));
    AS::operator=(cds::move(table));
  }

public:
  template <typename KF, typename... A> CDS_ATTR(constexpr(20)) auto tryEmplace(KF&& key, A&&... args)
      CDS_ATTR(noexcept(
          noexcept(construct(alloc(), nullptr, cds::forward<KF>(key), cds::forward<A>(args)...))
          && noexcept(rvalue<KC>()(rvalue<KP>()(rvalue<Node>().data), cds::forward<KF>(key)))
          && noexcept(alloc(0))
          && noexcept(rvalue<H>()(cds::forward<KF>(key)))
              )) -> T& {
    KC const comp;
    KP const proj;
    if (!_bArr) {
      alloc(RP::current());
    }

    auto hash = (*this)(cds::forward<KF>(key));
    auto*& buck = bucket(hash);
    auto head = buck;
    auto size = 0;
    while (head) {
      if (comp(proj(head->data), cds::forward<KF>(key))) {
        return head->data;
      }
      head = head->next;
      ++size;
    }

    head = construct(alloc(), buck, cds::forward<KF>(key), cds::forward<A>(args)...);
    buck = head;
    ++_eCnt;

    if (size >= RP::load()) {
      auto const rh = RP::balance(_bCnt, _eCnt, 1);
      if (rh.type == RP::BalanceType::Required) {
        rehash(rh.size, hash, head);
      }
    }

    return head->data;
  }

  CDS_ATTR(constexpr(20)) auto clear() noexcept -> void {
    if (!_bArr) {
      return;
    }

    for(decltype(_bCnt) bIdx = 0; bIdx < _bCnt; ++bIdx) {
      auto*& head = _bArr[bIdx];
      while (head != nullptr) {
        auto copy = head;
        head = head->next;
        free(copy);
      }
    }

    RP::reset();
    free();
    _eCnt = 0;
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto size() const noexcept -> Size {
    return _eCnt;
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto empty() const noexcept -> bool {
    return size() == 0;
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto bucketCount() const noexcept -> Size {
    return _bCnt;
  }

  CDS_ATTR(2(nodiscard, constexpr(14))) auto begin() noexcept -> Iterator {
    return Iterator{_bArr, _bCnt};
  }

  CDS_ATTR(2(nodiscard, constexpr(14))) auto end() noexcept -> Iterator {
    return Iterator{nullptr, 0};
  }

  CDS_ATTR(2(nodiscard, constexpr(14))) auto begin() const noexcept -> ConstIterator {
    return ConstIterator{_bArr, _bCnt};
  }

  CDS_ATTR(2(nodiscard, constexpr(14))) auto end() const noexcept -> ConstIterator {
    return ConstIterator{nullptr, 0};
  }

  CDS_ATTR(2(nodiscard, constexpr(14))) auto cbegin() const noexcept -> ConstIterator {
    return ConstIterator{_bArr, _bCnt};
  }

  CDS_ATTR(2(nodiscard, constexpr(14))) auto cend() const noexcept -> ConstIterator {
    return ConstIterator{nullptr, 0};
  }

private:
  CDS_ATTR(constexpr(20)) auto rehash(Size bCnt, Size hashNN, Node const* NN) CDS_ATTR(noexcept(
    noexcept(alloc(bCnt)) && noexcept(rvalue<H>()(rvalue<KP>()(rvalue<T>())))
  )) -> void {
    KP const proj;
    auto const oBCnt = _bCnt;
    alloc(bCnt);

    for (decltype(_bCnt) idx = 0; idx < oBCnt; ++idx) {
      auto*& ob = bucket(idx);
      while (ob) {
        auto const hash = NN == ob ? hashNN : (*this)(proj(ob->data));
        auto& nb = bucket(hash);
        if (nb == ob) {
          break;
        }

        auto* mb = ob;
        ob = ob->next;
        rehashEmplace(nb, mb);
      }

      auto* obh = ob;
      while (obh && obh->next) {
        auto const hash = NN == obh->next ? hashNN : (*this)(proj(obh->next->data));
        auto& nb = bucket(hash);
        if (nb == ob) {
          obh = obh->next;
          continue;
        }

        auto* mb = obh->next;
        obh->next = obh->next->next;
        rehashEmplace(nb, mb);
      }
    }
  }

  CDS_ATTR(constexpr(14)) static auto rehashEmplace(Node*& into, Node* node) noexcept -> void {
    node->next = into;
    into = node;
  }

  CDS_ATTR(2(nodiscard, constexpr(14))) auto bucket(Size hash) noexcept -> Node*& {
    return _bArr[hash % _bCnt];
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto bucket(Size hash) const noexcept -> Node const* {
    return _bArr[hash % _bCnt];
  }

  CDS_ATTR(constexpr(20)) auto alloc(Size bCnt)
      CDS_ATTR(noexcept(noexcept(rvalue<AS>().template get<Node*>().allocate(0)))) -> void {
    assert(bCnt > _bCnt && "Invalid bucket allocation, expected new size to be greater");
    auto& alloc = AS::template get<Node*>();
    auto* nb = alloc.allocate(bCnt);
    fillInitialize(copyInitialize(_bArr, _bArr + _bCnt, nb), nb + bCnt, nullptr);
#if CDS_ATTR(cpp20)
    if (inConstexpr()) {
      if (_bArr) {
        alloc.deallocate(cds::exchange(_bArr, nb), cds::exchange(_bCnt, bCnt));
        return;
      }
      _bArr = nb;
      _bCnt = bCnt;
      return;
    }
#endif // #if CDS_ATTR(cpp20)
    alloc.deallocate(cds::exchange(_bArr, nb), cds::exchange(_bCnt, bCnt));
  }

  CDS_ATTR(constexpr(20)) auto alloc()
      CDS_ATTR(noexcept(noexcept(rvalue<AS>().template get<Node*>().allocate(0)))) -> Node* {
    return AS::template get<Node>().allocate(1);
  }

  CDS_ATTR(constexpr(20)) auto free() noexcept -> void {
    destruct(_bArr, _bArr + _bCnt);
    AS::template get<Node*>().deallocate(_bArr, _bCnt);
  }

  CDS_ATTR(constexpr(20)) auto free(Node* node) noexcept -> void {
    destruct(node);
    AS::template get<Node>().deallocate(node, 1);
  }

  Size _bCnt {0u};
  Size _eCnt {0u};
  Node** _bArr {nullptr};
};
} // namespace impl
} // namespace cds

#endif // CDS_DS_HASH_TABLE_BASE_HPP
