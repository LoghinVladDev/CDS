//
// Created by loghin on 6/18/22.
//

#ifndef __CDS_MAP_ABSTRACT_KEY_SET_PROXY_HPP__
#define __CDS_MAP_ABSTRACT_KEY_SET_PROXY_HPP__

namespace cds {

    template < typename __KeyType, typename __ValueType > // NOLINT(bugprone-reserved-identifier)
    class Map < __KeyType, __ValueType > :: AbstractKeySetProxy :
            public cds :: Set < KeyType const >,
            protected Map < __KeyType, __ValueType > :: AbstractProxy {

    public:
        using KeyType = typename Map < __KeyType, __ValueType > :: KeyType const;

    public:
        using typename Set < KeyType > :: ElementType;

    public:
        using typename Set < KeyType > :: ConstIterator;

    public:
        using typename Set < KeyType > :: ConstReverseIterator;

    protected:
        using typename Set < KeyType > :: InitializerList;

    protected:
        using typename Set < KeyType > :: DelegateConstIterator;

    protected:
        using typename Set < KeyType > :: AbstractIterator;

    protected:
        using typename Set < KeyType > :: AbstractDelegateIterator;

    protected:
        using typename Set < KeyType > :: DelegateIteratorRequestType;

    protected:
        auto delegateConstIterator (
                DelegateIteratorRequestType requestType
        ) const noexcept -> cds :: UniquePointer < DelegateConstIterator > override = 0;

    protected:
        __CDS_Explicit constexpr AbstractKeySetProxy (
                Map < __KeyType, __ValueType > * pMap
        ) noexcept;

    protected:
        constexpr AbstractKeySetProxy (
                AbstractKeySetProxy const & set
        ) noexcept;

    protected:
        constexpr AbstractKeySetProxy (
                AbstractKeySetProxy && set
        ) noexcept;

    public:
        __CDS_cpplang_ConstexprDestructor ~AbstractKeySetProxy() noexcept override;

    public:
        auto remove (
                KeyType const & value
        ) noexcept -> bool override;

    public:
        auto remove (
                ConstIterator const & iterator
        ) noexcept -> bool override = 0;

    public:
        auto remove (
                ConstReverseIterator const & iterator
        ) noexcept -> bool override = 0;

    public:
        auto remove (
                ConstIterator   const * pIterators,
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
        auto contains (
                KeyType const & element
        ) const noexcept -> bool override;

    public:
        auto clear () noexcept -> void override;

    public:
        __CDS_NoDiscard __CDS_cpplang_VirtualConstexpr auto size () const noexcept -> Size override = 0;

    };

}

#endif // __CDS_MAP_ABSTRACT_KEY_SET_PROXY_HPP__
