/*
 * Created by loghin on 6/27/22.
 */

#ifndef __CDS_EX_SET_HPP__
#define __CDS_EX_SET_HPP__ /* NOLINT(bugprone-reserved-identifier) */

#warning No longer an experimental feature. Use the non-experimental header.
#include <CDS/Set>

#include <CDS/experimental/Collection>

#include "shared/collectionInternalCommunication/client/primitive/FindUniqueImmutablePrimitiveClient.hpp"

#include "set/Constructs.hpp"

namespace cds { /* NOLINT(modernize-concat-nested-namespaces) */
    namespace experimental {

        template <
                typename                                                                                            __ElementType,  /* NOLINT(bugprone-reserved-identifier) */
                cds :: meta :: EnableIf < cds :: experimental :: meta :: isValidSetElement < __ElementType > () >   __enabler       /* NOLINT(bugprone-reserved-identifier) */
        > using Set __CDS_DeprecatedHint("No longer an experimental feature.") = cds :: Set < __ElementType >;

    }
}

#endif /* __CDS_EX_SET_HPP__ */
