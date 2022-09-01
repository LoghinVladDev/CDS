//
// Created by stefan on 28.08.2022.
//

#ifndef __CDS_TREE_SET_CONSTRUCTS_HPP__
#define __CDS_TREE_SET_CONSTRUCTS_HPP__

namespace cds {                 // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {

        template < typename __ElementType >             // NOLINT(bugprone-reserved-identifier)
        class TreeSet;

        namespace __hidden {    // NOLINT(modernize-concat-nested-namespaces)
            namespace __impl {

                template < typename __ElementType >     // NOLINT(bugprone-reserved-identifier)
                auto __treeSetKeyExtractor (            // NOLINT(bugprone-reserved-identifier)
                        __ElementType const & element
                ) noexcept -> __ElementType const & {

                    return element;
                }


                template < typename __ElementType >     // NOLINT(bugprone-reserved-identifier)
                auto __treeSetDestructor (              // NOLINT(bugprone-reserved-identifier)
                        __ElementType & element
                ) noexcept -> void {

                    element.~__ElementType();
                }


                template < typename __ElementType >     // NOLINT(bugprone-reserved-identifier)
                auto __treeSetCopyConstructor (         // NOLINT(bugprone-reserved-identifier)
                        __ElementType       & destination,
                        __ElementType const & source
                ) noexcept -> void {

                    (void) new ( & destination ) __ElementType ( source );
                }


                template < typename __ElementType >     // NOLINT(bugprone-reserved-identifier)
                using __TreeSetImplementation =         // NOLINT(bugprone-reserved-identifier)
                        __RedBlackTree <
                                __ElementType,
                                __ElementType,
                                & __treeSetKeyExtractor < __ElementType >,
                                & cds :: predicates :: lessThan < __ElementType >,
                                & cds :: meta :: equals < __ElementType >,
                                & __treeSetDestructor < __ElementType >
                        >;


                template < typename __ElementType >         // NOLINT(bugprone-reserved-identifier)
                using __TreeSetDispatcher =                 // NOLINT(bugprone-reserved-identifier)
                        typename __TreeSetImplementation <
                                __ElementType
                        > :: template __SetDispatcher <
                                TreeSet < __ElementType >
                        >;


                template < typename __ElementType >         // NOLINT(bugprone-reserved-identifier)
                using __TreeSetServer =                     // NOLINT(bugprone-reserved-identifier)
                        __SetServer <
                                cds :: experimental :: TreeSet < __ElementType >,
                                __ElementType
                        >;


                template < typename __ElementType >
            }
        }
    }
}

#endif //__CDS_TREE_SET_CONSTRUCTS_HPP__
