//
// Created by loghin on 6/22/22.
//

#ifndef __CDS_EX_HASH_MAP_HASH_TABLE_CONSTRUCTS_HPP__
#define __CDS_EX_HASH_MAP_HASH_TABLE_CONSTRUCTS_HPP__

namespace cds {                 // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {    // NOLINT(modernize-concat-nested-namespaces)
        namespace __hidden {    // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier)
            namespace __impl {  // NOLINT(bugprone-reserved-identifier)

                template <
                        typename __KeyType,     // NOLINT(bugprone-reserved-identifier)
                        typename __ValueType    // NOLINT(bugprone-reserved-identifier)
                > struct __HashMapDataNode {    // NOLINT(bugprone-reserved-identifier)
                    cds :: __hidden :: __impl :: __allocation :: __RawContainer < __KeyType >   _key;
                    cds :: __hidden :: __impl :: __allocation :: __RawContainer < __ValueType > _value;
                };


                template <
                        typename __KeyType,                         // NOLINT(bugprone-reserved-identifier)
                        typename __ValueType                        // NOLINT(bugprone-reserved-identifier)
                > constexpr auto __hashMapDataNodeKeyExtractor (    // NOLINT(bugprone-reserved-identifier)
                        __HashMapDataNode < __KeyType, __ValueType > const & dataNode
                ) noexcept -> __KeyType const & {

                    return dataNode._key.data();
                }


                template <
                        typename __KeyType,                         // NOLINT(bugprone-reserved-identifier)
                        typename __ValueType                        // NOLINT(bugprone-reserved-identifier)
                > constexpr auto __hashMapDataNodeDestructor (      // NOLINT(bugprone-reserved-identifier)
                        __HashMapDataNode < __KeyType, __ValueType > & dataNode
                ) noexcept -> void {

                    dataNode._key.destruct();
                    dataNode._value.destruct();
                }


                template <
                        typename __KeyType,                         // NOLINT(bugprone-reserved-identifier)
                        typename __ValueType                        // NOLINT(bugprone-reserved-identifier)
                > constexpr auto __hashMapDataNodeCopyConstructor ( // NOLINT(bugprone-reserved-identifier)
                        __HashMapDataNode < __KeyType, __ValueType >        & destinationDataNode,
                        __HashMapDataNode < __KeyType, __ValueType >  const & sourceDataNode
                ) noexcept -> void {

                    destinationDataNode._key.construct ( sourceDataNode._key.data() );
                    destinationDataNode._value.construct ( sourceDataNode._value.data() );
                }

            }
        }
    }
}

#endif // __CDS_EX_HASH_MAP_HASH_TABLE_CONSTRUCTS_HPP__
