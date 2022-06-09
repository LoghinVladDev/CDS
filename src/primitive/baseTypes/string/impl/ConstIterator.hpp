//
// Created by loghin on 6/4/22.
//

#ifndef __CDS_STRING_BASE_CONST_ITERATOR_IMPL_HPP__
#define __CDS_STRING_BASE_CONST_ITERATOR_IMPL_HPP__

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace __hidden { // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier)
        namespace __impl { // NOLINT(bugprone-reserved-identifier)

            template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
            constexpr __BaseString < __CharType > :: ConstIterator :: ConstIterator (
                    __BaseString < __CharType > const * pString,
                    Index                               index
            ) noexcept :
                    AbstractConstIterator (
                            pString,
                            index,
                            true
                    ) {

            }

            template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
            constexpr __BaseString < __CharType > :: ConstIterator :: ConstIterator (
                    ConstIterator && iterator
            ) noexcept :
                    AbstractConstIterator ( std :: move ( iterator ) ) {

            }

            template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
            __CDS_cpplang_NonConstConstexprMemberFunction auto __BaseString < __CharType > :: ConstIterator :: operator = (
                    ConstIterator const & iterator
            ) noexcept -> ConstIterator & {

                return reinterpret_cast < ConstIterator & > ( this-> AbstractConstIterator :: operator = ( iterator ) );  // NOLINT(misc-unconventional-assign-operator)
            }

            template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
            __CDS_cpplang_NonConstConstexprMemberFunction auto __BaseString < __CharType > :: ConstIterator :: operator = (
                    ConstIterator && iterator
            ) noexcept -> ConstIterator & {

                return reinterpret_cast < ConstIterator & > ( this-> AbstractConstIterator :: operator = ( std :: move ( iterator ) ) );  // NOLINT(misc-unconventional-assign-operator)
            }

            template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
            __CDS_cpplang_NonConstConstexprMemberFunction auto __BaseString < __CharType > :: ConstIterator :: operator ++ () noexcept -> ConstIterator & {

                return reinterpret_cast < ConstIterator & > ( this->next() );
            }

            template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
            __CDS_cpplang_ConstexprNonLiteralReturn auto __BaseString < __CharType > :: ConstIterator :: operator ++ (
                    int
            ) noexcept -> ConstIterator {

                auto copy = * this;
                (void) this->next();
                return copy;
            }

            template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
            __CDS_cpplang_NonConstConstexprMemberFunction auto __BaseString < __CharType > :: ConstIterator :: operator -- () noexcept -> ConstIterator & {

                return reinterpret_cast < ConstIterator & > ( this->previous() );
            }

            template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
            __CDS_cpplang_ConstexprNonLiteralReturn auto __BaseString < __CharType > :: ConstIterator :: operator -- (
                    int
            ) noexcept -> ConstIterator {

                auto copy = * this;
                (void) this->previous();
                return copy;
            }

            template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
            constexpr auto __BaseString < __CharType > :: ConstIterator :: operator * () const noexcept -> __CharType {

                return this->value();
            }

            template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
            constexpr auto __BaseString < __CharType > :: ConstIterator :: operator == (
                    ConstIterator const & iterator
            ) const noexcept -> bool {

                return this->equals ( iterator );
            }

            template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
            constexpr auto __BaseString < __CharType > :: ConstIterator :: operator != (
                    ConstIterator const & iterator
            ) const noexcept -> bool {

                return ! this->equals ( iterator );
            }

        }
    }
}

#endif // __CDS_STRING_BASE_CONST_ITERATOR_IMPL_HPP__
