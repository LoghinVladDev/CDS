/* NOLINT(llvm-header-guard)
 * Created by loghin on 6/13/22.
 */

#ifndef __CDS_HASH_SET_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_HASH_SET_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

#include <CDS/Set>                  /* NOLINT(llvm-include-order) */
#include <CDS/FunctionalInterface>

#include "../../../shared/Node.hpp"
#include "../../../shared/rehashPolicy/rehashPolicy.hpp"

#include "../../../shared/iterator/HashTableIterator.hpp"

#include "../../../shared/iterableInternalCommunication/server/SetServerDispatcher.hpp"

#include "../../../shared/delegateIterator/AbstractDelegateIterator.hpp"
#include "../../../shared/delegateIterator/DelegateIterator.hpp"

#include "../../../shared/hashTable/HashTable.hpp"

#include "../../../shared/iterableInternalCommunication/server/SetServer.hpp"

#include "hashSet/Constructs.hpp"

namespace cds {

    template <
            typename __ElementType, /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __Hasher       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    > class __CDS_InheritsEBOs HashSet :
            public Set < __ElementType >,
            protected __hidden :: __impl :: __HashSetServer < __ElementType, __Hasher >,
            public __hidden :: __impl :: __HashSetImplementation < __ElementType, __Hasher >,
            public __hidden :: __impl :: __HashSetDispatcher < __ElementType, __Hasher >,
            public __hidden :: __impl :: __HashSetRandomInsertionClient < __ElementType, __Hasher >,
            public __hidden :: __impl :: __HashSetIteratorRemoveClient < __ElementType, __Hasher >,
            public __hidden :: __impl :: __HashSetFindOfIterableClient < __ElementType, __Hasher >,
            public __hidden :: __impl :: __HashSetFindOfInitializerListClient < __ElementType, __Hasher >,
            public __hidden :: __impl :: __HashSetFindByClient < __ElementType, __Hasher >,
            public __hidden :: __impl :: __HashSetRemoveOfIterableClient < __ElementType, __Hasher >,
            public __hidden :: __impl :: __HashSetRemoveOfInitializerListClient < __ElementType, __Hasher >,
            public __hidden :: __impl :: __HashSetRemoveByClient < __ElementType, __Hasher >,
            public __hidden :: __impl :: __HashSetGenericStatementsClient < __ElementType, __Hasher >,
            public __hidden :: __impl :: __HashSetFindUniqueClient < __ElementType, __Hasher >,
            public __hidden :: __impl :: __HashSetContainsOfIterableClient < __ElementType, __Hasher >,
            public __hidden :: __impl :: __HashSetContainsOfInitializerListClient < __ElementType, __Hasher >,
            public __hidden :: __impl :: __HashSetDelegateForwardConstIterableClient < __ElementType, __Hasher > {

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using SetBase                               = Set < __ElementType >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using Server                                = __hidden :: __impl :: __HashSetServer < __ElementType, __Hasher >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using Implementation                        = __hidden :: __impl :: __HashSetImplementation < __ElementType, __Hasher >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using Dispatcher                            = __hidden :: __impl :: __HashSetDispatcher < __ElementType, __Hasher >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using RandomInsertionClient                 = __hidden :: __impl :: __HashSetRandomInsertionClient < __ElementType, __Hasher >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using IteratorRemoveClient                  = __hidden :: __impl :: __HashSetIteratorRemoveClient < __ElementType, __Hasher >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using FindOfIterableClient                  = __hidden :: __impl :: __HashSetFindOfIterableClient < __ElementType, __Hasher >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using FindOfInitializerListClient           = __hidden :: __impl :: __HashSetFindOfInitializerListClient < __ElementType, __Hasher >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using FindByClient                          = __hidden :: __impl :: __HashSetFindByClient < __ElementType, __Hasher >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using RemoveOfIterableClient                = __hidden :: __impl :: __HashSetRemoveOfIterableClient < __ElementType, __Hasher >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using RemoveOfInitializerListClient         = __hidden :: __impl :: __HashSetRemoveOfInitializerListClient < __ElementType, __Hasher >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using RemoveByClient                        = __hidden :: __impl :: __HashSetRemoveByClient < __ElementType, __Hasher >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using GenericStatementsClient               = __hidden :: __impl :: __HashSetGenericStatementsClient < __ElementType, __Hasher >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using ContainsOfIterableClient              = __hidden :: __impl :: __HashSetContainsOfIterableClient < __ElementType, __Hasher >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using ContainsOfInitializerListClient       = __hidden :: __impl :: __HashSetContainsOfInitializerListClient < __ElementType, __Hasher >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using FindUniqueClient                      = __hidden :: __impl :: __HashSetFindUniqueClient < __ElementType, __Hasher >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using DelegateForwardConstIterableClient    = __hidden :: __impl :: __HashSetDelegateForwardConstIterableClient < __ElementType, __Hasher >;


    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        friend Server;


    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using typename SetBase :: __GenericHandler;         /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using typename SetBase :: __GenericConstHandler;    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */


    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using typename DelegateForwardConstIterableClient :: ConstIterator;


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
        friend RemoveByClient;

    private:    /* NOLINT(readability-redundant-access-specifiers) */
        friend RemoveOfIterableClient;

    private:    /* NOLINT(readability-redundant-access-specifiers) */
        friend RemoveOfInitializerListClient;


    private:    /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto __iicch_obtainGenericHandler ( /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                __hidden :: __impl :: __IterableInternalRequestType requestType
        ) noexcept -> __GenericHandler override;

    private:    /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto __iicch_obtainGenericConstHandler (    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                __hidden :: __impl :: __IterableInternalRequestType requestType
        ) const noexcept -> __GenericConstHandler override;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using DelegateForwardConstIterableClient :: begin;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using DelegateForwardConstIterableClient :: end;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using DelegateForwardConstIterableClient :: cbegin;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
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

    private:
        using IteratorRemoveClient :: removeAll;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using FindUniqueClient :: find;


    public: /* NOLINT(readability-redundant-access-specifiers) */
        constexpr HashSet () noexcept;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        HashSet ( /* NOLINT(google-explicit-constructor) */
                HashSet const & set
        ) noexcept;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        constexpr HashSet (
                HashSet && set
        ) noexcept;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_Explicit constexpr HashSet (
                __Hasher const & hasher
        ) noexcept;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        template <
                typename __IteratorType,                    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                typename __TElementType = __ElementType,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                cds :: meta :: EnableIf <
                        cds :: meta :: isCopyConstructible < __TElementType > ()
                > = 0
        > HashSet (
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
        > HashSet (
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
        > HashSet (
                std :: initializer_list < __ElementType > const & initializerList
        ) noexcept;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        template <
                typename __TElementType = __ElementType,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                cds :: meta :: EnableIf <
                        cds :: meta :: isCopyConstructible < __TElementType > ()
                > = 0
        > HashSet (
                __Hasher                                    const & hasher,
                std :: initializer_list < __ElementType >   const & initializerList
        ) noexcept;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        template < typename __IterableType > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        __CDS_Explicit HashSet (
                __IterableType  const & iterable
        ) noexcept;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        template < typename __IterableType > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        HashSet (
                __Hasher        const & hasher,
                __IterableType  const & iterable
        ) noexcept;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        ~HashSet () noexcept override;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        auto operator = (
                HashSet const & set
        ) noexcept -> HashSet &;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        auto operator = (
                HashSet && set
        ) noexcept -> HashSet &;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        auto operator = (
                std :: initializer_list < __ElementType > const & initializerList
        ) noexcept -> HashSet &;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        template < typename __IterableType > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        auto operator = (
                __IterableType const & iterable
        ) noexcept -> HashSet &;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator == (
                HashSet const & set
        ) const noexcept -> bool;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator != (
                HashSet const & set
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
        __CDS_NoDiscard auto sequence () & noexcept -> Sequence < HashSet < __ElementType, __Hasher > >;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard auto sequence () && noexcept -> Sequence < HashSet < __ElementType, __Hasher > >;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard auto sequence () const & noexcept -> Sequence < HashSet < __ElementType, __Hasher > const >;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard auto sequence () const && noexcept -> Sequence < HashSet < __ElementType, __Hasher > const >;
    };

} /* namespace cds */

#include "../../../shared/hashTable/impl/HashTable.hpp"

#include "../../../shared/iterator/impl/HashTableIterator.hpp"

#include "../../../shared/iterableInternalCommunication/server/impl/SetServer.hpp"
#include "../../../shared/iterableInternalCommunication/server/impl/SetServerDispatcher.hpp"

#include "../../../shared/delegateIterator/impl/AbstractDelegateIterator.hpp"
#include "../../../shared/delegateIterator/impl/DelegateIterator.hpp"

#include "hashSet/impl/HashSet.hpp"                                                                                     /* NOLINT(llvm-include-order) */
#include "hashSet/impl/CTAD.hpp"

#include "../../../shared/hashSet/impl/Sequence.hpp"

#include "../../../shared/collection/FunctionalConstructors.hpp"
#include "../../../shared/collection/impl/FunctionalConstructors.hpp"

#endif /* __CDS_HASH_SET_HPP__ */
