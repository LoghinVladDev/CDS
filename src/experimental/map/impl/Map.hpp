//
// Created by loghin on 6/16/22.
//

#ifndef __CDS_EX_MAP_IMPL_HPP__
#define __CDS_EX_MAP_IMPL_HPP__

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {

        template < typename __KeyType, typename __ValueType > // NOLINT(bugprone-reserved-identifier)
        __CDS_cpplang_ConstexprPureAbstract auto Map < __KeyType, __ValueType > :: keys () const noexcept -> Set < KeyType const > const & {

            return this->keySetProxy();
        }


        template < typename __KeyType, typename __ValueType > // NOLINT(bugprone-reserved-identifier)
        __CDS_cpplang_ConstexprPureAbstract auto Map < __KeyType, __ValueType > :: keys () noexcept -> Set < KeyType const > & {

            return this->keySetProxy();
        }


        template < typename __KeyType, typename __ValueType > // NOLINT(bugprone-reserved-identifier)
        __CDS_cpplang_ConstexprPureAbstract auto Map < __KeyType, __ValueType > :: values () const noexcept -> MutableCollection < ValueType > const & {

            return this->valueCollectionProxy();
        }


        template < typename __KeyType, typename __ValueType > // NOLINT(bugprone-reserved-identifier)
        __CDS_cpplang_ConstexprPureAbstract auto Map < __KeyType, __ValueType > :: values () noexcept -> MutableCollection < ValueType > & {

            return this->valueCollectionProxy();
        }


        template < typename __KeyType, typename __ValueType > // NOLINT(bugprone-reserved-identifier)
        __CDS_cpplang_ConstexprPureAbstract auto Map < __KeyType, __ValueType > :: entries () const noexcept -> MutableCollection < EntryType > const & {

            return this->entrySetProxy();
        }


        template < typename __KeyType, typename __ValueType > // NOLINT(bugprone-reserved-identifier)
        __CDS_cpplang_ConstexprPureAbstract auto Map < __KeyType, __ValueType > :: entries () noexcept -> MutableCollection < EntryType > & {

            return this->entrySetProxy();
        }


        template < typename __KeyType, typename __ValueType > // NOLINT(bugprone-reserved-identifier)
        constexpr Map < __KeyType, __ValueType > :: Map () noexcept = default;


        template < typename __KeyType, typename __ValueType > // NOLINT(bugprone-reserved-identifier)
        constexpr Map < __KeyType, __ValueType > :: Map (
                Map const & map
        ) noexcept :
                MutableCollection < EntryType > ( map ) {

        }


        template < typename __KeyType, typename __ValueType > // NOLINT(bugprone-reserved-identifier)
        constexpr Map < __KeyType, __ValueType > :: Map (
                Map && map
        ) noexcept :
                MutableCollection < EntryType > ( std :: move ( map ) ) {

        }


        template < typename __KeyType, typename __ValueType > // NOLINT(bugprone-reserved-identifier)
        constexpr Map < __KeyType, __ValueType > :: ~Map () noexcept = default;


        template < typename __KeyType, typename __ValueType > // NOLINT(bugprone-reserved-identifier)
        template < typename __TValueType, cds :: meta :: EnableIf < cds :: meta :: isDefaultConstructible < __TValueType > () > > // NOLINT(bugprone-reserved-identifier)
        auto Map < __KeyType, __ValueType > :: get (
                KeyType const & key
        ) noexcept -> ValueType & {

            bool isNew;
            auto entry = this->entryAt ( key, isNew );

            if ( isNew ) {
                auto newEntry = EntryType ( key, __ValueType () );
                newEntry.moveOrCopyKeyTo ( & entry );
                newEntry.moveOrCopyValueTo ( & entry, isNew );
            }

            return entry.value();
        }


        template < typename __KeyType, typename __ValueType > // NOLINT(bugprone-reserved-identifier)
        auto Map < __KeyType, __ValueType > :: at (
                KeyType const & key
        ) noexcept (false) -> ValueType & {

            auto pEntry = const_cast < EntryType * > ( reinterpret_cast < decltype ( this ) const > ( this )->pEntryAt ( key ) );
            if ( pEntry == nullptr ) {
                throw KeyException ( key );
            }

            return pEntry->value;
        }


        template < typename __KeyType, typename __ValueType > // NOLINT(bugprone-reserved-identifier)
        auto Map < __KeyType, __ValueType > :: at (
                KeyType const & key
        ) const noexcept (false) -> ValueType const & {

            auto pEntry = this->pEntryAt ( key );
            if ( pEntry == nullptr ) {
                throw KeyException ( key );
            }

            return pEntry->value;
        }


        template < typename __KeyType, typename __ValueType > // NOLINT(bugprone-reserved-identifier)
        template < typename __TValueType, cds :: meta :: EnableIf < cds :: meta :: isDefaultConstructible < __TValueType > () > > // NOLINT(bugprone-reserved-identifier)
        auto Map < __KeyType, __ValueType > :: operator [] (
                KeyType const & key
        ) noexcept -> ValueType & {

            return this->get ( key );
        }


        template < typename __KeyType, typename __ValueType > // NOLINT(bugprone-reserved-identifier)
        auto Map < __KeyType, __ValueType > :: operator [] (
                KeyType const & key
        ) const noexcept (false) -> ValueType const & {

            return this->at ( key );
        }


        template < typename __KeyType, typename __ValueType > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto Map < __KeyType, __ValueType > :: pNewInsert (
                ElementType const & referenceElement
        ) noexcept -> ElementType * & {

            return this->_pInsertionEntry;
        }


        template < typename __KeyType, typename __ValueType > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto Map < __KeyType, __ValueType > :: pNewInsertPost () noexcept -> void {

            bool isNew;
            auto newEntry = this->entryAt ( this->_pInsertionEntry->key(), isNew );

            if ( isNew ) {
                this->_pInsertionEntry->moveOrCopyKeyTo ( & newEntry );
            }

            this->_pInsertionEntry->moveOrCopyValueTo ( & newEntry, isNew );
            Memory :: instance().destroy ( cds :: exchange ( this->_pInsertionEntry, nullptr ) );
        }


        template < typename __KeyType, typename __ValueType > // NOLINT(bugprone-reserved-identifier)
        auto Map < __KeyType, __ValueType > :: toString () const noexcept -> String {

            if ( this->empty() ) {
                return "{}";
            }

            std :: stringstream oss;
            oss << "{ ";

            for ( auto iterator = this->begin(), end = this->end(); iterator != end; ++ iterator ) {

                cds :: meta :: print ( cds :: meta :: print ( oss, ( * iterator ).key() ) <<
                    ": ", ( * iterator ).value() ) << ", ";
            }

            auto asString = oss.str();

            asString [ asString.length() - 2U ] = ' ';
            asString [ asString.length() - 1U ] = '}';

            return asString;
        }


        template < typename __KeyType, typename __ValueType > // NOLINT(bugprone-reserved-identifier)
        template < typename __TKeyType, typename __TValueType > // NOLINT(bugprone-reserved-identifier)
        auto Map < __KeyType, __ValueType > :: emplace (
                __TKeyType      && key,
                __TValueType    && value
        ) noexcept -> void {

            bool isNew = false;
            auto entry = this->entryAt ( key, isNew );

            if ( isNew ) {
                entry._key._pObject     = new ( entry._key._pObject )   __KeyType   ( std :: forward < __TKeyType > ( key ) );
            } else {
                entry._value._pObject->~__ValueType();
            }

            entry._value._pObject   = new ( entry._value._pObject ) __ValueType ( std :: forward < __TValueType > ( value ) );
        }


        template < typename __KeyType, typename __ValueType > // NOLINT(bugprone-reserved-identifier)
        auto Map < __KeyType, __ValueType > :: insert (
                EntryType const & entry
        ) noexcept -> void {

            bool isNew;
            auto newEntry = this->entryAt ( entry.key(), isNew );

            if ( isNew ) {
                entry.moveOrCopyKeyTo ( & newEntry );
            }

            entry.moveOrCopyValueTo ( & newEntry, isNew );
        }


        template < typename __KeyType, typename __ValueType > // NOLINT(bugprone-reserved-identifier)
        auto Map < __KeyType, __ValueType > :: freeEntryData (
                EntryType & entry
        ) noexcept -> void {

            Memory :: instance().destroy ( entry._key._pObject );
            Memory :: instance().destroy ( entry._value._pObject );
        }

    }
}

#endif // __CDS_EX_MAP_IMPL_HPP__
