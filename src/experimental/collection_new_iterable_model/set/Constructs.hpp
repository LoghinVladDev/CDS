//
// Created by loghin on 7/23/2022.
//

#ifndef __CDS_EX_SET_CONSTRUCTS_HPP__
#define __CDS_EX_SET_CONSTRUCTS_HPP__

namespace cds {                 // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {    // NOLINT(modernize-concat-nested-namespaces)

        namespace meta {

            template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
            constexpr auto isValidSetElement () noexcept -> bool {

                return
                        cds :: meta :: equalToPossible < __ElementType, __ElementType > () ||
                        cds :: meta :: isDerivedFrom < __ElementType, cds :: Object > ();
            }

        }

        template <
                typename __ElementType, // NOLINT(bugprone-reserved-identifier)
                cds :: meta :: EnableIf <
                        cds :: experimental :: meta :: isValidSetElement < __ElementType > ()
                > = 0
        > class Set;

        namespace __hidden {    // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier)
            namespace __impl {  // NOLINT(bugprone-reserved-identifier)

                template <
                        typename __ElementType, // NOLINT(bugprone-reserved-identifier)
                        cds :: meta :: EnableIf <
                                cds :: experimental :: meta :: isValidSetElement < __ElementType > ()
                        > __enabler = 0         // NOLINT(bugprone-reserved-identifier)
                > using __SetFindUniqueClient = // NOLINT(bugprone-reserved-identifier)
                        __FindUniqueImmutablePrimitiveClient <
                                cds :: experimental :: Set < __ElementType, __enabler >,
                                __ElementType,
                                __ElementType,
                                false
                        >;

            }
        }
    }
}

#endif // __CDS_EX_SET_CONSTRUCTS_HPP__
