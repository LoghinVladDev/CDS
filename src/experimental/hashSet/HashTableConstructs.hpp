//
// Created by loghin on 6/23/22.
//

#ifndef __CDS_EX_HASH_SET_HASH_TABLE_CONSTRUCTS_HPP__
#define __CDS_EX_HASH_SET_HASH_TABLE_CONSTRUCTS_HPP__

namespace cds {                 // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {    // NOLINT(modernize-concat-nested-namespaces)
        namespace __hidden {    // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier)
            namespace __impl {  // NOLINT(bugprone-reserved-identifier)

                template < typename __ElementType >                                                                         // NOLINT(bugprone-reserved-identifier)
                using __HashSetDataNode = cds :: __hidden :: __impl :: __allocation :: __RawContainer < __ElementType >;    // NOLINT(bugprone-reserved-identifier)


                template < typename __ElementType >             // NOLINT(bugprone-reserved-identifier)
                constexpr auto __hashSetDataNodeKeyExtractor (  // NOLINT(bugprone-reserved-identifier)
                        __HashSetDataNode < __ElementType > const & dataNode
                ) noexcept -> __ElementType const & {

                    return dataNode.data();
                }


                template < typename __ElementType >             // NOLINT(bugprone-reserved-identifier)
                constexpr auto __hashSetDataNodeDestructor (      // NOLINT(bugprone-reserved-identifier)
                        __HashSetDataNode < __ElementType > const & dataNode
                ) noexcept -> void {

                    dataNode.destruct();
                }


                template < typename __ElementType >             // NOLINT(bugprone-reserved-identifier)
                constexpr auto __hashSetDataNodeCopyConstructor ( // NOLINT(bugprone-reserved-identifier)
                        __HashSetDataNode < __ElementType >       & destinationDataNode,
                        __HashSetDataNode < __ElementType > const & sourceDataNode
                ) noexcept -> void {

                    destinationDataNode.construct ( sourceDataNode.data() );
                }


                template < typename __ElementType >             // NOLINT(bugprone-reserved-identifier)
                constexpr auto __hashSetDataNodeEquals (          // NOLINT(bugprone-reserved-identifier)
                        __HashSetDataNode < __ElementType > const & leftNode,
                        __HashSetDataNode < __ElementType > const & rightNode
                ) noexcept -> bool {

                    return
                            cds :: meta :: equals ( leftNode.data(), rightNode.data() );
                }

            }
        }
    }
}

#endif // __CDS_EX_HASH_SET_HASH_TABLE_CONSTRUCTS_HPP__
