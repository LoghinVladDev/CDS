//
// Created by loghin on 6/25/22.
//

#ifndef __CDS_LINKED_HASH_SET_CTAD_HPP__
#define __CDS_LINKED_HASH_SET_CTAD_HPP__

#if __CDS_cpplang_CTAD_available

namespace cds {

    template <
            typename __ElementType, // NOLINT(bugprone-reserved-identifier)
            typename __Hasher = cds :: FunctionHasher < __ElementType, & cds :: hash < __ElementType > > // NOLINT(bugprone-reserved-identifier)
    > LinkedHashSet (
            std :: initializer_list < __ElementType >
    ) -> LinkedHashSet < __ElementType, __Hasher >;

    template <
            typename __ElementType, // NOLINT(bugprone-reserved-identifier)
            typename __Hasher = cds :: FunctionHasher < __ElementType, & cds :: hash < __ElementType > > // NOLINT(bugprone-reserved-identifier)
    > LinkedHashSet (
            std :: initializer_list < __ElementType >,
            __Hasher
    ) -> LinkedHashSet < __ElementType, __Hasher >;

}

#endif

#endif // __CDS_LINKED_HASH_SET_CTAD_HPP__
