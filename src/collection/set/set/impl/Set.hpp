//
// Created by loghin on 6/3/22.
//

#ifndef __CDS_SET_IMPL_HPP__
#define __CDS_SET_IMPL_HPP__

namespace cds {

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
    __CDS_OptimalInline auto Set < __ElementType, __enabler > :: remove (
            ElementType const & element
    ) noexcept -> bool {

        return this->removeFirst ( element );
    }


    template < typename __ElementType, cds :: meta :: EnableIf < meta :: isValidSetElement < __ElementType > () > __enabler > // NOLINT(bugprone-reserved-identifier)
    template < typename __VElementType, cds :: meta :: EnableIf < cds :: meta :: isCopyConstructible < __VElementType > () > > // NOLINT(bugprone-reserved-identifier)
    auto Set < __ElementType, __enabler > :: insert (
            ElementType const & element
    ) noexcept -> void {

        auto pElementLocation = this->pNewInsert ( element );
        if ( pElementLocation != nullptr ) {
            new ( pElementLocation ) ElementType ( element );
        }
    }


    template < typename __ElementType, cds :: meta :: EnableIf < meta :: isValidSetElement < __ElementType > () > __enabler > // NOLINT(bugprone-reserved-identifier)
    template < typename __VElementType, cds :: meta :: EnableIf < cds :: meta :: isMoveConstructible < __VElementType > () > > // NOLINT(bugprone-reserved-identifier)
    auto Set < __ElementType, __enabler > :: insert (
            ElementType && element
    ) noexcept -> void {

        auto pElementLocation = this->pNewInsert ( element );
        if ( pElementLocation != nullptr ) {
            new ( pElementLocation ) ElementType ( std :: move ( element ) );
        }
    }

}

#endif // __CDS_SET_IMPL_HPP__
