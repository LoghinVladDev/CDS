//
// Created by loghin on 6/4/22.
//

#ifndef __CDS_STRING_VIEW_BASE_CONST_REVERSE_ITERATOR_IMPL_HPP__
#define __CDS_STRING_VIEW_BASE_CONST_REVERSE_ITERATOR_IMPL_HPP__

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace __hidden { // NOLINT(modernize-concat-nested-namespaces)
        namespace __impl {

            template < typename __CharType >
            constexpr __BaseStringView < __CharType > :: ConstReverseIterator :: ConstReverseIterator (
                    __BaseStringView < __CharType > const * pString,
                    Index                                   index
            ) noexcept :
                    AbstractConstIterator (
                            pString,
                            index,
                            false
                    ) {

            }

            template < typename __CharType >
            constexpr __BaseStringView < __CharType > :: ConstReverseIterator :: ConstReverseIterator (
                    ConstReverseIterator && iterator
            ) noexcept :
                    AbstractConstIterator ( std :: move ( iterator ) ) {

            }

            template < typename __CharType >
            __CDS_cpplang_NonConstConstexprMemberFunction auto __BaseStringView < __CharType > :: ConstReverseIterator :: operator = (
                    ConstReverseIterator const & iterator
            ) noexcept -> ConstReverseIterator & {

                return reinterpret_cast < ConstReverseIterator & > ( this-> AbstractConstIterator :: operator = ( iterator ) );  // NOLINT(misc-unconventional-assign-operator)
            }

            template < typename __CharType >
            __CDS_cpplang_NonConstConstexprMemberFunction auto __BaseStringView < __CharType > :: ConstReverseIterator :: operator = (
                    ConstReverseIterator && iterator
            ) noexcept -> ConstReverseIterator & {

                return reinterpret_cast < ConstReverseIterator & > ( this-> AbstractConstIterator :: operator = ( std :: move ( iterator ) ) );  // NOLINT(misc-unconventional-assign-operator)
            }

            template < typename __CharType >
            __CDS_cpplang_NonConstConstexprMemberFunction auto __BaseStringView < __CharType > :: ConstReverseIterator :: operator ++ () noexcept -> ConstReverseIterator & {

                return reinterpret_cast < ConstReverseIterator & > ( this->next() );
            }

            template < typename __CharType >
            __CDS_cpplang_ConstexprNonLiteralReturn auto __BaseStringView < __CharType > :: ConstReverseIterator :: operator ++ (
                    int
            ) noexcept -> ConstReverseIterator {

                auto copy = * this;
                (void) this->next();
                return copy;
            }

            template < typename __CharType >
            __CDS_cpplang_NonConstConstexprMemberFunction auto __BaseStringView < __CharType > :: ConstReverseIterator :: operator -- () noexcept -> ConstReverseIterator & {

                return reinterpret_cast < ConstReverseIterator & > ( this->previous() );
            }

            template < typename __CharType >
            __CDS_cpplang_ConstexprNonLiteralReturn auto __BaseStringView < __CharType > :: ConstReverseIterator :: operator -- (
                    int
            ) noexcept -> ConstReverseIterator {

                auto copy = * this;
                (void) this->previous();
                return copy;
            }

            template < typename __CharType >
            constexpr auto __BaseStringView < __CharType > :: ConstReverseIterator :: operator * () const noexcept -> __CharType {

                return this->value();
            }

            template < typename __CharType >
            constexpr auto __BaseStringView < __CharType > :: ConstReverseIterator :: operator == (
                    ConstReverseIterator const & iterator
            ) const noexcept -> bool {

                return this->equals ( iterator );
            }

            template < typename __CharType >
            constexpr auto __BaseStringView < __CharType > :: ConstReverseIterator :: operator != (
                    ConstReverseIterator const & iterator
            ) const noexcept -> bool {

                return ! this->equals ( iterator );
            }

        }
    }
}

#endif // __CDS_STRING_VIEW_BASE_CONST_REVERSE_ITERATOR_IMPL_HPP__
