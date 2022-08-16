//
// Created by loghin on 14/08/22.
//

#ifndef __CDS_SHARED_ITERATOR_GENERIC_DECORATOR_HPP__
#define __CDS_SHARED_ITERATOR_GENERIC_DECORATOR_HPP__

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {

        namespace __hidden {    // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier)
            namespace __impl {  // NOLINT(bugprone-reserved-identifier)

                template <
                        typename __DecoratedIteratorType,                               // NOLINT(bugprone-reserved-identifier)
                        typename __ValueAtType                                          // NOLINT(bugprone-reserved-identifier)
                > constexpr auto __valueAtHint (    // NOLINT(bugprone-reserved-identifier)
                        __DecoratedIteratorType const & baseIterator
                ) noexcept -> __ValueAtType &;


                template <
                        typename __DecoratedIteratorType,   // NOLINT(bugprone-reserved-identifier)
                        typename __ValueAtType              // NOLINT(bugprone-reserved-identifier)
                > using __ValueAtFunction =                 // NOLINT(bugprone-reserved-identifier)
                        decltype ( & __valueAtHint < __DecoratedIteratorType, __ValueAtType > );

            }
        }

        template <
                typename                                                                            __DecoratedIteratorType,    // NOLINT(bugprone-reserved-identifier)
                typename                                                                            __ValueAtType,              // NOLINT(bugprone-reserved-identifier)
                __hidden :: __impl :: __ValueAtFunction < __DecoratedIteratorType, __ValueAtType >  __valueAt                   // NOLINT(bugprone-reserved-identifier)
        > class ForwardIteratorGenericDecorator : public meta :: ForwardIterator {

        private:
            __DecoratedIteratorType _iterator;

        public:
            constexpr ForwardIteratorGenericDecorator () noexcept;

        public:
            __CDS_Explicit constexpr ForwardIteratorGenericDecorator (
                    __DecoratedIteratorType const & iterator
            ) noexcept;

        public:
            __CDS_Explicit constexpr ForwardIteratorGenericDecorator (
                    __DecoratedIteratorType && iterator
            ) noexcept;

        public:
            constexpr ForwardIteratorGenericDecorator (
                    ForwardIteratorGenericDecorator const & iterator
            ) noexcept;

        public:
            constexpr ForwardIteratorGenericDecorator (
                    ForwardIteratorGenericDecorator && iterator
            ) noexcept;

        public:
            __CDS_NoDiscard constexpr auto operator * () const noexcept -> __ValueAtType &;

        public:
            __CDS_NoDiscard constexpr auto operator -> () const noexcept -> __ValueAtType *;

        public:
            __CDS_NoDiscard constexpr auto operator == (
                    ForwardIteratorGenericDecorator const & iterator
            ) const noexcept -> bool;

        public:
            __CDS_NoDiscard constexpr auto operator != (
                    ForwardIteratorGenericDecorator const & iterator
            ) const noexcept -> bool;

        public:
            __CDS_cpplang_NonConstConstexprMemberFunction auto operator ++ () noexcept -> ForwardIteratorGenericDecorator &;

        public:
            __CDS_cpplang_NonConstConstexprMemberFunction auto operator ++ (int) noexcept -> ForwardIteratorGenericDecorator;

        public:
            __CDS_NoDiscard __CDS_Explicit constexpr operator bool () const noexcept;

        public:
            __CDS_NoDiscard constexpr auto iterator () const noexcept -> __DecoratedIteratorType const &;

        public:
            __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto iterator () noexcept -> __DecoratedIteratorType &;
        };

    }
}

#endif // __CDS_SHARED_ITERATOR_GENERIC_DECORATOR_HPP__
