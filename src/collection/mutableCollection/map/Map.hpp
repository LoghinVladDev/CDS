/* NOLINT(llvm-header-guard)
 * Created by loghin on 15.01.2021.
 */

#ifndef __CDS_MAP_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_MAP_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

#include <CDS/MutableCollection>
#include <CDS/Set>

#include "../../../shared/collectionInternalCommunication/client/primitive/FindUniqueMutablePrimitiveClient.hpp"    /* NOLINT(llvm-include-order) */
#include "../../../shared/collectionInternalCommunication/client/primitive/FindUniqueImmutablePrimitiveClient.hpp"
#include "../../../shared/collectionInternalCommunication/server/MutableCollectionServer.hpp"

#include "map/entry/Entry.hpp"

#include "map/Constructs.hpp"

namespace cds {

    template <
            typename __KeyType,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __ValueType    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    > using MapEntry = __hidden :: __impl :: __MapEntry < __KeyType, __ValueType >;


    template <
            typename __KeyType,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __ValueType    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    > __CDS_MaybeUnused constexpr auto mapEntryOf (
            __KeyType   && key,
            __ValueType && value
    ) noexcept ( noexcept ( MapEntry < __KeyType, __ValueType > ( std :: forward < __KeyType > ( key ), std :: forward < __ValueType > ( value ) ) ) ) -> MapEntry < __KeyType, __ValueType >;


    namespace meta {

        template < typename __T >               struct IsMapEntryCompatible                                     : FalseType {}; /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        template < typename __K, typename __V > struct IsMapEntryCompatible < cds :: Pair < __K, __V > >        : TrueType {};  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        template < typename __K, typename __V > struct IsMapEntryCompatible < cds :: MapEntry < __K, __V > >    : TrueType {};  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

        template < typename __T, bool = IsMapEntryCompatible < __T > :: value > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        struct MapEntryTraits {
            constexpr static bool const valid = false;
        };

        template < typename __K, typename __V > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        struct MapEntryTraits < cds :: MapEntry < __K, __V >, true > {
            constexpr static bool const valid = true;
            using KeyType   = cds :: meta :: RemoveConst < cds :: meta :: RemoveReference < decltype ( cds :: meta :: valueOf < cds :: MapEntry < __K, __V > > ().key () ) > >;
            using ValueType = cds :: meta :: RemoveReference < decltype ( cds :: meta :: valueOf < cds :: MapEntry < __K, __V > > ().value () ) >;
        };

        template < typename __K, typename __V > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        struct MapEntryTraits < cds :: Pair < __K, __V >, true > {
            constexpr static bool const valid = true;
            using KeyType   = cds :: meta :: RemoveReference < decltype ( cds :: meta :: valueOf < cds :: Pair < __K, __V > > ().first () ) >;
            using ValueType = cds :: meta :: RemoveReference < decltype ( cds :: meta :: valueOf < cds :: Pair < __K, __V > > ().second () ) >;
        };

    } /* namespace meta */


    template <
            typename __KeyType,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __ValueType    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    > class Map :                   /* NOLINT(*-virtual-class-destructor) */
            public MutableCollection < cds :: __hidden :: __impl :: __MapEntry < __KeyType, __ValueType > >,
            public __hidden :: __impl :: __MapFindUniqueImmutableClient < __KeyType, __ValueType >,
            public __hidden :: __impl :: __MapFindUniqueMutableClient < __KeyType, __ValueType > {

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using MutableCollectionBase     = MutableCollection < cds :: __hidden :: __impl :: __MapEntry < __KeyType, __ValueType > >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using FindUniqueImmutableClient = __hidden :: __impl :: __MapFindUniqueImmutableClient < __KeyType, __ValueType >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using FindUniqueMutableClient   = __hidden :: __impl :: __MapFindUniqueMutableClient < __KeyType, __ValueType >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using typename MutableCollectionBase :: __GenericHandler;       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using typename MutableCollectionBase :: __GenericConstHandler;  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using typename MutableCollectionBase :: ElementType;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        using MutableCollectionBase :: remove;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using EntryType = ElementType;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using KeyType   = __KeyType;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using ValueType = __ValueType;


    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        class AbstractMapProxy;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        class AbstractKeySetProxy;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        class AbstractValueMutableCollectionProxy;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        class AbstractEntryMutableCollectionProxy;


    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard virtual __CDS_cpplang_ConstexprPureAbstract auto keys () const noexcept -> Set < KeyType const > const & = 0;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard virtual __CDS_cpplang_ConstexprPureAbstract auto keys () noexcept -> Set < KeyType const > & = 0;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard virtual __CDS_cpplang_ConstexprPureAbstract auto values () const noexcept -> MutableCollection < ValueType > const & = 0;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard virtual __CDS_cpplang_ConstexprPureAbstract auto values () noexcept -> MutableCollection < ValueType > & = 0;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard virtual __CDS_cpplang_ConstexprPureAbstract auto entries () const noexcept -> MutableCollection < EntryType > const & = 0;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard virtual __CDS_cpplang_ConstexprPureAbstract auto entries () noexcept -> MutableCollection < EntryType > & = 0;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        constexpr Map () noexcept;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        constexpr Map (
                Map const & map
        ) noexcept;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        constexpr Map (
                Map && map
        ) noexcept;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_cpplang_ConstexprDestructor ~Map () noexcept override;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        auto operator = (
                Map const & /* map */
        ) noexcept -> Map & = delete;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        auto operator = (
                Map && /* map */
        ) noexcept -> Map & = delete;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using FindUniqueImmutableClient :: find;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using FindUniqueMutableClient :: find;


    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard auto toString () const noexcept -> String override;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        auto clear () noexcept -> void override = 0;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        virtual auto remove (
                __KeyType const & key
        ) noexcept -> bool = 0;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto contains (
                EntryType const & entry
        ) const noexcept -> bool override;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard __CDS_cpplang_VirtualConstexpr virtual auto containsKey (
                __KeyType const & key
        ) const noexcept -> bool = 0;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard __CDS_MaybeUnused __CDS_cpplang_VirtualConstexpr virtual auto containsValue (
                __ValueType const & value
        ) const noexcept -> bool = 0;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        virtual auto entryAt (
                __KeyType const & key,
                bool            * pNewElementCreated
        ) noexcept -> EntryType * = 0;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        virtual auto entryAt (
                __KeyType const & key
        ) const noexcept -> EntryType const * = 0;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        template <
                typename __TKeyType,                /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                typename __TValueType = ValueType,  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                cds :: meta :: EnableIf <
                        cds :: meta :: isDefaultConstructible < __TValueType > ()
                > = 0
        > auto get (
                __TKeyType && key
        ) noexcept -> ValueType &;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        auto at (
                KeyType const & key
        ) noexcept (false) -> ValueType &;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        auto at (
                KeyType const & key
        ) const noexcept (false) -> ValueType const &;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        template <
                typename __TKeyType,                /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                typename __TValueType = ValueType,  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                cds :: meta :: EnableIf <
                        cds :: meta :: isDefaultConstructible < __TValueType > ()
                > = 0
        > auto operator [] (
                __TKeyType && key
        ) noexcept -> ValueType &;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        auto operator [] (
                KeyType const & key
        ) const noexcept (false) -> ValueType const &;
    };

} /* namespace cds */

#include "map/AbstractMapProxy.hpp"                                                                                         /* NOLINT(llvm-include-order) */
#include "map/AbstractKeySetProxy.hpp"
#include "map/AbstractValueMutableCollectionProxy.hpp"
#include "map/AbstractEntryMutableCollectionProxy.hpp"

#include "../../../shared/collectionInternalCommunication/client/primitive/impl/FindUniqueMutablePrimitiveClient.hpp"       /* NOLINT(llvm-include-order) */
#include "../../../shared/collectionInternalCommunication/client/primitive/impl/FindUniqueImmutablePrimitiveClient.hpp"
#include "../../../shared/collectionInternalCommunication/server/impl/MutableCollectionServer.hpp"

#include "map/entry/impl/Entry.hpp"

#include "map/impl/Map.hpp"                                                                                                 /* NOLINT(llvm-include-order) */
#include "map/impl/AbstractMapProxy.hpp"
#include "map/impl/AbstractKeySetProxy.hpp"
#include "map/impl/AbstractValueMutableCollectionProxy.hpp"
#include "map/impl/AbstractEntryMutableCollectionProxy.hpp"

#endif /* __CDS_MAP_HPP__ */
