//
// Created by loghin on 6/22/22.
//

#ifndef __CDS_HASH_MAP_HASH_TABLE_CONSTRUCTS_HPP__
#define __CDS_HASH_MAP_HASH_TABLE_CONSTRUCTS_HPP__

namespace cds {             // NOLINT(modernize-concat-nested-namespaces)
    namespace __hidden {    // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier)
        namespace __impl {  // NOLINT(bugprone-reserved-identifier)

            template <
                    typename __KeyType,                         // NOLINT(bugprone-reserved-identifier)
                    typename __ValueType                        // NOLINT(bugprone-reserved-identifier)
            > constexpr auto __hashMapDataNodeKeyExtractor (    // NOLINT(bugprone-reserved-identifier)
                    typename Map < __KeyType, __ValueType > :: EntryType const & dataNode
            ) noexcept -> __KeyType const & {

                return dataNode.key();
            }


            template <
                    typename __KeyType,                         // NOLINT(bugprone-reserved-identifier)
                    typename __ValueType                        // NOLINT(bugprone-reserved-identifier)
            > constexpr auto __hashMapDataNodeDestructor (      // NOLINT(bugprone-reserved-identifier)
                    typename Map < __KeyType, __ValueType > :: EntryType & dataNode
            ) noexcept -> void {

                dataNode.~__MapEntry < __KeyType, __ValueType > ();
            }


            template <
                    typename __KeyType,                         // NOLINT(bugprone-reserved-identifier)
                    typename __ValueType,                       // NOLINT(bugprone-reserved-identifier)
                    cds :: meta :: EnableIf <
                            cds :: meta :: isCopyConstructible < __KeyType > () &&
                            cds :: meta :: isCopyConstructible < __ValueType > ()
                    > = 0
            > constexpr auto __hashMapDataNodeDelayedCopyConstructor ( // NOLINT(bugprone-reserved-identifier)
                    typename Map < __KeyType, __ValueType > :: EntryType        & destinationDataNode,
                    typename Map < __KeyType, __ValueType > :: EntryType  const & sourceDataNode
            ) noexcept -> void {

                new ( & destinationDataNode ) typename Map < __KeyType, __ValueType > :: EntryType ( sourceDataNode );
            }


            template <
                    typename __KeyType,                         // NOLINT(bugprone-reserved-identifier)
                    typename __ValueType,                       // NOLINT(bugprone-reserved-identifier)
                    cds :: meta :: EnableIf <
                            ! cds :: meta :: isCopyConstructible < __KeyType > () ||
                            ! cds :: meta :: isCopyConstructible < __ValueType > ()
                    > = 0
            > constexpr auto __hashMapDataNodeDelayedCopyConstructor ( // NOLINT(bugprone-reserved-identifier)
                    typename Map < __KeyType, __ValueType > :: EntryType        & destinationDataNode,
                    typename Map < __KeyType, __ValueType > :: EntryType  const & sourceDataNode
            ) noexcept -> void {

            }


            template <
                    typename __KeyType,                         // NOLINT(bugprone-reserved-identifier)
                    typename __ValueType                        // NOLINT(bugprone-reserved-identifier)
            > constexpr auto __hashMapDataNodeCopyConstructor ( // NOLINT(bugprone-reserved-identifier)
                    typename Map < __KeyType, __ValueType > :: EntryType        & destinationDataNode,
                    typename Map < __KeyType, __ValueType > :: EntryType  const & sourceDataNode
            ) noexcept -> void {

                __hashMapDataNodeDelayedCopyConstructor < __KeyType, __ValueType > ( destinationDataNode, sourceDataNode );
            }


            template <
                    typename __KeyType,                         // NOLINT(bugprone-reserved-identifier)
                    typename __ValueType                        // NOLINT(bugprone-reserved-identifier)
            > constexpr auto __hashMapDataNodeEquals (          // NOLINT(bugprone-reserved-identifier)
                    typename Map < __KeyType, __ValueType > :: EntryType const & leftNode,
                    typename Map < __KeyType, __ValueType > :: EntryType const & rightNode
            ) noexcept -> bool {

                return
                        cds :: meta :: equals ( leftNode.key(), rightNode.key() ) &&
                        cds :: meta :: equals ( leftNode.value(), rightNode.value() );
            }

        }
    }
}

#endif // __CDS_HASH_MAP_HASH_TABLE_CONSTRUCTS_HPP__
