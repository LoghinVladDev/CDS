//
// Created by loghin on 6/15/22.
//

#ifndef __CDS_EX_HASH_MAP_ASSOCIATOR_HPP__
#define __CDS_EX_HASH_MAP_ASSOCIATOR_HPP__

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental { // NOLINT(modernize-concat-nested-namespaces)
        namespace __hidden { // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier)
            namespace __impl { // NOLINT(bugprone-reserved-identifier)

                template < typename __KeyType, typename __ValueType, typename __HashCalculator > // NOLINT(bugprone-reserved-identifier)
                class __HashEntryArrayAssociator : public __EntryArray < __ValueType > :: template __EntryAssociator < __KeyType > { // NOLINT(bugprone-reserved-identifier)

                private:
                    struct HashArrayAssociationData {
                        __KeyType   const * _pKey;
                        Index               _equalKeyOffset;
                    };

                private:
                    struct Node {
                        HashArrayAssociationData  _data;
                        Node                    * _pNext;
                        Node                    * _pPrevious;
                    };

                private:
                    struct EqualKeyList {
                        Node  * _pHead;
                        Index   _keyGroupIndex;
                        Index   _keyGroupSize;
                    };

                private:
                    EqualKeyList  * _pNodeList { nullptr };

                private:
                    Index            _globalIndexAdjustment { 0 };

                private:
                    __HashCalculator _hashCalculator;

                public:
                    auto clear () noexcept -> void override {

                        this->__EntryAssociator :: clear ();

                        if ( this->_pNodeList != nullptr ) {
                            for ( Index listIndex = 0; listIndex < this->_hashCalculator.getBoundary(); ++ listIndex ) {

                                EqualKeyList & list = this->_pNodeList [ listIndex ];
                                while ( list._pHead != nullptr ) {
                                    auto pCopy  = list._pHead;
                                    list._pHead = list._pHead->_pNext;
                                    Memory :: instance().destroy ( pCopy );
                                }
                            }

                            Memory :: instance().destroyArray ( this->_pNodeList );
                        }

                        this->_globalIndexAdjustment = 0;
                    }

                public:
                    ~__HashEntryArrayAssociator () noexcept override {
                        this-> __HashEntryArrayAssociator :: clear();
                    }

                public:
                    __CDS_Explicit constexpr __HashEntryArrayAssociator (
                            __EntryArray < __ValueType > & entryArray
                    ) noexcept;

                protected:
                    auto getAssociation (
                            __KeyType const & key
                    ) noexcept -> Index override {

                        if ( this->_pNodeList == nullptr ) {
                            this->_pNodeList = Memory :: instance().createArray < EqualKeyList > ( this->_hashCalculator.getBoundary() );

                            for ( Index listIndex = 0; listIndex < this->_hashCalculator.getBoundary (); ++ listIndex ) {
                                this->_pNodeList [ listIndex ] = { nullptr, 0, 0 };
                            }
                        }

                        auto               hashValue        = this->_hashCalculator ( key );
                        EqualKeyList     & list             = this->_pNodeList [ hashValue ];
                        Node             * pListHead        = list._pHead;
                        Node             * pKeyNode         = nullptr;
                        Index              equalKeyOffset   = list._keyGroupSize;

                        while ( pListHead != nullptr ) {

                            if ( cds :: meta :: equals ( * pListHead->_data._pKey, key ) ) {
                                equalKeyOffset  = pListHead->_data._equalKeyOffset;
                                pKeyNode        = pListHead;

                                break;
                            }

                            pListHead = pListHead->_pNext;
                        }

                        if ( pKeyNode == nullptr ) {
                            pKeyNode                        = Memory :: instance().create < Node > ();

                            pKeyNode->_pPrevious            = nullptr;
                            pKeyNode->_pNext                = list._pHead;
                            pKeyNode->_data._pKey           = & key;
                            pKeyNode->_data._equalKeyOffset = list._keyGroupSize ++;

                            if ( list._pHead != nullptr ) {
                                list._pHead->_pPrevious = pKeyNode;
                            }

                            list._pHead             = pKeyNode;

                            pKeyNode                = nullptr;
                        }

                        Index actualIndex =
                                this->_globalIndexAdjustment +
                                list._keyGroupIndex +
                                ( list._keyGroupSize - equalKeyOffset - 1 );

                        if ( pKeyNode != nullptr ) {
                            return actualIndex;
                        }

                        this->rightShiftFrom ( actualIndex );

                        if ( ( hashValue << 1 ) < this->_hashCalculator.getBoundary () ) {
                            for ( Index downgradeIndex = hashValue; downgradeIndex >= 0; -- downgradeIndex ) {
                                -- this->_pNodeList [ downgradeIndex ]._keyGroupIndex;
                            }

                            ++ this->_globalIndexAdjustment;
                        } else {
                            for ( Index upgradeIndex = hashValue + 1; upgradeIndex < this->_hashCalculator.getBoundary(); ++ upgradeIndex ) {
                                ++ this->_pNodeList [ upgradeIndex ]._keyGroupIndex;
                            }
                        }

                        return actualIndex;
                    }
                };

            }
        }
    }
}

#endif // __CDS_EX_HASH_MAP_ASSOCIATOR_HPP__
