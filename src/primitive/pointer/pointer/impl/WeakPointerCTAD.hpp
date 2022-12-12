/* NOLINT(llvm-header-guard)
 * Created by loghin on 6/13/22.
 */

#ifndef __CDS_WEAK_POINTER_CTAD_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_WEAK_POINTER_CTAD_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

#if __CDS_cpplang_CTAD_available

namespace cds {

    template <
            typename __ElementType,                                                                         /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __Deleter      = __hidden :: __impl :: __DefaultSmartPointerDeleter < __ElementType >  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    > WeakPointer (
            SharedPointer < __ElementType, __Deleter > pointer
    ) -> WeakPointer < __ElementType, __Deleter >;


    template <
            typename __ElementType,                                                                             /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __Deleter      = __hidden :: __impl :: __DefaultSmartPointerDeleter < __ElementType [] >   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-avoid-c-arrays) */
    > WeakPointer (
            SharedPointer < __ElementType [], __Deleter > pointer                                               /* NOLINT(*-avoid-c-arrays) */
    ) -> WeakPointer < __ElementType [], __Deleter >;                                                           /* NOLINT(*-avoid-c-arrays) */

} /* namespace cds */

#endif

#endif /* __CDS_WEAK_POINTER_CTAD_HPP__ */
