//
// Created by loghin on 27/07/22.
//

#ifndef __CDS_SHARED_HASH_TABLE_HPP__
#define __CDS_SHARED_HASH_TABLE_HPP__

namespace cds {                 // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {    // NOLINT(modernize-concat-nested-namespaces)
        namespace __hidden {    // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier)
            namespace __impl {  // NOLINT(bugprone-reserved-identifier)

                template <
                        typename                                                            __ElementType,      // NOLINT(bugprone-reserved-identifier)
                        typename                                                            __KeyType,          // NOLINT(bugprone-reserved-identifier)
                        typename                                                            __KeyHasher,        // NOLINT(bugprone-reserved-identifier)
                        typename                                                            __RehashPolicy,     // NOLINT(bugprone-reserved-identifier)
                        cds :: utility :: ExtractorFunction < __ElementType, __KeyType >    __keyExtractor,     // NOLINT(bugprone-reserved-identifier)
                        cds :: utility :: ComparisonFunction < __ElementType >              __keyComparator,    // NOLINT(bugprone-reserved-identifier)
                        cds :: utility :: DestructorFunction < __ElementType >              __nodeDestructor    // NOLINT(bugprone-reserved-identifier)
                > class __HashTable :                                                                           // NOLINT(bugprone-reserved-identifier)
                        protected cds :: __hidden :: __impl :: __HashTableUtils <
                                __KeyHasher,
                                __RehashPolicy
                        > {

                protected:
                    using ElementType   = __ElementType;    // NOLINT(bugprone-reserved-identifier)

                protected:
                    using KeyType       = __KeyType;        // NOLINT(bugprone-reserved-identifier)

                protected:
                    using KeyHasher     = __KeyHasher;      // NOLINT(bugprone-reserved-identifier)

                protected:
                    using RehashPolicy  = __RehashPolicy;   // NOLINT(bugprone-reserved-identifier)
                };

            }
        }
    }
}

#endif // __CDS_SHARED_HASH_TABLE_HPP__
