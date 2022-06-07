//
// Created by loghin on 6/4/22.
//

#ifndef __CDS_EX_STRING_BASE_ITERATOR_HPP__
#define __CDS_EX_STRING_BASE_ITERATOR_HPP__

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental { // NOLINT(modernize-concat-nested-namespaces)
        namespace hidden { // NOLINT(modernize-concat-nested-namespaces)
            namespace impl {

                template < typename CharType >
                class BaseString < CharType > :: Iterator : public AbstractIterator {

                public:
                    constexpr Iterator (
                            BaseString < CharType >   * pString,
                            Index                       index
                    ) noexcept;

                public:
                    constexpr Iterator (
                            Iterator const & iterator
                    ) noexcept = default;

                public:
                    constexpr Iterator (
                            Iterator && iterator
                    ) noexcept;

                public:
                    __CDS_cpplang_NonConstConstexprMemberFunction auto operator = (
                            Iterator const & iterator
                    ) noexcept -> Iterator &;

                public:
                    __CDS_cpplang_NonConstConstexprMemberFunction auto operator = (
                            Iterator && iterator
                    ) noexcept -> Iterator &;

                public:
                    __CDS_cpplang_ConstexprDestructor ~Iterator() noexcept override = default;

                public:
                    __CDS_cpplang_NonConstConstexprMemberFunction auto operator ++ () noexcept -> Iterator &;

                public:
                    __CDS_cpplang_ConstexprNonLiteralReturn auto operator ++ (
                            int
                    ) noexcept -> Iterator;

                public:
                    __CDS_cpplang_NonConstConstexprMemberFunction auto operator -- () noexcept -> Iterator &;

                public:
                    __CDS_cpplang_ConstexprNonLiteralReturn auto operator -- (
                            int
                    ) noexcept -> Iterator;

                public:
                    constexpr auto operator * () const noexcept -> CharType &;

                public:
                    constexpr auto operator == (
                            Iterator const & iterator
                    ) const noexcept -> bool;

                public:
                    constexpr auto operator != (
                            Iterator const & iterator
                    ) const noexcept -> bool;
                };

            }
        }
    }
}

#endif // __CDS_EX_STRING_BASE_ITERATOR_HPP__