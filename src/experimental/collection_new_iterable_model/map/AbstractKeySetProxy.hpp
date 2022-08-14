//
// Created by loghin on 14/08/22.
//

#ifndef __CDS_EX_MAP_ABSTRACT_KEY_SET_PROXY_HPP__
#define __CDS_EX_MAP_ABSTRACT_KEY_SET_PROXY_HPP__

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {

        template <
                typename __KeyType,     // NOLINT(bugprone-reserved-identifier)
                typename __ValueType    // NOLINT(bugprone-reserved-identifier)
        > class Map <
                __KeyType,
                __ValueType
        > :: AbstractKeySetProxy :
                public cds :: experimental :: Set < __KeyType const >,
                protected Map < __KeyType, __ValueType > :: AbstractMapProxy {

        protected:  using ProxyBase = Map < __KeyType, __ValueType > :: AbstractMapProxy;
        protected:  using SetBase   = Set < __KeyType const >;

        protected:  using typename SetBase :: __GenericHandler;         // NOLINT(bugprone-reserved-identifier)
        protected:  using typename SetBase :: __GenericConstHandler;    // NOLINT(bugprone-reserved-identifier)

        protected:
            __CDS_Explicit constexpr AbstractKeySetProxy (
                    Map < __KeyType, __ValueType > * pMap
            ) noexcept;

        public:
            auto clear () noexcept -> void override;

        public:
            auto remove (
                    KeyType const & key
            ) noexcept -> bool override;
        };

    }
}

#endif // __CDS_EX_MAP_ABSTRACT_KEY_SET_PROXY_HPP__
