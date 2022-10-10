/*
 * Created by loghin on 14/08/22.
 */

#ifndef __CDS_LINKED_HASH_MAP_CTAD_HPP__
#define __CDS_LINKED_HASH_MAP_CTAD_HPP__ /* NOLINT(bugprone-reserved-identifier) */

#if __CDS_cpplang_CTAD_available

namespace cds {

    template <
            typename __KeyType,                                                         /* NOLINT(bugprone-reserved-identifier) */
            typename __ValueType,                                                       /* NOLINT(bugprone-reserved-identifier) */
            typename __Hasher = cds :: WrapperHasher < __KeyType, Hash < __KeyType > >  /* NOLINT(bugprone-reserved-identifier) */
    > LinkedHashMap (
            std :: initializer_list < cds :: __hidden :: __impl :: __MapEntry < __KeyType, __ValueType > >
    ) -> LinkedHashMap < __KeyType, __ValueType, __Hasher >;

    template <
            typename __KeyType,                                                         /* NOLINT(bugprone-reserved-identifier) */
            typename __ValueType,                                                       /* NOLINT(bugprone-reserved-identifier) */
            typename __Hasher = cds :: WrapperHasher < __KeyType, Hash < __KeyType > >  /* NOLINT(bugprone-reserved-identifier) */
    > LinkedHashMap (
            __Hasher,
            std :: initializer_list < cds :: __hidden :: __impl :: __MapEntry < __KeyType, __ValueType > >
    ) -> LinkedHashMap < __KeyType, __ValueType, __Hasher >;

}

#endif

#endif /* __CDS_LINKED_HASH_MAP_CTAD_HPP__ */
