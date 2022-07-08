//
// Created by loghin on 6/26/22.
//

#ifndef __CDS_SHARED_REMOVE_BY_CLIENT_HPP__
#define __CDS_SHARED_REMOVE_BY_CLIENT_HPP__

namespace cds {                 // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {    // NOLINT(modernize-concat-nested-namespaces)
        namespace __hidden {    // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier)
            namespace __impl {  // NOLINT(bugprone-reserved-identifier)

                template <
                        typename __IterableType,        // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType          // NOLINT(bugprone-reserved-identifier)
                > class __RemoveByClient {              // NOLINT(bugprone-reserved-identifier)

                protected:
                    using ElementType = __ElementType const;

                protected:
                    template < typename __Predicate > // NOLINT(bugprone-reserved-identifier)
                    auto removeIf (
                            Size                count,
                            __Predicate const & predicate
                    ) noexcept ( noexcept ( predicate ( cds :: meta :: referenceOf < ElementType > () ) ) ) -> Size;

                protected:
                    template < typename __Predicate > // NOLINT(bugprone-reserved-identifier)
                    auto removeFirstIf (
                            __Predicate const & predicate
                    ) noexcept ( noexcept ( predicate ( cds :: meta :: referenceOf < ElementType > () ) ) ) -> bool;

                protected:
                    template < typename __Predicate > // NOLINT(bugprone-reserved-identifier)
                    auto removeLastIf (
                            __Predicate const & predicate
                    ) noexcept ( noexcept ( predicate ( cds :: meta :: referenceOf < ElementType > () ) ) ) -> bool;

                protected:
                    template < typename __Predicate > // NOLINT(bugprone-reserved-identifier)
                    auto removeAllIf (
                            __Predicate const & predicate
                    ) noexcept ( noexcept ( predicate ( cds :: meta :: referenceOf < ElementType > () ) ) ) -> Size;
                };

            }
        }
    }
}

#endif // __CDS_SHARED_REMOVE_BY_CLIENT_HPP__
