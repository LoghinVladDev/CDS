//
// Created by loghin on 25.01.2021.
//

#ifndef CDS_MAP_HPP
#define CDS_MAP_HPP

#include <CDS/Types>
#include <CDS/Concepts>

#include <CDS/Collection>
#include <CDS/Pair>
#include <CDS/Optional>
#include <CDS/Reference>
#include <CDS/Hasher>

namespace cds {

    template <class K, class V, class H = utility :: MediumCollisionDefaultHashFunction<K>> __CDS_Requires (
        UniqueIdentifiable<K> &&
        HashCalculatorHasBoundaryFunction<H>
    ) class HashMap;


    template <class K, class V> __CDS_Requires( UniqueIdentifiable <K> )
    class Map : public Collection < Pair < K, V > > {
    public:
        using Key                       = K;
        using KeyReference              = Key &;
        using KeyConstReference         = Key const &;
        using KeyMoveReference          = Key &&;

        using Value                     = V;
        using ValueReference            = Value &;
        using ValueConstReference       = Value const &;
        using ValueMoveReference        = Value &&;

        using Entry                     = Pair < Key, Value >;
        using EntryReference            = Entry &;
        using EntryConstReference       = Entry const &;
        using EntryMoveReference        = Entry &&;
        using EntryPointer              = Entry *;
        using EntryPointerReference     = EntryPointer &;

        using EntryReferenceList        = DoubleLinkedList < Reference < Entry > >;
        using EntryConstReferenceList   = DoubleLinkedList < EntryConstReference >;

        using InitializerList           = typename Collection < Entry > :: InitializerList;

    public:
        using Iterator                  = typename Collection < Entry > :: Iterator;
        using ConstIterator             = typename Collection < Entry > :: ConstIterator;

        using ReverseIterator           = typename Collection < Entry > :: ReverseIterator;
        using ConstReverseIterator      = typename Collection < Entry > :: ConstReverseIterator;

    protected:
        using DelegateIterator          = typename Collection < Entry > :: DelegateIterator;
        using DelegateConstIterator     = typename Collection < Entry > :: DelegateConstIterator;

    public:
        __CDS_MaybeUnused virtual auto keys () const noexcept -> DoubleLinkedList < Reference < const Key > > = 0;
        virtual auto values () noexcept -> DoubleLinkedList < Reference < Value > > = 0;
        virtual auto values () const noexcept -> DoubleLinkedList < Reference < const Value > > = 0;
        virtual auto entries () noexcept -> DoubleLinkedList < Pair < Reference < const Key >, Reference < Value > > > = 0;
        virtual auto entries () const noexcept -> DoubleLinkedList < Pair < Reference < const Key >, Reference < const Value > > > = 0;

        virtual auto find (KeyConstReference) const noexcept -> Optional < Reference < const Value > > = 0;
        virtual auto find (KeyConstReference) noexcept -> Optional < Reference < Value > > = 0;
        virtual auto get (KeyConstReference) noexcept -> ValueReference = 0;
        virtual auto get (KeyConstReference) const noexcept(false) -> ValueConstReference = 0;
        __CDS_MaybeUnused virtual auto getOr (KeyConstReference, ValueConstReference) const noexcept -> ValueConstReference = 0;

        virtual __CDS_OptimalInline auto operator [] (KeyConstReference k) noexcept -> ValueReference {
            return this->get(k);
        }

        virtual __CDS_OptimalInline auto operator [] (KeyConstReference k) const noexcept(false) -> ValueConstReference {
            return this->get(k);
        }

        __CDS_MaybeUnused virtual auto containsValue (ValueConstReference) const noexcept -> bool = 0;
        virtual auto containsKey (KeyConstReference) const noexcept -> bool = 0;

        virtual auto remove (KeyConstReference) noexcept -> bool = 0;

        auto allocInsertGetPtr (EntryConstReference) noexcept -> EntryPointerReference override = 0;

        template < typename U = Entry, EnableIf < Type < U > :: copyConstructible > = 0 >
        __CDS_OptimalInline auto insert (EntryConstReference entry) noexcept -> ValueReference {
            return ( (this->allocInsertGetPtr(entry)) = new Entry(entry) )->second();
        }

        template < typename U = Entry, EnableIf < Type < U > :: moveConstructible > = 0 >
        __CDS_OptimalInline auto insert (EntryMoveReference entry) noexcept -> ValueReference {
            return ( ( this->allocInsertGetPtr(entry)) = new Entry(entry) )->second();
        }

        __CDS_MaybeUnused __CDS_OptimalInline auto emplace ( KeyConstReference k, ValueConstReference v ) noexcept -> ValueConstReference {
            return this->insert( {k, v} );
        }

        __CDS_cpplang_ConstexprDestructor ~Map() noexcept override = default;

    private:

        auto makeUnique () noexcept -> void override { }

        auto remove ( EntryConstReference, Size ) noexcept -> bool override { return false; }
        auto removeLast ( EntryConstReference o ) noexcept -> bool override { return false; }
        auto removeOf ( const Collection<Entry> &, Size ) noexcept -> bool override { return false; }
        auto removeLastOf ( const Collection<Entry> & ) noexcept -> bool override { return false; }
        auto removeNotOf ( const Collection<Entry> &, Size ) noexcept -> bool override { return false; }
        auto removeLastNotOf ( const Collection<Entry> & ) noexcept -> bool override { return false; }
        auto removeOf ( const std::initializer_list<Entry> &, Size ) noexcept -> bool override { return false; }
        auto removeLastOf ( const std::initializer_list<Entry> & ) noexcept -> bool override { return false; }
        auto removeNotOf ( const std::initializer_list<Entry> &, Size ) noexcept -> bool override { return false; }
        auto removeLastNotOf ( const std::initializer_list<Entry> & ) noexcept -> bool override { return false; }
    };

}

#include <sstream>

namespace cds {

    template < typename K, typename V > __CDS_Requires( UniqueIdentifiable < K > )
    class __CDS_MaybeUnused MultiMap : public Collection < Pair < K, V > > {
        using Key                                   = K;
        using Value                                 = V;
        using KeyReference        __CDS_MaybeUnused = Key &;
        using ValueReference      __CDS_MaybeUnused = Value &;
        using KeyConstReference   __CDS_MaybeUnused = Key const &;
        using ValueConstReference __CDS_MaybeUnused = Value const &;

        __CDS_MaybeUnused virtual auto keys () const noexcept -> DoubleLinkedList < Reference < Key const > > = 0;
        virtual auto values () noexcept -> DoubleLinkedList < Reference < Value > > = 0;
        virtual auto values () const noexcept -> DoubleLinkedList < Reference < Value const > > = 0;
        virtual auto entries () noexcept -> DoubleLinkedList < Pair < Reference < Key const >, Reference < Value > > > = 0;
        virtual auto entries () const noexcept -> DoubleLinkedList < Pair < Reference < Key const >, Reference < Value const > > > = 0;
    };

}

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace utility {

        template <class K, class V> __CDS_Requires( UniqueIdentifiable <K> )
        struct TypeParseTraits<Map< K, V> > {
            constexpr static StringLiteral name = "Map";
        };

    }
}

#endif //CDS_MAP_HPP
