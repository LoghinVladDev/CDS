//
// Created by loghin on 6/13/22.
//

#ifndef __CDS_EX_HASH_MAP_CTAD_HPP__
#define __CDS_EX_HASH_MAP_CTAD_HPP__

#if __CDS_cpplang_CTAD_available

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {

        template <
                typename __KeyType,                                                             // NOLINT(bugprone-reserved-identifier)
                typename __ValueType,                                                           // NOLINT(bugprone-reserved-identifier)
                typename __Hasher = FunctionHasher < __KeyType, & cds :: hash < __KeyType > >   // NOLINT(bugprone-reserved-identifier)
        > HashMap (
                std :: initializer_list < __hidden :: __impl :: __MapEntry < __KeyType, __ValueType > >
        ) -> HashMap < __KeyType, __ValueType, __Hasher >;

        template <
                typename __KeyType,                                                             // NOLINT(bugprone-reserved-identifier)
                typename __ValueType,                                                           // NOLINT(bugprone-reserved-identifier)
                typename __Hasher = FunctionHasher < __KeyType, & cds :: hash < __KeyType > >   // NOLINT(bugprone-reserved-identifier)
        > HashMap (
                std :: initializer_list < __hidden :: __impl :: __MapEntry < __KeyType, __ValueType > >,
                __Hasher
        ) -> HashMap < __KeyType, __ValueType, __Hasher >;

    }
}

#endif

#endif // __CDS_EX_HASH_SET_CTAD_HPP__
