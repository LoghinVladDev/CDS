//
// Created by loghin on 6/4/22.
//

#ifndef __CDS_EX_STRING_BASE_ABSTRACT_ITERATOR_HPP__
#define __CDS_EX_STRING_BASE_ABSTRACT_ITERATOR_HPP__

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental { // NOLINT(modernize-concat-nested-namespaces)
        namespace hidden { // NOLINT(modernize-concat-nested-namespaces)
            namespace impl {

                template < typename CharType >
                class BaseString < CharType > :: AbstractIterator {

                private:
                    BaseString < CharType >   * _pString    { nullptr };

                private:
                    Index                       _index      { 0 };

                private:
                    bool                        _forward    { true };

                protected:
                    constexpr AbstractIterator (
                            BaseString < CharType >   * pString,
                            Index                       index,
                            bool                        forward
                    ) noexcept;

                protected:
                    constexpr AbstractIterator (
                            AbstractIterator const & iterator
                    ) noexcept = default;

                protected:
                    constexpr AbstractIterator (
                            AbstractIterator && iterator
                    ) noexcept;

                protected:
                    __CDS_cpplang_NonConstConstexprMemberFunction auto operator = (
                            AbstractIterator const & iterator
                    ) noexcept -> AbstractIterator &;

                protected:
                    __CDS_cpplang_NonConstConstexprMemberFunction auto operator = (
                            AbstractIterator && iterator
                    ) noexcept -> AbstractIterator &;

                public:
                    __CDS_cpplang_ConstexprDestructor virtual ~AbstractIterator() noexcept = default;

                public:
                    __CDS_cpplang_NonConstConstexprMemberFunction auto next () noexcept -> AbstractIterator &;

                public:
                    __CDS_cpplang_NonConstConstexprMemberFunction auto previous () noexcept -> AbstractIterator &;

                public:
                    constexpr auto value () const noexcept -> CharType &;

                public:
                    __CDS_NoDiscard constexpr auto equals (
                            AbstractIterator const & iterator
                    ) const noexcept -> bool;
                };

            }
        }
    }
}

#endif // __CDS_EX_STRING_BASE_ABSTRACT_ITERATOR_HPP__
