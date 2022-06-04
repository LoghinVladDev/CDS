//
// Created by loghin on 6/4/22.
//

#ifndef __CDS_EX_STRING_BASE_CONST_ITERATOR_HPP__
#define __CDS_EX_STRING_BASE_CONST_ITERATOR_HPP__

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental { // NOLINT(modernize-concat-nested-namespaces)
        namespace hidden { // NOLINT(modernize-concat-nested-namespaces)
            namespace impl {

                template < typename CharType >
                class BaseString < CharType > :: ConstIterator : public AbstractConstIterator {

                public:
                    constexpr ConstIterator (
                            BaseString < CharType > const * pString,
                            Index                           index
                    ) noexcept;

                public:
                    constexpr ConstIterator (
                            ConstIterator const & iterator
                    ) noexcept = default;

                public:
                    constexpr ConstIterator (
                            ConstIterator && iterator
                    ) noexcept;

                public:
                    __CDS_cpplang_NonConstConstexprMemberFunction auto operator = (
                            ConstIterator const & iterator
                    ) noexcept -> ConstIterator &;

                public:
                    __CDS_cpplang_NonConstConstexprMemberFunction auto operator = (
                            ConstIterator && iterator
                    ) noexcept -> ConstIterator &;

                public:
                    __CDS_cpplang_ConstexprDestructor ~ConstIterator() noexcept override = default;

                public:
                    constexpr auto operator ++ () noexcept -> ConstIterator &;

                public:
                    __CDS_cpplang_ConstexprNonLiteralReturn auto operator ++ (
                            int
                    ) noexcept -> ConstIterator;

                public:
                    constexpr auto operator -- () noexcept -> ConstIterator &;

                public:
                    __CDS_cpplang_ConstexprNonLiteralReturn auto operator -- (
                            int
                    ) noexcept -> ConstIterator;

                public:
                    constexpr auto operator * () const noexcept -> CharType;

                public:
                    constexpr auto operator == (
                            ConstIterator const & iterator
                    ) const noexcept -> bool;

                public:
                    constexpr auto operator != (
                            ConstIterator const & iterator
                    ) const noexcept -> bool;
                };

            }
        }
    }
}

#endif // __CDS_EX_STRING_BASE_CONST_ITERATOR_HPP__
