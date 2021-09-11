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


template <class K, class V>
#if defined(__cpp_concepts) && !defined(_MSC_VER)
requires UniqueIdentifiable <K>
#endif
class Map : public Collection < Pair < K, V > > {
public:
    using Key                       = K;
    using Value                     = V;
    using KeyReference              = Key &;
    using ValueReference            = Value &;
    using KeyConstReference         = Key const &;
    using ValueConstReference       = Value const &;
    using Entry                     = Pair < Key, Value >;
    using EntryReference            = Pair < Key, Value > &;
    using EntryConstReference       = Pair < Key, Value > const &;

    using EntryReferenceList        = LinkedList < Reference < Entry > >;
    using EntryConstReferenceList   = LinkedList < EntryConstReference >;

    class MapPairNonExistent : public std::exception {
    public:
        __CDS_NoDiscard auto what() const noexcept -> StringLiteral final {
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

    virtual inline auto operator [] (KeyConstReference k) noexcept -> ValueReference { return this->get(k); }
    virtual inline auto operator [] (KeyConstReference k) const noexcept(false) -> ValueConstReference { return this->get(k); }

    __CDS_MaybeUnused virtual auto containsValue (ValueConstReference) const noexcept -> bool = 0;
    virtual auto containsKey (KeyConstReference) const noexcept -> bool = 0;
    virtual auto remove (KeyConstReference) noexcept -> bool = 0;
    virtual auto insert (EntryConstReference) noexcept -> ValueConstReference & = 0;
    virtual auto insert (Entry &&) noexcept -> ValueConstReference & = 0;
    __CDS_MaybeUnused virtual auto emplace (KeyConstReference, ValueConstReference) noexcept -> ValueConstReference = 0;

    inline auto add (EntryConstReference e) noexcept -> void override {
        this->insert(e);
    }

    inline auto add (Entry && e) noexcept -> void override {
        this->insert(e);
    }

    ~Map() noexcept override = default;
private:
    auto contains ( EntryConstReference ) const noexcept -> bool override { return false; }

    auto back () noexcept(false) -> EntryReference final { throw NotImplementedException(); }
    auto back () const noexcept(false) -> EntryConstReference final { throw NotImplementedException(); }
    auto front () const noexcept(false) -> EntryConstReference final { throw NotImplementedException(); }
    auto front () noexcept(false) -> EntryReference final { throw NotImplementedException(); }

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
    auto replace ( EntryConstReference, EntryConstReference, Size ) noexcept -> void override {}
    auto replaceFirst ( EntryConstReference what, EntryConstReference with ) noexcept -> void override {}
    auto replaceAll ( EntryConstReference what, EntryConstReference with ) noexcept -> void override {}
    auto replaceLast ( EntryConstReference, EntryConstReference ) noexcept -> void override {}
    auto replaceOf ( const Collection<Entry> &, EntryConstReference, Size ) noexcept -> void override {}
    auto replaceFirstOf ( const Collection<Entry> & what, EntryConstReference with ) noexcept -> void override {}
    auto replaceAllOf ( const Collection<Entry> & what, EntryConstReference with ) noexcept -> void override {}
    auto replaceLastOf ( const Collection<Entry> &, EntryConstReference ) noexcept -> void override {}
    auto replaceNotOf ( const Collection<Entry> &, EntryConstReference, Size ) noexcept -> void override {}
    auto replaceFirstNotOf ( const Collection<Entry> & what, EntryConstReference with ) noexcept -> void override {}
    auto replaceAllNotOf ( const Collection<Entry> & what, EntryConstReference with ) noexcept -> void override {}
    auto replaceLastNotOf ( const Collection<Entry> &, EntryConstReference ) noexcept -> void override {}
    auto replaceOf ( const std::initializer_list<Entry> &, EntryConstReference, Size ) noexcept -> void override {}
    auto replaceFirstOf ( const std::initializer_list<Entry> & what, EntryConstReference with ) noexcept -> void override {}
    auto replaceAllOf ( const std::initializer_list<Entry> & what, EntryConstReference with ) noexcept -> void override {}
    auto replaceLastOf ( const std::initializer_list<Entry> &, EntryConstReference ) noexcept -> void override {}
    auto replaceNotOf ( const std::initializer_list<Entry> &, EntryConstReference, Size ) noexcept -> void override {}
    auto replaceFirstNotOf ( const std::initializer_list<Entry> & what, EntryConstReference with ) noexcept -> void override {}
    auto replaceAllNotOf ( const std::initializer_list<Entry> & what, EntryConstReference with ) noexcept -> void override {}
    auto replaceLastNotOf ( const std::initializer_list<Entry> &, EntryConstReference ) noexcept -> void override {}
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

        [[nodiscard]] constexpr auto what () const noexcept -> StringLiteral final {
            return this->_message.cStr();
        }
    };

    __CDS_MaybeUnused virtual auto keys () const noexcept -> LinkedList < Reference < Key const > > = 0;
    virtual auto values () noexcept -> LinkedList < Reference < Value > > = 0;
    virtual auto values () const noexcept -> LinkedList < Reference < Value const > > = 0;
    virtual auto entries () noexcept -> LinkedList < Pair < Reference < Key const >, Reference < Value > > > = 0;
    virtual auto entries () const noexcept -> LinkedList < Pair < Reference < Key const >, Reference < Value const > > > = 0;
};

#endif //CDS_MAP_HPP
