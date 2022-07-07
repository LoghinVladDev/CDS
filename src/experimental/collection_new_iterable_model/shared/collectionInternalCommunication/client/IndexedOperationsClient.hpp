//
// Created by loghin on 6/30/2022.
//

#ifndef __CDS_SHARED_INDEXED_OPERATIONS_CLIENT_HPP__
#define __CDS_SHARED_INDEXED_OPERATIONS_CLIENT_HPP__

namespace cds {                 // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {    // NOLINT(modernize-concat-nested-namespaces)
        namespace __hidden {    // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier)
            namespace __impl {  // NOLINT(bugprone-reserved-identifier)

                template <
                        typename __ReceiverType,    // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType      // NOLINT(bugprone-reserved-identifier)
                > class __IndexedOperationsClient { // NOLINT(bugprone-reserved-identifier)

                private:
                    using ElementType = __ElementType;

                protected:
                    template <
                            typename __CollectionType,                  // NOLINT(bugprone-reserved-identifier)
                            typename __TElementType = __ElementType,    // NOLINT(bugprone-reserved-identifier)
                            cds :: meta :: EnableIf <
                                    cds :: meta :: isCopyConstructible < __TElementType > ()
                            > = 0
                    > auto sub (
                            __CollectionType  & storeIn,
                            Index               from,
                            Index               to
                    ) const noexcept -> __CollectionType &;

                protected:
                    template <
                            typename __CollectionType,                  // NOLINT(bugprone-reserved-identifier)
                            typename __TElementType = __ElementType,    // NOLINT(bugprone-reserved-identifier)
                            cds :: meta :: EnableIf <
                                    cds :: meta :: isCopyConstructible < __TElementType > ()
                            > = 0
                    > __CDS_NoDiscard auto sub (
                            Index               from,
                            Index               to
                    ) const noexcept -> __CollectionType;

                protected:
                    template <
                            template < typename ... > class __CollectionType,   // NOLINT(bugprone-reserved-identifier)
                            typename __TElementType = __ElementType,            // NOLINT(bugprone-reserved-identifier)
                            cds :: meta :: EnableIf <
                                    cds :: meta :: isCopyConstructible < __TElementType > ()
                            > = 0
                    > __CDS_NoDiscard auto sub (
                            Index               from,
                            Index               to
                    ) const noexcept -> __CollectionType < __ElementType >;

                protected:
                    __CDS_NoDiscard auto operator [] (
                            Index index
                    ) const noexcept (false) -> ElementType const &;

                protected:
                    __CDS_NoDiscard auto operator [] (
                            Index index
                    ) noexcept (false) -> ElementType &;

                protected:
                    auto removeAt (
                            Collection < Index > const & indices
                    ) noexcept -> Size;

                protected:
                    auto removeAt (
                            std :: initializer_list < Index > const & indices
                    ) noexcept -> Size;
                };

            }
        }
    }
}

#endif // __CDS_SHARED_INDEXED_OPERATIONS_CLIENT_HPP__
