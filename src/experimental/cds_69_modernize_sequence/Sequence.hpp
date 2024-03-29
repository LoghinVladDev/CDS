/*
 * Created by loghin on 02.06.2021.
 */

#ifndef __CDS_SEQUENCE_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_SEQUENCE_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

#include <CDS/Iterable>         /* NOLINT(llvm-include-order) */
#include <CDS/Optional>
#include <CDS/Function>
#include <CDS/meta/TypeTraits>

#include "../../shared/impl/generalMappers.hpp"
#include "../../shared/sequence/Predeclaration.hpp"
#include "../../shared/iterableInternalCommunication/server/IterableServer.hpp"

#include "sequence/lazySequence/ConstIterator.hpp"
#include "sequence/lazySequence/Constructs.hpp"
#include "sequence/lazySequence/transitionPipeline/ConstIterator.hpp"
#include "sequence/lazySequence/transitionPipeline/Constructs.hpp"
#include "sequence/lazySequence/transitionPipeline/LazySequenceTransitionPipeline.hpp"

#include "sequence/LazySequence.hpp"

/* TODO : indices of client */
/* TODO : Generic Statements */
/* TODO : Add apply, also, first, one to Generic Statements */
/* TODO : FindThat */
/* TODO : FindThat Optional? */
/* TODO : Drop Implemented with filter */

namespace cds {

    template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    class Sequence : public Object {
    };

} /* namespace cds */

#include "../../shared/iterableInternalCommunication/server/impl/IterableServerImpl.hpp"

#include "sequence/lazySequence/transitionPipeline/impl/ConstIterator.hpp"
#include "sequence/lazySequence/transitionPipeline/impl/LazySequenceTransitionPipeline.hpp"

#include "sequence/lazySequence/impl/ConstIterator.hpp"
#include "sequence/lazySequence/impl/LazySequence.hpp"

#endif /* __CDS_SEQUENCE_HPP__ */
