/*
 * Created by loghin on 02.06.2021.
 */

#ifndef __CDS_SEQUENCE_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_SEQUENCE_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

#include <CDS/Object>           /* NOLINT(llvm-include-order) */
#include <CDS/Optional>
#include <CDS/Function>
#include <CDS/meta/TypeTraits>

#include "../../shared/impl/generalMappers.hpp"
#include "../../shared/sequence/Predeclaration.hpp"
#include "../../shared/array/ArrayBase.hpp"

/* TODO : indices of client */
/* TODO : Generic Statements */
/* TODO : Add apply, also, first, one to Generic Statements */
/* TODO : FindThat */
/* TODO : FindThat Optional? */
/* TODO : Drop Implemented with filter */

namespace cds {

    template < typename __ElementType, typename __BaseIterable > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    class Sequence : public Object {

    private:
        using __BaseConstIteratorType = decltype ( cds :: meta :: referenceOf < __BaseIterable > ().cbegin() );

    private:
        using __BaseElementType = decltype ( * cds :: meta :: referenceOf < __BaseConstIteratorType > () );

    private:
        template < typename __ArrayElementType >
        class __SequenceInternalArray;

    private:
        Function < __ElementType ( __BaseElementType ) > entryMapper;

    private:
        __SequenceInternalArray < functional :: Predicate < __ElementType const & > > _filters;

    public:
        Sequence () noexcept = delete;

    public:
        Sequence (
                Sequence const & sequence
        ) noexcept;

    public:
        Sequence (
                Sequence && sequence
        ) noexcept;

    public:
        __CDS_Explicit Sequence (
                __BaseIterable const & iterable
        ) noexcept;

    public:
        __CDS_Explicit Sequence (
                __BaseIterable && iterable
        ) noexcept;

    public:
        ~Sequence () noexcept override;

    public:
        auto operator = (
                Sequence const & sequence
        ) noexcept -> Sequence &;

    public:
        auto operator = (
                Sequence && sequence
        ) noexcept -> Sequence &;

    public:

    };

} /* namespace cds */

#endif /* __CDS_SEQUENCE_HPP__ */
