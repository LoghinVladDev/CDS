//
// Created by loghin on 6/27/22.
//

#ifndef __CDS_SHARED_FIND_BY_MUTABLE_COMPOSITE_CLIENT_HPP__
#define __CDS_SHARED_FIND_BY_MUTABLE_COMPOSITE_CLIENT_HPP__

#include "../../../iterator/IteratorFindStatements.hpp"

namespace cds {                 // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {    // NOLINT(modernize-concat-nested-namespaces)
        namespace __hidden {    // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier)
            namespace __impl {  // NOLINT(bugprone-reserved-identifier)

                template <
                        typename __IterableType,                // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType,                 // NOLINT(bugprone-reserved-identifier)
                        typename __IteratorType                 // NOLINT(bugprone-reserved-identifier)
                > class __FindByMutableCompositeClient {        // NOLINT(bugprone-reserved-identifier)

                private:
                    using Iterator = __IteratorType;

                protected:
                    template <
                            template < typename ... > class __CollectionType,   // NOLINT(bugprone-reserved-identifier)
                            typename                        __Predicate         // NOLINT(bugprone-reserved-identifier)
                    > auto findThat (
                            Size                                        count,
                            __CollectionType < Iterator >             & storeIn,
                            __Predicate                         const & predicate
                    ) noexcept ( noexcept ( predicate ( cds :: meta :: referenceOf < __ElementType > () ) ) ) -> __CollectionType < Iterator > &;

                protected:
                    template <
                            template < typename ... > class __CollectionType,   // NOLINT(bugprone-reserved-identifier)
                            typename                        __Predicate         // NOLINT(bugprone-reserved-identifier)
                    > __CDS_NoDiscard auto findThat (
                            Size count,
                            __Predicate const & predicate
                    ) noexcept ( noexcept ( predicate ( cds :: meta :: referenceOf < __ElementType > () ) ) ) -> __CollectionType < Iterator >;

                protected:
                    template <
                            typename                        __Predicate         // NOLINT(bugprone-reserved-identifier)
                    > __CDS_NoDiscard auto findFirstThat (
                            __Predicate const & predicate
                    ) noexcept ( noexcept ( predicate ( cds :: meta :: referenceOf < __ElementType > () ) ) ) -> Iterator;

                protected:
                    template <
                            typename                        __Predicate         // NOLINT(bugprone-reserved-identifier)
                    > __CDS_NoDiscard auto findLastThat (
                            __Predicate const & predicate
                    ) noexcept ( noexcept ( predicate ( cds :: meta :: referenceOf < __ElementType > () ) ) ) -> Iterator;

                protected:
                    template <
                            template < typename ... > class __CollectionType,   // NOLINT(bugprone-reserved-identifier)
                            typename                        __Predicate         // NOLINT(bugprone-reserved-identifier)
                    > auto findAllThat (
                            __CollectionType < Iterator >             & storeIn,
                            __Predicate                         const & predicate
                    ) noexcept ( noexcept ( predicate ( cds :: meta :: referenceOf < __ElementType > () ) ) ) -> __CollectionType < Iterator > &;

                protected:
                    template <
                            template < typename ... > class __CollectionType,   // NOLINT(bugprone-reserved-identifier)
                            typename                        __Predicate         // NOLINT(bugprone-reserved-identifier)
                    > __CDS_NoDiscard auto findAllThat (
                            __Predicate const & predicate
                    ) noexcept ( noexcept ( predicate ( cds :: meta :: referenceOf < __ElementType > () ) ) ) -> __CollectionType < Iterator >;

                };


                template <
                        typename __IterableType,                // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType,                 // NOLINT(bugprone-reserved-identifier)
                        typename __IteratorType                 // NOLINT(bugprone-reserved-identifier)
                > using __LocalFindByMutableCompositeClient =   // NOLINT(bugprone-reserved-identifier)
                        __FindByMutableCompositeClient <
                                __IterableType,
                                __ElementType,
                                __IteratorType
                        >;

            }
        }
    }
}

#include "../../../iterator/impl/IteratorFindStatements.hpp"

#endif // __CDS_SHARED_FIND_BY_MUTABLE_COMPOSITE_CLIENT_HPP__
