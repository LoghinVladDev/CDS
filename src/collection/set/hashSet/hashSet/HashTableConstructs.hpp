//
// Created by loghin on 6/23/22.
//

#ifndef __CDS_HASH_SET_HASH_TABLE_CONSTRUCTS_HPP__
#define __CDS_HASH_SET_HASH_TABLE_CONSTRUCTS_HPP__

namespace cds {                 // NOLINT(modernize-concat-nested-namespaces)
    namespace __hidden {    // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier)
        namespace __impl {  // NOLINT(bugprone-reserved-identifier)


            template < typename __ElementType >             // NOLINT(bugprone-reserved-identifier)
            constexpr auto __hashSetKeyExtractor (  // NOLINT(bugprone-reserved-identifier)
                    __ElementType const & element
            ) noexcept -> __ElementType const & {

                return element;
            }


            template < typename __ElementType >             // NOLINT(bugprone-reserved-identifier)
            constexpr auto __hashSetDestructor (      // NOLINT(bugprone-reserved-identifier)
                    __ElementType & element
            ) noexcept -> void {

                element.~__ElementType();
            }


            template <
                    typename __ElementType, // NOLINT(bugprone-reserved-identifier)
                    cds :: meta :: EnableIf < cds :: meta :: isCopyConstructible < __ElementType > () > = 0
            > constexpr auto __hashSetDelayedCopyConstructor ( // NOLINT(bugprone-reserved-identifier)
                    __ElementType       & destinationDataNode,
                    __ElementType const & sourceDataNode
            ) noexcept -> void {

                new ( & destinationDataNode ) __ElementType ( sourceDataNode );
            }


            template <
                    typename __ElementType, // NOLINT(bugprone-reserved-identifier)
                    cds :: meta :: EnableIf < ! cds :: meta :: isCopyConstructible < __ElementType > () > = 0
            > constexpr auto __hashSetDelayedCopyConstructor ( // NOLINT(bugprone-reserved-identifier)
                    __ElementType       & destinationDataNode,
                    __ElementType const & sourceDataNode
            ) noexcept -> void {

            }


            template <
                    typename __ElementType // NOLINT(bugprone-reserved-identifier)
            > constexpr auto __hashSetCopyConstructor ( // NOLINT(bugprone-reserved-identifier)
                    __ElementType       & destinationDataNode,
                    __ElementType const & sourceDataNode
            ) noexcept -> void {

                __hashSetDelayedCopyConstructor ( destinationDataNode, sourceDataNode );
            }

        }
    }
}

#endif // __CDS_HASH_SET_HASH_TABLE_CONSTRUCTS_HPP__
