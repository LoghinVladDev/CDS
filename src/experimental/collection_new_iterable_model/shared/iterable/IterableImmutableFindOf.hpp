//
// Created by loghin on 6/26/22.
//

#ifndef __CDS_SHARED_ITERABLE_IMMUTABLE_FIND_OF_HPP__
#define __CDS_SHARED_ITERABLE_IMMUTABLE_FIND_OF_HPP__

#include "../iterator/IteratorFind.hpp"

namespace cds {                 // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {    // NOLINT(modernize-concat-nested-namespaces)
        namespace __hidden {    // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier)
            namespace __impl {  // NOLINT(bugprone-reserved-identifier)

                template <
                        typename                                                    __IterableType,     // NOLINT(bugprone-reserved-identifier)
                        typename                                                    __ElementType,      // NOLINT(bugprone-reserved-identifier)
                        typename                                                    __IteratorType,     // NOLINT(bugprone-reserved-identifier)
                        typename                                                    __FromIterableType, // NOLINT(bugprone-reserved-identifier)
                        __ContainsFunction < __FromIterableType, __ElementType >    __containsFunction  // NOLINT(bugprone-reserved-identifier)
                > class __IterableImmutableFindOf {                                                     // NOLINT(bugprone-reserved-identifier)

                private:
                    using ConstIterator = __IteratorType;

                protected:
                    template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier)
                    auto findOf (
                            Size                                        count,
                            __CollectionType < ConstIterator >        & storeIn,
                            __FromIterableType                  const & from
                    ) const noexcept -> __CollectionType < ConstIterator > &;

                protected:
                    template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier)
                    auto findOf (
                            Size                        count,
                            __FromIterableType  const & from
                    ) const noexcept -> __CollectionType < ConstIterator >;

                protected:
                    auto findFirstOf (
                            __FromIterableType const & from
                    ) const noexcept -> ConstIterator;

                protected:
                    auto findLastOf (
                            __FromIterableType const & from
                    ) const noexcept -> ConstIterator;

                protected:
                    template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier)
                    auto findAllOf (
                            __CollectionType < ConstIterator >        & storeIn,
                            __FromIterableType                  const & from
                    ) const noexcept -> __CollectionType < ConstIterator > &;

                protected:
                    template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier)
                    auto findAllOf (
                            __FromIterableType const & from
                    ) const noexcept -> __CollectionType < ConstIterator >;

                protected:
                    template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier)
                    auto findNotOf (
                            Size                                        count,
                            __CollectionType < ConstIterator >        & storeIn,
                            __FromIterableType                  const & from
                    ) const noexcept -> __CollectionType < ConstIterator > &;

                protected:
                    template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier)
                    auto findNotOf (
                            Size                        count,
                            __FromIterableType  const & from
                    ) const noexcept -> __CollectionType < ConstIterator >;

                protected:
                    auto findFirstNotOf (
                            __FromIterableType const & from
                    ) const noexcept -> ConstIterator;

                protected:
                    auto findLastNotOf (
                            __FromIterableType const & from
                    ) const noexcept -> ConstIterator;

                protected:
                    template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier)
                    auto findAllNotOf (
                            __CollectionType < ConstIterator >        & storeIn,
                            __FromIterableType                  const & from
                    ) const noexcept -> __CollectionType < ConstIterator > &;

                protected:
                    template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier)
                    auto findAllNotOf (
                            __FromIterableType const & from
                    ) const noexcept -> __CollectionType < ConstIterator >;
                };

            }
        }
    }
}

#include "../iterator/impl/IteratorFind.hpp"

#endif // __CDS_SHARED_ITERABLE_IMMUTABLE_FIND_OF_HPP__
