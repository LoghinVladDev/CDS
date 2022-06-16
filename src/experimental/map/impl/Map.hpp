//
// Created by loghin on 6/16/22.
//

#ifndef __CDS_EX_MAP_IMPL_HPP__
#define __CDS_EX_MAP_IMPL_HPP__

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {

        template < typename __KeyType, typename __ValueType > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto Map < __KeyType, __ValueType > :: begin () noexcept -> Iterator {

            return Iterator ( this, std :: move ( this->delegateIterator ( DelegateIteratorRequestType :: ForwardBegin ) ) );
        }


        template < typename __KeyType, typename __ValueType > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto Map < __KeyType, __ValueType > :: end () noexcept -> Iterator {

            return Iterator ( this, std :: move ( this->delegateIterator ( DelegateIteratorRequestType :: ForwardEnd ) ) );
        }


        template < typename __KeyType, typename __ValueType > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto Map < __KeyType, __ValueType > :: rbegin () noexcept -> ReverseIterator {

            return Iterator ( this, std :: move ( this->delegateIterator ( DelegateIteratorRequestType :: BackwardBegin ) ) );
        }


        template < typename __KeyType, typename __ValueType > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto Map < __KeyType, __ValueType > :: rend () noexcept -> ReverseIterator {

            return Iterator ( this, std :: move ( this->delegateIterator ( DelegateIteratorRequestType :: BackwardEnd ) ) );
        }


        template < typename __KeyType, typename __ValueType > // NOLINT(bugprone-reserved-identifier)
        constexpr Map < __KeyType, __ValueType > :: Map () noexcept = default;


        template < typename __KeyType, typename __ValueType > // NOLINT(bugprone-reserved-identifier)
        constexpr Map < __KeyType, __ValueType > :: Map (
                Map const & map
        ) noexcept :
                Collection < EntryType > ( map ) {

        }


        template < typename __KeyType, typename __ValueType > // NOLINT(bugprone-reserved-identifier)
        constexpr Map < __KeyType, __ValueType > :: Map (
                Map && map
        ) noexcept :
                Collection < EntryType > ( std :: move ( map ) ) {

        }


        template < typename __KeyType, typename __ValueType > // NOLINT(bugprone-reserved-identifier)
        constexpr Map < __KeyType, __ValueType > :: Map (
                Size size
        ) noexcept :
                Collection < EntryType > ( size ) {

        }


        template < typename __KeyType, typename __ValueType > // NOLINT(bugprone-reserved-identifier)
        constexpr Map < __KeyType, __ValueType > :: ~Map () noexcept = default;


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

            (void) this->add (
                    __hidden :: __impl :: __MapEntry (
                            std :: forward < __TKeyType > ( key ),
                            std :: forward < __TValueType > ( value )
                    )
            );
        }


        template < typename __KeyType, typename __ValueType > // NOLINT(bugprone-reserved-identifier)
        auto Map < __KeyType, __ValueType > :: insert (
                EntryType const & entry
        ) noexcept -> void {

            (void) this->add ( entry );
        }

    }
}

#endif // __CDS_EX_MAP_IMPL_HPP__
