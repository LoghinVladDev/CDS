/*
 * Created by loghin on 14/08/22.
 */

#ifndef __CDS_LINKED_HASH_MAP_CTAD_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_LINKED_HASH_MAP_CTAD_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

#if __CDS_cpplang_CTAD_available

namespace cds {

    template <
            typename __KeyType,                                                         /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __ValueType,                                                       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __Hasher = cds :: WrapperHasher < __KeyType, Hash < __KeyType > >  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    > LinkedHashMap (
            std :: initializer_list < cds :: __hidden :: __impl :: __MapEntry < __KeyType, __ValueType > >
    ) -> LinkedHashMap < __KeyType, __ValueType, __Hasher >;

    template <
            typename __KeyType,                                                         /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __ValueType,                                                       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __Hasher = cds :: WrapperHasher < __KeyType, Hash < __KeyType > >  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    > LinkedHashMap (
            __Hasher,
            std :: initializer_list < cds :: __hidden :: __impl :: __MapEntry < __KeyType, __ValueType > >
    ) -> LinkedHashMap < __KeyType, __ValueType, __Hasher >;

} /* namespace cds */

#endif

#endif /* __CDS_LINKED_HASH_MAP_CTAD_HPP__ */
