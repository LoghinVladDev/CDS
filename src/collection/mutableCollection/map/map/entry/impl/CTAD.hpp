/*
 * Created by loghin on 15/10/22.
 */

#ifndef __CDS_MAP_ENTRY_CTAD_IMPL_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_MAP_ENTRY_CTAD_IMPL_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

#if __CDS_cpplang_CTAD_available

namespace cds {
    namespace __hidden {
        namespace __impl {

            template <
                    typename __KeyType,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ValueType    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > __MapEntry (
                    __KeyType,
                    __ValueType
            ) -> __MapEntry < __KeyType, __ValueType >;

        }
    }
}

#endif

#endif /* __CDS_MAP_ENTRY_CTAD_IMPL_HPP__ */
