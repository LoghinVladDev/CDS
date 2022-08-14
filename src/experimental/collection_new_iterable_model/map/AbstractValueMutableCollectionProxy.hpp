//
// Created by loghin on 14/08/22.
//

#ifndef __CDS_EX_MAP_ABSTRACT_VALUE_MUTABLE_COLLECTION_PROXY_HPP__
#define __CDS_EX_MAP_ABSTRACT_VALUE_MUTABLE_COLLECTION_PROXY_HPP__

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {

        template <
                typename __KeyType,     // NOLINT(bugprone-reserved-identifier)
                typename __ValueType    // NOLINT(bugprone-reserved-identifier)
        > class Map <
                __KeyType,
                __ValueType
        > :: AbstractValueMutableCollectionProxy :
                public cds :: experimental :: MutableCollection < __ValueType >,
                protected Map < __KeyType, __ValueType > :: AbstractMapProxy {

        protected:  using ProxyBase             = Map < __KeyType, __ValueType > :: AbstractMapProxy;
        protected:  using MutableCollectionBase = MutableCollection < __ValueType >;

        protected:  using typename MutableCollectionBase :: __GenericHandler;         // NOLINT(bugprone-reserved-identifier)
        protected:  using typename MutableCollectionBase :: __GenericConstHandler;    // NOLINT(bugprone-reserved-identifier)

        protected:
            __CDS_Explicit constexpr AbstractValueMutableCollectionProxy (
                    Map < __KeyType, __ValueType > * pMap
            ) noexcept;

        public:
            auto clear () noexcept -> void override;
        };

    }
}

#endif // __CDS_EX_MAP_ABSTRACT_VALUE_MUTABLE_COLLECTION_PROXY_HPP__
