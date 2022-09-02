//
// Created by loghin on 6/16/22.
//

#ifndef __CDS_MAP_IMPL_HPP__
#define __CDS_MAP_IMPL_HPP__

namespace cds {

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
    __CDS_cpplang_ConstexprDestructor Map < __KeyType, __ValueType > :: ~Map () noexcept = default;


    template < typename __KeyType, typename __ValueType > // NOLINT(bugprone-reserved-identifier)
    template <
            typename __TKeyType,    // NOLINT(bugprone-reserved-identifier)
            typename __TValueType,  // NOLINT(bugprone-reserved-identifier)
            cds :: meta :: EnableIf <
                    cds :: meta :: isDefaultConstructible < __TValueType > ()
            >
    > __CDS_OptimalInline auto Map < __KeyType, __ValueType > :: get (
            __TKeyType && key
    ) noexcept -> ValueType & {

        bool isNew;
        auto pEntry = this->entryAt ( key, isNew );

        if ( isNew ) {
            new ( pEntry ) EntryType (
                    cds :: forward < __TKeyType > ( key ),
                    ValueType ()
            );
        }

        return pEntry->value();
    }


    template < typename __KeyType, typename __ValueType > // NOLINT(bugprone-reserved-identifier)
    __CDS_OptimalInline auto Map < __KeyType, __ValueType > :: at (
            KeyType const & key
    ) noexcept (false) -> ValueType & {

        auto pEntry = const_cast < EntryType * > ( this->entryAt ( key ) );
        if ( pEntry == nullptr ) {
            throw KeyException ( key );
        }

        return pEntry->value();
    }


    template < typename __KeyType, typename __ValueType > // NOLINT(bugprone-reserved-identifier)
    __CDS_OptimalInline auto Map < __KeyType, __ValueType > :: at (
            KeyType const & key
    ) const noexcept (false) -> ValueType const & {

        auto pEntry = this->entryAt ( key );
        if ( pEntry == nullptr ) {
            throw KeyException ( key );
        }

        return pEntry->value();
    }


    template < typename __KeyType, typename __ValueType > // NOLINT(bugprone-reserved-identifier)
    template < typename __TValueType, cds :: meta :: EnableIf < cds :: meta :: isDefaultConstructible < __TValueType > () > > // NOLINT(bugprone-reserved-identifier)
    __CDS_OptimalInline auto Map < __KeyType, __ValueType > :: operator [] (
            KeyType const & key
    ) noexcept -> ValueType & {

        return this->get ( key );
    }


    template < typename __KeyType, typename __ValueType > // NOLINT(bugprone-reserved-identifier)
    __CDS_OptimalInline auto Map < __KeyType, __ValueType > :: operator [] (
            KeyType const & key
    ) const noexcept (false) -> ValueType const & {

        return this->at ( key );
    }


    template < typename __KeyType, typename __ValueType > // NOLINT(bugprone-reserved-identifier)
    __CDS_OptimalInline auto Map < __KeyType, __ValueType > :: pNewInsert (
            ElementType const & referenceElement
    ) noexcept -> ElementType * {

        bool isNew;
        auto pNew = this->entryAt ( referenceElement.key(), isNew );

        if ( ! isNew ) {
            return nullptr;
        }

        return pNew;
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
    template <
            typename __TKeyType,    // NOLINT(bugprone-reserved-identifier)
            typename __TValueType   // NOLINT(bugprone-reserved-identifier)
    > auto Map < __KeyType, __ValueType > :: emplace (
            __TKeyType      && key,
            __TValueType    && value
    ) noexcept -> void {

        bool isNew = false;
        auto pEntry = this->entryAt ( key, isNew );

        if ( isNew ) {
            new ( pEntry ) ElementType (
                    std :: forward < __TKeyType > ( key ),
                    std :: forward < __TValueType > ( value )
            );
            return;
        }

        pEntry->value().~__ValueType();
        new ( & pEntry->value() ) __ValueType ( std :: forward < __TValueType > ( value ) );
    }


    template < typename __KeyType, typename __ValueType >                                                                   // NOLINT(bugprone-reserved-identifier)
    template < typename __TEntryType, cds :: meta :: EnableIf < cds :: meta :: isCopyConstructible < __TEntryType > () > >  // NOLINT(bugprone-reserved-identifier)
    auto Map < __KeyType, __ValueType > :: insert (
            __TEntryType const & entry
    ) noexcept -> void {

        bool isNew;
        auto pEntry = this->entryAt ( entry.key(), isNew );

        if ( isNew ) {
            new ( pEntry ) ElementType ( entry );
            return;
        }

        pEntry->value().~__ValueType();
        new ( & pEntry->value() ) __ValueType ( entry.value() );
    }


    template < typename __KeyType, typename __ValueType >                                                                   // NOLINT(bugprone-reserved-identifier)
    template < typename __TEntryType, cds :: meta :: EnableIf < cds :: meta :: isMoveConstructible < __TEntryType > () > >  // NOLINT(bugprone-reserved-identifier)
    auto Map < __KeyType, __ValueType > :: insert (
            __TEntryType && entry
    ) noexcept -> void {

        bool isNew;
        auto pEntry = this->entryAt ( entry.key(), isNew );

        if ( isNew ) {
            new ( pEntry ) ElementType ( std :: move ( entry ) ); // NOLINT(bugprone-move-forwarding-reference)
            return;
        }

        pEntry->value().~__ValueType();
        new ( & pEntry->value() ) __ValueType ( std :: move ( entry.value() ) );
    }

}

#endif // __CDS_MAP_IMPL_HPP__
