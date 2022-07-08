//
// Created by loghin on 6/30/2022.
//

#ifndef __CDS_SHARED_SORT_CLIENT_HPP__
#define __CDS_SHARED_SORT_CLIENT_HPP__

namespace cds {                 // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {    // NOLINT(modernize-concat-nested-namespaces)
        namespace __hidden {    // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier)
            namespace __impl {  // NOLINT(bugprone-reserved-identifier)

                template <
                        typename __ReceiverType,    // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType      // NOLINT(bugprone-reserved-identifier)
                > class __SortClient {              // NOLINT(bugprone-reserved-identifier)

                private:
                    using ElementType = __ElementType;

                protected:
                    template < typename __ComparatorFunction = decltype ( & predicates :: lessThan < ElementType > ) > // NOLINT(bugprone-reserved-identifier)
                    auto sort (
                            __ComparatorFunction const & comparatorFunction = & predicates :: lessThan < ElementType >
                    ) noexcept ( noexcept ( comparatorFunction ( cds :: meta :: valueOf < ElementType > (), cds :: meta :: valueOf < ElementType > () ) ) ) -> void;

                };


                template <
                        typename __ReceiverType,    // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType      // NOLINT(bugprone-reserved-identifier)
                > using __LocalSortClient =         // NOLINT(bugprone-reserved-identifier)
                        __SortClient <
                                __ReceiverType,
                                __ElementType
                        >;

            }
        }
    }
}

#endif // __CDS_SHARED_SORT_CLIENT_HPP__