//
// Created by loghin on 6/4/22.
//

#ifndef __CDS_STRING_BASE_ABSTRACT_CONST_ITERATOR_HPP__
#define __CDS_STRING_BASE_ABSTRACT_CONST_ITERATOR_HPP__

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace __hidden { // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier)
        namespace __impl { // NOLINT(bugprone-reserved-identifier)

            template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
            class __BaseString < __CharType > :: AbstractConstIterator {

            private:
                __BaseString < __CharType > const * _pString    { nullptr };

            private:
                Index                               _index      { 0 };

            private:
                bool                                _forward    { true };

            protected:
                constexpr AbstractConstIterator (
                        __BaseString < __CharType > const * pString,
                        Index                               index,
                        bool                                forward
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
                constexpr auto value () const noexcept -> __CharType;

            public:
                __CDS_NoDiscard constexpr auto equals (
                        AbstractConstIterator const & iterator
                ) const noexcept -> bool;
            };

        }
    }
}

#endif // __CDS_STRING_BASE_ABSTRACT_CONST_ITERATOR_HPP__
