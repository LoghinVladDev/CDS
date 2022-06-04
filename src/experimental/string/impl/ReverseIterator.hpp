//
// Created by loghin on 6/4/22.
//

#ifndef __CDS_EX_STRING_BASE_REVERSE_ITERATOR_IMPL_HPP__
#define __CDS_EX_STRING_BASE_REVERSE_ITERATOR_IMPL_HPP__

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental { // NOLINT(modernize-concat-nested-namespaces)
        namespace hidden { // NOLINT(modernize-concat-nested-namespaces)
            namespace impl {

                template < typename CharType >
                constexpr BaseString < CharType > :: ReverseIterator :: ReverseIterator (
                        BaseString < CharType >   * pString,
                        Index                       index
                ) noexcept :
                        AbstractIterator (
                                pString,
                                index,
                                false
                        ) {

                }

                template < typename CharType >
                constexpr BaseString < CharType > :: ReverseIterator :: ReverseIterator (
                        ReverseIterator && iterator
                ) noexcept :
                        AbstractIterator ( std :: move ( iterator ) ) {

                }

                template < typename CharType >
                __CDS_cpplang_NonConstConstexprMemberFunction auto BaseString < CharType > :: ReverseIterator :: operator = (
                        ReverseIterator const & iterator
                ) noexcept -> ReverseIterator & {

                    return reinterpret_cast < ReverseIterator & > ( this-> AbstractIterator :: operator = ( iterator ) );  // NOLINT(misc-unconventional-assign-operator)
                }

                template < typename CharType >
                __CDS_cpplang_NonConstConstexprMemberFunction auto BaseString < CharType > :: ReverseIterator :: operator = (
                        ReverseIterator && iterator
                ) noexcept -> ReverseIterator & {

                    return reinterpret_cast < ReverseIterator & > ( this-> AbstractIterator :: operator = ( std :: move ( iterator ) ) );  // NOLINT(misc-unconventional-assign-operator)
                }

                template < typename CharType >
                constexpr auto BaseString < CharType > :: ReverseIterator :: operator ++ () noexcept -> ReverseIterator & {

                    return reinterpret_cast < ReverseIterator & > ( this->next() );
                }

                template < typename CharType >
                __CDS_cpplang_ConstexprNonLiteralReturn auto BaseString < CharType > :: ReverseIterator :: operator ++ (
                        int
                ) noexcept -> ReverseIterator {

                    auto copy = * this;
                    (void) this->next();
                    return copy;
                }

                template < typename CharType >
                constexpr auto BaseString < CharType > :: ReverseIterator :: operator -- () noexcept -> ReverseIterator & {

                    return reinterpret_cast < ReverseIterator & > ( this->previous() );
                }

                template < typename CharType >
                __CDS_cpplang_ConstexprNonLiteralReturn auto BaseString < CharType > :: ReverseIterator :: operator -- (
                        int
                ) noexcept -> ReverseIterator {

                    auto copy = * this;
                    (void) this->previous();
                    return copy;
                }

                template < typename CharType >
                constexpr auto BaseString < CharType > :: ReverseIterator :: operator * () const noexcept -> CharType & {

                    return this->value();
                }

                template < typename CharType >
                constexpr auto BaseString < CharType > :: ReverseIterator :: operator == (
                        ReverseIterator const & iterator
                ) const noexcept -> bool {

                    return this->equals ( iterator );
                }

                template < typename CharType >
                constexpr auto BaseString < CharType > :: ReverseIterator :: operator != (
                        ReverseIterator const & iterator
                ) const noexcept -> bool {

                    return ! this->equals ( iterator );
                }

            }
        }
    }
}

#endif // __CDS_EX_STRING_BASE_REVERSE_ITERATOR_IMPL_HPP__
