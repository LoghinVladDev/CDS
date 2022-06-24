//
// Created by loghin on 6/18/22.
//

#ifndef __CDS_MAP_ABSTRACT_VALUE_MUTABLE_COLLECTION_PROXY_HPP__
#define __CDS_MAP_ABSTRACT_VALUE_MUTABLE_COLLECTION_PROXY_HPP__

namespace cds {

    template < typename __KeyType, typename __ValueType > // NOLINT(bugprone-reserved-identifier)
    class Map < __KeyType, __ValueType > :: AbstractValueMutableCollectionProxy :
            public cds :: MutableCollection < ValueType >,
            protected Map < __KeyType, __ValueType > :: AbstractProxy {

    public:
        using ValueType = typename Map < __KeyType, __ValueType > :: ValueType;

    public:
        using typename MutableCollection < ValueType > :: ElementType;

    public:
        using typename MutableCollection < ValueType > :: Iterator;

    public:
        using typename MutableCollection < ValueType > :: ConstIterator;

    public:
        using typename MutableCollection < ValueType > :: ReverseIterator;

    public:
        using typename MutableCollection < ValueType > :: ConstReverseIterator;

    protected:
        using typename MutableCollection < ValueType > :: InitializerList;

    protected:
        using typename MutableCollection < ValueType > :: DelegateIterator;

    protected:
        using typename MutableCollection < ValueType > :: DelegateConstIterator;

    protected:
        using typename MutableCollection < ValueType > :: AbstractIterator;

    protected:
        using typename MutableCollection < ValueType > :: AbstractDelegateIterator;

    protected:
        using typename MutableCollection < ValueType > :: DelegateIteratorRequestType;

    protected:
        auto delegateIterator (
                DelegateIteratorRequestType requestType
        ) noexcept -> cds :: UniquePointer < DelegateIterator > override = 0;

    protected:
        auto delegateConstIterator (
                DelegateIteratorRequestType requestType
        ) const noexcept -> cds :: UniquePointer < DelegateConstIterator > override = 0;

    protected:
        __CDS_Explicit constexpr AbstractValueMutableCollectionProxy (
                Map < __KeyType, __ValueType > * pMap
        ) noexcept;

    protected:
        constexpr AbstractValueMutableCollectionProxy (
                AbstractValueMutableCollectionProxy const & collection
        ) noexcept;

    protected:
        constexpr AbstractValueMutableCollectionProxy (
                AbstractValueMutableCollectionProxy && collection
        ) noexcept;

    public:
        __CDS_cpplang_ConstexprDestructor ~AbstractValueMutableCollectionProxy() noexcept override;

    public:
        auto remove (
                Iterator const & iterator
        ) noexcept -> bool override = 0;

    public:
        auto remove (
                ConstIterator const & iterator
        ) noexcept -> bool override = 0;

    public:
        auto remove (
                ReverseIterator const & iterator
        ) noexcept -> bool override = 0;

    public:
        auto remove (
                ConstReverseIterator const & iterator
        ) noexcept -> bool override = 0;

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

    protected:
        auto pNewInsert (
                ElementType const & referenceElement
        ) noexcept -> ElementType * override;

    public:
        auto clear () noexcept -> void override;

    public:
        __CDS_NoDiscard auto toString () const noexcept -> String override;

    public:
        __CDS_NoDiscard __CDS_cpplang_VirtualConstexpr auto size () const noexcept -> Size override = 0;
    };

}

#endif // __CDS_MAP_ABSTRACT_VALUE_MUTABLE_COLLECTION_PROXY_HPP__
