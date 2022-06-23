//
// Created by loghin on 6/22/22.
//

#ifndef __CDS_HASH_MAP_DELEGATE_CONST_ITERATOR_IMPL_HPP__
#define __CDS_HASH_MAP_DELEGATE_CONST_ITERATOR_IMPL_HPP__

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {

        template < typename __KeyType, typename __ValueType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
        constexpr HashMap < __KeyType, __ValueType, __Hasher > :: HashMapDelegateConstIterator :: HashMapDelegateConstIterator (
                HashTableConstIterator const & iterator
        ) noexcept :
                _iterator ( iterator ) {

        }


        template < typename __KeyType, typename __ValueType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
        constexpr HashMap < __KeyType, __ValueType, __Hasher > :: HashMapDelegateConstIterator :: HashMapDelegateConstIterator (
                HashMapDelegateConstIterator const & iterator
        ) noexcept :
                _iterator ( iterator._iterator ) {

        }


        template < typename __KeyType, typename __ValueType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
        constexpr HashMap < __KeyType, __ValueType, __Hasher > :: HashMapDelegateConstIterator :: HashMapDelegateConstIterator (
                HashMapDelegateConstIterator && iterator
        ) noexcept :
                _iterator ( std :: move ( iterator._iterator ) ) {

        }


        template < typename __KeyType, typename __ValueType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
        __CDS_cpplang_ConstexprDestructor HashMap < __KeyType, __ValueType, __Hasher > :: HashMapDelegateConstIterator :: ~HashMapDelegateConstIterator () noexcept = default;


        template < typename __KeyType, typename __ValueType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
        constexpr auto HashMap < __KeyType, __ValueType, __Hasher > :: HashMapDelegateConstIterator :: valid () const noexcept -> bool {

            return static_cast < bool > ( this->_iterator );
        }


        template < typename __KeyType, typename __ValueType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
        constexpr auto HashMap < __KeyType, __ValueType, __Hasher > :: HashMapDelegateConstIterator :: iterator () const noexcept -> HashTableConstIterator const & {

            return this->_iterator;
        }


        template < typename __KeyType, typename __ValueType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
        __CDS_cpplang_ConstexprOverride auto HashMap < __KeyType, __ValueType, __Hasher > :: HashMapDelegateConstIterator :: next () noexcept -> HashMapDelegateConstIterator & {

            ++ this->_iterator;
            return * this;
        }


        template < typename __KeyType, typename __ValueType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
        __CDS_cpplang_ConstexprOverride auto HashMap < __KeyType, __ValueType, __Hasher > :: HashMapDelegateConstIterator :: previous () noexcept -> HashMapDelegateConstIterator & {

            return this->next();
        }


        template < typename __KeyType, typename __ValueType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
        __CDS_cpplang_ConstexprOverride auto HashMap < __KeyType, __ValueType, __Hasher > :: HashMapDelegateConstIterator :: value () const noexcept -> HashMap < __KeyType, __ValueType, __Hasher > :: ElementType const & {

            auto & entry = * this->_iterator;
            this->_wrapper = EntryType ( entry._key.data(), entry._value.data() );
            return this->_wrapper;
        }


        template < typename __KeyType, typename __ValueType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
        __CDS_cpplang_ConstexprOverride auto HashMap < __KeyType, __ValueType, __Hasher > :: HashMapDelegateConstIterator :: equals (
                AbstractDelegateIterator const & iterator
        ) const noexcept -> bool {

            return reinterpret_cast < decltype ( this ) > ( & iterator )->_iterator == this->_iterator;
        }


        template < typename __KeyType, typename __ValueType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto HashMap < __KeyType, __ValueType, __Hasher > :: HashMapDelegateConstIterator :: copy () const noexcept -> HashMapDelegateConstIterator * {

            return cds :: copy ( * this );
        }

    }
}

#endif // __CDS_HASH_MAP_DELEGATE_CONST_ITERATOR_IMPL_HPP__
