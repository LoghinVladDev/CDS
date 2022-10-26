/*
 * Created by loghin on 6/13/22.
 */

#ifndef __CDS_HASH_SET_CTAD_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_HASH_SET_CTAD_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

#if __CDS_cpplang_CTAD_available

namespace cds {

    template <
            typename __ElementType,                                                             /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __Hasher = cds :: WrapperHasher < __ElementType, Hash < __ElementType > >  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    > HashSet (
            std :: initializer_list < __ElementType >
    ) -> HashSet < __ElementType, __Hasher >;

    template <
            typename __ElementType,                                                             /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __Hasher = cds :: WrapperHasher < __ElementType, Hash < __ElementType > >  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    > HashSet (
            __Hasher,
            std :: initializer_list < __ElementType >
    ) -> HashSet < __ElementType, __Hasher >;

} /* namespace cds */

#endif

#endif /* __CDS_HASH_SET_CTAD_HPP__ */
