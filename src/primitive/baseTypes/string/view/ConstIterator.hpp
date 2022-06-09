//
// Created by loghin on 6/4/22.
//

#ifndef __CDS_STRING_VIEW_BASE_CONST_ITERATOR_HPP__
#define __CDS_STRING_VIEW_BASE_CONST_ITERATOR_HPP__

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace __hidden { // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier)
        namespace __impl { // NOLINT(bugprone-reserved-identifier)

            template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
            class __BaseStringView < __CharType > :: ConstIterator : public AbstractConstIterator {

            public:
                constexpr ConstIterator (
                        __BaseStringView < __CharType > const * pString,
                        Index                                   index
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
                __CDS_cpplang_NonConstConstexprMemberFunction auto operator ++ () noexcept -> ConstIterator &;

            public:
                __CDS_cpplang_ConstexprNonLiteralReturn auto operator ++ (
                        int
                ) noexcept -> ConstIterator;

            public:
                __CDS_cpplang_NonConstConstexprMemberFunction auto operator -- () noexcept -> ConstIterator &;

            public:
                __CDS_cpplang_ConstexprNonLiteralReturn auto operator -- (
                        int
                ) noexcept -> ConstIterator;

            public:
                constexpr auto operator * () const noexcept -> __CharType;

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

#endif // __CDS_STRING_VIEW_BASE_CONST_ITERATOR_HPP__
