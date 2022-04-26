//
// Created by loghin on 4/26/22.
//

#ifndef __CDS_LIST_IMPL_HPP__
#define __CDS_LIST_IMPL_HPP__

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {

        template < typename T >
        constexpr auto List < T > :: size () const noexcept -> Size {
            return this->_size;
        }

        template < typename T >
        constexpr auto List < T > :: empty () const noexcept -> bool {
            return this->_size == 0ULL;
        }

        template < typename T >
        auto List < T > :: toString () const noexcept -> String {
            if ( this->empty() ) {
                return {"[ ]"};
            }

            std::stringstream out;
            out << "[ ";

                for ( auto const & element __CDS_MaybeUnused : (*this) ) {
                Type < T > :: streamPrint(out, element ) << ", ";
            }

            auto asString = out.str();
            return asString.substr(0u, asString.length() - 2u).append(" ]");
        }

        template < typename T >
        __CDS_OptimalInline auto List < T > :: equals ( Object const & object ) const noexcept -> bool {
            if ( this == & object ) {
                return true;
            }

            auto pObject = dynamic_cast < decltype ( this ) > ( & object );
            if ( pObject != nullptr ) {
                if ( this->_size != pObject->_size ) {
                    return false;
                }
            }

            return Collection < T > :: equals ( object );
        }

        template < typename T >
        constexpr List < T > :: List ( List const & list ) noexcept :
                _size ( list._size ) {

        }

        template < typename T >
        constexpr List < T > :: List ( List && list ) noexcept :
                _size ( cds :: exchange ( list._size, 0ULL ) ) {

        }

    }
}

#endif // __CDS_LIST_IMPL_HPP__
