//
// Created by loghin on 6/18/22.
//

#ifndef __CDS_EX_HASH_MAP_IMPL_HPP__
#define __CDS_EX_HASH_MAP_IMPL_HPP__

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {

        template < typename __KeyType, typename __ValueType, typename __HashCalculator > // NOLINT(bugprone-reserved-identifier)
        __CDS_cpplang_ConstexprOverride auto HashMap < __KeyType, __ValueType, __HashCalculator > :: keySetProxy () const noexcept -> AbstractKeySetProxy const & {

            return this->_keySetProxy;
        }


        template < typename __KeyType, typename __ValueType, typename __HashCalculator > // NOLINT(bugprone-reserved-identifier)
        __CDS_cpplang_ConstexprOverride auto HashMap < __KeyType, __ValueType, __HashCalculator > :: keySetProxy () noexcept -> AbstractKeySetProxy & {

            return this->_keySetProxy;
        }


        template < typename __KeyType, typename __ValueType, typename __HashCalculator > // NOLINT(bugprone-reserved-identifier)
        __CDS_cpplang_ConstexprOverride auto HashMap < __KeyType, __ValueType, __HashCalculator > :: valueCollectionProxy () const noexcept -> AbstractValueCollectionProxy const & {

            return this->_valueCollectionProxy;
        }


        template < typename __KeyType, typename __ValueType, typename __HashCalculator > // NOLINT(bugprone-reserved-identifier)
        __CDS_cpplang_ConstexprOverride auto HashMap < __KeyType, __ValueType, __HashCalculator > :: valueCollectionProxy () noexcept -> AbstractValueCollectionProxy & {

            return this->_valueCollectionProxy;
        }


        template < typename __KeyType, typename __ValueType, typename __HashCalculator > // NOLINT(bugprone-reserved-identifier)
        __CDS_cpplang_ConstexprOverride auto HashMap < __KeyType, __ValueType, __HashCalculator > :: entrySetProxy () const noexcept -> AbstractEntrySetProxy const & {

            return this->_entrySetProxy;
        }


        template < typename __KeyType, typename __ValueType, typename __HashCalculator > // NOLINT(bugprone-reserved-identifier)
        __CDS_cpplang_ConstexprOverride auto HashMap < __KeyType, __ValueType, __HashCalculator > :: entrySetProxy () noexcept -> AbstractEntrySetProxy & {

            return this->_entrySetProxy;
        }


        template < typename __KeyType, typename __ValueType, typename __HashCalculator > // NOLINT(bugprone-reserved-identifier)
        constexpr HashMap < __KeyType, __ValueType, __HashCalculator > :: HashMap () noexcept :
                _keySetProxy ( this ),
                _valueCollectionProxy ( this ),
                _entrySetProxy ( this ) {

        }

    }
}

#endif // __CDS_EX_HASH_MAP_IMPL_HPP__
