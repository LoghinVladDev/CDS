/*
 * Created by loghin on 09/08/22.
 */

#ifndef __CDS_EX_SET_IMPL_HPP__
#define __CDS_EX_SET_IMPL_HPP__ /* NOLINT(bugprone-reserved-identifier) */

namespace cds { /* NOLINT(modernize-concat-nested-namespaces) */
    namespace experimental {

        template <
                typename __ElementType,     /* NOLINT(bugprone-reserved-identifier) */
                cds :: meta :: EnableIf <
                        cds :: experimental :: meta :: isValidSetElement < __ElementType > ()
                > __enabler                 /* NOLINT(bugprone-reserved-identifier) */
        > constexpr Set <
                __ElementType,
                __enabler
        > :: Set () noexcept = default;


        template <
                typename __ElementType,     /* NOLINT(bugprone-reserved-identifier) */
                cds :: meta :: EnableIf <
                        cds :: experimental :: meta :: isValidSetElement < __ElementType > ()
                > __enabler                 /* NOLINT(bugprone-reserved-identifier) */
        > constexpr Set <
                __ElementType,
                __enabler
        > :: Set (
                Set const & set
        ) noexcept :
                CollectionBase ( set ) {

            /* call base copy constructor */
        }


        template <
                typename __ElementType,     /* NOLINT(bugprone-reserved-identifier) */
                cds :: meta :: EnableIf <
                        cds :: experimental :: meta :: isValidSetElement < __ElementType > ()
                > __enabler                 /* NOLINT(bugprone-reserved-identifier) */
        > constexpr Set <
                __ElementType,
                __enabler
        > :: Set (
                Set && set
        ) noexcept :
                CollectionBase ( std :: move ( set ) ) {

            /* call base move constructor */
        }


        template <
                typename __ElementType,     /* NOLINT(bugprone-reserved-identifier) */
                cds :: meta :: EnableIf <
                        cds :: experimental :: meta :: isValidSetElement < __ElementType > ()
                > __enabler                 /* NOLINT(bugprone-reserved-identifier) */
        > __CDS_cpplang_ConstexprDestructor Set <
                __ElementType,
                __enabler
        > :: ~Set () noexcept = default;


        template <
                typename __ElementType,     /* NOLINT(bugprone-reserved-identifier) */
                cds :: meta :: EnableIf <
                        cds :: experimental :: meta :: isValidSetElement < __ElementType > ()
                > __enabler                 /* NOLINT(bugprone-reserved-identifier) */
        > auto Set <
                __ElementType,
                __enabler
        > :: toString () const noexcept -> String {

            /* Set toString representation is curly-brackets enclosed list */
            /* if empty, return empty list */
            if ( this->empty() ) {
                return {"{}"};
            }

            /* use a StringStream to output the contents for maximum compatibility. Start with open bracket */
            std::stringstream out;
            out << "{ ";

            /* iterate through Set and append iterator value to Stream */
            for ( auto iterator = this->begin(), end = this->end(); iterator != end; ++ iterator ) {
                cds :: meta :: print ( out, * iterator ) << ", ";
            }

            /* transform to std string */
            auto asString = out.str();

            /* replace ", " with " }" */
            asString [ asString.length() - 2U ] = ' ';
            asString [ asString.length() - 1U ] = '}';

            /* return std :: string to be reused as cds :: String */
            return asString;
        }

    }
}

#endif /* __CDS_EX_SET_IMPL_HPP__ */
