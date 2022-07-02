//
// Created by loghin on 6/30/22.
//

#ifndef __CDS_SHARED_FUNCTIONAL_INDICES_CLIENT_HPP__
#define __CDS_SHARED_FUNCTIONAL_INDICES_CLIENT_HPP__

namespace cds {                 // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {    // NOLINT(modernize-concat-nested-namespaces)
        namespace __hidden {    // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier)
            namespace __impl {  // NOLINT(bugprone-reserved-identifier)

                template <
                        typename __ReceiverType,    // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType      // NOLINT(bugprone-reserved-identifier)
                > class __FunctionalIndicesClient { // NOLINT(bugprone-reserved-identifier)

                private:
                    using ElementType = __ElementType;

                protected:
                    template <
                            typename __CollectionType,  // NOLINT(bugprone-reserved-identifier)
                            typename __Predicate        // NOLINT(bugprone-reserved-identifier)
                    > auto indicesOfThat (
                            Size                        count,
                            __CollectionType          & storeIn,
                            __Predicate         const & predicate
                    ) const noexcept ( noexcept ( predicate ( cds :: meta :: referenceOf < ElementType const > () ) ) ) -> __CollectionType &;

                protected:
                    template <
                            template < typename ... > class __CollectionType,   // NOLINT(bugprone-reserved-identifier)
                            typename __Predicate                                // NOLINT(bugprone-reserved-identifier)
                    > __CDS_NoDiscard auto indicesOfThat (
                            Size                count,
                            __Predicate const & predicate
                    ) const noexcept ( noexcept ( predicate ( cds :: meta :: referenceOf < ElementType const > () ) ) ) -> __CollectionType < Index >;

                protected:
                    template < typename __Predicate >   // NOLINT(bugprone-reserved-identifier)
                    __CDS_NoDiscard auto firstIndexOfThat (
                            __Predicate const & predicate
                    ) const noexcept ( noexcept ( predicate ( cds :: meta :: referenceOf < ElementType const > () ) ) ) -> Index;

                protected:
                    template < typename __Predicate >   // NOLINT(bugprone-reserved-identifier)
                    __CDS_NoDiscard auto lastIndexOfThat (
                            __Predicate const & predicate
                    ) const noexcept ( noexcept ( predicate ( cds :: meta :: referenceOf < ElementType const > () ) ) ) -> Index;

                protected:
                    template <
                            typename __CollectionType,  // NOLINT(bugprone-reserved-identifier)
                            typename __Predicate        // NOLINT(bugprone-reserved-identifier)
                    > auto allIndicesOfThat (
                            __CollectionType          & storeIn,
                            __Predicate         const & predicate
                    ) const noexcept ( noexcept ( predicate ( cds :: meta :: referenceOf < ElementType const > () ) ) ) -> __CollectionType &;

                protected:
                    template <
                            template < typename ... > class __CollectionType,   // NOLINT(bugprone-reserved-identifier)
                            typename                        __Predicate         // NOLINT(bugprone-reserved-identifier)
                    > __CDS_NoDiscard auto allIndicesOfThat (
                            __Predicate const & predicate
                    ) const noexcept ( noexcept ( predicate ( cds :: meta :: referenceOf < ElementType const > () ) ) ) -> __CollectionType < Index >;
                };

            }
        }
    }
}

#endif // __CDS_SHARED_FUNCTIONAL_INDICES_CLIENT_HPP__
