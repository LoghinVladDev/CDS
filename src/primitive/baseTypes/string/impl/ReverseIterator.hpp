//
// Created by loghin on 6/4/22.
//

#ifndef __CDS_STRING_BASE_REVERSE_ITERATOR_IMPL_HPP__
#define __CDS_STRING_BASE_REVERSE_ITERATOR_IMPL_HPP__

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace __hidden { // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier)
        namespace __impl { // NOLINT(bugprone-reserved-identifier)

            template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
            constexpr __BaseString < __CharType > :: ReverseIterator :: ReverseIterator (
                    __BaseString < __CharType >   * pString,
                    Index                           index
            ) noexcept :
                    AbstractIterator (
                            pString,
                            index,
                            false
                    ) {

            }

            template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
            constexpr __BaseString < __CharType > :: ReverseIterator :: ReverseIterator (
                    ReverseIterator && iterator
            ) noexcept :
                    AbstractIterator ( std :: move ( iterator ) ) {

            }

            template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
            __CDS_cpplang_NonConstConstexprMemberFunction auto __BaseString < __CharType > :: ReverseIterator :: operator = (
                    ReverseIterator const & iterator
            ) noexcept -> ReverseIterator & {

                return reinterpret_cast < ReverseIterator & > ( this-> AbstractIterator :: operator = ( iterator ) );  // NOLINT(misc-unconventional-assign-operator)
            }

            template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
            __CDS_cpplang_NonConstConstexprMemberFunction auto __BaseString < __CharType > :: ReverseIterator :: operator = (
                    ReverseIterator && iterator
            ) noexcept -> ReverseIterator & {

                return reinterpret_cast < ReverseIterator & > ( this-> AbstractIterator :: operator = ( std :: move ( iterator ) ) );  // NOLINT(misc-unconventional-assign-operator)
            }

            template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
            __CDS_cpplang_NonConstConstexprMemberFunction auto __BaseString < __CharType > :: ReverseIterator :: operator ++ () noexcept -> ReverseIterator & {

                return reinterpret_cast < ReverseIterator & > ( this->next() );
            }

            template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
            __CDS_cpplang_ConstexprNonLiteralReturn auto __BaseString < __CharType > :: ReverseIterator :: operator ++ (
                    int
            ) noexcept -> ReverseIterator {

                auto copy = * this;
                (void) this->next();
                return copy;
            }

            template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
            __CDS_cpplang_NonConstConstexprMemberFunction auto __BaseString < __CharType > :: ReverseIterator :: operator -- () noexcept -> ReverseIterator & {

                return reinterpret_cast < ReverseIterator & > ( this->previous() );
            }

            template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
            __CDS_cpplang_ConstexprNonLiteralReturn auto __BaseString < __CharType > :: ReverseIterator :: operator -- (
                    int
            ) noexcept -> ReverseIterator {

                auto copy = * this;
                (void) this->previous();
                return copy;
            }

            template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
            constexpr auto __BaseString < __CharType > :: ReverseIterator :: operator * () const noexcept -> __CharType & {

                return this->value();
            }

            template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
            constexpr auto __BaseString < __CharType > :: ReverseIterator :: operator == (
                    ReverseIterator const & iterator
            ) const noexcept -> bool {

                return this->equals ( iterator );
            }

            template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
            constexpr auto __BaseString < __CharType > :: ReverseIterator :: operator != (
                    ReverseIterator const & iterator
            ) const noexcept -> bool {

                return ! this->equals ( iterator );
            }

        }
    }
}

#endif // __CDS_STRING_BASE_REVERSE_ITERATOR_IMPL_HPP__
