//
// Created by loghin on 6/4/22.
//

#ifndef __CDS_EX_STRING_BASE_ITERATOR_IMPL_HPP__
#define __CDS_EX_STRING_BASE_ITERATOR_IMPL_HPP__

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental { // NOLINT(modernize-concat-nested-namespaces)
        namespace hidden { // NOLINT(modernize-concat-nested-namespaces)
            namespace impl {

                template < typename CharType >
                constexpr BaseString < CharType > :: Iterator :: Iterator (
                        BaseString < CharType >   * pString,
                        Index                       index
                ) noexcept :
                        AbstractIterator (
                                pString,
                                index,
                                true
                        ) {

                }

                template < typename CharType >
                constexpr BaseString < CharType > :: Iterator :: Iterator (
                        Iterator && iterator
                ) noexcept :
                        AbstractIterator ( std :: move ( iterator ) ) {

                }

                template < typename CharType >
                __CDS_cpplang_NonConstConstexprMemberFunction auto BaseString < CharType > :: Iterator :: operator = (
                        Iterator const & iterator
                ) noexcept -> Iterator & {

                    return reinterpret_cast < Iterator & > ( this-> AbstractIterator :: operator = ( iterator ) );  // NOLINT(misc-unconventional-assign-operator)
                }

                template < typename CharType >
                __CDS_cpplang_NonConstConstexprMemberFunction auto BaseString < CharType > :: Iterator :: operator = (
                        Iterator && iterator
                ) noexcept -> Iterator & {

                    return reinterpret_cast < Iterator & > ( this-> AbstractIterator :: operator = ( std :: move ( iterator ) ) );  // NOLINT(misc-unconventional-assign-operator)
                }

                template < typename CharType >
                constexpr auto BaseString < CharType > :: Iterator :: operator ++ () noexcept -> Iterator & {

                    return reinterpret_cast < Iterator & > ( this->next() );
                }

                template < typename CharType >
                __CDS_cpplang_ConstexprNonLiteralReturn auto BaseString < CharType > :: Iterator :: operator ++ (
                        int
                ) noexcept -> Iterator {

                    auto copy = * this;
                    (void) this->next();
                    return copy;
                }

                template < typename CharType >
                constexpr auto BaseString < CharType > :: Iterator :: operator -- () noexcept -> Iterator & {

                    return reinterpret_cast < Iterator & > ( this->previous() );
                }

                template < typename CharType >
                __CDS_cpplang_ConstexprNonLiteralReturn auto BaseString < CharType > :: Iterator :: operator -- (
                        int
                ) noexcept -> Iterator {

                    auto copy = * this;
                    (void) this->previous();
                    return copy;
                }

                template < typename CharType >
                constexpr auto BaseString < CharType > :: Iterator :: operator * () const noexcept -> CharType & {

                    return this->value();
                }

                template < typename CharType >
                constexpr auto BaseString < CharType > :: Iterator :: operator == (
                        Iterator const & iterator
                ) const noexcept -> bool {

                    return this->equals ( iterator );
                }

                template < typename CharType >
                constexpr auto BaseString < CharType > :: Iterator :: operator != (
                        Iterator const & iterator
                ) const noexcept -> bool {

                    return ! this->equals ( iterator );
                }

            }
        }
    }
}

#endif // __CDS_EX_STRING_BASE_ITERATOR_IMPL_HPP__
