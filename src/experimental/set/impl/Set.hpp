//
// Created by loghin on 6/3/22.
//

#ifndef __CDS_EX_SET_IMPL_HPP__
#define __CDS_EX_SET_IMPL_HPP__

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {

        template < typename T, meta :: EnableIf < meta :: isValidSetElement < T > () > enabler >
        auto Set < T, enabler > :: toString () const noexcept -> String {

            if ( this->empty() ) {
                return "{}";
            }

            std :: stringstream out;
            out << "{ ";

            for ( auto iterator = this->begin(), end = this->end(); iterator != end; ++ iterator ) {
                meta :: print ( out, * iterator );
            }

            auto asString = out.str();
            return asString.substr ( 0, asString.length() - 2 ) + " }";
        }

        template < typename T, meta :: EnableIf < meta :: isValidSetElement < T > () > enabler >
        template < typename V, meta :: EnableIf < meta :: isCopyConstructible < V > () > >
        auto Set < T, enabler > :: insert (
                ElementType const & element
        ) noexcept -> void {

            this->add ( element );
        }

        template < typename T, meta :: EnableIf < meta :: isValidSetElement < T > () > enabler >
        template < typename V, meta :: EnableIf < meta :: isMoveConstructible < V > () > >
        auto Set < T, enabler > :: insert (
                ElementType && element
        ) noexcept -> void {

            this->add ( std :: move ( element ) );
        }

    }
}

#endif // __CDS_EX_SET_IMPL_HPP__
