//
// Created by loghin on 6/4/22.
//

#ifndef __CDS_EX_STRING_BASE_CONST_ITERATOR_IMPL_HPP__
#define __CDS_EX_STRING_BASE_CONST_ITERATOR_IMPL_HPP__

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental { // NOLINT(modernize-concat-nested-namespaces)
        namespace hidden { // NOLINT(modernize-concat-nested-namespaces)
            namespace impl {

                template < typename CharType >
                constexpr BaseString < CharType > :: ConstIterator :: ConstIterator (
                        BaseString < CharType > const * pString,
                        Index                           index
                ) noexcept :
                        AbstractConstIterator (
                                pString,
                                index,
                                true
                        ) {

                }

                template < typename CharType >
                constexpr BaseString < CharType > :: ConstIterator :: ConstIterator (
                        ConstIterator && iterator
                ) noexcept :
                        AbstractConstIterator ( std :: move ( iterator ) ) {

                }

                template < typename CharType >
                __CDS_cpplang_NonConstConstexprMemberFunction auto BaseString < CharType > :: ConstIterator :: operator = (
                        ConstIterator const & iterator
                ) noexcept -> ConstIterator & {

                    return reinterpret_cast < ConstIterator & > ( this-> AbstractConstIterator :: operator = ( iterator ) );  // NOLINT(misc-unconventional-assign-operator)
                }

                template < typename CharType >
                __CDS_cpplang_NonConstConstexprMemberFunction auto BaseString < CharType > :: ConstIterator :: operator = (
                        ConstIterator && iterator
                ) noexcept -> ConstIterator & {

                    return reinterpret_cast < ConstIterator & > ( this-> AbstractConstIterator :: operator = ( std :: move ( iterator ) ) );  // NOLINT(misc-unconventional-assign-operator)
                }

                template < typename CharType >
                __CDS_cpplang_NonConstConstexprMemberFunction auto BaseString < CharType > :: ConstIterator :: operator ++ () noexcept -> ConstIterator & {

                    return reinterpret_cast < ConstIterator & > ( this->next() );
                }

                template < typename CharType >
                __CDS_cpplang_ConstexprNonLiteralReturn auto BaseString < CharType > :: ConstIterator :: operator ++ (
                        int
                ) noexcept -> ConstIterator {

                    auto copy = * this;
                    (void) this->next();
                    return copy;
                }

                template < typename CharType >
                __CDS_cpplang_NonConstConstexprMemberFunction auto BaseString < CharType > :: ConstIterator :: operator -- () noexcept -> ConstIterator & {

                    return reinterpret_cast < ConstIterator & > ( this->previous() );
                }

                template < typename CharType >
                __CDS_cpplang_ConstexprNonLiteralReturn auto BaseString < CharType > :: ConstIterator :: operator -- (
                        int
                ) noexcept -> ConstIterator {

                    auto copy = * this;
                    (void) this->previous();
                    return copy;
                }

                template < typename CharType >
                constexpr auto BaseString < CharType > :: ConstIterator :: operator * () const noexcept -> CharType {

                    return this->value();
                }

                template < typename CharType >
                constexpr auto BaseString < CharType > :: ConstIterator :: operator == (
                        ConstIterator const & iterator
                ) const noexcept -> bool {

                    return this->equals ( iterator );
                }

                template < typename CharType >
                constexpr auto BaseString < CharType > :: ConstIterator :: operator != (
                        ConstIterator const & iterator
                ) const noexcept -> bool {

                    return ! this->equals ( iterator );
                }

            }
        }
    }
}

#endif // __CDS_EX_STRING_BASE_CONST_ITERATOR_IMPL_HPP__
