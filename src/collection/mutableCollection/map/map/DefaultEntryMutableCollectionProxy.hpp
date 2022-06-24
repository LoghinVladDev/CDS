//
// Created by loghin on 6/18/22.
//

#ifndef __CDS_MAP_DEFAULT_ENTRY_MUTABLE_COLLECTION_PROXY_HPP__
#define __CDS_MAP_DEFAULT_ENTRY_MUTABLE_COLLECTION_PROXY_HPP__

namespace cds {

    template < typename __KeyType, typename __ValueType > // NOLINT(bugprone-reserved-identifier)
    class Map < __KeyType, __ValueType > :: DefaultEntryMutableCollectionProxy : public AbstractEntryMutableCollectionProxy {

    public:
        using typename AbstractEntryMutableCollectionProxy :: EntryType;

    public:
        using typename AbstractEntryMutableCollectionProxy :: ElementType;

    public:
        using typename AbstractEntryMutableCollectionProxy :: Iterator;

    public:
        using typename AbstractEntryMutableCollectionProxy :: ConstIterator;

    public:
        using typename AbstractEntryMutableCollectionProxy :: ReverseIterator;

    public:
        using typename AbstractEntryMutableCollectionProxy :: ConstReverseIterator;

    protected:
        using typename AbstractEntryMutableCollectionProxy :: InitializerList;

    protected:
        using typename AbstractEntryMutableCollectionProxy :: DelegateIterator;

    protected:
        using typename AbstractEntryMutableCollectionProxy :: DelegateConstIterator;

    protected:
        using typename AbstractEntryMutableCollectionProxy :: AbstractIterator;

    protected:
        using typename AbstractEntryMutableCollectionProxy :: AbstractDelegateIterator;

    protected:
        using typename AbstractEntryMutableCollectionProxy :: DelegateIteratorRequestType;

    public:
        auto delegateIterator (
                DelegateIteratorRequestType requestType
        ) noexcept -> cds :: UniquePointer < DelegateIterator > override;

    public:
        auto delegateConstIterator (
                DelegateIteratorRequestType requestType
        ) const noexcept -> cds :: UniquePointer < DelegateConstIterator > override;

    public:
        __CDS_Explicit constexpr DefaultEntryMutableCollectionProxy (
                Map < __KeyType, __ValueType > * pMap
        ) noexcept;

    public:
        constexpr DefaultEntryMutableCollectionProxy (
                DefaultEntryMutableCollectionProxy const & collection
        ) noexcept;

    public:
        constexpr DefaultEntryMutableCollectionProxy (
                DefaultEntryMutableCollectionProxy && collection
        ) noexcept;

    public:
        __CDS_cpplang_ConstexprDestructor ~DefaultEntryMutableCollectionProxy () noexcept override;

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
        auto operator == (
                DefaultEntryMutableCollectionProxy const & collection
        ) const noexcept -> bool;

    public:
        auto operator != (
                DefaultEntryMutableCollectionProxy const & collection
        ) const noexcept -> bool;

    public:
        __CDS_NoDiscard auto size () const noexcept -> Size override;
    };

}

#endif // __CDS_MAP_DEFAULT_ENTRY_MUTABLE_COLLECTION_PROXY_HPP__
