//
// Created by loghin on 6/13/22.
//

#ifndef __CDS_HASH_SET_CTAD_HPP__
#define __CDS_HASH_SET_CTAD_HPP__

#if __CDS_cpplang_CTAD_available

namespace cds {

    template <
            typename __ElementType, // NOLINT(bugprone-reserved-identifier)
            typename __Hasher = cds :: FunctionHasher < __ElementType, & cds :: hash < __ElementType > > // NOLINT(bugprone-reserved-identifier)
    > HashSet (
            std :: initializer_list < __ElementType >
    ) -> HashSet < __ElementType, __Hasher >;

    template <
            typename __ElementType, // NOLINT(bugprone-reserved-identifier)
            typename __Hasher = cds :: FunctionHasher < __ElementType, & cds :: hash < __ElementType > > // NOLINT(bugprone-reserved-identifier)
    > HashSet (
            std :: initializer_list < __ElementType >,
            __Hasher
    ) -> HashSet < __ElementType, __Hasher >;

}

#endif

#endif // __CDS_HASH_SET_CTAD_HPP__
