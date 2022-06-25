//
// Created by loghin on 6/25/22.
//

#ifndef __CDS_LINKED_HASH_SET_SINGLE_LINKED_LIST_CONSTRUCTS_HPP__
#define __CDS_LINKED_HASH_SET_SINGLE_LINKED_LIST_CONSTRUCTS_HPP__

namespace cds {             // NOLINT(modernize-concat-nested-namespaces)
    namespace __hidden {    // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier)
        namespace __impl {  // NOLINT(bugprone-reserved-identifier)

            template < typename __ElementType >             // NOLINT(bugprone-reserved-identifier)
            constexpr auto __linkedHashSetElementDestruct ( // NOLINT(bugprone-reserved-identifier)
                    __ElementType & element
            ) noexcept -> void {

                (void) element;
            }


            template < typename __ElementType >                     // NOLINT(bugprone-reserved-identifier)
            constexpr auto __linkedHashSetElementCopyConstruct (    // NOLINT(bugprone-reserved-identifier)
                    __ElementType       & destinationElement,
                    __ElementType const & sourceElement
            ) noexcept -> void {

                destinationElement = sourceElement;
            }

        }
    }
}

#endif // __CDS_LINKED_HASH_SET_SINGLE_LINKED_LIST_CONSTRUCTS_HPP__
