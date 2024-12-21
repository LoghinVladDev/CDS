//
// Created by vloghin on 19.12.2024.
//

#ifndef CDS_THREADING_ATOMIC_ATOMIC_C11_HPP
#define CDS_THREADING_ATOMIC_ATOMIC_C11_HPP
#pragma once

#include <stdatomic.h>

namespace cds {
namespace impl {
enum class AtomicMemoryOrder {
  Relaxed = memory_order_relaxed,
  Consume = memory_order_consume,
  Acquire = memory_order_acquire,
  Release = memory_order_release,
  AcqRel = memory_order_acq_rel,
  SeqCst = memory_order_seq_cst,
  AcquireRelease = AcqRel,
  SequentiallyConsistent = SeqCst,
};
} // namespace impl
} // namespace cds

#endif // #ifndef CDS_THREADING_ATOMIC_ATOMIC_C11_HPP
