//
// Created by loghin on 6/18/22.
//

#ifndef __CDS_EX_MAP_ABSTRACT_ENTRY_MUTABLE_COLLECTION_PROXY_IMPL_HPP__
#define __CDS_EX_MAP_ABSTRACT_ENTRY_MUTABLE_COLLECTION_PROXY_IMPL_HPP__

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {

        template < typename __KeyType, typename __ValueType > // NOLINT(bugprone-reserved-identifier)
        constexpr Map < __KeyType, __ValueType > :: AbstractEntryMutableCollectionProxy :: AbstractEntryMutableCollectionProxy (
                Map < __KeyType, __ValueType > * pMap
        ) noexcept :
                AbstractProxy ( pMap ) {

        }


        template < typename __KeyType, typename __ValueType > // NOLINT(bugprone-reserved-identifier)
        constexpr Map < __KeyType, __ValueType > :: AbstractEntryMutableCollectionProxy :: AbstractEntryMutableCollectionProxy (
                AbstractEntryMutableCollectionProxy const & collection
        ) noexcept :
                AbstractProxy ( collection ) {

        }


        template < typename __KeyType, typename __ValueType > // NOLINT(bugprone-reserved-identifier)
        constexpr Map < __KeyType, __ValueType > :: AbstractEntryMutableCollectionProxy :: AbstractEntryMutableCollectionProxy (
                AbstractEntryMutableCollectionProxy && collection
        ) noexcept :
                AbstractProxy ( std :: move ( collection ) ) {

        }


        template < typename __KeyType, typename __ValueType > // NOLINT(bugprone-reserved-identifier)
        __CDS_cpplang_ConstexprDestructor Map < __KeyType, __ValueType > :: AbstractEntryMutableCollectionProxy :: ~AbstractEntryMutableCollectionProxy() noexcept = default;


        template < typename __KeyType, typename __ValueType > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto Map < __KeyType, __ValueType > :: AbstractEntryMutableCollectionProxy :: remove (
                EntryType const & entry
        ) noexcept -> bool {

            return this->map().remove ( entry.key() );
        }


        template < typename __KeyType, typename __ValueType > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto Map < __KeyType, __ValueType > :: AbstractEntryMutableCollectionProxy :: remove (
                Iterator    const * pIterators,
                Size                iteratorCount
        ) noexcept -> Size {

            Size removedCount = 0ULL;
            for ( Size index = 0ULL; index < iteratorCount; ++ index ) {
                if ( this->remove ( pIterators [ index ] ) ) {
                    ++ removedCount;
                }
            }

            return removedCount;
        }


        template < typename __KeyType, typename __ValueType > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto Map < __KeyType, __ValueType > :: AbstractEntryMutableCollectionProxy :: remove (
                ConstIterator   const * pIterators,
                Size                    iteratorCount
        ) noexcept -> Size {

            Size removedCount = 0ULL;
            for ( Size index = 0ULL; index < iteratorCount; ++ index ) {
                if ( this->remove ( pIterators [ index ] ) ) {
                    ++ removedCount;
                }
            }

            return removedCount;
        }


        template < typename __KeyType, typename __ValueType > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto Map < __KeyType, __ValueType > :: AbstractEntryMutableCollectionProxy :: remove (
                ReverseIterator const * pIterators,
                Size                    iteratorCount
        ) noexcept -> Size {

            Size removedCount = 0ULL;
            for ( Size index = 0ULL; index < iteratorCount; ++ index ) {
                if ( this->remove ( pIterators [ index ] ) ) {
                    ++ removedCount;
                }
            }

            return removedCount;
        }


        template < typename __KeyType, typename __ValueType > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto Map < __KeyType, __ValueType > :: AbstractEntryMutableCollectionProxy :: remove (
                ConstReverseIterator    const * pIterators,
                Size                            iteratorCount
        ) noexcept -> Size {

            Size removedCount = 0ULL;
            for ( Size index = 0ULL; index < iteratorCount; ++ index ) {
                if ( this->remove ( pIterators [ index ] ) ) {
                    ++ removedCount;
                }
            }

            return removedCount;
        }


        template < typename __KeyType, typename __ValueType > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto Map < __KeyType, __ValueType > :: AbstractEntryMutableCollectionProxy :: pNewInsert (
                ElementType const & elementType
        ) noexcept -> ElementType * & {

            return this->map()->pNewInsert ( elementType );
        }


        template < typename __KeyType, typename __ValueType > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto Map < __KeyType, __ValueType > :: AbstractEntryMutableCollectionProxy :: pNewInsertPost () noexcept -> void {

            return this->map()->pNewInsertPost();
        }


        template < typename __KeyType, typename __ValueType > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto Map < __KeyType, __ValueType > :: AbstractEntryMutableCollectionProxy :: contains (
                EntryType const & entry
        ) const noexcept -> bool {

            return this->map()->containsKey ( entry.key() );
        }


        template < typename __KeyType, typename __ValueType > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto Map < __KeyType, __ValueType > :: AbstractEntryMutableCollectionProxy :: clear () noexcept -> void {

            this->map()->clear();
        }


        template < typename __KeyType, typename __ValueType > // NOLINT(bugprone-reserved-identifier)
        auto Map < __KeyType, __ValueType > :: AbstractEntryMutableCollectionProxy :: toString () const noexcept -> String {

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

#endif // __CDS_EX_MAP_ABSTRACT_ENTRY_MUTABLE_COLLECTION_PROXY_IMPL_HPP__
