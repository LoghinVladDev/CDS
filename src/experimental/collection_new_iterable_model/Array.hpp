/*
 * Created by loghin on 7/2/22.
 */

#ifndef __CDS_EX_ARRAY_HPP__
#define __CDS_EX_ARRAY_HPP__ /* NOLINT(bugprone-reserved-identifier) */

#warning No longer an experimental feature. Use the non-experimental header.
#include <CDS/Array>

#include <CDS/experimental/List>

#include "shared/iterator/IteratorSort.hpp"
#include "shared/iterator/AddressIterator.hpp"

#include "shared/collectionInternalCommunication/server/ListServerDispatcher.hpp"

#include "shared/array/ArrayBase.hpp"

#include "shared/delegateIterator/AbstractDelegateIterator.hpp"
#include "shared/delegateIterator/DelegateIterator.hpp"

#include "shared/collectionInternalCommunication/server/ListServer.hpp"

#include "array/Constructs.hpp"

namespace cds { /* NOLINT(modernize-concat-nested-namespaces) */
    namespace experimental {

        /**
         * @deprecated
         */
        template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
        using Array __CDS_DeprecatedHint("No longer an experimental feature.") = cds :: Array < __ElementType >;

    }
}

#endif /* __CDS_EX_ARRAY_HPP__ */
