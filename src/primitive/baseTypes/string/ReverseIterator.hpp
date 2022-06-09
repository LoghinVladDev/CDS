//
// Created by loghin on 6/4/22.
//

#ifndef __CDS_STRING_BASE_REVERSE_ITERATOR_HPP__
#define __CDS_STRING_BASE_REVERSE_ITERATOR_HPP__

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace __hidden { // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier)
        namespace __impl { // NOLINT(bugprone-reserved-identifier)

            template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
            class __BaseString < __CharType > :: ReverseIterator : public AbstractIterator {

            public:
                constexpr ReverseIterator (
                        __BaseString < __CharType > * pString,
                        Index                         index
                ) noexcept;

            public:
                constexpr ReverseIterator (
                        ReverseIterator const & iterator
                ) noexcept = default;

            public:
                constexpr ReverseIterator (
                        ReverseIterator && iterator
                ) noexcept;

            public:
                __CDS_cpplang_NonConstConstexprMemberFunction auto operator = (
                        ReverseIterator const & iterator
                ) noexcept -> ReverseIterator &;

            public:
                __CDS_cpplang_NonConstConstexprMemberFunction auto operator = (
                        ReverseIterator && iterator
                ) noexcept -> ReverseIterator &;

            public:
                __CDS_cpplang_ConstexprDestructor ~ReverseIterator() noexcept override = default;

            public:
                __CDS_cpplang_NonConstConstexprMemberFunction auto operator ++ () noexcept -> ReverseIterator &;

            public:
                __CDS_cpplang_ConstexprNonLiteralReturn auto operator ++ (
                        int
                ) noexcept -> ReverseIterator;

            public:
                __CDS_cpplang_NonConstConstexprMemberFunction auto operator -- () noexcept -> ReverseIterator &;

            public:
                __CDS_cpplang_ConstexprNonLiteralReturn auto operator -- (
                        int
                ) noexcept -> ReverseIterator;

            public:
                constexpr auto operator * () const noexcept -> __CharType &;

            public:
                constexpr auto operator == (
                        ReverseIterator const & iterator
                ) const noexcept -> bool;

            public:
                constexpr auto operator != (
                        ReverseIterator const & iterator
                ) const noexcept -> bool;
            };

        }
    }
}

#endif // __CDS_STRING_BASE_REVERSE_ITERATOR_HPP__
