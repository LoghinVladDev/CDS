//
// Created by stefan on 28.08.2022.
//

#ifndef __CDS_TREE_SET_HPP__
#define __CDS_TREE_SET_HPP__

namespace cds {                 // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {


        template < typename __ElementType >                             // NOLINT(bugprone-reserved-identifier)
        TreeSet < __ElementType > :: TreeSet () noexcept = default;


        template < typename __ElementType >                             // NOLINT(bugprone-reserved-identifier)
        TreeSet < __ElementType > :: TreeSet (
                TreeSet const & set
        ) noexcept {

            this->__rbt_copyCleared (
                    set,
                    & __hidden :: __impl :: __treeSetCopyConstructor < __ElementType >
            );
        }

        template < typename __ElementType >                             // NOLINT(bugprone-reserved-identifier)
        auto TreeSet < __ElementType > :: clear () noexcept -> void {

            this->__rbt_clear();
        }

        template < typename __ElementType >                             // NOLINT(bugprone-reserved-identifier)
        auto TreeSet < __ElementType > :: remove (
                __ElementType const & element
        ) noexcept -> bool {

            this->__rbt_remove ( element );
        }
    }
}

#endif //__CDS_TREE_SET_HPP__
