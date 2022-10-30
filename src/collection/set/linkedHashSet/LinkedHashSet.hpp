/* NOLINT(llvm-header-guard)
 * Created by loghin on 6/24/22.
 */

#ifndef __CDS_LINKED_HASH_SET_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_LINKED_HASH_SET_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

#include <CDS/Set>                  /* NOLINT(llvm-include-order) */
#include <CDS/FunctionalInterface>

#include "../../../shared/Node.hpp"
#include "../../../shared/rehashPolicy/rehashPolicy.hpp"

#include "../../../shared/iterator/HashTableIterator.hpp"
#include "../../../shared/iterator/NodeIterator.hpp"                    /* NOLINT(llvm-include-order) */
#include "../../../shared/iterator/IteratorGenericDecorator.hpp"

#include "../../../shared/iterableInternalCommunication/server/SetServerDispatcher.hpp"

#include "../../../shared/delegateIterator/AbstractDelegateIterator.hpp"
#include "../../../shared/delegateIterator/DelegateIterator.hpp"

#include "../../../shared/hashTable/HashTable.hpp"
#include "../../../shared/linkedList/SingleLinkedList.hpp"

#include "../../../shared/iterableInternalCommunication/server/SetServer.hpp"

#include "linkedHashSet/Constructs.hpp"

namespace cds {

    template <
            typename __ElementType, /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __Hasher       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    > class __CDS_InheritsEBOs LinkedHashSet :
            public Set < __ElementType >,
            protected __hidden :: __impl :: __LinkedHashSetServer < __ElementType, __Hasher >,
            public __hidden :: __impl :: __LinkedHashSetHashTableImplementation < __ElementType, __Hasher >,
            public __hidden :: __impl :: __LinkedHashSetLinkedListImplementation < __ElementType, __Hasher >,
            public __hidden :: __impl :: __LinkedHashSetRandomInsertionClient < __ElementType, __Hasher >,
            public __hidden :: __impl :: __LinkedHashSetIteratorRemoveClient < __ElementType, __Hasher >,
            public __hidden :: __impl :: __LinkedHashSetFindOfIterableClient < __ElementType, __Hasher >,
            public __hidden :: __impl :: __LinkedHashSetFindOfInitializerListClient < __ElementType, __Hasher >,
            public __hidden :: __impl :: __LinkedHashSetFindByClient < __ElementType, __Hasher >,
            public __hidden :: __impl :: __LinkedHashSetRemoveOfIterableClient < __ElementType, __Hasher >,
            public __hidden :: __impl :: __LinkedHashSetRemoveOfInitializerListClient < __ElementType, __Hasher >,
            public __hidden :: __impl :: __LinkedHashSetRemoveByClient < __ElementType, __Hasher >,
            public __hidden :: __impl :: __LinkedHashSetGenericStatementsClient < __ElementType, __Hasher >,
            public __hidden :: __impl :: __LinkedHashSetFindUniqueClient < __ElementType, __Hasher >,
            public __hidden :: __impl :: __LinkedHashSetContainsOfIterableClient < __ElementType, __Hasher >,
            public __hidden :: __impl :: __LinkedHashSetContainsOfInitializerListClient < __ElementType, __Hasher >,
            public __hidden :: __impl :: __LinkedHashSetDelegateForwardConstIterableClient < __ElementType, __Hasher > {

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using SetBase                               = Set < __ElementType >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using Server                                = __hidden :: __impl :: __LinkedHashSetServer < __ElementType, __Hasher >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using HashTableImplementation               = __hidden :: __impl :: __LinkedHashSetHashTableImplementation < __ElementType, __Hasher >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using LinkedListImplementation              = __hidden :: __impl :: __LinkedHashSetLinkedListImplementation < __ElementType, __Hasher >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using RandomInsertionClient                 = __hidden :: __impl :: __LinkedHashSetRandomInsertionClient < __ElementType, __Hasher >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using IteratorRemoveClient                  = __hidden :: __impl :: __LinkedHashSetIteratorRemoveClient < __ElementType, __Hasher >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using FindOfIterableClient                  = __hidden :: __impl :: __LinkedHashSetFindOfIterableClient < __ElementType, __Hasher >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using FindOfInitializerListClient           = __hidden :: __impl :: __LinkedHashSetFindOfInitializerListClient < __ElementType, __Hasher >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using FindByClient                          = __hidden :: __impl :: __LinkedHashSetFindByClient < __ElementType, __Hasher >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using RemoveOfIterableClient                = __hidden :: __impl :: __LinkedHashSetRemoveOfIterableClient < __ElementType, __Hasher >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using RemoveOfInitializerListClient         = __hidden :: __impl :: __LinkedHashSetRemoveOfInitializerListClient < __ElementType, __Hasher >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using RemoveByClient                        = __hidden :: __impl :: __LinkedHashSetRemoveByClient < __ElementType, __Hasher >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using GenericStatementsClient               = __hidden :: __impl :: __LinkedHashSetGenericStatementsClient < __ElementType, __Hasher >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using ContainsOfIterableClient              = __hidden :: __impl :: __LinkedHashSetContainsOfIterableClient < __ElementType, __Hasher >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using ContainsOfInitializerListClient       = __hidden :: __impl :: __LinkedHashSetContainsOfInitializerListClient < __ElementType, __Hasher >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using FindUniqueClient                      = __hidden :: __impl :: __LinkedHashSetFindUniqueClient < __ElementType, __Hasher >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using DelegateForwardConstIterableClient    = __hidden :: __impl :: __LinkedHashSetDelegateForwardConstIterableClient < __ElementType, __Hasher >;


    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        friend Server;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using typename SetBase :: __GenericHandler;         /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using typename SetBase :: __GenericConstHandler;    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */


    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using ConstIterator = __hidden :: __impl :: __LinkedHashSetIterator < __ElementType, __Hasher >;


    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using ElementType   = __ElementType;


    private:    /* NOLINT(readability-redundant-access-specifiers) */
        friend RandomInsertionClient;

    private:    /* NOLINT(readability-redundant-access-specifiers) */
        friend IteratorRemoveClient;

    private:    /* NOLINT(readability-redundant-access-specifiers) */
        friend DelegateForwardConstIterableClient;

    private:    /* NOLINT(readability-redundant-access-specifiers) */
        friend FindUniqueClient;


    private:    /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto __iicch_obtainGenericHandler ( /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                __hidden :: __impl :: __IterableInternalRequestType requestType
        ) noexcept -> __GenericHandler override;

    private:    /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto __iicch_obtainGenericConstHandler (    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                __hidden :: __impl :: __IterableInternalRequestType requestType
        ) const noexcept -> __GenericConstHandler override;

    private:  /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard static auto __cbegin (
                LinkedHashSet const * pObject
        ) noexcept -> __hidden :: __impl :: __AbstractDelegateIterator < __ElementType const > *;  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

    private:  /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard static auto __cend (
                LinkedHashSet const * pObject
        ) noexcept -> __hidden :: __impl :: __AbstractDelegateIterator < __ElementType const > *;    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

    private:  /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard constexpr static auto __cbeginLocal (
                LinkedHashSet const * pObject
        ) noexcept -> ConstIterator;    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

    private:  /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard constexpr static auto __cendLocal (
                LinkedHashSet const * pObject
        ) noexcept -> ConstIterator;      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

    private:  /* NOLINT(readability-redundant-access-specifiers) */
        static auto __newAddress ( /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                LinkedHashSet       * pObject,
                __ElementType const * pReferenceElement,
                bool                * pNewElementCreated
        ) noexcept -> __ElementType *;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        static auto __removeConst ( /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                LinkedHashSet       * pObject,
                ConstIterator const * pIterator
        ) noexcept -> bool;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        static auto __removeConstArray ( /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                LinkedHashSet                 * pObject,
                ConstIterator   const * const * ppIterators,
                Size                            iteratorArraySize
        ) noexcept -> Size;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        static auto __findConst ( /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                LinkedHashSet const * pObject,
                __ElementType const & element
        ) noexcept -> __hidden :: __impl :: __AbstractDelegateIterator < __ElementType const > *;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_cpplang_NonConstConstexprMemberFunction auto __findConstLocal ( /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                LinkedHashSet const * pObject,
                __ElementType const & element
        ) noexcept -> ConstIterator;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using DelegateForwardConstIterableClient :: begin;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using DelegateForwardConstIterableClient :: end;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using DelegateForwardConstIterableClient :: cbegin;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using DelegateForwardConstIterableClient :: cend;


    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using RemoveByClient :: removeThat;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using RemoveByClient :: removeFirstThat;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using RemoveByClient :: removeLastThat;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using RemoveByClient :: removeAllThat;


    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using GenericStatementsClient :: forEach;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using GenericStatementsClient :: some;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using GenericStatementsClient :: atLeast;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using GenericStatementsClient :: atMost;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using GenericStatementsClient :: moreThan;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using GenericStatementsClient :: fewerThan;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using GenericStatementsClient :: count;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using GenericStatementsClient :: any;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using GenericStatementsClient :: all;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using GenericStatementsClient :: none;


    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using RemoveOfIterableClient :: removeOf;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using RemoveOfIterableClient :: removeFirstOf;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using RemoveOfIterableClient :: removeLastOf;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using RemoveOfIterableClient :: removeAllOf;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using RemoveOfIterableClient :: removeNotOf;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using RemoveOfIterableClient :: removeFirstNotOf;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using RemoveOfIterableClient :: removeLastNotOf;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using RemoveOfIterableClient :: removeAllNotOf;


    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using RemoveOfInitializerListClient :: removeOf;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using RemoveOfInitializerListClient :: removeFirstOf;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using RemoveOfInitializerListClient :: removeLastOf;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using RemoveOfInitializerListClient :: removeAllOf;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using RemoveOfInitializerListClient :: removeNotOf;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using RemoveOfInitializerListClient :: removeFirstNotOf;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using RemoveOfInitializerListClient :: removeLastNotOf;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using RemoveOfInitializerListClient :: removeAllNotOf;


    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using FindByClient :: findThat;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using FindByClient :: findFirstThat;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using FindByClient :: findLastThat;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using FindByClient :: findAllThat;


    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using FindOfIterableClient :: findOf;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using FindOfIterableClient :: findFirstOf;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using FindOfIterableClient :: findLastOf;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using FindOfIterableClient :: findAllOf;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using FindOfIterableClient :: findNotOf;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using FindOfIterableClient :: findFirstNotOf;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using FindOfIterableClient :: findLastNotOf;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using FindOfIterableClient :: findAllNotOf;


    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using FindOfInitializerListClient :: findOf;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using FindOfInitializerListClient :: findFirstOf;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using FindOfInitializerListClient :: findLastOf;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using FindOfInitializerListClient :: findAllOf;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using FindOfInitializerListClient :: findNotOf;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using FindOfInitializerListClient :: findFirstNotOf;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using FindOfInitializerListClient :: findLastNotOf;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using FindOfInitializerListClient :: findAllNotOf;


    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using ContainsOfIterableClient :: containsAnyOf;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using ContainsOfIterableClient :: containsAnyNotOf;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using ContainsOfIterableClient :: containsAllOf;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using ContainsOfIterableClient :: containsNoneOf;


    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using ContainsOfInitializerListClient :: containsAnyOf;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using ContainsOfInitializerListClient :: containsAnyNotOf;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using ContainsOfInitializerListClient :: containsAllOf;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using ContainsOfInitializerListClient :: containsNoneOf;


    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using RandomInsertionClient :: add;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using RandomInsertionClient :: addAll;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using RandomInsertionClient :: addAllOf;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using RandomInsertionClient :: insert;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using RandomInsertionClient :: insertAll;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using RandomInsertionClient :: insertAllOf;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using RandomInsertionClient :: emplace;


    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using IteratorRemoveClient :: remove;


    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using FindUniqueClient :: find;


    public: /* NOLINT(readability-redundant-access-specifiers) */
        constexpr LinkedHashSet () noexcept;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        LinkedHashSet ( /* NOLINT(google-explicit-constructor) */
                LinkedHashSet const & set
        ) noexcept;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        constexpr LinkedHashSet (
                LinkedHashSet && set
        ) noexcept;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_Explicit constexpr LinkedHashSet (
                __Hasher const & hasher
        ) noexcept;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        template <
                typename __IteratorType,                    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                typename __TElementType = __ElementType,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                cds :: meta :: EnableIf <
                        cds :: meta :: isCopyConstructible < __TElementType > ()
                > = 0
        > LinkedHashSet (
                __IteratorType const & begin,
                __IteratorType const & end,
                Size                   count = 0ULL
        ) noexcept;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        template <
                typename __IteratorType,                    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                typename __TElementType = __ElementType,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                cds :: meta :: EnableIf <
                        cds :: meta :: isCopyConstructible < __TElementType > ()
                > = 0
        > LinkedHashSet (
                __Hasher        const & hasher,
                __IteratorType  const & begin,
                __IteratorType  const & end,
                Size                    count = 0ULL
        ) noexcept;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        template <
                typename __TElementType = __ElementType,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                cds :: meta :: EnableIf <
                        cds :: meta :: isCopyConstructible < __TElementType > ()
                > = 0
        > LinkedHashSet (
                std :: initializer_list < __ElementType > const & initializerList
        ) noexcept;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        template <
                typename __TElementType = __ElementType,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                cds :: meta :: EnableIf <
                        cds :: meta :: isCopyConstructible < __TElementType > ()
                > = 0
        > LinkedHashSet (
                __Hasher                                    const & hasher,
                std :: initializer_list < __ElementType >   const & initializerList
        ) noexcept;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        template < typename __IterableType > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        __CDS_Explicit LinkedHashSet (
                __IterableType  const & iterable
        ) noexcept;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        template < typename __IterableType > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        LinkedHashSet (
                __Hasher        const & hasher,
                __IterableType  const & iterable
        ) noexcept;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        ~LinkedHashSet () noexcept override;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        auto operator = (
                LinkedHashSet const & set
        ) noexcept -> LinkedHashSet &;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        auto operator = (
                LinkedHashSet && set
        ) noexcept -> LinkedHashSet &;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        auto operator = (
                std :: initializer_list < __ElementType > const & initializerList
        ) noexcept -> LinkedHashSet &;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        template < typename __IterableType > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        auto operator = (
                __IterableType const & iterable
        ) noexcept -> LinkedHashSet &;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator == (
                LinkedHashSet const & set
        ) const noexcept -> bool;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator != (
                LinkedHashSet const & set
        ) const noexcept -> bool;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        auto clear () noexcept -> void override;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto size () const noexcept -> Size override;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        auto remove (
                __ElementType const & element
        ) noexcept -> bool override;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto contains (
                __ElementType const & element
        ) const noexcept -> bool override;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard auto sequence () & noexcept -> Sequence < LinkedHashSet < __ElementType, __Hasher > >;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard auto sequence () && noexcept -> Sequence < LinkedHashSet < __ElementType, __Hasher > >;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard auto sequence () const & noexcept -> Sequence < LinkedHashSet < __ElementType, __Hasher > const >;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard auto sequence () const && noexcept -> Sequence < LinkedHashSet < __ElementType, __Hasher > const >;
    };

} /* namespace cds */

#include "../../../shared/hashTable/impl/HashTable.hpp"
#include "../../../shared/linkedList/impl/SingleLinkedList.hpp"

#include "../../../shared/iterator/impl/HashTableIterator.hpp"
#include "../../../shared/iterator/impl/NodeIterator.hpp"                                                   /* NOLINT(llvm-include-order) */
#include "../../../shared/iterator/impl/IteratorGenericDecorator.hpp"

#include "../../../shared/iterableInternalCommunication/server/impl/SetServer.hpp"
#include "../../../shared/iterableInternalCommunication/server/impl/SetServerDispatcher.hpp"

#include "../../../shared/delegateIterator/impl/AbstractDelegateIterator.hpp"
#include "../../../shared/delegateIterator/impl/DelegateIterator.hpp"

#include "../../../shared/linkedHashSet/impl/Sequence.hpp"

#include "linkedHashSet/impl/LinkedHashSet.hpp"                                                             /* NOLINT(llvm-include-order) */
#include "linkedHashSet/impl/CTAD.hpp"

#include "../../../shared/collection/FunctionalConstructors.hpp"
#include "../../../shared/collection/impl/FunctionalConstructors.hpp"

#endif /* __CDS_LINKED_HASH_SET_HPP__ */
