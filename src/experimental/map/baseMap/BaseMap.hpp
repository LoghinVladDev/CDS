//
// Created by loghin on 6/15/22.
//

#ifndef __CDS_EX_BASE_MAP_HPP__
#define __CDS_EX_BASE_MAP_HPP__

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental { // NOLINT(modernize-concat-nested-namespaces)
        namespace __hidden { // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier)
            namespace __impl { // NOLINT(bugprone-reserved-identifier)

                template <
                        typename __KeyType, // NOLINT(bugprone-reserved-identifier)
                        typename __ValueType, // NOLINT(bugprone-reserved-identifier)
                        typename __KeySetType, // NOLINT(bugprone-reserved-identifier)
                        typename __ValueCollectionType, // NOLINT(bugprone-reserved-identifier)
                        typename __EntryAssociatorType, // NOLINT(bugprone-reserved-identifier)
                        cds :: meta :: EnableIf <
                                cds :: meta :: isDerivedFrom < __KeySetType, cds :: experimental :: Set < __KeyType > > () &&
                                cds :: meta :: isDerivedFrom < __ValueCollectionType, cds :: experimental :: Collection < __ValueType > > ()
                        >
                > class __BaseMap : public cds :: experimental :: Map < __KeyType, __ValueType > { // NOLINT(bugprone-reserved-identifier)

                public:
                    using typename Map < __KeyType, __ValueType > :: ElementType;

                public:
                    using typename Map < __KeyType, __ValueType > :: EntryType;

                public:
                    using typename Map < __KeyType, __ValueType > :: KeyType;

                public:
                    using typename Map < __KeyType, __ValueType > :: ValueType;

                protected:
                    using typename Map < __KeyType, __ValueType > :: InitializerList;

                public:
                    using typename Map < __KeyType, __ValueType > :: Iterator;

                public:
                    using typename Map < __KeyType, __ValueType > :: ConstIterator;

                public:
                    using typename Map < __KeyType, __ValueType > :: ReverseIterator;

                public:
                    using typename Map < __KeyType, __ValueType > :: ConstReverseIterator;

                protected:
                    using typename Map < __KeyType, __ValueType > :: AbstractDelegateIterator;

                protected:
                    using typename Map < __KeyType, __ValueType > :: DelegateIterator;

                protected:
                    using typename Map < __KeyType, __ValueType > :: DelegateConstIterator;

                protected:
                    using typename Map < __KeyType, __ValueType > :: DelegateIteratorRequestType;

                protected:
                    class HashMapDelegateIterator;

                protected:
                    class HashMapDelegateConstIterator;

                protected:
                    class HashMapDelegateReverseIterator;

                protected:
                    class HashMapDelegateConstReverseIterator;

                public:
                    auto delegateIterator (
                            DelegateIteratorRequestType requestType
                    ) noexcept -> cds :: UniquePointer < DelegateIterator > override;

                public:
                    auto delegateConstIterator (
                            DelegateIteratorRequestType requestType
                    ) const noexcept -> cds :: UniquePointer < DelegateConstIterator > override;

                private:
                    __KeySetType            _keySet;

                private:
                    __ValueCollectionType   _valueCollection;

                private:
                    __EntryAssociatorType   _associator; /// associator < Key, ValueCollection >. Manages ValueCollection

                private:
                    ElementType           * _pInsertTemporary { nullptr };

                public:
                    constexpr __BaseMap () noexcept;

                public:
                    __BaseMap (
                            __BaseMap const & map
                    ) noexcept;

                public:
                    constexpr __BaseMap (
                            __BaseMap && map
                    ) noexcept;

                public:
                    ~__BaseMap () noexcept override;

                public:
                    auto get (
                            KeyType const & key
                    ) noexcept (false) -> ValueType & override;

                public:
                    auto get (
                            KeyType const & key
                    ) const noexcept (false) -> ValueType const & override;

                protected:
                    auto pNewInsert (
                            ElementType const & referenceElement
                    ) noexcept -> ElementType * & override;

                protected:
                    auto pNewInsertPost () noexcept -> void override;

                public:
                    auto contains (
                            ElementType const & entry
                    ) const noexcept -> bool override;

                public:
                    auto containsKey (
                            KeyType const & key
                    ) const noexcept -> bool override;

                public:
                    auto containsValue (
                            ValueType const & value
                    ) const noexcept -> bool override;

                public:
                    auto remove (
                            Iterator const & iterator
                    ) noexcept -> bool override;

                public:
                    auto remove (
                            ConstIterator const & iterator
                    ) noexcept -> bool override;

                public:
                    auto remove (
                            ReverseIterator const & iterator
                    ) noexcept -> bool override;

                public:
                    auto remove (
                            ConstReverseIterator const & iterator
                    ) noexcept -> bool override;

                public:
                    auto remove (
                            Iterator    const * pIterators,
                            Size                iteratorCount
                    ) noexcept -> Size override;

                public:
                    auto remove (
                            ConstIterator   const * pIterators,
                            Size                    iteratorCount
                    ) noexcept -> Size override;

                public:
                    auto remove (
                            ReverseIterator const * pIterators,
                            Size                    iteratorCount
                    ) noexcept -> Size override;

                public:
                    auto remove (
                            ConstReverseIterator    const * pIterators,
                            Size                            iteratorCount
                    ) noexcept -> Size override;

                public:
                    auto clear () noexcept -> void override;
                };

            }
        }
    }
}

#endif // __CDS_EX_BASE_MAP_HPP__
