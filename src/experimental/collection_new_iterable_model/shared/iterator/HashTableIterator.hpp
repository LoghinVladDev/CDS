/*
 * Created by loghin on 27/07/22.
 */

#ifndef __CDS_EX_SHARED_HASH_TABLE_ITERATOR_HPP__
#define __CDS_EX_SHARED_HASH_TABLE_ITERATOR_HPP__ /* NOLINT(bugprone-reserved-identifier) */

#warning No longer an experimental feature. Use the non-experimental header.
#include "../../../../shared/iterator/HashTableIterator.hpp"

namespace cds { /* NOLINT(modernize-concat-nested-namespaces) */
    namespace experimental {

        template < typename __ElementType >                                                                                                         /* NOLINT(bugprone-reserved-identifier) */
        using HashTableIterator         __CDS_DeprecatedHint("No longer an experimental feature.") = cds :: HashTableIterator < __ElementType >;    /* NOLINT(bugprone-reserved-identifier) */

        template < typename __ElementType >                                                                                                             /* NOLINT(bugprone-reserved-identifier) */
        using HashTableConstIterator    __CDS_DeprecatedHint("No longer an experimental feature.") = cds :: HashTableConstIterator < __ElementType >;   /* NOLINT(bugprone-reserved-identifier) */

    }
}

#endif /* __CDS_EX_SHARED_HASH_TABLE_ITERATOR_HPP__ */
