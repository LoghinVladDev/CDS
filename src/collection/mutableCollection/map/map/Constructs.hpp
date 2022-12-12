/* NOLINT(llvm-header-guard)
 * Created by loghin on 10/08/22.
 */

#ifndef __CDS_MAP_CONSTRUCTS_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_MAP_CONSTRUCTS_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

namespace cds {

    template <
            typename __KeyType,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __ValueType    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    > class Map;

    namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        namespace __impl {  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            template <
                    typename __KeyType,                 /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ValueType                /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > using __MapFindUniqueImmutableClient =    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __FindUniqueImmutablePrimitiveClient <
                            cds :: Map < __KeyType, __ValueType >,
                            __MapEntry < __KeyType, __ValueType >,
                            __KeyType,
                            false
                    >;

            template <
                    typename __KeyType,               /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ValueType              /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > using __MapFindUniqueMutableClient =    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __FindUniqueMutablePrimitiveClient <
                            cds :: Map < __KeyType, __ValueType >,
                            __MapEntry < __KeyType, __ValueType >,
                            __KeyType,
                            false
                    >;

        } /* namespace __impl */
    } /* namespace __hidden */

} /* namespace cds */

#endif /* __CDS_MAP_CONSTRUCTS_HPP__ */
