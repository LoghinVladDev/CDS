//
// Created by loghin on 6/17/22.
//

#ifndef __CDS_EX_BASE_MAP_IMPL_HPP__
#define __CDS_EX_BASE_MAP_IMPL_HPP__

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental { // NOLINT(modernize-concat-nested-namespaces)
        namespace __hidden { // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier)
            namespace __impl { // NOLINT(bugprone-reserved-identifier)

                template < typename __ValueType >
                inline __ValueType persistentValue;

                template < typename __ValueType >
                inline __ValueType * persistentAddress = nullptr;


                template <
                        typename __KeyType, // NOLINT(bugprone-reserved-identifier)
                        typename __ValueType, // NOLINT(bugprone-reserved-identifier)
                        typename __KeySetType, // NOLINT(bugprone-reserved-identifier)
                        typename __ValueCollectionType, // NOLINT(bugprone-reserved-identifier)
                        typename __EntryAssociatorType, // NOLINT(bugprone-reserved-identifier)
                        cds :: meta :: EnableIf <
                                cds :: meta :: isDerivedFrom < __KeySetType, cds :: experimental :: Set < __KeyType > > () &&
                                cds :: meta :: isDerivedFrom < __ValueCollectionType, cds :: experimental :: Collection < __ValueType > > ()
                        > __enabler // NOLINT(bugprone-reserved-identifier)
                > __CDS_OptimalInline auto __BaseMap <
                        __KeyType,
                        __ValueType,
                        __KeySetType,
                        __ValueCollectionType,
                        __EntryAssociatorType,
                        __enabler
                > :: delegateIterator (
                        DelegateIteratorRequestType requestType
                ) noexcept -> cds :: UniquePointer < DelegateIterator > {

                    return nullptr;
                }


                template <
                        typename __KeyType, // NOLINT(bugprone-reserved-identifier)
                        typename __ValueType, // NOLINT(bugprone-reserved-identifier)
                        typename __KeySetType, // NOLINT(bugprone-reserved-identifier)
                        typename __ValueCollectionType, // NOLINT(bugprone-reserved-identifier)
                        typename __EntryAssociatorType, // NOLINT(bugprone-reserved-identifier)
                        cds :: meta :: EnableIf <
                                cds :: meta :: isDerivedFrom < __KeySetType, cds :: experimental :: Set < __KeyType > > () &&
                                cds :: meta :: isDerivedFrom < __ValueCollectionType, cds :: experimental :: Collection < __ValueType > > ()
                        > __enabler // NOLINT(bugprone-reserved-identifier)
                > __CDS_OptimalInline auto __BaseMap <
                        __KeyType,
                        __ValueType,
                        __KeySetType,
                        __ValueCollectionType,
                        __EntryAssociatorType,
                        __enabler
                > :: delegateConstIterator (
                        DelegateIteratorRequestType requestType
                ) const noexcept -> cds :: UniquePointer < DelegateConstIterator > {

                    return nullptr;
                }


                template <
                        typename __KeyType, // NOLINT(bugprone-reserved-identifier)
                        typename __ValueType, // NOLINT(bugprone-reserved-identifier)
                        typename __KeySetType, // NOLINT(bugprone-reserved-identifier)
                        typename __ValueCollectionType, // NOLINT(bugprone-reserved-identifier)
                        typename __EntryAssociatorType, // NOLINT(bugprone-reserved-identifier)
                        cds :: meta :: EnableIf <
                                cds :: meta :: isDerivedFrom < __KeySetType, cds :: experimental :: Set < __KeyType > > () &&
                                cds :: meta :: isDerivedFrom < __ValueCollectionType, cds :: experimental :: Collection < __ValueType > > ()
                        > __enabler // NOLINT(bugprone-reserved-identifier)
                > constexpr __BaseMap <
                        __KeyType,
                        __ValueType,
                        __KeySetType,
                        __ValueCollectionType,
                        __EntryAssociatorType,
                        __enabler
                > :: __BaseMap () noexcept :
                        _associator ( this->_valueCollection ) {

                }


                template <
                        typename __KeyType, // NOLINT(bugprone-reserved-identifier)
                        typename __ValueType, // NOLINT(bugprone-reserved-identifier)
                        typename __KeySetType, // NOLINT(bugprone-reserved-identifier)
                        typename __ValueCollectionType, // NOLINT(bugprone-reserved-identifier)
                        typename __EntryAssociatorType, // NOLINT(bugprone-reserved-identifier)
                        cds :: meta :: EnableIf <
                                cds :: meta :: isDerivedFrom < __KeySetType, cds :: experimental :: Set < __KeyType > > () &&
                                cds :: meta :: isDerivedFrom < __ValueCollectionType, cds :: experimental :: Collection < __ValueType > > ()
                        > __enabler // NOLINT(bugprone-reserved-identifier)
                > __BaseMap <
                        __KeyType,
                        __ValueType,
                        __KeySetType,
                        __ValueCollectionType,
                        __EntryAssociatorType,
                        __enabler
                > :: __BaseMap (
                        __BaseMap const & map
                ) noexcept :
                        _associator ( this->_valueCollection ) {

                }


                template <
                        typename __KeyType, // NOLINT(bugprone-reserved-identifier)
                        typename __ValueType, // NOLINT(bugprone-reserved-identifier)
                        typename __KeySetType, // NOLINT(bugprone-reserved-identifier)
                        typename __ValueCollectionType, // NOLINT(bugprone-reserved-identifier)
                        typename __EntryAssociatorType, // NOLINT(bugprone-reserved-identifier)
                        cds :: meta :: EnableIf <
                                cds :: meta :: isDerivedFrom < __KeySetType, cds :: experimental :: Set < __KeyType > > () &&
                                cds :: meta :: isDerivedFrom < __ValueCollectionType, cds :: experimental :: Collection < __ValueType > > ()
                        > __enabler // NOLINT(bugprone-reserved-identifier)
                > constexpr __BaseMap <
                        __KeyType,
                        __ValueType,
                        __KeySetType,
                        __ValueCollectionType,
                        __EntryAssociatorType,
                        __enabler
                > :: __BaseMap (
                        __BaseMap && map
                ) noexcept :
                        _associator ( this->_valueCollection ) {

                }


                template <
                        typename __KeyType, // NOLINT(bugprone-reserved-identifier)
                        typename __ValueType, // NOLINT(bugprone-reserved-identifier)
                        typename __KeySetType, // NOLINT(bugprone-reserved-identifier)
                        typename __ValueCollectionType, // NOLINT(bugprone-reserved-identifier)
                        typename __EntryAssociatorType, // NOLINT(bugprone-reserved-identifier)
                        cds :: meta :: EnableIf <
                                cds :: meta :: isDerivedFrom < __KeySetType, cds :: experimental :: Set < __KeyType > > () &&
                                cds :: meta :: isDerivedFrom < __ValueCollectionType, cds :: experimental :: Collection < __ValueType > > ()
                        > __enabler // NOLINT(bugprone-reserved-identifier)
                > __BaseMap <
                        __KeyType,
                        __ValueType,
                        __KeySetType,
                        __ValueCollectionType,
                        __EntryAssociatorType,
                        __enabler
                > :: ~__BaseMap () noexcept {

                    (void) this->__BaseMap :: clear();
                }


                template <
                        typename __KeyType, // NOLINT(bugprone-reserved-identifier)
                        typename __ValueType, // NOLINT(bugprone-reserved-identifier)
                        typename __KeySetType, // NOLINT(bugprone-reserved-identifier)
                        typename __ValueCollectionType, // NOLINT(bugprone-reserved-identifier)
                        typename __EntryAssociatorType, // NOLINT(bugprone-reserved-identifier)
                        cds :: meta :: EnableIf <
                                cds :: meta :: isDerivedFrom < __KeySetType, cds :: experimental :: Set < __KeyType > > () &&
                                cds :: meta :: isDerivedFrom < __ValueCollectionType, cds :: experimental :: Collection < __ValueType > > ()
                        > __enabler // NOLINT(bugprone-reserved-identifier)
                > auto __BaseMap <
                        __KeyType,
                        __ValueType,
                        __KeySetType,
                        __ValueCollectionType,
                        __EntryAssociatorType,
                        __enabler
                > :: get (
                        KeyType const & key
                ) noexcept (false) -> ValueType & {

                    return persistentValue < __ValueType >;
                }


                template <
                        typename __KeyType, // NOLINT(bugprone-reserved-identifier)
                        typename __ValueType, // NOLINT(bugprone-reserved-identifier)
                        typename __KeySetType, // NOLINT(bugprone-reserved-identifier)
                        typename __ValueCollectionType, // NOLINT(bugprone-reserved-identifier)
                        typename __EntryAssociatorType, // NOLINT(bugprone-reserved-identifier)
                        cds :: meta :: EnableIf <
                                cds :: meta :: isDerivedFrom < __KeySetType, cds :: experimental :: Set < __KeyType > > () &&
                                cds :: meta :: isDerivedFrom < __ValueCollectionType, cds :: experimental :: Collection < __ValueType > > ()
                        > __enabler // NOLINT(bugprone-reserved-identifier)
                > auto __BaseMap <
                        __KeyType,
                        __ValueType,
                        __KeySetType,
                        __ValueCollectionType,
                        __EntryAssociatorType,
                        __enabler
                > :: get (
                        KeyType const & key
                ) const noexcept (false) -> ValueType const & {

                    return persistentValue < __ValueType >;
                }


                template <
                        typename __KeyType, // NOLINT(bugprone-reserved-identifier)
                        typename __ValueType, // NOLINT(bugprone-reserved-identifier)
                        typename __KeySetType, // NOLINT(bugprone-reserved-identifier)
                        typename __ValueCollectionType, // NOLINT(bugprone-reserved-identifier)
                        typename __EntryAssociatorType, // NOLINT(bugprone-reserved-identifier)
                        cds :: meta :: EnableIf <
                                cds :: meta :: isDerivedFrom < __KeySetType, cds :: experimental :: Set < __KeyType > > () &&
                                cds :: meta :: isDerivedFrom < __ValueCollectionType, cds :: experimental :: Collection < __ValueType > > ()
                        > __enabler // NOLINT(bugprone-reserved-identifier)
                > auto __BaseMap <
                        __KeyType,
                        __ValueType,
                        __KeySetType,
                        __ValueCollectionType,
                        __EntryAssociatorType,
                        __enabler
                > :: pNewInsert (
                        ElementType const & referenceElement
                ) noexcept -> ElementType * & {

                    return this->_pInsertTemporary;
                }


                template <
                        typename __KeyType, // NOLINT(bugprone-reserved-identifier)
                        typename __ValueType, // NOLINT(bugprone-reserved-identifier)
                        typename __KeySetType, // NOLINT(bugprone-reserved-identifier)
                        typename __ValueCollectionType, // NOLINT(bugprone-reserved-identifier)
                        typename __EntryAssociatorType, // NOLINT(bugprone-reserved-identifier)
                        cds :: meta :: EnableIf <
                                cds :: meta :: isDerivedFrom < __KeySetType, cds :: experimental :: Set < __KeyType > > () &&
                                cds :: meta :: isDerivedFrom < __ValueCollectionType, cds :: experimental :: Collection < __ValueType > > ()
                        > __enabler // NOLINT(bugprone-reserved-identifier)
                > auto __BaseMap <
                        __KeyType,
                        __ValueType,
                        __KeySetType,
                        __ValueCollectionType,
                        __EntryAssociatorType,
                        __enabler
                > :: pNewInsertPost () noexcept -> void {

                    auto const & mappedKeyReference = this->_pInsertTemporary->moveOrCopyKeyTo ( this->_keySet );
                    this->_pInsertTemporary->moveOrCopyValueTo ( mappedKeyReference, this->_associator );

                    Memory :: instance().destroy ( cds :: exchange ( this->_pInsertTemporary, nullptr ) );
                }


                template <
                        typename __KeyType, // NOLINT(bugprone-reserved-identifier)
                        typename __ValueType, // NOLINT(bugprone-reserved-identifier)
                        typename __KeySetType, // NOLINT(bugprone-reserved-identifier)
                        typename __ValueCollectionType, // NOLINT(bugprone-reserved-identifier)
                        typename __EntryAssociatorType, // NOLINT(bugprone-reserved-identifier)
                        cds :: meta :: EnableIf <
                                cds :: meta :: isDerivedFrom < __KeySetType, cds :: experimental :: Set < __KeyType > > () &&
                                cds :: meta :: isDerivedFrom < __ValueCollectionType, cds :: experimental :: Collection < __ValueType > > ()
                        > __enabler // NOLINT(bugprone-reserved-identifier)
                > auto __BaseMap <
                        __KeyType,
                        __ValueType,
                        __KeySetType,
                        __ValueCollectionType,
                        __EntryAssociatorType,
                        __enabler
                > :: contains (
                        ElementType const & entry
                ) const noexcept -> bool {

                    return false;
                }


                template <
                        typename __KeyType, // NOLINT(bugprone-reserved-identifier)
                        typename __ValueType, // NOLINT(bugprone-reserved-identifier)
                        typename __KeySetType, // NOLINT(bugprone-reserved-identifier)
                        typename __ValueCollectionType, // NOLINT(bugprone-reserved-identifier)
                        typename __EntryAssociatorType, // NOLINT(bugprone-reserved-identifier)
                        cds :: meta :: EnableIf <
                                cds :: meta :: isDerivedFrom < __KeySetType, cds :: experimental :: Set < __KeyType > > () &&
                                cds :: meta :: isDerivedFrom < __ValueCollectionType, cds :: experimental :: Collection < __ValueType > > ()
                        > __enabler // NOLINT(bugprone-reserved-identifier)
                > auto __BaseMap <
                        __KeyType,
                        __ValueType,
                        __KeySetType,
                        __ValueCollectionType,
                        __EntryAssociatorType,
                        __enabler
                > :: containsKey (
                        KeyType const & key
                ) const noexcept -> bool {

                    return false;
                }


                template <
                        typename __KeyType, // NOLINT(bugprone-reserved-identifier)
                        typename __ValueType, // NOLINT(bugprone-reserved-identifier)
                        typename __KeySetType, // NOLINT(bugprone-reserved-identifier)
                        typename __ValueCollectionType, // NOLINT(bugprone-reserved-identifier)
                        typename __EntryAssociatorType, // NOLINT(bugprone-reserved-identifier)
                        cds :: meta :: EnableIf <
                                cds :: meta :: isDerivedFrom < __KeySetType, cds :: experimental :: Set < __KeyType > > () &&
                                cds :: meta :: isDerivedFrom < __ValueCollectionType, cds :: experimental :: Collection < __ValueType > > ()
                        > __enabler // NOLINT(bugprone-reserved-identifier)
                > auto __BaseMap <
                        __KeyType,
                        __ValueType,
                        __KeySetType,
                        __ValueCollectionType,
                        __EntryAssociatorType,
                        __enabler
                > :: containsValue (
                        ValueType const & value
                ) const noexcept -> bool {

                    return false;
                }


                template <
                        typename __KeyType, // NOLINT(bugprone-reserved-identifier)
                        typename __ValueType, // NOLINT(bugprone-reserved-identifier)
                        typename __KeySetType, // NOLINT(bugprone-reserved-identifier)
                        typename __ValueCollectionType, // NOLINT(bugprone-reserved-identifier)
                        typename __EntryAssociatorType, // NOLINT(bugprone-reserved-identifier)
                        cds :: meta :: EnableIf <
                                cds :: meta :: isDerivedFrom < __KeySetType, cds :: experimental :: Set < __KeyType > > () &&
                                cds :: meta :: isDerivedFrom < __ValueCollectionType, cds :: experimental :: Collection < __ValueType > > ()
                        > __enabler // NOLINT(bugprone-reserved-identifier)
                > auto __BaseMap <
                        __KeyType,
                        __ValueType,
                        __KeySetType,
                        __ValueCollectionType,
                        __EntryAssociatorType,
                        __enabler
                > :: remove (
                        Iterator const & iterator
                ) noexcept -> bool {

                    return false;
                }


                template <
                        typename __KeyType, // NOLINT(bugprone-reserved-identifier)
                        typename __ValueType, // NOLINT(bugprone-reserved-identifier)
                        typename __KeySetType, // NOLINT(bugprone-reserved-identifier)
                        typename __ValueCollectionType, // NOLINT(bugprone-reserved-identifier)
                        typename __EntryAssociatorType, // NOLINT(bugprone-reserved-identifier)
                        cds :: meta :: EnableIf <
                                cds :: meta :: isDerivedFrom < __KeySetType, cds :: experimental :: Set < __KeyType > > () &&
                                cds :: meta :: isDerivedFrom < __ValueCollectionType, cds :: experimental :: Collection < __ValueType > > ()
                        > __enabler // NOLINT(bugprone-reserved-identifier)
                > auto __BaseMap <
                        __KeyType,
                        __ValueType,
                        __KeySetType,
                        __ValueCollectionType,
                        __EntryAssociatorType,
                        __enabler
                > :: remove (
                        ConstIterator const & iterator
                ) noexcept -> bool {

                    return false;
                }


                template <
                        typename __KeyType, // NOLINT(bugprone-reserved-identifier)
                        typename __ValueType, // NOLINT(bugprone-reserved-identifier)
                        typename __KeySetType, // NOLINT(bugprone-reserved-identifier)
                        typename __ValueCollectionType, // NOLINT(bugprone-reserved-identifier)
                        typename __EntryAssociatorType, // NOLINT(bugprone-reserved-identifier)
                        cds :: meta :: EnableIf <
                                cds :: meta :: isDerivedFrom < __KeySetType, cds :: experimental :: Set < __KeyType > > () &&
                                cds :: meta :: isDerivedFrom < __ValueCollectionType, cds :: experimental :: Collection < __ValueType > > ()
                        > __enabler // NOLINT(bugprone-reserved-identifier)
                > auto __BaseMap <
                        __KeyType,
                        __ValueType,
                        __KeySetType,
                        __ValueCollectionType,
                        __EntryAssociatorType,
                        __enabler
                > :: remove (
                        ReverseIterator const & iterator
                ) noexcept -> bool {

                    return false;
                }


                template <
                        typename __KeyType, // NOLINT(bugprone-reserved-identifier)
                        typename __ValueType, // NOLINT(bugprone-reserved-identifier)
                        typename __KeySetType, // NOLINT(bugprone-reserved-identifier)
                        typename __ValueCollectionType, // NOLINT(bugprone-reserved-identifier)
                        typename __EntryAssociatorType, // NOLINT(bugprone-reserved-identifier)
                        cds :: meta :: EnableIf <
                                cds :: meta :: isDerivedFrom < __KeySetType, cds :: experimental :: Set < __KeyType > > () &&
                                cds :: meta :: isDerivedFrom < __ValueCollectionType, cds :: experimental :: Collection < __ValueType > > ()
                        > __enabler // NOLINT(bugprone-reserved-identifier)
                > auto __BaseMap <
                        __KeyType,
                        __ValueType,
                        __KeySetType,
                        __ValueCollectionType,
                        __EntryAssociatorType,
                        __enabler
                > :: remove (
                        ConstReverseIterator const & iterator
                ) noexcept -> bool {

                    return false;
                }


                template <
                        typename __KeyType, // NOLINT(bugprone-reserved-identifier)
                        typename __ValueType, // NOLINT(bugprone-reserved-identifier)
                        typename __KeySetType, // NOLINT(bugprone-reserved-identifier)
                        typename __ValueCollectionType, // NOLINT(bugprone-reserved-identifier)
                        typename __EntryAssociatorType, // NOLINT(bugprone-reserved-identifier)
                        cds :: meta :: EnableIf <
                                cds :: meta :: isDerivedFrom < __KeySetType, cds :: experimental :: Set < __KeyType > > () &&
                                cds :: meta :: isDerivedFrom < __ValueCollectionType, cds :: experimental :: Collection < __ValueType > > ()
                        > __enabler // NOLINT(bugprone-reserved-identifier)
                > auto __BaseMap <
                        __KeyType,
                        __ValueType,
                        __KeySetType,
                        __ValueCollectionType,
                        __EntryAssociatorType,
                        __enabler
                > :: remove (
                        Iterator    const * pIterators,
                        Size                iteratorCount
                ) noexcept -> Size {

                    return 0ULL;
                }


                template <
                        typename __KeyType, // NOLINT(bugprone-reserved-identifier)
                        typename __ValueType, // NOLINT(bugprone-reserved-identifier)
                        typename __KeySetType, // NOLINT(bugprone-reserved-identifier)
                        typename __ValueCollectionType, // NOLINT(bugprone-reserved-identifier)
                        typename __EntryAssociatorType, // NOLINT(bugprone-reserved-identifier)
                        cds :: meta :: EnableIf <
                                cds :: meta :: isDerivedFrom < __KeySetType, cds :: experimental :: Set < __KeyType > > () &&
                                cds :: meta :: isDerivedFrom < __ValueCollectionType, cds :: experimental :: Collection < __ValueType > > ()
                        > __enabler // NOLINT(bugprone-reserved-identifier)
                > auto __BaseMap <
                        __KeyType,
                        __ValueType,
                        __KeySetType,
                        __ValueCollectionType,
                        __EntryAssociatorType,
                        __enabler
                > :: remove (
                        ConstIterator   const * pIterators,
                        Size                    iteratorCount
                ) noexcept -> Size {

                    return 0ULL;
                }


                template <
                        typename __KeyType, // NOLINT(bugprone-reserved-identifier)
                        typename __ValueType, // NOLINT(bugprone-reserved-identifier)
                        typename __KeySetType, // NOLINT(bugprone-reserved-identifier)
                        typename __ValueCollectionType, // NOLINT(bugprone-reserved-identifier)
                        typename __EntryAssociatorType, // NOLINT(bugprone-reserved-identifier)
                        cds :: meta :: EnableIf <
                                cds :: meta :: isDerivedFrom < __KeySetType, cds :: experimental :: Set < __KeyType > > () &&
                                cds :: meta :: isDerivedFrom < __ValueCollectionType, cds :: experimental :: Collection < __ValueType > > ()
                        > __enabler // NOLINT(bugprone-reserved-identifier)
                > auto __BaseMap <
                        __KeyType,
                        __ValueType,
                        __KeySetType,
                        __ValueCollectionType,
                        __EntryAssociatorType,
                        __enabler
                > :: remove (
                        ReverseIterator const * pIterators,
                        Size                    iteratorCount
                ) noexcept -> Size {

                    return 0ULL;
                }


                template <
                        typename __KeyType, // NOLINT(bugprone-reserved-identifier)
                        typename __ValueType, // NOLINT(bugprone-reserved-identifier)
                        typename __KeySetType, // NOLINT(bugprone-reserved-identifier)
                        typename __ValueCollectionType, // NOLINT(bugprone-reserved-identifier)
                        typename __EntryAssociatorType, // NOLINT(bugprone-reserved-identifier)
                        cds :: meta :: EnableIf <
                                cds :: meta :: isDerivedFrom < __KeySetType, cds :: experimental :: Set < __KeyType > > () &&
                                cds :: meta :: isDerivedFrom < __ValueCollectionType, cds :: experimental :: Collection < __ValueType > > ()
                        > __enabler // NOLINT(bugprone-reserved-identifier)
                > auto __BaseMap <
                        __KeyType,
                        __ValueType,
                        __KeySetType,
                        __ValueCollectionType,
                        __EntryAssociatorType,
                        __enabler
                > :: remove (
                        ConstReverseIterator    const * pIterators,
                        Size                            iteratorCount
                ) noexcept -> Size {

                    return 0ULL;
                }


                template <
                        typename __KeyType, // NOLINT(bugprone-reserved-identifier)
                        typename __ValueType, // NOLINT(bugprone-reserved-identifier)
                        typename __KeySetType, // NOLINT(bugprone-reserved-identifier)
                        typename __ValueCollectionType, // NOLINT(bugprone-reserved-identifier)
                        typename __EntryAssociatorType, // NOLINT(bugprone-reserved-identifier)
                        cds :: meta :: EnableIf <
                                cds :: meta :: isDerivedFrom < __KeySetType, cds :: experimental :: Set < __KeyType > > () &&
                                cds :: meta :: isDerivedFrom < __ValueCollectionType, cds :: experimental :: Collection < __ValueType > > ()
                        > __enabler // NOLINT(bugprone-reserved-identifier)
                > auto __BaseMap <
                        __KeyType,
                        __ValueType,
                        __KeySetType,
                        __ValueCollectionType,
                        __EntryAssociatorType,
                        __enabler
                > :: clear () noexcept -> void {

                    this->_keySet.clear();
                    this->_associator.clear();
                }

            }
        }
    }
}

#endif // __CDS_EX_BASE_MAP_IMPL_HPP__
