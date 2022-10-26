//
// Created by stefan on 26.09.2022.
//

#ifndef __CDS_EX_TREE_MAP_IMPL_HPP__
#define __CDS_EX_TREE_MAP_IMPL_HPP__    /* NOLINT(bugprone-reserved-identifier) */

namespace cds {                 /* NOLINT(modernize-concat-nested-namespaces) */
    namespace experimental {

        template <
                typename __KeyType,     /* NOLINT(bugprone-reserved-identifier) */
                typename __ValueType    /* NOLINT(bugprone-reserved-identifier) */
        > __CDS_cpplang_ConstexprOverride auto TreeMap <
                __KeyType,
                __ValueType
        > :: __cicch_obtainGenericHandler (         /* NOLINT(bugprone-reserved-identifier) */
                cds :: __hidden :: __impl :: __CollectionInternalRequestType requestType
        ) noexcept -> __GenericHandler {

            return this->__ms_handlers() [ static_cast < uint32 > ( requestType ) ];
        }

        template <
                typename __KeyType,     /* NOLINT(bugprone-reserved-identifier) */
                typename __ValueType    /* NOLINT(bugprone-reserved-identifier) */
        > __CDS_cpplang_ConstexprOverride auto TreeMap <
                __KeyType,      /* NOLINT(bugprone-reserved-identifier) */
                __ValueType     /* NOLINT(bugprone-reserved-identifier) */
        > :: __cicch_obtainGenericConstHandler (         /* NOLINT(bugprone-reserved-identifier) */
                cds :: __hidden :: __impl :: __CollectionInternalRequestType requestType
        ) const noexcept -> __GenericConstHandler {

            return this->__ms_constHandlers() [ static_cast < uint32 > ( requestType ) ];
        }
    }
}
#endif //__CDS_EX_TREE_MAP_IMPL_HPP__
