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
#include <CDS/NotImplementedException>
#include "../ordered/LinkedListPublic.hpp"


template <class K, class V, class H = dataTypes::MediumCollisionDefaultHashFunction<K>>
#if defined(__cpp_concepts) && !defined(_MSC_VER)
requires
UniqueIdentifiable<K> &&
HashCalculatorHasBoundaryFunction<H>
#endif
class HashMap;


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

    using EntryReferenceList        = LinkedList < Reference < Entry > >;
    using EntryConstReferenceList   = LinkedList < EntryConstReference >;

    class MapPairNonExistent : public std::exception {
    public:
        __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto what() const noexcept -> StringLiteral final {
            return "Map Entry for given Key does not exist";
        }
    };

    __CDS_MaybeUnused virtual auto keys () const noexcept -> LinkedList < Reference < const Key > > = 0;
    virtual auto values () noexcept -> LinkedList < Reference < Value > > = 0;
    virtual auto values () const noexcept -> LinkedList < Reference < const Value > > = 0;
    virtual auto entries () noexcept -> LinkedList < Pair < Reference < const Key >, Reference < Value > > > = 0;
    virtual auto entries () const noexcept -> LinkedList < Pair < Reference < const Key >, Reference < const Value > > > = 0;

    virtual auto find (KeyConstReference) const noexcept -> Optional < Reference < const Value > > = 0;
    virtual auto find (KeyConstReference) noexcept -> Optional < Reference < Value > > = 0;
    virtual auto get (KeyConstReference) noexcept -> ValueReference = 0;
    virtual auto get (KeyConstReference) const noexcept(false) -> ValueConstReference = 0;
    __CDS_MaybeUnused virtual auto getOr (KeyConstReference, ValueConstReference) const noexcept -> ValueConstReference = 0;

    virtual __CDS_OptimalInline auto operator [] (KeyConstReference k) noexcept -> ValueReference { return this->get(k); }
    virtual __CDS_OptimalInline auto operator [] (KeyConstReference k) const noexcept(false) -> ValueConstReference { return this->get(k); }

    __CDS_MaybeUnused virtual auto containsValue (ValueConstReference) const noexcept -> bool = 0;
    virtual auto containsKey (KeyConstReference) const noexcept -> bool = 0;

    virtual auto remove (KeyConstReference) noexcept -> bool = 0;

    auto allocInsertGetPtr (EntryConstReference) noexcept -> EntryPointerReference override = 0;

    template < typename U = Entry, typename std :: enable_if < Type < U > :: copyConstructible, int > :: type = 0 >
    __CDS_OptimalInline auto insert (EntryConstReference entry) noexcept -> ValueConstReference {
        return ( (this->allocInsertGetPtr(entry)) = new Entry(entry) )->second();
    }

    template < typename U = Entry, typename std :: enable_if < Type < U > :: moveConstructible, int > :: type = 0 >
    __CDS_OptimalInline auto insert (EntryMoveReference entry) noexcept -> ValueConstReference {
        return ( ( this->allocInsertGetPtr(entry)) = new Entry(entry) )->second();
    }

    __CDS_MaybeUnused __CDS_OptimalInline auto emplace ( KeyConstReference k, ValueConstReference v ) noexcept -> ValueConstReference {
        return this->insert( {k, v} );
    }

    ~Map() noexcept override = default;

private:

    auto makeUnique () noexcept -> void override { }

    auto remove ( EntryConstReference, Size ) noexcept -> bool override { return false; }
    auto removeAll ( EntryConstReference o ) noexcept -> bool override { return false; }
    auto removeFirst ( EntryConstReference o ) noexcept -> bool override { return false; }
    auto removeLast ( EntryConstReference o ) noexcept -> bool override { return false; }
    auto removeOf ( const Collection<Entry> &, Size ) noexcept -> bool override { return false; }
    auto removeFirstOf ( const Collection<Entry> & o ) noexcept -> bool override { return false; }
    auto removeAllOf ( const Collection<Entry> & o ) noexcept -> bool override { return false; }
    auto removeLastOf ( const Collection<Entry> & ) noexcept -> bool override { return false; }
    auto removeNotOf ( const Collection<Entry> &, Size ) noexcept -> bool override { return false; }
    auto removeFirstNotOf ( const Collection<Entry> & o ) noexcept -> bool override { return false; }
    auto removeAllNotOf ( const Collection<Entry> & o ) noexcept -> bool override { return false; }
    auto removeLastNotOf ( const Collection<Entry> & ) noexcept -> bool override { return false; }
    auto removeOf ( const std::initializer_list<Entry> &, Size ) noexcept -> bool override { return false; }
    auto removeFirstOf ( const std::initializer_list<Entry> & o ) noexcept -> bool override { return false; }
    auto removeAllOf ( const std::initializer_list<Entry> & o ) noexcept -> bool override { return false; }
    auto removeLastOf ( const std::initializer_list<Entry> & ) noexcept -> bool override { return false; }
    auto removeNotOf ( const std::initializer_list<Entry> &, Size ) noexcept -> bool override { return false; }
    auto removeFirstNotOf ( const std::initializer_list<Entry> & o ) noexcept -> bool override { return false; }
    auto removeAllNotOf ( const std::initializer_list<Entry> & o ) noexcept -> bool override { return false; }
    auto removeLastNotOf ( const std::initializer_list<Entry> & ) noexcept -> bool override { return false; }
};

#include <sstream>

template < typename K, typename V >
REQUIRES (UniqueIdentifiable < K >)
class __CDS_MaybeUnused MultiMap : public Collection < Pair < K, V > > {
    using Key                                   = K;
    using Value                                 = V;
    using KeyReference        __CDS_MaybeUnused = Key &;
    using ValueReference      __CDS_MaybeUnused = Value &;
    using KeyConstReference                     = Key const &;
    using ValueConstReference __CDS_MaybeUnused = Value const &;

    class __CDS_MaybeUnused PairNonExistent : public std::exception {
    private:
        String _message;

    public:
        PairNonExistent() noexcept : std::exception() {
            this->_message = "No Value for given Key";
        }

        explicit PairNonExistent(KeyConstReference key) noexcept : std::exception () {
            std::stringstream oss;

            if __CDS_cpplang_IfConstexpr ( Type < KeyConstReference > :: ostreamPrintable )
                oss << "No Value for given Key '" << key << "'";
            else
                oss << "No Value for given Key";

            this->_message = oss.str();
        }

        __CDS_NoDiscard __CDS_cpplang_VirtualConstexpr auto what () const noexcept -> StringLiteral final {
            return this->_message.cStr();
        }
    };

    __CDS_MaybeUnused virtual auto keys () const noexcept -> LinkedList < Reference < Key const > > = 0;
    virtual auto values () noexcept -> LinkedList < Reference < Value > > = 0;
    virtual auto values () const noexcept -> LinkedList < Reference < Value const > > = 0;
    virtual auto entries () noexcept -> LinkedList < Pair < Reference < Key const >, Reference < Value > > > = 0;
    virtual auto entries () const noexcept -> LinkedList < Pair < Reference < Key const >, Reference < Value const > > > = 0;
};

namespace Utility {
    template <class K, class V> __CDS_Requires( UniqueIdentifiable <K> )
    struct TypeParseTraits<Map< K, V> > {
        constexpr static StringLiteral name = "Map";
    };
}


#endif //CDS_MAP_HPP
