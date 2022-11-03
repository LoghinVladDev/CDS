/*
 * Created by loghin on 02.06.2021.
 */

#ifndef __CDS_SEQUENCE_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_SEQUENCE_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

#include <CDS/Iterable>         /* NOLINT(llvm-include-order) */
#include <CDS/Optional>
#include <CDS/Function>
#include <CDS/meta/TypeTraits>
#include <CDS/Array>

#include "../../shared/impl/generalMappers.hpp"
#include "../../shared/sequence/Predeclaration.hpp"
#include "../../shared/iterableInternalCommunication/server/IterableServer.hpp"

#include "sequence/lazySequence/ConstIterator.hpp"
#include "sequence/lazySequence/Constructs.hpp"

/* TODO : indices of client */
/* TODO : Generic Statements */
/* TODO : Add apply, also, first, one to Generic Statements */
/* TODO : FindThat */
/* TODO : FindThat Optional? */
/* TODO : Drop Implemented with filter */

namespace cds {

    namespace __hidden {
        namespace __impl {

            template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            class __LazySequence :              /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    public cds :: Iterable < __ElementType > {

            private:
                friend class __LazySequenceConstIterator < __ElementType >;

            public:
                cds :: Array < cds :: functional :: Predicate < __ElementType const & > > _filters;

            private:
                cds :: Iterable < __ElementType > const & _baseIterable;

            private:
                using BaseIterable = cds :: Iterable < __ElementType >;

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

    template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    class Sequence : public Object {
    };

} /* namespace cds */

#include "../../shared/iterableInternalCommunication/server/impl/IterableServer.hpp"

#endif /* __CDS_SEQUENCE_HPP__ */
