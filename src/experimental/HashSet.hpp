//
// Created by loghin on 6/13/22.
//

#ifndef __CDS_EX_HASH_SET_HPP__
#define __CDS_EX_HASH_SET_HPP__

#include <CDS/experimental/Set>
#include <CDS/Destructor>
#include <CDS/Extractor>
#include <CDS/CopyConstructor>
#include <CDS/Comparator>
#include <CDS/Hasher>
#include "../shared/rehashPolicy/rehashPolicy.hpp"
#include "shared/hash/HashTable.hpp"
#include "hashSet/HashTableConstructs.hpp"

namespace cds { // NOLINT(modernize-concat-nested-namespaces)

    template < typename __CollectionType > // NOLINT(bugprone-reserved-identifier)
    class Sequence;

    namespace experimental {

        template <
                typename __ElementType,                                                                 // NOLINT(bugprone-reserved-identifier)
                typename __Hasher = FunctionHasher < __ElementType, & cds :: hash < __ElementType > >   // NOLINT(bugprone-reserved-identifier)
        > class HashSet :
                public Set < __ElementType >,
                protected __hidden :: __impl :: __HashTable <
                        __hidden :: __impl :: __HashSetDataNode < __ElementType >,
                        __ElementType,
                        FunctionExtractor <
                                __hidden :: __impl :: __HashSetDataNode < __ElementType >,
                                __ElementType,
                                & __hidden :: __impl :: __hashSetDataNodeKeyExtractor < __ElementType >
                        >,
                        FunctionComparator < __ElementType, & cds :: meta :: equals < __ElementType > >,
                        __Hasher,
                        cds :: __hidden :: __impl :: __PrimeRehashPolicy,
                        FunctionDestructor <
                                __hidden :: __impl :: __HashSetDataNode < __ElementType >,
                                & __hidden :: __impl :: __hashSetDataNodeDestructor < __ElementType >
                        >
                > {

        protected:
            using __HashTableElementType =  // NOLINT(bugprone-reserved-identifier)
                    __hidden :: __impl :: __HashSetDataNode < __ElementType >;

        protected:
            using __HashTableKeyType =  // NOLINT(bugprone-reserved-identifier)
                    __ElementType;

        protected:
            using __HashTableFunctionExtractor =    // NOLINT(bugprone-reserved-identifier)
                    FunctionExtractor <
                            __HashTableElementType,
                            __HashTableKeyType,
                            & __hidden :: __impl :: __hashSetDataNodeKeyExtractor <
                                    __ElementType
                            >
                    >;

        protected:
            using __HashTableFunctionComparator =   // NOLINT(bugprone-reserved-identifier)
                    FunctionComparator <
                            __ElementType,
                            & cds :: meta :: equals < __ElementType >
                    >;
            
        protected:
            using __HashTableHasher =   // NOLINT(bugprone-reserved-identifier)
                    __Hasher;
            
        protected:
            using __HashTableRehashPolicy = // NOLINT(bugprone-reserved-identifier)
                    cds :: __hidden :: __impl :: __PrimeRehashPolicy;
            
        protected:
            using __HashTableFunctionDestructor =   // NOLINT(bugprone-reserved-identifier)
                    FunctionDestructor < 
                            __HashTableElementType,
                            & __hidden :: __impl :: __hashSetDataNodeDestructor < __ElementType >
                    >;
            
        protected:
            using __HashTableFunctionCopyConstructor =  // NOLINT(bugprone-reserved-identifier)
                    FunctionCopyConstructor <
                            __HashTableElementType,
                            & __hidden :: __impl :: __hashSetDataNodeCopyConstructor < __ElementType >
                    >;
            
        protected:
            using __HashTableFunctionEntryEquals =  // NOLINT(bugprone-reserved-identifier)
                    __HashTableFunctionComparator;

        public:
            using typename Set < __ElementType > :: ElementType;

        public:
            using typename Set < __ElementType > :: ConstIterator;

        public:
            using typename Set < __ElementType > :: ConstReverseIterator;

        protected:
            using typename Set < __ElementType > :: InitializerList;

        protected:
            using typename Set < __ElementType > :: DelegateConstIterator;

        protected:
            using typename Set < __ElementType > :: AbstractIterator;

        protected:
            using typename Set < __ElementType > :: AbstractDelegateIterator;

        protected:
            using typename Set < __ElementType > :: DelegateIteratorRequestType;

        private:
            class HashSetDelegateIterator;

        private:
            ElementType * _pInsertionElement { nullptr };
            bool          _forward;

        private:
            auto delegateConstIterator (
                    DelegateIteratorRequestType requestType
            ) const noexcept -> cds :: UniquePointer < DelegateConstIterator > override;

        public:
            constexpr HashSet () noexcept;

        public:
            template < 
                    typename __TElementType = __ElementType,    // NOLINT(bugprone-reserved-identifier)
                    cds :: meta :: EnableIf < 
                            cds :: meta :: isCopyConstructible < __TElementType > () 
                    > = 0 
            > __CDS_Implicit HashSet (                          // NOLINT(google-explicit-constructor)
                    HashSet const & set
            ) noexcept;

        public:
            constexpr HashSet (
                    HashSet && set
            ) noexcept;

        public:
            __CDS_Explicit HashSet (
                    __Hasher const & hasher
            ) noexcept;

        public:
            template < typename __IteratorType, cds :: meta :: EnableIf < cds :: meta :: isIterator < __IteratorType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
            HashSet (
                    __IteratorType const & begin,
                    __IteratorType const & end
            ) noexcept;

        public:
            template < typename __IteratorType, cds :: meta :: EnableIf < cds :: meta :: isIterator < __IteratorType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
            HashSet (
                    __IteratorType      const & begin,
                    __IteratorType      const & end,
                    __Hasher            const & hasher
            ) noexcept;

        public:
            __CDS_Implicit HashSet ( // NOLINT(google-explicit-constructor)
                    InitializerList const & initializerList
            ) noexcept;

        public:
            HashSet (
                    InitializerList     const & initializerList,
                    __Hasher            const & hasher
            ) noexcept;

        public:
            template < typename __OtherElementType, cds :: meta :: EnableIf < cds :: meta :: isConvertible < __OtherElementType, __ElementType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
            __CDS_Explicit HashSet (
                    Collection < __OtherElementType >   const & collection
            ) noexcept;

        public:
            template < typename __OtherElementType, cds :: meta :: EnableIf < cds :: meta :: isConvertible < __OtherElementType, __ElementType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
            HashSet (
                    Collection < __OtherElementType >   const & collection,
                    __Hasher                            const & hasher
            ) noexcept;

        public:
            ~HashSet() noexcept override;

        public:
            __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto size () const noexcept -> Size override;

        public:
            auto remove (
                    ElementType const & element
            ) noexcept -> bool override;

        public:
            auto remove (
                    ConstIterator const & iterator
            ) noexcept -> bool override;

        public:
            auto remove (
                    ConstReverseIterator const & iterator
            ) noexcept -> bool override;

        protected:
            auto remove (
                    ConstIterator   const * pIterators,
                    Size                    iteratorCount
            ) noexcept -> Size override;

        protected:
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
                    ElementType const & element
            ) const noexcept -> bool override;

        public:
            auto clear () noexcept -> void override;

        public:
            auto operator == (
                    HashSet const & set
            ) const noexcept -> bool;

        public:
            auto operator != (
                    HashSet const & set
            ) const noexcept -> bool;

        public:
            template < typename __VElementType = __ElementType, cds :: meta :: EnableIf < cds :: meta :: isCopyConstructible < __VElementType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
            auto operator = (
                    HashSet const & hashSet
            ) noexcept -> HashSet &;

        public:
            auto operator = (
                    HashSet && hashSet
            ) noexcept -> HashSet &;

        public:
            template < typename __OtherElementType, cds :: meta :: EnableIf < cds :: meta :: isConvertible < __OtherElementType, __ElementType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
            auto operator = (
                    Collection < __OtherElementType > const & collection
            ) noexcept -> HashSet &;

        public:
            auto sequence () & noexcept -> Sequence < HashSet < __ElementType, __Hasher > >;

        public:
            auto sequence () && noexcept -> Sequence < HashSet < __ElementType, __Hasher > >;

        public:
            auto sequence () const & noexcept -> Sequence < HashSet < __ElementType, __Hasher > const >;

        public:
            auto sequence () const && noexcept -> Sequence < HashSet < __ElementType, __Hasher > const >;
        };

    }
}

#include "hashSet/DelegateIterator.hpp"

#include "hashSet/impl/DelegateIterator.hpp"
#include "hashSet/impl/HashSet.hpp"

#include "hashSet/CTAD.hpp"

#include "shared/hashSet/impl/HashSetSequence.hpp"
#include "shared/hash/impl/HashTable.hpp"

#include "shared/collection/FunctionalConstructors.hpp"
#include "shared/collection/impl/FunctionalConstructors.hpp"


#endif // __CDS_EX_HASH_SET_HPP__
