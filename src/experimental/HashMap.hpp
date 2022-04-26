//
// Created by loghin on 4/24/2022.
//

#ifndef __CDS_EX_HASH_MAP_HPP__
#define __CDS_EX_HASH_MAP_HPP__

#include <CDS/experimental/Map>

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {

        template < typename K, typename V, typename H > __CDS_Requires (
                UniqueIdentifiable < K > &&
                HashCalculatorHasBoundaryFunction < H >
        ) class HashMap : public Map < K, V > {
        public:
            using KeyType               = typename Map < K, V > :: KeyType;
            using ValueType             = typename Map < K, V > :: ValueType;
            using EntryType             = typename Map < K, V > :: EntryType;
            using HashCalculatorType    = H;

        protected:
            using InitializerList       = typename Map < K, V > :: InitializerList;

        public:
            using Iterator              = typename Map < K, V > :: Iterator;
            using ConstIterator         = typename Map < K, V > :: ConstIterator;
            using ReverseIterator       = typename Map < K, V > :: ReverseIterator;
            using ConstReverseIterator  = typename Map < K, V > :: ConstReverseIterator;

        private:
            using HashBucketType        = DoubleLinkedList < Pair < KeyType const *, ValueType * > >;

        private:
            HashCalculatorType          _hashCalculator;
            HashBucketType            * _pBuckets { nullptr };

        public:
            HashMap () noexcept :
                    _pBuckets ( Memory :: instance().createArray < HashBucketType > ( this->hashCalculator().getBoundary() ) ) {

            }

            __CDS_NoDiscard __CDS_OptimalInline auto copy () const noexcept -> HashMap < K, V, H > * override {
                return Memory :: instance().create < HashMap < K, V, H > > ( * this );
            }

            __CDS_NoDiscard __CDS_OptimalInline auto hashCalculator () const noexcept -> H const & {
                return this->_hashCalculator;
            }

            template < typename MapHashCalculatorType >
            HashMap ( HashMap < K, V, HashCalculatorType > const & map ) noexcept :
                    _pBuckets ( Memory :: instance().createArray < HashBucketType > ( map.hashCalculator() ) ),
                    _hashCalculator ( map._hashCalculator ) {

                auto keyIt      = map._keys.begin();
                auto valueIt    = map._values.begin();

                while ( keyIt != map._keys.end() ) {
                    (void) this->_keys.pushBack( * keyIt );
                    (void) this->_values.pushBack( * valueIt );

                    auto & bucket = this->_pBuckets [ this->_hashCalculator( * keyIt ) ];
                    (void) bucket.pushBack ( { & ( this->_keys.back() ), & ( this->_values.back() ) } );

                    ++ keyIt, ++ valueIt;
                }
            }

            HashMap ( HashMap && map ) noexcept :
                    Map < K, V > ( std :: forward < Map < K, V > > ( map ) ),
                    _pBuckets ( cds :: exchange ( map._pBuckets, nullptr ) ),
                    _hashCalculator ( map._hashCalculator ) {

            }

            auto find ( KeyType const & key ) noexcept -> Optional < Reference < ValueType > > {
                auto & bucket = this->_pBuckets[this->_hashCalculator(key)];
                for ( auto & pair : bucket ) {
                    if ( Type < KeyType > :: compare ( key, * pair.first() ) ) {
                        return { Reference ( * pair.second() ) };
                    }
                }

                return {};
            }

            auto find ( KeyType const & key ) const noexcept -> Optional < Reference < ValueType const > > {
                auto & bucket = this->_pBuckets[this->_hashCalculator(key)];
                for ( auto & pair : bucket ) {
                    if ( Type < KeyType > :: compare ( key, * pair.first() ) ) {
                        return { Reference ( * pair.second() ) };
                    }
                }

                return {};
            }

            __CDS_NoDiscard auto containsKey ( KeyType const & key ) const noexcept -> bool override {
                return this->find(key).hasValue();
            }

        protected:
            auto allocInsertGetPtr ( EntryType const & entry ) noexcept -> EntryType * & override {
                auto findResult = this->find(entry.key());
                if ( findResult.hasValue() ) {
                    findResult.value() = entry.value();
                    return findResult.value();
                }

                auto & returnValue = Map < K, V > :: allocInsertGetPtr ( entry );
            }


        };

    }
}

#endif // __CDS_EX_HASH_MAP_HPP__
