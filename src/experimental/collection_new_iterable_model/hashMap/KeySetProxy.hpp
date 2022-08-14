//
// Created by loghin on 14/08/22.
//

#ifndef __CDS_EX_HASH_MAP_KEY_SET_PROXY_HPP__
#define __CDS_EX_HASH_MAP_KEY_SET_PROXY_HPP__

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {

        template <
                typename __KeyType,     // NOLINT(bugprone-reserved-identifier)
                typename __ValueType,   // NOLINT(bugprone-reserved-identifier)
                typename __Hasher       // NOLINT(bugprone-reserved-identifier)
        > class HashMap <
                __KeyType,
                __ValueType,
                __Hasher
        > :: KeySetProxy :
                public AbstractKeySetProxy {

        protected:  using typename AbstractKeySetProxy :: __GenericHandler;         // NOLINT(bugprone-reserved-identifier)
        protected:  using typename AbstractKeySetProxy :: __GenericConstHandler;    // NOLINT(bugprone-reserved-identifier)

        private:
            __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto __cicch_obtainGenericHandler ( // NOLINT(bugprone-reserved-identifier)
                    __hidden :: __impl :: __CollectionInternalRequestType requestType
            ) noexcept -> __GenericHandler override;

        private:
            __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto __cicch_obtainGenericConstHandler (    // NOLINT(bugprone-reserved-identifier)
                    __hidden :: __impl :: __CollectionInternalRequestType requestType
            ) const noexcept -> __GenericConstHandler override;

        public:
            __CDS_Explicit constexpr KeySetProxy (
                    HashMap < __KeyType, __ValueType, __Hasher > * pMap
            ) noexcept;
        };

    }
}

#endif // __CDS_EX_HASH_MAP_KEY_SET_PROXY_HPP__
