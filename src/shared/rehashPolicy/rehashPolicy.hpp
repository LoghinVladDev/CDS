//
// Created by loghin on 6/20/22.
//

#ifndef __CDS_SHARED_REHASH_POLICY_HPP__
#define __CDS_SHARED_REHASH_POLICY_HPP__

namespace cds {             // NOLINT(modernize-concat-nested-namespaces)
    namespace __hidden {    // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier)
        namespace __impl {  // NOLINT(bugprone-reserved-identifier)

            template < typename __SizeType > // NOLINT(bugprone-reserved-identifier)
            struct __RehashResult { // NOLINT(bugprone-reserved-identifier)
                __SizeType  _size;
                bool        _required;
            };

            template < typename __SizeType, bool __hasLoadFactor > // NOLINT(bugprone-reserved-identifier)
            class __RehashPolicy { // NOLINT(bugprone-reserved-identifier)

            public:
                using SizeType = __SizeType;

            public:
                constexpr static bool hasLoadFactor = false;
            };

            template < typename __BaseType = uint32 >                                   // NOLINT(bugprone-reserved-identifier)
            class __PrimeRehashPolicy : public __RehashPolicy < __BaseType, true > {    // NOLINT(bugprone-reserved-identifier)

            private:
                __BaseType _loadFactor;

            private:
                __BaseType _factorIndex = 0U;

            public:
                __CDS_Explicit constexpr __PrimeRehashPolicy (
                        __BaseType loadFactor = 1U
                ) noexcept :
                        _loadFactor ( loadFactor ) {

                }

            public:
                constexpr __PrimeRehashPolicy (
                        __PrimeRehashPolicy const & policy
                ) noexcept = default;

            public:
                __CDS_cpplang_NonConstConstexprMemberFunction auto reset () noexcept -> void {
                    this->_factorIndex = 0U;
                }

            public:
                __CDS_NoDiscard constexpr auto currentFactor () const noexcept -> __BaseType {

                    return __PrimeRehashPolicy :: _table [ this->_factorIndex ];
                }

            public:
                __CDS_NoDiscard constexpr auto loadFactor () const noexcept -> __BaseType {

                    return this->_loadFactor;
                }

            public:
                __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto rehashRequired (
                        Size bucketCount,
                        Size elementCount,
                        Size requiredCount
                ) noexcept -> __RehashResult < __BaseType > {

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
                static __BaseType const _table [29U];
            };

            template < typename __BaseType > // NOLINT(bugprone-reserved-identifier)
            __BaseType const __PrimeRehashPolicy < __BaseType > :: _table [29U] = {
                        13U, 27U, 57U, 117U, 237U,
                        477U, 957U, 1917U, 3837U, 7677U,
                        15357U, 30717U, 61437U, 122877U,
                        245757U, 491517U, 983037U, 1966077U,
                        3932157U, 7864317U, 15728637U, 31457277U,
                        62914557U, 125829117U, 251658237U,
                        503316477U, 1006632957U, 2013265917U,
                        4026531837U
            };

        }
    }
}

#endif // __CDS_SHARED_REHASH_POLICY_HPP__
