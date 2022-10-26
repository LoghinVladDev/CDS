/*
 * Created by loghin on 23/10/22.
 */

#ifndef __CDS_LOCK_CTAD_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_LOCK_CTAD_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

namespace cds {

#if defined(__CDS_MUTEX_HPP__)

    Lock ( Mutex & ) -> Lock < Mutex >;
    DeferredLock ( Mutex & ) -> DeferredLock < Mutex >;

#endif

} /* namespace cds */

#endif /* __CDS_LOCK_CTAD_HPP__ */
