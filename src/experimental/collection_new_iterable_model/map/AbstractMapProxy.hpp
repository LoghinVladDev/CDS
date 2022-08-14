//
// Created by loghin on 14/08/22.
//

#ifndef __CDS_EX_MAP_ABSTRACT_MAP_PROXY_HPP__
#define __CDS_EX_MAP_ABSTRACT_MAP_PROXY_HPP__

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {

        template <
                typename __KeyType,     // NOLINT(bugprone-reserved-identifier)
                typename __ValueType    // NOLINT(bugprone-reserved-identifier)
        > class Map <
                __KeyType,
                __ValueType
        > :: AbstractMapProxy {

        private:
            Map < __KeyType, __ValueType > * _pMap;

        protected:
            __CDS_Explicit constexpr AbstractMapProxy (
                    Map < __KeyType, __ValueType > * pMap
            ) noexcept;

        protected:
            constexpr AbstractMapProxy (
                    AbstractMapProxy const & proxy
            ) noexcept;

        protected:
            constexpr AbstractMapProxy (
                    AbstractMapProxy && proxy
            ) noexcept;

        protected:
            template < typename __DerivedType = Map < __KeyType, __ValueType > > // NOLINT(bugprone-reserved-identifier)
            auto map () noexcept -> __DerivedType *;

        protected:
            template < typename __DerivedType = Map < __KeyType, __ValueType > > // NOLINT(bugprone-reserved-identifier)
            auto map () const noexcept -> __DerivedType const *;

        };

    }
}

#endif // __CDS_EX_MAP_ABSTRACT_MAP_PROXY_HPP__
