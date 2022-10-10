/*
 * Created by loghin on 10/08/22.
 */

#ifndef __CDS_MAP_CONSTRUCTS_HPP__
#define __CDS_MAP_CONSTRUCTS_HPP__ /* NOLINT(bugprone-reserved-identifier) */

namespace cds {

    template <
            typename __KeyType,     /* NOLINT(bugprone-reserved-identifier) */
            typename __ValueType    /* NOLINT(bugprone-reserved-identifier) */
    > class Map;

    namespace __hidden {    /* NOLINT(bugprone-reserved-identifier, modernize-concat-nested-namespaces) */
        namespace __impl {  /* NOLINT(bugprone-reserved-identifier) */

            template <
                    typename __KeyType,                 /* NOLINT(bugprone-reserved-identifier) */
                    typename __ValueType                /* NOLINT(bugprone-reserved-identifier) */
            > using __MapFindUniqueImmutableClient =    /* NOLINT(bugprone-reserved-identifier) */
                    __FindUniqueImmutablePrimitiveClient <
                            cds :: Map < __KeyType, __ValueType >,
                            __MapEntry < __KeyType, __ValueType >,
                            __KeyType,
                            false
                    >;

            template <
                    typename __KeyType,               /* NOLINT(bugprone-reserved-identifier) */
                    typename __ValueType              /* NOLINT(bugprone-reserved-identifier) */
            > using __MapFindUniqueMutableClient =    /* NOLINT(bugprone-reserved-identifier) */
                    __FindUniqueMutablePrimitiveClient <
                            cds :: Map < __KeyType, __ValueType >,
                            __MapEntry < __KeyType, __ValueType >,
                            __KeyType,
                            false
                    >;

        }
    }

}

#endif /* __CDS_MAP_CONSTRUCTS_HPP__ */
