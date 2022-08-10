//
// Created by loghin on 09/08/22.
//

#ifndef __CDS_EX_SET_IMPL_HPP__
#define __CDS_EX_SET_IMPL_HPP__

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {

        template <
                typename __ElementType,     // NOLINT(bugprone-reserved-identifier)
                cds :: meta :: EnableIf <
                        cds :: experimental :: meta :: isValidSetElement < __ElementType > ()
                > __enabler                 // NOLINT(bugprone-reserved-identifier)
        > constexpr Set <
                __ElementType,
                __enabler
        > :: Set () noexcept = default;


        template <
                typename __ElementType,     // NOLINT(bugprone-reserved-identifier)
                cds :: meta :: EnableIf <
                        cds :: experimental :: meta :: isValidSetElement < __ElementType > ()
                > __enabler                 // NOLINT(bugprone-reserved-identifier)
        > constexpr Set <
                __ElementType,
                __enabler
        > :: Set (
                Set const & set
        ) noexcept :
                CollectionBase ( set ) {

        }


        template <
                typename __ElementType,     // NOLINT(bugprone-reserved-identifier)
                cds :: meta :: EnableIf <
                        cds :: experimental :: meta :: isValidSetElement < __ElementType > ()
                > __enabler                 // NOLINT(bugprone-reserved-identifier)
        > constexpr Set <
                __ElementType,
                __enabler
        > :: Set (
                Set && set
        ) noexcept :
                CollectionBase ( std :: move ( set ) ) {

        }


        template <
                typename __ElementType,     // NOLINT(bugprone-reserved-identifier)
                cds :: meta :: EnableIf <
                        cds :: experimental :: meta :: isValidSetElement < __ElementType > ()
                > __enabler                 // NOLINT(bugprone-reserved-identifier)
        > __CDS_cpplang_ConstexprDestructor Set <
                __ElementType,
                __enabler
        > :: ~Set () noexcept = default;


        template <
                typename __ElementType,     // NOLINT(bugprone-reserved-identifier)
                cds :: meta :: EnableIf <
                        cds :: experimental :: meta :: isValidSetElement < __ElementType > ()
                > __enabler                 // NOLINT(bugprone-reserved-identifier)
        > auto Set <
                __ElementType,
                __enabler
        > :: toString () const noexcept -> String {

            if ( this->empty() ) {
                return {"{}"};
            }

            std::stringstream out;
            out << "{ ";

            for ( auto iterator = this->begin(), end = this->end(); iterator != end; ++ iterator ) {

                cds :: meta :: print ( out, * iterator ) << ", ";
            }

            auto asString = out.str();

            asString [ asString.length() - 2U ] = ' ';
            asString [ asString.length() - 1U ] = '}';

            return asString;
        }

    }
}

#endif // __CDS_EX_SET_IMPL_HPP__
