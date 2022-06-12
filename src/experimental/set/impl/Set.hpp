//
// Created by loghin on 6/3/22.
//

#ifndef __CDS_EX_SET_IMPL_HPP__
#define __CDS_EX_SET_IMPL_HPP__

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {


        template < typename __ElementType, cds :: meta :: EnableIf < meta :: isValidSetElement < __ElementType > () > __enabler > // NOLINT(bugprone-reserved-identifier)
        auto Set < __ElementType, __enabler > :: toString () const noexcept -> String {

            if ( this->empty() ) {
                return "{}";
            }

            std :: stringstream out;
            out << "{ ";

            for ( auto iterator = this->begin(), end = this->end(); iterator != end; ++ iterator ) {
                cds :: meta :: print ( out, * iterator );
            }

            auto asString = out.str();
            return asString.substr ( 0, asString.length() - 2 ) + " }";
        }


        template < typename __ElementType, cds :: meta :: EnableIf < meta :: isValidSetElement < __ElementType > () > __enabler > // NOLINT(bugprone-reserved-identifier)
        template < typename __VElementType, cds :: meta :: EnableIf < cds :: meta :: isCopyConstructible < __VElementType > () > > // NOLINT(bugprone-reserved-identifier)
        auto Set < __ElementType, __enabler > :: insert (
                ElementType const & element
        ) noexcept -> void {

            this->add ( element );
        }


        template < typename __ElementType, cds :: meta :: EnableIf < meta :: isValidSetElement < __ElementType > () > __enabler > // NOLINT(bugprone-reserved-identifier)
        template < typename __VElementType, cds :: meta :: EnableIf < cds :: meta :: isMoveConstructible < __VElementType > () > > // NOLINT(bugprone-reserved-identifier)
        auto Set < __ElementType, __enabler > :: insert (
                ElementType && element
        ) noexcept -> void {

            this->add ( std :: move ( element ) );
        }


    }
}

#endif // __CDS_EX_SET_IMPL_HPP__
