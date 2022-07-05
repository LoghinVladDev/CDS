//
// Created by loghin on 6/30/22.
//

#ifndef __CDS_SHARED_INDICES_CLIENT_HPP__
#define __CDS_SHARED_INDICES_CLIENT_HPP__

namespace cds {                 // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {    // NOLINT(modernize-concat-nested-namespaces)
        namespace __hidden {    // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier)
            namespace __impl {  // NOLINT(bugprone-reserved-identifier)

                template <
                        typename __ReceiverType,    // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType      // NOLINT(bugprone-reserved-identifier)
                > class __IndicesClient {           // NOLINT(bugprone-reserved-identifier)

                private:
                    using ElementType = __ElementType;

                protected:
                    template < typename __CollectionType >  // NOLINT(bugprone-reserved-identifier)
                    auto indicesOf (
                            Size                        count,
                            __CollectionType          & storeIn,
                            ElementType         const & element
                    ) const noexcept -> __CollectionType &;

                protected:
                    template < template < typename ... > class __CollectionType >   // NOLINT(bugprone-reserved-identifier)
                    __CDS_NoDiscard auto indicesOf (
                            Size                count,
                            ElementType const & element
                    ) const noexcept -> __CollectionType < Index >;

                protected:
                    __CDS_NoDiscard auto firstIndexOf (
                            ElementType const & element
                    ) const noexcept -> Index;

                protected:
                    __CDS_NoDiscard auto lastIndexOf (
                            ElementType const & element
                    ) const noexcept -> Index;

                protected:
                    template < typename __CollectionType >  // NOLINT(bugprone-reserved-identifier)
                    auto allIndicesOf (
                            __CollectionType          & storeIn,
                            ElementType         const & element
                    ) const noexcept -> __CollectionType &;

                protected:
                    template < template < typename ... > class __CollectionType >   // NOLINT(bugprone-reserved-identifier)
                    __CDS_NoDiscard auto allIndicesOf (
                            ElementType const & element
                    ) const noexcept -> __CollectionType < Index >;
                };

            }
        }
    }
}

#endif // __CDS_SHARED_INDICES_CLIENT_HPP__