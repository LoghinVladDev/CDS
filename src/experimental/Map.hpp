//
// Created by loghin on 4/23/2022.
//

#ifndef __CDS_EX_MAP_HPP__
#define __CDS_EX_MAP_HPP__

#include <CDS/Concepts>
#include <CDS/Collection>
#include <CDS/DoubleLinkedList>
#include <CDS/experimental/View>

namespace cds {

    namespace hidden { // NOLINT(modernize-concat-nested-namespaces)
        namespace impl {
            template < typename K, typename V >
            class MapEntry {
            private:
                Reference < K const >   _keyReference;
                Reference < V >         _valueReference;

            public:
                MapEntry ( K const & key, V & value ) noexcept :
                        _keyReference ( key ),
                        _valueReference ( value ) {

                }

                __CDS_NoDiscard constexpr auto key () const noexcept -> K const & {
                    return this->_keyReference.get();
                }

                __CDS_NoDiscard constexpr auto value () noexcept -> V & {
                    return this->_valueReference.get();
                }

                __CDS_NoDiscard constexpr auto value () const noexcept -> V const & {
                    return this->_valueReference.get();
                }
            };
        }
    }

    template < typename K, typename V >
    class Pair;

    template < typename T >
    class List;

    namespace experimental {
        template < typename K, typename V > __CDS_Requires (
                UniqueIdentifiable < K >
        ) class Map : public Collection < hidden :: impl :: MapEntry < K const, V > > {
        protected:
            DoubleLinkedList < K > _keys;
            DoubleLinkedList < V > _values;

        public:
            using KeyType               = K;
            using ValueType             = V;

            using EntryType             = hidden :: impl :: MapEntry < KeyType const, ValueType >;

        protected:
            using InitializerListEntry  = Pair < KeyType, ValueType >;
            using InitializerList       = std :: initializer_list < InitializerListEntry >;

        public:
            using Iterator              = typename Collection < EntryType > :: Iterator;
            using ConstIterator         = typename Collection < EntryType > :: ConstIterator;
            using ReverseIterator       = typename Collection < EntryType > :: ReverseIterator;
            using ConstReverseIterator  = typename Collection < EntryType > :: ConstReverseIterator;

        protected:
            using DelegateIterator      = typename Collection < EntryType > :: DelegateIterator;
            using DelegateConstIterator = typename Collection < EntryType > :: DelegateConstIterator;

            Map () noexcept = default;
            Map ( Map const & map ) noexcept :
                    _keys ( map._keys ),
                    _values ( map._values ) {

            }

            Map ( Map && map ) noexcept :
                    _keys ( std :: move ( map._keys ) ),
                    _values ( std :: move ( map._values ) ) {

            }

        public:
            ~Map () noexcept override = default;

            __CDS_NoDiscard constexpr auto keys () const noexcept -> List < KeyType > const & {
                return this->_keys;
            }

            __CDS_NoDiscard constexpr auto empty () const noexcept -> bool override {
                return this->keys().empty();
            }

            __CDS_NoDiscard constexpr auto size () const noexcept -> Size override {
                return this->keys().size();
            }

            auto clear () noexcept -> void override {
                this->_keys.clear();
                this->_values.clear();
            }

            auto copy () const noexcept -> Map * override = 0;

            constexpr auto values () noexcept -> View < List < ValueType > > {
                return View < List < ValueType > > ( this->_values );
            }

            constexpr auto values () const noexcept -> View < List < ValueType > const > {
                return View < List < ValueType > const > ( this->_values );
            }

            __CDS_OptimalInline auto entries () noexcept -> DoubleLinkedList < EntryType > {
                DoubleLinkedList < EntryType > entries;

                auto keyIt = this->_keys.begin();
                auto valueIt = this->_values.begin();

                while ( keyIt != this->keys().end() ) {
                    entries.add ( EntryType ( * keyIt, * valueIt ) );
                    ++ keyIt, ++ valueIt;
                }

                return entries;
            }

            __CDS_NoDiscard __CDS_OptimalInline virtual auto containsKey ( KeyType const & key ) const noexcept -> bool {
                return this->keys().contains ( key );
            }

            __CDS_NoDiscard __CDS_OptimalInline auto containsValue ( ValueType const & value ) const noexcept -> bool {
                return this->values().contains ( value );
            }

            __CDS_NoDiscard __CDS_OptimalInline virtual auto find ( KeyType const & key ) noexcept -> Optional < Reference < ValueType > > = 0;
            __CDS_NoDiscard __CDS_OptimalInline virtual auto find ( KeyType const & key ) const noexcept -> Optional < Reference < ValueType > const > = 0;

            __CDS_NoDiscard __CDS_OptionalInline auto toString () const noexcept -> String override {
                if ( this->empty() ) {
                    return "{ }";
                }

                std :: stringstream out;
                out << "{ ";

                auto keyIt      = this->_keys.begin();
                auto valueIt    = this->_values.begin();

                while ( keyIt != this->_keys.end() ) {
                    Type < V > :: streamPrint ( Type < K > :: streamPrint ( out, * keyIt ) << " : ", * valueIt ) << ", ";
                    ++ keyIt, ++ valueIt;
                }

                return String ( out.str() ).removeSuffix(", ").append(" }");
            }

        protected:
            auto allocInsertGetPtr ( EntryType const & entry ) noexcept -> EntryType * & override {
                static auto dummyInsertAddress = Type < EntryType > :: unsafeAddress();

                (void) this->_keys.pushBack ( entry.key() );
                (void) this->_values.pushBack ( entry.value() );

                return dummyInsertAddress;
            }

        public:
            virtual auto insert ( Pair < KeyType, ValueType > const & entry ) noexcept -> ValueType & {
                (void) this->_keys.pushBack ( entry.first() );
                (void) this->_values.pushBack ( entry.second() );
                return this->_values.back();
            }

            virtual auto insert ( Pair < KeyType, ValueType > && entry ) noexcept -> ValueType & {
                (void) this->_keys.pushBack ( std :: move ( entry.first() ) );
                (void) this->_values.pushBack ( std :: move ( entry.second() ) );
                return this->_values.back();
            }

        private:

            auto remove ( EntryType const &, Size ) noexcept -> bool override { return false; }
            auto removeLast ( EntryType const & entry ) noexcept -> bool override { return false; }
            auto removeOf ( Collection < EntryType > const &, Size ) noexcept -> bool override { return false; }
            auto removeLastOf ( Collection < EntryType > const & ) noexcept -> bool override { return false; }
            auto removeNotOf ( Collection < EntryType > const &, Size ) noexcept -> bool override { return false; }
            auto removeLastNotOf ( Collection < EntryType > const & ) noexcept -> bool override { return false; }
            auto removeOf ( std :: initializer_list < EntryType > const &, Size ) noexcept -> bool override { return false; }
            auto removeLastOf ( std :: initializer_list < EntryType > const & ) noexcept -> bool override { return false; }
            auto removeNotOf ( std :: initializer_list < EntryType > const &, Size ) noexcept -> bool override { return false; }
            auto removeLastNotOf ( std :: initializer_list < EntryType > const & ) noexcept -> bool override { return false; }
        };
    }

}

#endif // __CDS_EX_MAP_HPP__
