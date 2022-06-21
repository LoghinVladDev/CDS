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
                _pMap ( pMap ) {

        }


        template < typename __KeyType, typename __ValueType > // NOLINT(bugprone-reserved-identifier)
        constexpr Map < __KeyType, __ValueType > :: AbstractValueMutableCollectionProxy :: AbstractValueMutableCollectionProxy (
                AbstractValueMutableCollectionProxy const & collection
        ) noexcept :
                MutableCollection < ValueType > ( collection ),
                _pMap ( collection._pMap ) {

        }


        template < typename __KeyType, typename __ValueType > // NOLINT(bugprone-reserved-identifier)
        constexpr Map < __KeyType, __ValueType > :: AbstractValueMutableCollectionProxy :: AbstractValueMutableCollectionProxy (
                AbstractValueMutableCollectionProxy && collection
        ) noexcept :
                MutableCollection < ValueType > ( std :: move ( collection ) ),
                _pMap ( collection._pMap ) {

        }


        template < typename __KeyType, typename __ValueType > // NOLINT(bugprone-reserved-identifier)
        __CDS_cpplang_ConstexprDestructor Map < __KeyType, __ValueType > :: AbstractValueMutableCollectionProxy :: ~AbstractValueMutableCollectionProxy() noexcept = default;


        template < typename __KeyType, typename __ValueType > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto Map < __KeyType, __ValueType > :: AbstractValueMutableCollectionProxy :: remove (
                Iterator const & iterator
        ) noexcept -> bool {

            /// TODO : after implementing HashMap iterator
            return false;
        }


        template < typename __KeyType, typename __ValueType > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto Map < __KeyType, __ValueType > :: AbstractValueMutableCollectionProxy :: remove (
                ConstIterator const & iterator
        ) noexcept -> bool {

            /// TODO : after implementing HashMap iterator
            return false;
        }


        template < typename __KeyType, typename __ValueType > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto Map < __KeyType, __ValueType > :: AbstractValueMutableCollectionProxy :: remove (
                ReverseIterator const & iterator
        ) noexcept -> bool {

            /// TODO : after implementing HashMap iterator
            return false;
        }


        template < typename __KeyType, typename __ValueType > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto Map < __KeyType, __ValueType > :: AbstractValueMutableCollectionProxy :: remove (
                ConstReverseIterator const & iterator
        ) noexcept -> bool {

            /// TODO : after implementing HashMap iterator
            return false;
        }


        template < typename __KeyType, typename __ValueType > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto Map < __KeyType, __ValueType > :: AbstractValueMutableCollectionProxy :: remove (
                Iterator    const * pIterators,
                Size                iteratorCount
        ) noexcept -> Size {

            /// TODO : after implementing HashMap iterator
            return 0ULL;
        }


        template < typename __KeyType, typename __ValueType > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto Map < __KeyType, __ValueType > :: AbstractValueMutableCollectionProxy :: remove (
                ConstIterator   const * pIterators,
                Size                    iteratorCount
        ) noexcept -> Size {

            /// TODO : after implementing HashMap iterator
            return 0ULL;
        }


        template < typename __KeyType, typename __ValueType > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto Map < __KeyType, __ValueType > :: AbstractValueMutableCollectionProxy :: remove (
                ReverseIterator const * pIterators,
                Size                    iteratorCount
        ) noexcept -> Size {

            /// TODO : after implementing HashMap iterator
            return 0ULL;
        }


        template < typename __KeyType, typename __ValueType > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto Map < __KeyType, __ValueType > :: AbstractValueMutableCollectionProxy :: remove (
                ConstReverseIterator    const * pIterators,
                Size                            iteratorCount
        ) noexcept -> Size {

            /// TODO : after implementing HashMap iterator
            return 0ULL;
        }


        template < typename __KeyType, typename __ValueType > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto Map < __KeyType, __ValueType > :: AbstractValueMutableCollectionProxy :: pNewInsert (
                ElementType const & elementType
        ) noexcept -> ElementType * & {

            static auto dummyAddress = reinterpret_cast < ElementType * > ( 0x10 );
            return dummyAddress;
        }


        template < typename __KeyType, typename __ValueType > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto Map < __KeyType, __ValueType > :: AbstractValueMutableCollectionProxy :: clear () noexcept -> void {

            this->_pMap->clear();
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
