//
// Created by loghin on 6/18/22.
//

#ifndef __CDS_EX_MAP_ABSTRACT_VALUE_MUTABLE_COLLECTION_PROXY_IMPL_HPP__
#define __CDS_EX_MAP_ABSTRACT_VALUE_MUTABLE_COLLECTION_PROXY_IMPL_HPP__

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {

        template < typename __KeyType, typename __ValueType > // NOLINT(bugprone-reserved-identifier)
        constexpr Map < __KeyType, __ValueType > :: AbstractValueMutableCollectionProxy :: AbstractValueMutableCollectionProxy (
                Map < __KeyType, __ValueType > * pMap
        ) noexcept :
                AbstractProxy ( pMap ) {

        }


        template < typename __KeyType, typename __ValueType > // NOLINT(bugprone-reserved-identifier)
        constexpr Map < __KeyType, __ValueType > :: AbstractValueMutableCollectionProxy :: AbstractValueMutableCollectionProxy (
                AbstractValueMutableCollectionProxy const & collection
        ) noexcept :
                AbstractProxy ( collection ) {

        }


        template < typename __KeyType, typename __ValueType > // NOLINT(bugprone-reserved-identifier)
        constexpr Map < __KeyType, __ValueType > :: AbstractValueMutableCollectionProxy :: AbstractValueMutableCollectionProxy (
                AbstractValueMutableCollectionProxy && collection
        ) noexcept :
                AbstractProxy ( std :: move ( collection ) ) {

        }


        template < typename __KeyType, typename __ValueType > // NOLINT(bugprone-reserved-identifier)
        __CDS_cpplang_ConstexprDestructor Map < __KeyType, __ValueType > :: AbstractValueMutableCollectionProxy :: ~AbstractValueMutableCollectionProxy() noexcept = default;


        template < typename __KeyType, typename __ValueType > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto Map < __KeyType, __ValueType > :: AbstractValueMutableCollectionProxy :: remove (
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
        __CDS_OptimalInline auto Map < __KeyType, __ValueType > :: AbstractValueMutableCollectionProxy :: remove (
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
        __CDS_OptimalInline auto Map < __KeyType, __ValueType > :: AbstractValueMutableCollectionProxy :: remove (
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
        __CDS_OptimalInline auto Map < __KeyType, __ValueType > :: AbstractValueMutableCollectionProxy :: remove (
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
        __CDS_OptimalInline auto Map < __KeyType, __ValueType > :: AbstractValueMutableCollectionProxy :: pNewInsert (
                ElementType const & elementType
        ) noexcept -> ElementType * {

            return nullptr;
        }


        template < typename __KeyType, typename __ValueType > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto Map < __KeyType, __ValueType > :: AbstractValueMutableCollectionProxy :: clear () noexcept -> void {

            this->map()->clear();
        }


        template < typename __KeyType, typename __ValueType > // NOLINT(bugprone-reserved-identifier)
        auto Map < __KeyType, __ValueType > :: AbstractValueMutableCollectionProxy :: toString () const noexcept -> String {

            if ( this->empty() ) {
                return {"[]"};
            }

            std::stringstream out;
            out << "[ ";

            for ( auto iterator = this->begin(), end = this->end(); iterator != end; ++ iterator ) {

                cds :: meta :: print ( out, * iterator ) << ", ";
            }

            auto asString = out.str();

            asString [ asString.length() - 2U ] = ' ';
            asString [ asString.length() - 1U ] = ']';

            return asString;
        }

    }
}

#endif // __CDS_EX_MAP_ABSTRACT_VALUE_MUTABLE_COLLECTION_PROXY_IMPL_HPP__
