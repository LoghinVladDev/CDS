//
// Created by uic70278 on 6/30/2022.
//

#ifndef __CDS_SHARED_INDEXED_OPERATIONS_CLIENT_HPP__
#define __CDS_SHARED_INDEXED_OPERATIONS_CLIENT_HPP__

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {
        namespace __hidden {
            namespace __impl {

                template <
                        typename __ReceiverType,    // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType      // NOLINT(bugprone-reserved-identifier)
                > class __IndexedOperationsClient { // NOLINT(bugprone-reserved-identifier)

                private:
                    using ElementType = __ElementType;

                protected:
                    template <
                            typename __CollectionType,
                            typename __TElementType = __ElementType,
                            cds :: meta :: EnableIf <
                                    cds :: meta :: isCopyConstructible < __TElementType > ()
                            > = 0
                    > auto sub (
                            __CollectionType  & storeIn,
                            Index               from,
                            Index               in
                    ) const noexcept -> __CollectionType &;

                protected:
                    template <
                            typename __CollectionType,
                            typename __TElementType = __ElementType,
                            cds :: meta :: EnableIf <
                                    cds :: meta :: isCopyConstructible < __TElementType > ()
                            > = 0
                    > auto sub (
                            Index               from,
                            Index               in
                    ) const noexcept -> __CollectionType;

                protected:
                    template <
                            template < typename ... > class __CollectionType,
                            typename __TElementType = __ElementType,
                            cds :: meta :: EnableIf <
                                    cds :: meta :: isCopyConstructible < __TElementType > ()
                            > = 0
                    > auto sub (
                            Index               from,
                            Index               in
                    ) const noexcept -> __CollectionType < __ElementType >;

                protected:
                    auto operator [] (
                            Index index
                    ) const noexcept (false) -> ElementType const &;

                protected:
                    auto operator [] (
                            Index index
                    ) noexcept (false) -> ElementType &;

                protected:
                    auto removeAt (
                            Collection < Index > const & indices
                    ) noexcept -> bool;

                protected:
                    auto removeAt (
                            std :: initializer_list < Index > const & indices
                    ) noexcept -> bool;
                };

            }
        }
    }
}

#endif // __CDS_SHARED_INDEXED_OPERATIONS_CLIENT_HPP__
