//
// Created by loghin on 6/27/22.
//

#ifndef __CDS_EX_LIST_IMPL_HPP__
#define __CDS_EX_LIST_IMPL_HPP__

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {

        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr List < __ElementType > :: List () noexcept = default;


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr List < __ElementType > :: List (
                List const & list
        ) noexcept = default;


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr List < __ElementType > :: List (
                List && list
        ) noexcept = default;


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_cpplang_ConstexprDestructor List < __ElementType > :: ~List () noexcept = default;


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        auto List < __ElementType > :: toString () const noexcept -> String {

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

#endif // __CDS_EX_LIST_IMPL_HPP__