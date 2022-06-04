//
// Created by loghin on 6/4/22.
//

#ifndef __CDS_EX_BASE_STRING_VIEW_IMPL_HPP__
#define __CDS_EX_BASE_STRING_VIEW_IMPL_HPP__


namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {
        namespace hidden {
            namespace impl {

                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned BaseStringView < CharType > :: BaseStringView (
                        ElementType const * pString
                ) noexcept :
                        _pData ( pString ),
                        _length ( pString == nullptr ? 0ULL : StringUtils < CharType > :: length ( pString ) ) {

                }

            }
        }
    }
}


#endif // __CDS_EX_BASE_STRING_VIEW_IMPL_HPP__
