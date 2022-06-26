//
// Created by loghin on 6/26/22.
//

#ifndef __CDS_SHARED_ITERABLE_FIND_OF_HPP__
#define __CDS_SHARED_ITERABLE_FIND_OF_HPP__

namespace cds {                 // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {    // NOLINT(modernize-concat-nested-namespaces)
        namespace __hidden {    // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier)
            namespace __impl {  // NOLINT(bugprone-reserved-identifier)

                template <
                        typename                                                    __IterableType,     // NOLINT(bugprone-reserved-identifier)
                        typename                                                    __ElementType,      // NOLINT(bugprone-reserved-identifier)
                        typename                                                    __FromIterableType, // NOLINT(bugprone-reserved-identifier)
                        __ContainsFunction < __FromIterableType, __ElementType >    __containsFunction  // NOLINT(bugprone-reserved-identifier)
                > class __IterableFindOf {                                                              // NOLINT(bugprone-reserved-identifier)

                };

            }
        }
    }
}

#endif // __CDS_SHARED_ITERABLE_FIND_OF_HPP__
