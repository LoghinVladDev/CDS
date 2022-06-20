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
        constexpr Map < __KeyType, __ValueType > :: Map (
                Size size
        ) noexcept :
                MutableCollection < EntryType > ( size ) {

        }


        template < typename __KeyType, typename __ValueType > // NOLINT(bugprone-reserved-identifier)
        constexpr Map < __KeyType, __ValueType > :: ~Map () noexcept = default;


        template < typename __KeyType, typename __ValueType > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto Map < __KeyType, __ValueType > :: pNewInsert (
                ElementType const & referenceElement
        ) noexcept -> ElementType * & {

            return this->_pInsertionEntry;
        }


        template < typename __KeyType, typename __ValueType > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto Map < __KeyType, __ValueType > :: pNewInsertPost () noexcept -> void {

            this->completeInsertion ( this->_pInsertionEntry );
            Memory :: instance().destroy ( cds :: exchange ( this->_pInsertionEntry, nullptr ) );
        }


        template < typename __KeyType, typename __ValueType > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto Map < __KeyType, __ValueType > :: entryMoveOrCopyKeyTo (
                EntryType       * pDestination,
                EntryType       * pSource
        ) noexcept -> void {

            pSource->moveOrCopyKeyTo ( pDestination );
        }


        template < typename __KeyType, typename __ValueType > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto Map < __KeyType, __ValueType > :: entryMoveOrCopyValueTo (
                EntryType       * pDestination,
                EntryType       * pSource
        ) noexcept -> void {

            pSource->moveOrCopyValueTo ( pDestination );
        }


        template < typename __KeyType, typename __ValueType > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto Map < __KeyType, __ValueType > :: entryCopyTo (
                EntryType       * pDestination,
                EntryType const * pSource
        ) noexcept -> void {

            pSource->copyTo ( pDestination );
        }


        template < typename __KeyType, typename __ValueType > // NOLINT(bugprone-reserved-identifier)
        constexpr auto Map < __KeyType, __ValueType > :: entryEmpty (
                EntryType const * pEntry
        ) noexcept -> bool {

            return pEntry->empty();
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

            auto pEntry = this->pEntryAt ( key );
            if ( pEntry->_key._pAny == nullptr ) {
                pEntry->_key._pObject = Memory :: instance().create < __KeyType > ( std :: forward < __TKeyType > ( key ) );
            }

            if ( pEntry->_value._pAny == nullptr ) {
                pEntry->_value._pObject = Memory :: instance().create < __ValueType > ( std :: forward < __TValueType > ( value ) );
            } else {
                pEntry->_value._pObject->~__ValueType();
                pEntry->_value._pObject = new ( pEntry->_value._pObject ) __ValueType ( std :: forward < __TValueType > ( value ) );
            }
        }


        template < typename __KeyType, typename __ValueType > // NOLINT(bugprone-reserved-identifier)
        auto Map < __KeyType, __ValueType > :: insert (
                EntryType const & entry
        ) noexcept -> void {

            (void) this->add ( entry );
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
