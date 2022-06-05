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
                Index const BaseStringView < CharType > :: invalidIndex = StringUtils < CharType > :: invalidIndex;


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned BaseStringView < CharType > :: BaseStringView (
                        ElementType const * pString
                ) noexcept :
                        _pData ( pString ),
                        _length ( pString == nullptr ? 0ULL : StringUtils < CharType > :: length ( pString ) ) {

                }


                template < typename CharType >
                constexpr auto BaseStringView < CharType > :: length () const noexcept -> Size {

                    return this->_length;
                }


                template < typename CharType >
                constexpr auto BaseStringView < CharType > :: size () const noexcept -> Size {

                    return this->length();
                }


                template < typename CharType >
                constexpr auto BaseStringView < CharType > :: empty () const noexcept -> bool {

                    return this->_length == 0ULL;
                }


                template < typename CharType >
                constexpr auto BaseStringView < CharType > :: cStr () const noexcept -> ElementType const * {

                    return this->_pData;
                }


                template < typename CharType >
                constexpr auto BaseStringView < CharType > :: data () const noexcept -> ElementType const * {

                    return this->_pData;
                }


                template < typename CharType >
                constexpr BaseStringView < CharType > :: operator ElementType const * () const noexcept {

                    return this->_pData;
                }

            }
        }
    }
}


#endif // __CDS_EX_BASE_STRING_VIEW_IMPL_HPP__
