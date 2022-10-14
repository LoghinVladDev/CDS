/*
 * Created by loghin on 10/08/22.
 */

#ifndef __CDS_MAP_IMPL_HPP__
#define __CDS_MAP_IMPL_HPP__ /* NOLINT(bugprone-reserved-identifier) */

namespace cds {

    template <
            typename __KeyType,
            typename __ValueType
    > constexpr auto mapEntryOf (
            __KeyType   && key,
            __ValueType && value
    ) noexcept ( noexcept ( MapEntry < __KeyType, __ValueType > ( std :: forward < __KeyType > ( key ), std :: forward < __ValueType > ( value ) ) ) ) -> MapEntry < __KeyType, __ValueType > {

        return MapEntry < __KeyType, __ValueType > ( std :: forward < __KeyType > ( key ), std :: forward < __ValueType > ( value ) );
    }


    template <
            typename __KeyType,     /* NOLINT(bugprone-reserved-identifier) */
            typename __ValueType    /* NOLINT(bugprone-reserved-identifier) */
    > __CDS_cpplang_ConstexprPureAbstract auto Map <
            __KeyType,
            __ValueType
    > :: keys () const noexcept -> Set < KeyType const > const & {

        return this->keySetProxy();
    }


    template <
            typename __KeyType,     /* NOLINT(bugprone-reserved-identifier) */
            typename __ValueType    /* NOLINT(bugprone-reserved-identifier) */
    > __CDS_cpplang_ConstexprPureAbstract auto Map <
            __KeyType,
            __ValueType
    > :: keys () noexcept -> Set < KeyType const > & {

        return this->keySetProxy();
    }


    template <
            typename __KeyType,     /* NOLINT(bugprone-reserved-identifier) */
            typename __ValueType    /* NOLINT(bugprone-reserved-identifier) */
    > __CDS_cpplang_ConstexprPureAbstract auto Map <
            __KeyType,
            __ValueType
    > :: values () const noexcept -> MutableCollection < ValueType > const & {

        return this->valueMutableCollectionProxy();
    }


    template <
            typename __KeyType,     /* NOLINT(bugprone-reserved-identifier) */
            typename __ValueType    /* NOLINT(bugprone-reserved-identifier) */
    > __CDS_cpplang_ConstexprPureAbstract auto Map <
            __KeyType,
            __ValueType
    > :: values () noexcept -> MutableCollection < ValueType > & {

        return this->valueMutableCollectionProxy();
    }


    template <
            typename __KeyType,     /* NOLINT(bugprone-reserved-identifier) */
            typename __ValueType    /* NOLINT(bugprone-reserved-identifier) */
    > __CDS_cpplang_ConstexprPureAbstract auto Map <
            __KeyType,
            __ValueType
    > :: entries () const noexcept -> MutableCollection < EntryType > const & {

        return this->entryMutableCollectionProxy();
    }


    template <
            typename __KeyType,     /* NOLINT(bugprone-reserved-identifier) */
            typename __ValueType    /* NOLINT(bugprone-reserved-identifier) */
    > __CDS_cpplang_ConstexprPureAbstract auto Map <
            __KeyType,
            __ValueType
    > :: entries () noexcept -> MutableCollection < EntryType > & {

        return this->entryMutableCollectionProxy();
    }


    template <
            typename __KeyType,     /* NOLINT(bugprone-reserved-identifier) */
            typename __ValueType    /* NOLINT(bugprone-reserved-identifier) */
    > constexpr Map <
            __KeyType,
            __ValueType
    > :: Map () noexcept = default;


    template <
            typename __KeyType,     /* NOLINT(bugprone-reserved-identifier) */
            typename __ValueType    /* NOLINT(bugprone-reserved-identifier) */
    > constexpr Map <
            __KeyType,
            __ValueType
    > :: Map (
            Map const & map
    ) noexcept :
            MutableCollectionBase ( map ) {

    }


    template <
            typename __KeyType,     /* NOLINT(bugprone-reserved-identifier) */
            typename __ValueType    /* NOLINT(bugprone-reserved-identifier) */
    > constexpr Map <
            __KeyType,
            __ValueType
    > :: Map (
            Map && map
    ) noexcept :
            MutableCollectionBase ( std :: move ( map ) ) {

    }


    template <
            typename __KeyType,     /* NOLINT(bugprone-reserved-identifier) */
            typename __ValueType    /* NOLINT(bugprone-reserved-identifier) */
    > __CDS_cpplang_ConstexprDestructor Map <
            __KeyType,
            __ValueType
    > :: ~Map () noexcept = default;


    template <
            typename __KeyType,     /* NOLINT(bugprone-reserved-identifier) */
            typename __ValueType    /* NOLINT(bugprone-reserved-identifier) */
    > auto Map <
            __KeyType,
            __ValueType
    > :: toString () const noexcept -> String {

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


    template <
            typename __KeyType,     /* NOLINT(bugprone-reserved-identifier) */
            typename __ValueType    /* NOLINT(bugprone-reserved-identifier) */
    > __CDS_cpplang_ConstexprOverride auto Map <
            __KeyType,
            __ValueType
    > :: contains (
            EntryType const & entry
    ) const noexcept -> bool {

        return this->containsKey ( entry.key() );
    }


    template <
            typename __KeyType,     /* NOLINT(bugprone-reserved-identifier) */
            typename __ValueType    /* NOLINT(bugprone-reserved-identifier) */
    > template <
            typename __TKeyType,    /* NOLINT(bugprone-reserved-identifier) */
            typename __TValueType,  /* NOLINT(bugprone-reserved-identifier) */
            cds :: meta :: EnableIf <
                    cds :: meta :: isDefaultConstructible < __TValueType > ()
            >
    > __CDS_OptimalInline auto Map <
            __KeyType,
            __ValueType
    > :: get (
            __TKeyType && key
    ) noexcept -> ValueType & {

        bool isNew;
        auto pEntry = this->entryAt ( key, & isNew );

        if ( isNew ) {
            new ( pEntry ) EntryType (
                    cds :: forward < __TKeyType > ( key ),
                    ValueType ()
            );
        }

        return pEntry->value();
    }


    template <
            typename __KeyType,     /* NOLINT(bugprone-reserved-identifier) */
            typename __ValueType    /* NOLINT(bugprone-reserved-identifier) */
    > __CDS_OptimalInline auto Map <
            __KeyType,
            __ValueType
    > :: at (
            KeyType const & key
    ) noexcept (false) -> ValueType & {

        auto pEntry = const_cast < EntryType * > ( this->entryAt ( key ) );
        if ( pEntry == nullptr ) {
            throw KeyException ( key );
        }

        return pEntry->value();
    }


    template <
            typename __KeyType,     /* NOLINT(bugprone-reserved-identifier) */
            typename __ValueType    /* NOLINT(bugprone-reserved-identifier) */
    > __CDS_OptimalInline auto Map <
            __KeyType,
            __ValueType
    > :: at (
            KeyType const & key
    ) const noexcept (false) -> ValueType const & {

        auto pEntry = this->entryAt ( key );
        if ( pEntry == nullptr ) {
            throw KeyException ( key );
        }

        return pEntry->value();
    }


    template <
            typename __KeyType,     /* NOLINT(bugprone-reserved-identifier) */
            typename __ValueType    /* NOLINT(bugprone-reserved-identifier) */
    > template <
            typename __TKeyType,    /* NOLINT(bugprone-reserved-identifier) */
            typename __TValueType,  /* NOLINT(bugprone-reserved-identifier) */
            cds :: meta :: EnableIf <
                    cds :: meta :: isDefaultConstructible < __TValueType > ()
            >
    > __CDS_OptimalInline auto Map <
            __KeyType,
            __ValueType
    > :: operator [] (
            __TKeyType && key
    ) noexcept -> ValueType & {

        return this->get ( key );
    }


    template <
            typename __KeyType,     /* NOLINT(bugprone-reserved-identifier) */
            typename __ValueType    /* NOLINT(bugprone-reserved-identifier) */
    > __CDS_OptimalInline auto Map <
            __KeyType,
            __ValueType
    > :: operator [] (
            KeyType const & key
    ) const noexcept (false) -> ValueType const & {

        return this->at ( key );
    }

}

#endif /* __CDS_MAP_IMPL_HPP__ */
