//
// Created by loghin on 6/3/22.
//

#ifndef __CDS_EX_SET_IMPL_HPP__
#define __CDS_EX_SET_IMPL_HPP__

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {

        template < typename __ElementType, cds :: meta :: EnableIf < meta :: isValidSetElement < __ElementType > () > __enabler > // NOLINT(bugprone-reserved-identifier)
        constexpr Set < __ElementType, __enabler > :: Set (
                Set const & set
        ) noexcept :
                Collection < __ElementType > ( set ) {

        }


        template < typename __ElementType, cds :: meta :: EnableIf < meta :: isValidSetElement < __ElementType > () > __enabler > // NOLINT(bugprone-reserved-identifier)
        constexpr Set < __ElementType, __enabler > :: Set (
                Set && set
        ) noexcept :
                Collection < __ElementType > ( std :: move ( set ) ) {

        }


        template < typename __ElementType, cds :: meta :: EnableIf < meta :: isValidSetElement < __ElementType > () > __enabler > // NOLINT(bugprone-reserved-identifier)
        constexpr Set < __ElementType, __enabler > :: Set (
                Size size
        ) noexcept :
                Collection < __ElementType > ( size ) {

        }


        template < typename __ElementType, cds :: meta :: EnableIf < meta :: isValidSetElement < __ElementType > () > __enabler > // NOLINT(bugprone-reserved-identifier)
        auto Set < __ElementType, __enabler > :: toString () const noexcept -> String {

            if ( this->empty() ) {
                return "{}";
            }

            std :: stringstream out;
            out << "{ ";

            for ( auto iterator = this->begin(), end = this->end(); iterator != end; ++ iterator ) {
                cds :: meta :: print ( out, * iterator ) << ", ";
            }

            auto asString = out.str();

            asString [ asString.length() - 2U ] = ' ';
            asString [ asString.length() - 1U ] = '}';

            return asString;
        }


        template < typename __ElementType, cds :: meta :: EnableIf < meta :: isValidSetElement < __ElementType > () > __enabler > // NOLINT(bugprone-reserved-identifier)
        template < typename __VElementType, cds :: meta :: EnableIf < cds :: meta :: isCopyConstructible < __VElementType > () > > // NOLINT(bugprone-reserved-identifier)
        auto Set < __ElementType, __enabler > :: insert (
                ElementType const & element
        ) noexcept -> ElementType const & {

            auto & pElementLocation = this->pNewInsert ( element );
            if ( pElementLocation == nullptr ) {
                pElementLocation = Memory :: instance().create < ElementType > ( element );
                this->pNewInsertPost();
            }

            return * pElementLocation;
        }


        template < typename __ElementType, cds :: meta :: EnableIf < meta :: isValidSetElement < __ElementType > () > __enabler > // NOLINT(bugprone-reserved-identifier)
        template < typename __VElementType, cds :: meta :: EnableIf < cds :: meta :: isMoveConstructible < __VElementType > () > > // NOLINT(bugprone-reserved-identifier)
        auto Set < __ElementType, __enabler > :: insert (
                ElementType && element
        ) noexcept -> ElementType const & {

            auto & pElementLocation = this->pNewInsert ( element );
            if ( pElementLocation == nullptr ) {
                pElementLocation = Memory :: instance().create < ElementType > ( std :: move ( element ) );
                this->pNewInsertPost();
            }

            return * pElementLocation;
        }


    }
}

#endif // __CDS_EX_SET_IMPL_HPP__
