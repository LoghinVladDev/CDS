//
// Created by loghin on 6/9/22.
//

#ifndef __CDS_BASE_STRING_NON_EXCEPTION_HPP__
#define __CDS_BASE_STRING_NON_EXCEPTION_HPP__

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace __hidden { // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier)
        namespace __impl { // NOLINT(bugprone-reserved-identifier)

            template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
            __CDS_cpplang_ConstexprConditioned auto __BaseString < __CharType > :: operator == (
                    __BaseString const & string
            ) const noexcept -> bool {

                return __BaseStringView < __CharType > ( * this ) == __BaseStringView < __CharType > ( string );
            }


            template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
            __CDS_cpplang_ConstexprConditioned auto __BaseString < __CharType > :: operator != (
                    __BaseString const & string
            ) const noexcept -> bool {

                return __BaseStringView < __CharType > ( * this ) != __BaseStringView < __CharType > ( string );
            }

        }
    }
}

#endif //__CDS_BASE_STRING_NON_EXCEPTION_HPP__
