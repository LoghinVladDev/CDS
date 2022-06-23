//
// Created by loghin on 6/23/22.
//

#ifndef __CDS_EX_MAP_ABSTRACT_PROXY_HPP__
#define __CDS_EX_MAP_ABSTRACT_PROXY_HPP__

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {

        template < typename __KeyType, typename __ValueType > // NOLINT(bugprone-reserved-identifier)
        class Map < __KeyType, __ValueType > :: AbstractProxy {

        private:
            Map < __KeyType, __ValueType > * _pMap;

        protected:
            __CDS_Explicit constexpr AbstractProxy (
                    Map < __KeyType, __ValueType > * pMap
            ) noexcept;

        protected:
            constexpr AbstractProxy (
                    AbstractProxy const & proxy
            ) noexcept;

        protected:
            constexpr AbstractProxy (
                    AbstractProxy && proxy
            ) noexcept;

        protected:
            template < typename __DerivedType = Map < __KeyType, __ValueType > > // NOLINT(bugprone-reserved-identifier)
            constexpr auto map () const noexcept -> __DerivedType *;

        };

    }
}

#endif // __CDS_EX_MAP_ABSTRACT_PROXY_HPP__
