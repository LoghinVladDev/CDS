/*
 * Created by loghin on 05/11/22.
 */

#ifndef __CDS_SEQUENCE_LAZY_SEQUENCE_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_SEQUENCE_LAZY_SEQUENCE_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

namespace cds {
    namespace __hidden {
        namespace __impl {

            template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            class __LazySequence :              /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    public cds :: Iterable < __ElementType >,
                    public __LazySequenceDelegateForwardIterableClient < __ElementType >,
                    public __LazySequenceContainsOfIterableClient < __ElementType >,
                    public __LazySequenceContainsOfInitializerListClient < __ElementType >,
                    public __LazySequenceFindOfIterableClient < __ElementType >,
                    public __LazySequenceFindOfInitializerListClient < __ElementType >,
                    public __LazySequenceFindByClient < __ElementType >,
                    public __LazySequenceGenericStatementsClient < __ElementType > {

            private:
                friend class __LazySequenceConstIterator < __ElementType >;

            public:
                cds :: Array < cds :: functional :: Predicate < __ElementType const & > >           _filters;

            private:
                cds :: Iterable < __ElementType >                                           const & _baseIterable;

            private:
                using BaseIterable = cds :: Iterable < __ElementType >;

            private:
                using DelegateForwardIterableClient =
                        __LazySequenceDelegateForwardIterableClient < __ElementType >;

            private:
                using ContainsOfIterableClient =
                        __LazySequenceContainsOfIterableClient < __ElementType >;

            private:
                using ContainsOfInitializerListClient =
                        __LazySequenceContainsOfInitializerListClient < __ElementType >;

            private:
                using FindOfIterableClient =
                        __LazySequenceFindOfIterableClient < __ElementType >;

            private:
                using FindOfInitializerListClient =
                        __LazySequenceFindOfInitializerListClient < __ElementType >;

            private:
                using FindByClient =
                        __LazySequenceFindByClient < __ElementType >;

            private:
                using GenericStatementsClient =
                        __LazySequenceGenericStatementsClient < __ElementType >;

            private:
                using typename BaseIterable :: __GenericHandler;

            private:
                using typename BaseIterable :: __GenericConstHandler;

            private:
                __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto __iicch_obtainGenericHandler (
                        __IterableInternalRequestType requestType
                ) noexcept -> __GenericHandler override;

            private:
                __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto __iicch_obtainGenericConstHandler (
                        __IterableInternalRequestType requestType
                ) const noexcept -> __GenericConstHandler override;

            public:
                using typename DelegateForwardIterableClient :: ConstIterator;

            public:
                using DelegateForwardIterableClient :: begin;

            public:
                using DelegateForwardIterableClient :: end;

            public:
                using DelegateForwardIterableClient :: cbegin;

            public:
                using DelegateForwardIterableClient :: cend;

            public:
                using ContainsOfIterableClient :: containsAnyOf;

            public:
                using ContainsOfIterableClient :: containsAllOf;

            public:
                using ContainsOfIterableClient :: containsNoneOf;

            public:
                using ContainsOfIterableClient :: containsAnyNotOf;

            public:
                using ContainsOfInitializerListClient :: containsAnyOf;

            public:
                using ContainsOfInitializerListClient :: containsAllOf;

            public:
                using ContainsOfInitializerListClient :: containsNoneOf;

            public:
                using ContainsOfInitializerListClient :: containsAnyNotOf;

            public:
                using FindOfIterableClient :: findOf;

            public:
                using FindOfIterableClient :: findFirstOf;

            public:
                using FindOfIterableClient :: findLastOf;

            public:
                using FindOfIterableClient :: findAllOf;

            public:
                using FindOfIterableClient :: findNotOf;

            public:
                using FindOfIterableClient :: findFirstNotOf;

            public:
                using FindOfIterableClient :: findLastNotOf;

            public:
                using FindOfIterableClient :: findAllNotOf;

            public:
                using FindOfInitializerListClient :: findOf;

            public:
                using FindOfInitializerListClient :: findFirstOf;

            public:
                using FindOfInitializerListClient :: findLastOf;

            public:
                using FindOfInitializerListClient :: findAllOf;

            public:
                using FindOfInitializerListClient :: findNotOf;

            public:
                using FindOfInitializerListClient :: findFirstNotOf;

            public:
                using FindOfInitializerListClient :: findLastNotOf;

            public:
                using FindOfInitializerListClient :: findAllNotOf;

            public:
                using FindByClient :: findThat;

            public:
                using FindByClient :: findFirstThat;

            public:
                using FindByClient :: findLastThat;

            public:
                using FindByClient :: findAllThat;

            public:
                using GenericStatementsClient :: forEach;

            public:
                using GenericStatementsClient :: count;

            public:
                using GenericStatementsClient :: atLeast;

            public:
                using GenericStatementsClient :: atMost;

            public:
                using GenericStatementsClient :: moreThan;

            public:
                using GenericStatementsClient :: fewerThan;

            public:
                using GenericStatementsClient :: any;

            public:
                using GenericStatementsClient :: all;

            public:
                using GenericStatementsClient :: none;

            public:
                __LazySequence () noexcept = delete;

            public:
                __LazySequence (
                        cds :: Iterable < __ElementType > const & iterable
                ) noexcept;

            public:
                ~__LazySequence() noexcept override = default;

            public:
                template < typename __Predicate >
                __CDS_NoDiscard auto filter ( __Predicate const & predicate ) noexcept -> __LazySequence &;
            };

        }
    }
}

#endif /* __CDS_SEQUENCE_LAZY_SEQUENCE_HPP__ */
