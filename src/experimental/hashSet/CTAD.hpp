//
// Created by loghin on 6/13/22.
//

#ifndef __CDS_EX_HASH_SET_CTAD_HPP__
#define __CDS_EX_HASH_SET_CTAD_HPP__

#if __CDS_cpplang_CTAD_available

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {

        template <
                typename __ElementType, // NOLINT(bugprone-reserved-identifier)
                typename __HashCalculator = cds :: utility :: LowCollisionDefaultHashFunction < __ElementType > // NOLINT(bugprone-reserved-identifier)
        > HashSet (
                std :: initializer_list < __ElementType >
        ) -> HashSet < __ElementType, __HashCalculator >;

    }
}

#endif

#endif // __CDS_EX_HASH_SET_CTAD_HPP__
