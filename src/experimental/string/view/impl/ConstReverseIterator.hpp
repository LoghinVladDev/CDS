//
// Created by loghin on 6/4/22.
//

#ifndef __CDS_EX_STRING_VIEW_BASE_CONST_REVERSE_ITERATOR_IMPL_HPP__
#define __CDS_EX_STRING_VIEW_BASE_CONST_REVERSE_ITERATOR_IMPL_HPP__

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental { // NOLINT(modernize-concat-nested-namespaces)
        namespace hidden { // NOLINT(modernize-concat-nested-namespaces)
            namespace impl {

                template < typename CharType >
                constexpr BaseStringView < CharType > :: ConstReverseIterator :: ConstReverseIterator (
                        BaseStringView < CharType > const * pString,
                        Index                               index
                ) noexcept :
                        AbstractConstIterator (
                                pString,
                                index,
                                true
                        ) {

                }

                template < typename CharType >
                constexpr BaseStringView < CharType > :: ConstReverseIterator :: ConstReverseIterator (
                        ConstReverseIterator && iterator
                ) noexcept :
                        AbstractConstIterator ( std :: move ( iterator ) ) {

                }

                template < typename CharType >
                __CDS_cpplang_NonConstConstexprMemberFunction auto BaseStringView < CharType > :: ConstReverseIterator :: operator = (
                        ConstReverseIterator const & iterator
                ) noexcept -> ConstReverseIterator & {

                    return reinterpret_cast < ConstReverseIterator & > ( this-> AbstractConstIterator :: operator = ( iterator ) );  // NOLINT(misc-unconventional-assign-operator)
                }

                template < typename CharType >
                __CDS_cpplang_NonConstConstexprMemberFunction auto BaseStringView < CharType > :: ConstReverseIterator :: operator = (
                        ConstReverseIterator && iterator
                ) noexcept -> ConstReverseIterator & {

                    return reinterpret_cast < ConstReverseIterator & > ( this-> AbstractConstIterator :: operator = ( std :: move ( iterator ) ) );  // NOLINT(misc-unconventional-assign-operator)
                }

                template < typename CharType >
                constexpr auto BaseStringView < CharType > :: ConstReverseIterator :: operator ++ () noexcept -> ConstReverseIterator & {

                    return reinterpret_cast < ConstReverseIterator & > ( this->next() );
                }

                template < typename CharType >
                __CDS_cpplang_ConstexprNonLiteralReturn auto BaseStringView < CharType > :: ConstReverseIterator :: operator ++ (
                        int
                ) noexcept -> ConstReverseIterator {

                    auto copy = * this;
                    (void) this->next();
                    return copy;
                }

                template < typename CharType >
                constexpr auto BaseStringView < CharType > :: ConstReverseIterator :: operator -- () noexcept -> ConstReverseIterator & {

                    return reinterpret_cast < ConstReverseIterator & > ( this->previous() );
                }

                template < typename CharType >
                __CDS_cpplang_ConstexprNonLiteralReturn auto BaseStringView < CharType > :: ConstReverseIterator :: operator -- (
                        int
                ) noexcept -> ConstReverseIterator {

                    auto copy = * this;
                    (void) this->previous();
                    return copy;
                }

                template < typename CharType >
                constexpr auto BaseStringView < CharType > :: ConstReverseIterator :: operator * () const noexcept -> CharType {

                    return this->value();
                }

                template < typename CharType >
                constexpr auto BaseStringView < CharType > :: ConstReverseIterator :: operator == (
                        ConstReverseIterator const & iterator
                ) const noexcept -> bool {

                    return this->equals ( iterator );
                }

                template < typename CharType >
                constexpr auto BaseStringView < CharType > :: ConstReverseIterator :: operator != (
                        ConstReverseIterator const & iterator
                ) const noexcept -> bool {

                    return ! this->equals ( iterator );
                }

            }
        }
    }
}

#endif // __CDS_EX_STRING_VIEW_BASE_CONST_REVERSE_ITERATOR_IMPL_HPP__
