/*
 * Created by loghin on 11/1/2022.
 */

#ifndef __CDS_LAZY_SEQUENCE_CONST_ITERATOR_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_LAZY_SEQUENCE_CONST_ITERATOR_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

namespace cds {
    namespace __hidden {
        namespace __impl {

            template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            class __LazySequence;               /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            template < typename __ElementType >                                         /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            class __LazySequenceConstIterator : public cds :: meta :: ForwardIterator { /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            private:
                __LazySequence < __ElementType > const & _sequence;

            private:
                typename cds :: Iterable < __ElementType > :: ConstIterator _iterator;

            public:
                constexpr __LazySequenceConstIterator () noexcept = delete;

            public:
                constexpr __LazySequenceConstIterator (
                        __LazySequenceConstIterator const & iterator
                ) noexcept;

            public:
                constexpr __LazySequenceConstIterator (
                        __LazySequenceConstIterator && iterator
                ) noexcept;

            public:
                constexpr __LazySequenceConstIterator (
                        typename cds :: Iterable < __ElementType > :: ConstIterator      && iterator,
                        __LazySequence < __ElementType >                            const & sequence
                ) noexcept;

            public:
                ~__LazySequenceConstIterator () noexcept = default;

            public:
                __CDS_cpplang_NonConstConstexprMemberFunction auto operator = (
                        __LazySequenceConstIterator const & iterator
                ) noexcept -> __LazySequenceConstIterator &;

            public:
                __CDS_cpplang_NonConstConstexprMemberFunction auto operator = (
                        __LazySequenceConstIterator && iterator
                ) noexcept -> __LazySequenceConstIterator &;

            public:
                __CDS_NoDiscard constexpr auto operator * () const noexcept -> __ElementType &;

            public:
                __CDS_NoDiscard constexpr auto operator -> () const noexcept -> __ElementType;

            public:
                __CDS_NoDiscard constexpr auto operator == (
                        __LazySequenceConstIterator const & iterator
                ) const noexcept -> bool;

            public:
                __CDS_NoDiscard constexpr auto operator != (
                        __LazySequenceConstIterator const & iterator
                ) const noexcept -> bool;

            public:
                __CDS_cpplang_NonConstConstexprMemberFunction auto operator ++ () noexcept -> __LazySequenceConstIterator &;

            public:
                __CDS_cpplang_NonConstConstexprMemberFunction auto operator ++ (int) noexcept -> __LazySequenceConstIterator;

            public:
                __CDS_NoDiscard __CDS_Explicit constexpr operator bool () const noexcept;
            };

        }
    }
}

#endif /* __CDS_LAZY_SEQUENCE_CONST_ITERATOR_HPP__ */
