//
// Created by loghin on 6/4/22.
//

#ifndef __CDS_EX_STRING_BASE_ABSTRACT_CONST_ITERATOR_HPP__
#define __CDS_EX_STRING_BASE_ABSTRACT_CONST_ITERATOR_HPP__

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental { // NOLINT(modernize-concat-nested-namespaces)
        namespace hidden { // NOLINT(modernize-concat-nested-namespaces)
            namespace impl {

                template < typename CharType >
                class BaseString < CharType > :: AbstractConstIterator {

                private:
                    BaseString < CharType > const * _pString    { nullptr };

                private:
                    Index                           _index      { 0 };

                private:
                    bool                            _forward    { true };

                protected:
                    constexpr AbstractConstIterator (
                            BaseString < CharType > const * pString,
                            Index                           index,
                            bool                            forward
                    ) noexcept;

                protected:
                    constexpr AbstractConstIterator (
                            AbstractConstIterator const & iterator
                    ) noexcept = default;

                protected:
                    constexpr AbstractConstIterator (
                            AbstractConstIterator && iterator
                    ) noexcept;

                protected:
                    __CDS_cpplang_NonConstConstexprMemberFunction auto operator = (
                            AbstractConstIterator const & iterator
                    ) noexcept -> AbstractConstIterator &;

                protected:
                    __CDS_cpplang_NonConstConstexprMemberFunction auto operator = (
                            AbstractConstIterator && iterator
                    ) noexcept -> AbstractConstIterator &;

                public:
                    __CDS_cpplang_ConstexprDestructor virtual ~AbstractConstIterator() noexcept = default;

                public:
                    __CDS_cpplang_NonConstConstexprMemberFunction auto next () noexcept -> AbstractConstIterator &;

                public:
                    __CDS_cpplang_NonConstConstexprMemberFunction auto previous () noexcept -> AbstractConstIterator &;

                public:
                    constexpr auto value () const noexcept -> CharType;

                public:
                    __CDS_NoDiscard constexpr auto equals (
                            AbstractConstIterator const & iterator
                    ) const noexcept -> bool;
                };

            }
        }
    }
}

#endif // __CDS_EX_STRING_BASE_ABSTRACT_CONST_ITERATOR_HPP__
