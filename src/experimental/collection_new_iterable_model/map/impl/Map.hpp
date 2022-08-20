/*
 * Created by loghin on 10/08/22.
 */

#ifndef __CDS_EX_MAP_IMPL_HPP__
#define __CDS_EX_MAP_IMPL_HPP__ /* NOLINT(bugprone-reserved-identifier) */

namespace cds { /* NOLINT(modernize-concat-nested-namespaces) */
    namespace experimental {

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

    }
}

#endif /* __CDS_EX_MAP_IMPL_HPP__ */
