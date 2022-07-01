//
// Created by uic70278 on 6/30/2022.
//

#ifndef __CDS_SHARED_SORTING_CLIENT_HPP__
#define __CDS_SHARED_SORTING_CLIENT_HPP__

namespace cds {                 // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {    // NOLINT(modernize-concat-nested-namespaces)
        namespace __hidden {    // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier)
            namespace __impl {  // NOLINT(bugprone-reserved-identifier)

                template <
                        typename __ReceiverType,    // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType      // NOLINT(bugprone-reserved-identifier)
                > class __SortingClient {           // NOLINT(bugprone-reserved-identifier)

                private:
                    using ElementType = __ElementType;

                protected:
                    template < typename __ComparatorFunction = decltype ( & predicates :: lessThan < ElementType > ) > // NOLINT(bugprone-reserved-identifier)
                    auto sort (
                            __ComparatorFunction const & comparatorFunction = & predicates :: lessThan < ElementType >
                    ) noexcept ( noexcept ( comparatorFunction ( cds :: meta :: valueOf < ElementType > (), cds :: meta :: valueOf < ElementType > () ) ) ) -> void;

                };

            }
        }
    }
}

#endif // __CDS_SHARED_SORTING_CLIENT_HPP__