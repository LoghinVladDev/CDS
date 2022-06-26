//
// Created by loghin on 6/26/22.
//

#ifndef __CDS_EX_ARRAY_HPP__
#define __CDS_EX_ARRAY_HPP__

#include "Collection.hpp"

namespace cds {
    namespace experimental {
//
//        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
//        class RandomAccessIterator {
//        private:
//            __ElementType * _pCurrent { nullptr };
//
//        public:
//            constexpr RandomAccessIterator () noexcept = default;
//            constexpr RandomAccessIterator (
//                    __ElementType * pCurrent
//            ) noexcept : _pCurrent (pCurrent) {}
//            constexpr RandomAccessIterator(RandomAccessIterator const&) noexcept = default;
//            constexpr RandomAccessIterator(RandomAccessIterator &&) noexcept = default;
//            auto operator = (RandomAccessIterator const &) noexcept -> RandomAccessIterator & = default;
//            auto operator = (RandomAccessIterator &&) noexcept -> RandomAccessIterator & = default;
//            auto operator == (RandomAccessIterator const & it) const noexcept -> bool {
//                return this->_pCurrent == it._pCurrent;
//            }
//            auto operator != (RandomAccessIterator const & it) const noexcept -> bool {
//                return this->_pCurrent != it._pCurrent;
//            }
//            auto operator * () const noexcept -> __ElementType & {
//                return * this->_pCurrent;
//            }
//            auto operator ++ () noexcept -> RandomAccessIterator & {
//                ++ this->_pCurrent;
//                return * this;
//            }
//            auto valid () const noexcept -> bool {
//                return this->_pCurrent != nullptr;
//            }
//        };

        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        class Array :
                public Collection < __ElementType >,
                public __hidden :: __impl :: __DelegateConstIterableImpl <
                        Array < __ElementType >,
                        __ElementType,
                        RandomAccessIterator < __ElementType const >,
                        true,
                        false
                > {

        protected:
            using Collection < __ElementType > :: begin;
            using Collection < __ElementType > :: end;
            using Collection < __ElementType > :: cbegin;
            using Collection < __ElementType > :: cend;

            auto __dci_delegate ( __hidden::__impl::DelegateIteratorRequestType requestType ) const noexcept ->
                    __hidden :: __impl :: __AbstractDelegateIterator < __ElementType const > * override {

                return this->__dci_delegateAcquisition ( requestType );
            }
        private:
            __ElementType v[64];
            Size s{0};

        public:
            using Iterator = RandomAccessIterator < __ElementType const >;

        public:
            auto begin () const noexcept -> Iterator {
                return & this->v[0];
            }

        public:
            auto end () const noexcept -> Iterator {
                return & this->v[s];
            }

        public:
            void pushBack ( __ElementType const & e ) {
                this->v[this->s++] = e;
            }
        };

    }
}

#endif // __CDS_ARRAY_HPP__
