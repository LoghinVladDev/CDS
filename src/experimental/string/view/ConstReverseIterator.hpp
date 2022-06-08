//
// Created by loghin on 6/4/22.
//

#ifndef __CDS_EX_STRING_VIEW_BASE_CONST_REVERSE_ITERATOR_HPP__
#define __CDS_EX_STRING_VIEW_BASE_CONST_REVERSE_ITERATOR_HPP__

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental { // NOLINT(bugprone-reserved-identifier)
        namespace __hidden { // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier)
            namespace __impl { // NOLINT(bugprone-reserved-identifier)

                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                class __BaseStringView < __CharType > :: ConstReverseIterator : public AbstractConstIterator {

                public:
                    constexpr ConstReverseIterator (
                            __BaseStringView < __CharType > const * pString,
                            Index                                   index
                    ) noexcept;

                public:
                    constexpr ConstReverseIterator (
                            ConstReverseIterator const & iterator
                    ) noexcept = default;

                public:
                    constexpr ConstReverseIterator (
                            ConstReverseIterator && iterator
                    ) noexcept;

                public:
                    __CDS_cpplang_NonConstConstexprMemberFunction auto operator = (
                            ConstReverseIterator const & iterator
                    ) noexcept -> ConstReverseIterator &;

                public:
                    __CDS_cpplang_NonConstConstexprMemberFunction auto operator = (
                            ConstReverseIterator && iterator
                    ) noexcept -> ConstReverseIterator &;

                public:
                    __CDS_cpplang_ConstexprDestructor ~ConstReverseIterator() noexcept override = default;

                public:
                    __CDS_cpplang_NonConstConstexprMemberFunction auto operator ++ () noexcept -> ConstReverseIterator &;

                public:
                    __CDS_cpplang_ConstexprNonLiteralReturn auto operator ++ (
                            int
                    ) noexcept -> ConstReverseIterator;

                public:
                    __CDS_cpplang_NonConstConstexprMemberFunction auto operator -- () noexcept -> ConstReverseIterator &;

                public:
                    __CDS_cpplang_ConstexprNonLiteralReturn auto operator -- (
                            int
                    ) noexcept -> ConstReverseIterator;

                public:
                    constexpr auto operator * () const noexcept -> __CharType;

                public:
                    constexpr auto operator == (
                            ConstReverseIterator const & iterator
                    ) const noexcept -> bool;

                public:
                    constexpr auto operator != (
                            ConstReverseIterator const & iterator
                    ) const noexcept -> bool;
                };

            }
        }
    }
}

#endif // __CDS_EX_STRING_VIEW_BASE_CONST_REVERSE_ITERATOR_HPP__
