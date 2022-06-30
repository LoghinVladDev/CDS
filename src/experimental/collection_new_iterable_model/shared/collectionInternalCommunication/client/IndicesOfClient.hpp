//
// Created by loghin on 6/30/22.
//

#ifndef __CDS_SHARED_INDICES_OF_CLIENT_HPP__
#define __CDS_SHARED_INDICES_OF_CLIENT_HPP__

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {
        namespace __hidden {
            namespace __impl {

                template <
                        typename                                                    __ReceiverType,         // NOLINT(bugprone-reserved-identifier)
                        typename                                                    __ElementType,          // NOLINT(bugprone-reserved-identifier)
                        typename                                                    __FromCollectionType,   // NOLINT(bugprone-reserved-identifier)
                        __ContainsFunction < __FromCollectionType, __ElementType >  __contains              // NOLINT(bugprone-reserved-identifier)
                > class __IndicesOfClient {                                                                 // NOLINT(bugprone-reserved-identifier)

                private:
                    using ElementType = __ElementType;

                protected:
                    template < typename __CollectionType >
                    auto indicesOfFrom (
                            Size                            count,
                            __CollectionType              & storeIn,
                            __FromCollectionType    const & from
                    ) const noexcept -> __CollectionType &;

                protected:
                    template < template < typename ... > class __CollectionType >
                    auto indicesOfFrom (
                            Size                            count,
                            __FromCollectionType    const & from
                    ) const noexcept -> __CollectionType < Index >;

                protected:
                    auto firstIndexOfFrom (
                            __FromCollectionType const & from
                    ) const noexcept -> Index;

                protected:
                    auto lastIndexOfFrom (
                            __FromCollectionType const & from
                    ) const noexcept -> Index;

                protected:
                    template < typename __CollectionType >
                    auto allIndicesOfFrom (
                            __CollectionType              & storeIn,
                            __FromCollectionType    const & from
                    ) const noexcept -> __CollectionType &;

                protected:
                    template < template < typename ... > class __CollectionType >
                    auto allIndicesOfFrom (
                            __FromCollectionType const & from
                    ) const noexcept -> __CollectionType < Index >;

                protected:
                    template < typename __CollectionType >
                    auto indicesOfNotFrom (
                            Size                            count,
                            __CollectionType              & storeIn,
                            __FromCollectionType    const & from
                    ) const noexcept -> __CollectionType &;

                protected:
                    template < template < typename ... > class __CollectionType >
                    auto indicesOfNotFrom (
                            Size                            count,
                            __FromCollectionType    const & from
                    ) const noexcept -> __CollectionType < Index >;

                protected:
                    auto firstIndexOfNotFrom (
                            __FromCollectionType const & from
                    ) const noexcept -> Index;

                protected:
                    auto lastIndexOfNotFrom (
                            __FromCollectionType const & from
                    ) const noexcept -> Index;

                protected:
                    template < typename __CollectionType >
                    auto allIndicesOfNotFrom (
                            __CollectionType              & storeIn,
                            __FromCollectionType    const & from
                    ) const noexcept -> __CollectionType &;

                protected:
                    template < template < typename ... > class __CollectionType >
                    auto allIndicesOfNotFrom (
                            __FromCollectionType const & from
                    ) const noexcept -> __CollectionType < Index >;
                };

            }
        }
    }
}

#endif // __CDS_SHARED_INDICES_OF_CLIENT_HPP__
