/* NOLINT(llvm-header-guard)
 * Created by loghin on 6/27/22.
 */

#ifndef __CDS_LIST_IMPL_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_LIST_IMPL_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

namespace cds {

    template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    Index const List < __ElementType > :: invalidIndex;


    template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    constexpr List < __ElementType > :: List () noexcept = default;


    template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    constexpr List < __ElementType > :: List (
            List const & list
    ) noexcept = default;


    template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    constexpr List < __ElementType > :: List (
            List && list
    ) noexcept = default;


    template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    __CDS_cpplang_ConstexprDestructor List < __ElementType > :: ~List () noexcept = default;


    template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    auto List < __ElementType > :: toString () const noexcept -> String {

        /* List represented by values enclosed in square brackets. If Empty, return bracket set */
        if ( this->empty() ) {
            return {"[]"};
        }

        /* use a StringStream to output the contents for maximum compatibility. Start with open bracket */
        std::stringstream out;
        out << "[ ";

        /* iterate through Set and append iterator value to Stream */
        for ( auto iterator = this->begin(), end = this->end(); iterator != end; ++ iterator ) { /* NOLINT(clion-misra-cpp2008-8-0-1) */
            cds :: meta :: print ( out, * iterator ) << ", ";
        }

        /* transform to std string */
        auto asString = out.str();

        /* replace ", " with " ]" */
        asString [ asString.length() - 2U ] = ' ';
        asString [ asString.length() - 1U ] = ']';

        /* return std :: string to be reused as cds :: String */
        return asString;
    }


    template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto List < __ElementType > :: circularAdjustedIndex (
            Index index
    ) const noexcept -> Index {

        /* if given negative index, wrap to the nearest positive index by skipping minimum no. of 'size' blocks */
        if ( index < 0 ) {
            index += ( ( - index ) / this->size() + 1 ) * this->size();
        }

        /* if greater than size, use remainder. */
        if ( index >= static_cast < Index > ( this->size() ) ) {
            index = index % this->size();
        }

        /* return bounded index */
        return index;
    }

} /* namespace cds */

#endif /* __CDS_LIST_IMPL_HPP__ */
