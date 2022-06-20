//
// Created by loghin on 6/20/22.
//

#ifndef __CDS_REHASH_POLICY_HPP__
#define __CDS_REHASH_POLICY_HPP__

namespace cds {
    namespace __hidden {
        namespace __impl {

            template < typename __SizeType >
            struct __RehashResult {
                __SizeType  _size;
                bool        _required;
            };

            template < typename __SizeType, bool __hasLoadFactor >
            class __RehashPolicy {

            public:
                using SizeType = __SizeType;

            public:
                constexpr static bool hasLoadFactor = false;
            };

            class __PrimeRehashPolicy : __RehashPolicy < uint32, true > {

            private:
                uint32 _loadFactor;

            private:
                uint32 _factorIndex = 0U;

            public:
                __CDS_Explicit constexpr __PrimeRehashPolicy (
                        uint32 loadFactor = 1U
                ) noexcept :
                        _loadFactor ( loadFactor ) {

                }

            public:
                __CDS_NoDiscard constexpr auto currentFactor () const noexcept -> uint32 {

                    return __PrimeRehashPolicy :: _table [ this->_factorIndex ];
                }

            public:
                __CDS_NoDiscard constexpr auto loadFactor () const noexcept -> uint32 {

                    return this->_loadFactor;
                }

            public:
                __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto rehashRequired (
                        Size bucketCount,
                        Size elementCount,
                        Size requiredCount
                ) noexcept -> __RehashResult < uint32 > {

                    if ( this->_factorIndex == 28U ) {
                        return { __PrimeRehashPolicy :: _table [ this->_factorIndex ], false };
                    }

                    Size const totalRequired        = requiredCount + elementCount;
                    Size const loadAdjusted         = bucketCount * this->_loadFactor;
                    Size const minimumGrowthFactor  = 2ULL;

                    if ( loadAdjusted > totalRequired ) {
                        return { this->currentFactor(), false };
                    } if ( totalRequired <= loadAdjusted * minimumGrowthFactor ) {
                        return { __PrimeRehashPolicy :: _table [ ++ this->_factorIndex ], true };
                    } else {
                        while ( totalRequired < _table [ this->_factorIndex ] * this->_loadFactor && this->_factorIndex < 28U ) {
                            ++ this->_factorIndex;
                        }

                        return { __PrimeRehashPolicy :: _table [ this->_factorIndex ], true };
                    }
                }

            private:
                constexpr static uint32 _table [] = {
                        13U, 27U, 57U, 117U, 237U,
                        477U, 957U, 1917U, 3837U, 7677U,
                        15357U, 30717U, 61437U, 122877U,
                        245757U, 491517U, 983037U, 1966077U,
                        3932157U, 7864317U, 15728637U, 31457277U,
                        62914557U, 125829117U, 251658237U,
                        503316477U, 1006632957U, 2013265917U,
                        4026531837U
                };
            };

        }
    }
}

#endif // __CDS_REHASH_POLICY_HPP__
