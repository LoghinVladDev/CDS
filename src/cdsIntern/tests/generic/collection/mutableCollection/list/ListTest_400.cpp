#include "ListTest_common.hpp"

namespace {
    namespace relIns {

        enum TFlags {
            TNoMask         = 0x0000FFFFU,
            ItCase1         = 0x00010000U,
            ItCase2         = 0x00020000U,
            ItCase3         = 0x00040000U,
            ItCase4         = 0x00080000U,
            ItCaseMask      = 0x000F0000U,
            ValueCase1      = 0x00100000U,
            ValueCase2      = 0x00200000U,
            ValueCase3      = 0x00400000U,
            ValueCase4      = 0x00800000U,
            ValueCaseMask   = 0x00F00000U,
            OffsetCase1     = 0x01000000U,
            OffsetCase2     = 0x02000000U,
            OffsetCase3     = 0x04000000U,
            OffsetCase4     = 0x08000000U,
            OffsetCaseMask  = 0x0F000000U
        };

        struct TData {
            cds::uint32 tNo;
            cds::uint32 itCaseNo;
            cds::uint32 valueCaseNo;
            cds::uint32 offsetCaseNo;
        };

        inline auto tFlagsToTData (cds::uint32 flags) noexcept -> TData {

            TData data;
            data.tNo = flags & TFlags::TNoMask;

            auto const case1Value = 1;
            auto const case2Value = 2;
            auto const case3Value = 3;
            auto const case4Value = 4;

            switch (flags & TFlags::ItCaseMask) {
                case TFlags::ItCase1: {
                    data.itCaseNo = case1Value;
                    break;
                }
                case TFlags::ItCase2: {
                    data.itCaseNo = case2Value;
                    break;
                }
                case TFlags::ItCase3: {
                    data.itCaseNo = case3Value;
                    break;
                }
                case TFlags::ItCase4: {
                    data.itCaseNo = case4Value;
                    break;
                }
                default: {
                    return {};
                }
            }

            switch (flags & TFlags::ValueCaseMask) {
                case TFlags::ValueCase1: {
                    data.valueCaseNo = case1Value;
                    break;
                }
                case TFlags::ValueCase2: {
                    data.valueCaseNo = case2Value;
                    break;
                }
                case TFlags::ValueCase3: {
                    data.valueCaseNo = case3Value;
                    break;
                }
                case TFlags::ValueCase4: {
                    data.valueCaseNo = case4Value;
                    break;
                }
                default: {
                    return {};
                }
            }

            switch (flags & TFlags::OffsetCaseMask) {
                case TFlags::OffsetCase1: {
                    data.offsetCaseNo = case1Value;
                    break;
                }
                case TFlags::OffsetCase2: {
                    data.offsetCaseNo = case2Value;
                    break;
                }
                case TFlags::OffsetCase3: {
                    data.offsetCaseNo = case3Value;
                    break;
                }
                case TFlags::OffsetCase4: {
                    data.offsetCaseNo = case4Value;
                    break;
                }

                default: {
                    return {};
                }
            }

            return data;
        }

        template <typename E> using BeginPfn = 
                typename List<E> :: Iterator (List <E> :: *) ();

        template <typename E> using RBeginPfn = 
                typename List<E> :: ReverseIterator (List <E> :: *) ();

        template <typename E> using CBeginPfn = 
                typename List<E> :: ConstIterator (List <E> :: *) () const;

        template <typename E> using CRBeginPfn = 
                typename List<E> :: ConstReverseIterator (List <E> :: *) () const;

        template <typename, bool, typename = void> struct ItCaseDet {};

        template <typename E> struct ItCaseDet <BeginPfn<E>, false> {
            constexpr static TFlags const itCase = ItCase1;
        };
        
        template <typename E> struct ItCaseDet <RBeginPfn<E>, true> {
            constexpr static TFlags const itCase = ItCase3;
        };
        
        template <typename E> struct ItCaseDet <CBeginPfn<E>, false> {
            constexpr static TFlags const itCase = ItCase2;
        };
        
        template <typename E> struct ItCaseDet <CRBeginPfn<E>, true> {
            constexpr static TFlags const itCase = ItCase4;
        };
        

        template <
                typename E,
                template <typename ...> class C,
                typename F,
                typename R
        > auto singleInsBefIt (
                cds::uint32 testData,
                C <E> underTest,
                Test const * pTestLib,
                F pfnBegin,
                cds::uint32 offset,
                E const & singleValue,
                bool opStatus,
                R const & opResult
        ) noexcept -> bool {

            auto const tData = tFlagsToTData(testData);
            List <E> & lRef = underTest;
            auto it = (lRef.*pfnBegin) ();
            for (int i = 0; i < offset; ++ i) {
                ++ it;
            }

            if (
                    (opStatus != lRef.insertBefore (it, singleValue)) ||
                    ! equals (lRef, opResult)
            ) {

                pTestLib->logError (
                    "'LTC-%zu-"
                    "insertBefore"
                    "ItCase%zu"
                    "SingleValue%zu"
                    "OffsetCase%zu"
                    "-" __CDS_cpplang_core_version_name "' failed",
                    tData.tNo,
                    tData.itCaseNo,
                    tData.valueCaseNo,
                    tData.offsetCaseNo
                );
                return false;
            }
            

            pTestLib->logOK (
                "'LTC-%zu-"
                "insertBefore"
                "ItCase%zu"
                "SingleValue%zu"
                "OffsetCase%zu"
                "-" __CDS_cpplang_core_version_name "' OK",
                tData.tNo,
                tData.itCaseNo,
                tData.valueCaseNo,
                tData.offsetCaseNo
            );
            return true;
        }


        template <
                typename E,
                template <typename ...> class C,
                typename IGen, bool reversed
        > auto singleInsBefAll (
                cds::uint32 & tNo,
                std::initializer_list<E> const & initValues,
                Test const * pTestLib,
                IGen pfn,
                cds::Array <cds::Size> const & offsets,
                cds::Array <E> const & singleValues,
                cds::Array <cds::Array <bool>> const & statuses,
                cds::Array <cds::Array <cds::Array <E>>> const & results
        ) -> bool {

            bool result = true;
            cds::Array <TFlags> const offsetDatas = {OffsetCase1, OffsetCase2, OffsetCase3, OffsetCase4};
            cds::Array <TFlags> const valueDatas = {ValueCase1, ValueCase2, ValueCase3};

            for (cds::uint32 vIdx = 0; vIdx < singleValues.size(); ++ vIdx) {
                for (cds::uint32 offIdx = 0; offIdx < offsets.size(); ++ offIdx) {
                    result = result && singleInsBefIt <E, C, IGen> (
                            tNo | ItCaseDet <IGen, reversed> :: itCase | valueDatas [vIdx] | offsetDatas [offIdx],
                            initValues, pTestLib, pfn,
                            offsets [offIdx], singleValues [vIdx],
                            statuses [vIdx] [offIdx],
                            results [vIdx] [offIdx]
                    );

                    tNo ++;
                }
            }

            return result;
        }
        

        template <
                typename E,
                template <typename ...> class C,
                typename F,
                typename R
        > auto singleInsAftIt (
                cds::uint32 testData,
                C <E> underTest,
                Test const * pTestLib,
                F pfnBegin,
                cds::uint32 offset,
                E const & singleValue,
                bool opStatus,
                R const & opResult
        ) noexcept -> bool {

            auto const tData = tFlagsToTData(testData);
            List <E> & lRef = underTest;
            auto it = (lRef.*pfnBegin) ();
            for (int i = 0; i < offset; ++ i) {
                ++ it;
            }

            if (
                    (opStatus != lRef.insertAfter (it, singleValue)) ||
                    ! equals (lRef, opResult)
            ) {

                pTestLib->logError (
                    "'LTC-%zu-"
                    "insertAfter"
                    "ItCase%zu"
                    "SingleValue%zu"
                    "OffsetCase%zu"
                    "-" __CDS_cpplang_core_version_name "' failed",
                    tData.tNo,
                    tData.itCaseNo,
                    tData.valueCaseNo,
                    tData.offsetCaseNo
                );
                return false;
            }
            

            pTestLib->logOK (
                "'LTC-%zu-"
                "insertAfter"
                "ItCase%zu"
                "SingleValue%zu"
                "OffsetCase%zu"
                "-" __CDS_cpplang_core_version_name "' OK",
                tData.tNo,
                tData.itCaseNo,
                tData.valueCaseNo,
                tData.offsetCaseNo
            );
            return true;
        }


        template <
                typename E,
                template <typename ...> class C,
                typename IGen, bool reversed
        > auto singleInsAftAll (
                cds::uint32 & tNo,
                std::initializer_list<E> const & initValues,
                Test const * pTestLib,
                IGen pfn,
                cds::Array <cds::Size> const & offsets,
                cds::Array <E> const & singleValues,
                cds::Array <cds::Array <bool>> const & statuses,
                cds::Array <cds::Array <cds::Array <E>>> const & results
        ) -> bool {

            bool result = true;
            cds::Array <TFlags> const offsetDatas = {OffsetCase1, OffsetCase2, OffsetCase3, OffsetCase4};
            cds::Array <TFlags> const valueDatas = {ValueCase1, ValueCase2, ValueCase3};

            for (cds::uint32 vIdx = 0; vIdx < singleValues.size(); ++ vIdx) {
                for (cds::uint32 offIdx = 0; offIdx < offsets.size(); ++ offIdx) {
                    result = result && singleInsAftIt <E, C, IGen> (
                            tNo | ItCaseDet <IGen, reversed> :: itCase | valueDatas [vIdx] | offsetDatas [offIdx],
                            initValues, pTestLib, pfn,
                            offsets [offIdx], singleValues [vIdx],
                            statuses [vIdx] [offIdx],
                            results [vIdx] [offIdx]
                    );

                    tNo ++;
                }
            }

            return result;
        }
        

        template <
                typename E,
                template <typename ...> class C,
                typename F,
                typename R
        > auto mulInsBefIt (
                cds::uint32 testData,
                C <E> underTest,
                Test const * pTestLib,
                F pfnBegin,
                cds::uint32 offset,
                cds::Array <E> const & mValues,
                bool opStatus,
                R const & opResult
        ) noexcept -> bool {

            auto const tData = tFlagsToTData(testData);
            List <E> & lRef = underTest;
            auto it = (lRef.*pfnBegin) ();
            for (int i = 0; i < offset; ++ i) {
                ++ it;
            }

            if (
                    (opStatus != lRef.insertAllOfBefore (it, mValues)) ||
                    ! equals (lRef, opResult)
            ) {

                pTestLib->logError (
                    "'LTC-%zu-"
                    "insertAllOfBefore"
                    "ItCase%zu"
                    "MultipleValues%zu"
                    "OffsetCase%zu"
                    "-" __CDS_cpplang_core_version_name "' failed",
                    tData.tNo,
                    tData.itCaseNo,
                    tData.valueCaseNo,
                    tData.offsetCaseNo
                );
                return false;
            }
            

            pTestLib->logOK (
                "'LTC-%zu-"
                "insertAllOfBefore"
                "ItCase%zu"
                "MultipleValues%zu"
                "OffsetCase%zu"
                "-" __CDS_cpplang_core_version_name "' OK",
                tData.tNo,
                tData.itCaseNo,
                tData.valueCaseNo,
                tData.offsetCaseNo
            );
            return true;
        }


        template <
                typename E,
                template <typename ...> class C,
                typename IGen, bool reversed
        > auto mulInsBefAll (
                cds::uint32 & tNo,
                std::initializer_list<E> const & initValues,
                Test const * pTestLib,
                IGen pfn,
                cds::Array <cds::Size> const & offsets,
                cds::Array <cds::Array<E>> const & mValues,
                cds::Array <cds::Array <bool>> const & statuses,
                cds::Array <cds::Array <cds::Array <E>>> const & results
        ) -> bool {

            bool result = true;
            cds::Array <TFlags> const offsetDatas = {OffsetCase1, OffsetCase2, OffsetCase3, OffsetCase4};
            cds::Array <TFlags> const valueDatas = {ValueCase1, ValueCase2, ValueCase3};

            for (cds::uint32 vIdx = 0; vIdx < mValues.size(); ++ vIdx) {
                for (cds::uint32 offIdx = 0; offIdx < offsets.size(); ++ offIdx) {
                    result = result && mulInsBefIt <E, C, IGen> (
                            tNo | ItCaseDet <IGen, reversed> :: itCase | valueDatas [vIdx] | offsetDatas [offIdx],
                            initValues, pTestLib, pfn,
                            offsets [offIdx], mValues [vIdx],
                            statuses [vIdx] [offIdx],
                            results [vIdx] [offIdx]
                    );

                    tNo ++;
                }
            }

            return result;
        }
        

        template <
                typename E,
                template <typename ...> class C,
                typename F,
                typename R
        > auto mulInsAftIt (
                cds::uint32 testData,
                C <E> underTest,
                Test const * pTestLib,
                F pfnBegin,
                cds::uint32 offset,
                cds::Array <E> const & mValues,
                bool opStatus,
                R const & opResult
        ) noexcept -> bool {

            auto const tData = tFlagsToTData(testData);
            List <E> & lRef = underTest;
            auto it = (lRef.*pfnBegin) ();
            for (int i = 0; i < offset; ++ i) {
                ++ it;
            }

            if (
                    (opStatus != lRef.insertAllOfAfter (it, mValues)) ||
                    ! equals (lRef, opResult)
            ) {

                pTestLib->logError (
                    "'LTC-%zu-"
                    "insertAllOfAfter"
                    "ItCase%zu"
                    "MultipleValues%zu"
                    "OffsetCase%zu"
                    "-" __CDS_cpplang_core_version_name "' failed",
                    tData.tNo,
                    tData.itCaseNo,
                    tData.valueCaseNo,
                    tData.offsetCaseNo
                );
                return false;
            }
            

            pTestLib->logOK (
                "'LTC-%zu-"
                "insertAllOfAfter"
                "ItCase%zu"
                "MultipleValues%zu"
                "OffsetCase%zu"
                "-" __CDS_cpplang_core_version_name "' OK",
                tData.tNo,
                tData.itCaseNo,
                tData.valueCaseNo,
                tData.offsetCaseNo
            );
            return true;
        }


        template <
                typename E,
                template <typename ...> class C,
                typename IGen, bool reversed
        > auto mulInsAftAll (
                cds::uint32 & tNo,
                std::initializer_list<E> const & initValues,
                Test const * pTestLib,
                IGen pfn,
                cds::Array <cds::Size> const & offsets,
                cds::Array <cds::Array <E>> const & mValues,
                cds::Array <cds::Array <bool>> const & statuses,
                cds::Array <cds::Array <cds::Array <E>>> const & results
        ) -> bool {

            bool result = true;
            cds::Array <TFlags> const offsetDatas = {OffsetCase1, OffsetCase2, OffsetCase3, OffsetCase4};
            cds::Array <TFlags> const valueDatas = {ValueCase1, ValueCase2, ValueCase3};

            for (cds::uint32 vIdx = 0; vIdx < mValues.size(); ++ vIdx) {
                for (cds::uint32 offIdx = 0; offIdx < offsets.size(); ++ offIdx) {
                    result = result && mulInsAftIt <E, C, IGen> (
                            tNo | ItCaseDet <IGen, reversed> :: itCase | valueDatas [vIdx] | offsetDatas [offIdx],
                            initValues, pTestLib, pfn,
                            offsets [offIdx], mValues [vIdx],
                            statuses [vIdx] [offIdx],
                            results [vIdx] [offIdx]
                    );

                    tNo ++;
                }
            }

            return result;
        }
        

        template <
                typename E,
                template <typename ...> class C,
                typename F,
                typename R,
                typename ... P
        > auto packInsBefIt (
                cds::uint32 testData,
                C <E> underTest,
                Test const * pTestLib,
                F pfnBegin,
                cds::uint32 offset,
                bool opStatus,
                R const & opResult,
                P && ... pack
        ) noexcept -> bool {

            auto const tData = tFlagsToTData(testData);
            List <E> & lRef = underTest;
            auto it = (lRef.*pfnBegin) ();
            for (int i = 0; i < offset; ++ i) {
                ++ it;
            }

            if (
                    (opStatus != lRef.insertAllBefore (it, std::forward <P> (pack) ...)) ||
                    ! equals (lRef, opResult)
            ) {

                pTestLib->logError (
                    "'LTC-%zu-"
                    "insertAllBefore"
                    "ItCase%zu"
                    "Pack%zu"
                    "OffsetCase%zu"
                    "-" __CDS_cpplang_core_version_name "' failed",
                    tData.tNo,
                    tData.itCaseNo,
                    tData.valueCaseNo,
                    tData.offsetCaseNo
                );
                return false;
            }
            

            pTestLib->logOK (
                "'LTC-%zu-"
                "insertAllBefore"
                "ItCase%zu"
                "Pack%zu"
                "OffsetCase%zu"
                "-" __CDS_cpplang_core_version_name "' OK",
                tData.tNo,
                tData.itCaseNo,
                tData.valueCaseNo,
                tData.offsetCaseNo
            );
            return true;
        }


        template <
                typename E,
                template <typename ...> class C,
                typename IGen, bool reversed, typename ... P
        > auto packInsBefAll (
                cds::uint32 & tNo,
                std::initializer_list<E> const & initValues,
                Test const * pTestLib,
                IGen pfn,
                cds::Array <cds::Size> const & offsets,
                cds::Array <bool> const & statuses,
                cds::Array <cds::Array <E>> const & results,
                P const & ... pack
        ) -> bool {

            bool result = true;
            cds::Array <TFlags> const offsetDatas = {OffsetCase1, OffsetCase2, OffsetCase3, OffsetCase4};

            for (cds::uint32 offIdx = 0; offIdx < offsets.size(); ++ offIdx) {
                result = result && packInsBefIt <E, C, IGen> (
                        tNo | ItCaseDet <IGen, reversed> :: itCase | ValueCase1 | offsetDatas [offIdx],
                        initValues, pTestLib, pfn,
                        offsets [offIdx], 
                        statuses [offIdx],
                        results [offIdx],
                        pack ...
                );

                tNo ++;
            }

            return result;
        }
        

        template <
                typename E,
                template <typename ...> class C,
                typename F,
                typename R,
                typename ... P
        > auto packInsAftIt (
                cds::uint32 testData,
                C <E> underTest,
                Test const * pTestLib,
                F pfnBegin,
                cds::uint32 offset,
                bool opStatus,
                R const & opResult,
                P && ... pack
        ) noexcept -> bool {

            auto const tData = tFlagsToTData(testData);
            List <E> & lRef = underTest;
            auto it = (lRef.*pfnBegin) ();
            for (int i = 0; i < offset; ++ i) {
                ++ it;
            }

            if (
                    (opStatus != lRef.insertAllAfter (it, std::forward <P> (pack) ...)) ||
                    ! equals (lRef, opResult)
            ) {

                pTestLib->logError (
                    "'LTC-%zu-"
                    "insertAllAfter"
                    "ItCase%zu"
                    "Pack%zu"
                    "OffsetCase%zu"
                    "-" __CDS_cpplang_core_version_name "' failed",
                    tData.tNo,
                    tData.itCaseNo,
                    tData.valueCaseNo,
                    tData.offsetCaseNo
                );
                return false;
            }
            

            pTestLib->logOK (
                "'LTC-%zu-"
                "insertAllAfter"
                "ItCase%zu"
                "Pack%zu"
                "OffsetCase%zu"
                "-" __CDS_cpplang_core_version_name "' OK",
                tData.tNo,
                tData.itCaseNo,
                tData.valueCaseNo,
                tData.offsetCaseNo
            );
            return true;
        }


        template <
                typename E,
                template <typename ...> class C,
                typename IGen, bool reversed, typename ... P
        > auto packInsAftAll (
                cds::uint32 & tNo,
                std::initializer_list<E> const & initValues,
                Test const * pTestLib,
                IGen pfn,
                cds::Array <cds::Size> const & offsets,
                cds::Array <bool> const & statuses,
                cds::Array <cds::Array <E>> const & results,
                P const & ... pack
        ) -> bool {

            bool result = true;
            cds::Array <TFlags> const offsetDatas = {OffsetCase1, OffsetCase2, OffsetCase3, OffsetCase4};

            for (cds::uint32 offIdx = 0; offIdx < offsets.size(); ++ offIdx) {
                result = result && packInsAftIt <E, C, IGen> (
                        tNo | ItCaseDet <IGen, reversed> :: itCase | ValueCase1 | offsetDatas [offIdx],
                        initValues, pTestLib, pfn,
                        offsets [offIdx], 
                        statuses [offIdx],
                        results [offIdx],
                        pack ...
                );

                tNo ++;
            }

            return result;
        }

    }


    /* ListTestGroup-RelativeInsertion-cpp-xx : LTG-00400-RI-cpp-xx. Tests LTC-00401-RI to LTC-00624-RI */
    template <
            template < typename ... > class __TestedType,
            typename __EnclosedType,
            typename ... __Values
    > auto listTestGroupRelativeInsertion (
            Test * pTestLib,
            std :: initializer_list < __EnclosedType > const & initValues,
            typename List < __EnclosedType > :: Iterator ( List < __EnclosedType > :: * pBeginFn ) (),
            typename List < __EnclosedType > :: Iterator ( List < __EnclosedType > :: * pEndFn ) (),
            typename List < __EnclosedType > :: ConstIterator ( List < __EnclosedType > :: * pBeginCFn ) () const,
            typename List < __EnclosedType > :: ConstIterator ( List < __EnclosedType > :: * pEndCFn ) () const,
            typename List < __EnclosedType > :: ReverseIterator ( List < __EnclosedType > :: * pRBeginFn ) (),
            typename List < __EnclosedType > :: ReverseIterator ( List < __EnclosedType > :: * pREndFn ) (),
            typename List < __EnclosedType > :: ConstReverseIterator ( List < __EnclosedType > :: * pRBeginCFn ) () const,
            typename List < __EnclosedType > :: ConstReverseIterator ( List < __EnclosedType > :: * pREndCFn ) () const,
            Size case1Offset,
            Size case2Offset,
            Size case3Offset,
            Size case4Offset,
            __EnclosedType const & singleValue1,
            __EnclosedType const & singleValue2,
            __EnclosedType const & singleValue3,
            std :: initializer_list < __EnclosedType > const & multipleValues1,
            std :: initializer_list < __EnclosedType > const & multipleValues2,
            std :: initializer_list < __EnclosedType > const & multipleValues3,

            std :: initializer_list < __EnclosedType > const & resSingle1Case1,
            std :: initializer_list < __EnclosedType > const & resSingle1Case2,
            std :: initializer_list < __EnclosedType > const & resSingle1Case3,
            std :: initializer_list < __EnclosedType > const & resSingle1Case4,
            std :: initializer_list < __EnclosedType > const & resSingle1RevCase1,
            std :: initializer_list < __EnclosedType > const & resSingle1RevCase2,
            std :: initializer_list < __EnclosedType > const & resSingle1RevCase3,
            std :: initializer_list < __EnclosedType > const & resSingle1RevCase4,

            std :: initializer_list < __EnclosedType > const & resSingle2Case1,
            std :: initializer_list < __EnclosedType > const & resSingle2Case2,
            std :: initializer_list < __EnclosedType > const & resSingle2Case3,
            std :: initializer_list < __EnclosedType > const & resSingle2Case4,
            std :: initializer_list < __EnclosedType > const & resSingle2RevCase1,
            std :: initializer_list < __EnclosedType > const & resSingle2RevCase2,
            std :: initializer_list < __EnclosedType > const & resSingle2RevCase3,
            std :: initializer_list < __EnclosedType > const & resSingle2RevCase4,

            std :: initializer_list < __EnclosedType > const & resSingle3Case1,
            std :: initializer_list < __EnclosedType > const & resSingle3Case2,
            std :: initializer_list < __EnclosedType > const & resSingle3Case3,
            std :: initializer_list < __EnclosedType > const & resSingle3Case4,
            std :: initializer_list < __EnclosedType > const & resSingle3RevCase1,
            std :: initializer_list < __EnclosedType > const & resSingle3RevCase2,
            std :: initializer_list < __EnclosedType > const & resSingle3RevCase3,
            std :: initializer_list < __EnclosedType > const & resSingle3RevCase4,

            std :: initializer_list < __EnclosedType > const & resMultiple1Case1,
            std :: initializer_list < __EnclosedType > const & resMultiple1Case2,
            std :: initializer_list < __EnclosedType > const & resMultiple1Case3,
            std :: initializer_list < __EnclosedType > const & resMultiple1Case4,
            std :: initializer_list < __EnclosedType > const & resMultiple1RevCase1,
            std :: initializer_list < __EnclosedType > const & resMultiple1RevCase2,
            std :: initializer_list < __EnclosedType > const & resMultiple1RevCase3,
            std :: initializer_list < __EnclosedType > const & resMultiple1RevCase4,

            std :: initializer_list < __EnclosedType > const & resMultiple2Case1,
            std :: initializer_list < __EnclosedType > const & resMultiple2Case2,
            std :: initializer_list < __EnclosedType > const & resMultiple2Case3,
            std :: initializer_list < __EnclosedType > const & resMultiple2Case4,
            std :: initializer_list < __EnclosedType > const & resMultiple2RevCase1,
            std :: initializer_list < __EnclosedType > const & resMultiple2RevCase2,
            std :: initializer_list < __EnclosedType > const & resMultiple2RevCase3,
            std :: initializer_list < __EnclosedType > const & resMultiple2RevCase4,

            std :: initializer_list < __EnclosedType > const & resMultiple3Case1,
            std :: initializer_list < __EnclosedType > const & resMultiple3Case2,
            std :: initializer_list < __EnclosedType > const & resMultiple3Case3,
            std :: initializer_list < __EnclosedType > const & resMultiple3Case4,
            std :: initializer_list < __EnclosedType > const & resMultiple3RevCase1,
            std :: initializer_list < __EnclosedType > const & resMultiple3RevCase2,
            std :: initializer_list < __EnclosedType > const & resMultiple3RevCase3,
            std :: initializer_list < __EnclosedType > const & resMultiple3RevCase4,

            std :: initializer_list < __EnclosedType > const & resMultipleVCase1,
            std :: initializer_list < __EnclosedType > const & resMultipleVCase2,
            std :: initializer_list < __EnclosedType > const & resMultipleVCase3,
            std :: initializer_list < __EnclosedType > const & resMultipleVCase4,
            std :: initializer_list < __EnclosedType > const & resMultipleVRevCase1,
            std :: initializer_list < __EnclosedType > const & resMultipleVRevCase2,
            std :: initializer_list < __EnclosedType > const & resMultipleVRevCase3,
            std :: initializer_list < __EnclosedType > const & resMultipleVRevCase4,

            std :: initializer_list < __EnclosedType > const & aresSingle1Case1,
            std :: initializer_list < __EnclosedType > const & aresSingle1Case2,
            std :: initializer_list < __EnclosedType > const & aresSingle1Case3,
            std :: initializer_list < __EnclosedType > const & aresSingle1Case4,
            std :: initializer_list < __EnclosedType > const & aresSingle1RevCase1,
            std :: initializer_list < __EnclosedType > const & aresSingle1RevCase2,
            std :: initializer_list < __EnclosedType > const & aresSingle1RevCase3,
            std :: initializer_list < __EnclosedType > const & aresSingle1RevCase4,

            std :: initializer_list < __EnclosedType > const & aresSingle2Case1,
            std :: initializer_list < __EnclosedType > const & aresSingle2Case2,
            std :: initializer_list < __EnclosedType > const & aresSingle2Case3,
            std :: initializer_list < __EnclosedType > const & aresSingle2Case4,
            std :: initializer_list < __EnclosedType > const & aresSingle2RevCase1,
            std :: initializer_list < __EnclosedType > const & aresSingle2RevCase2,
            std :: initializer_list < __EnclosedType > const & aresSingle2RevCase3,
            std :: initializer_list < __EnclosedType > const & aresSingle2RevCase4,

            std :: initializer_list < __EnclosedType > const & aresSingle3Case1,
            std :: initializer_list < __EnclosedType > const & aresSingle3Case2,
            std :: initializer_list < __EnclosedType > const & aresSingle3Case3,
            std :: initializer_list < __EnclosedType > const & aresSingle3Case4,
            std :: initializer_list < __EnclosedType > const & aresSingle3RevCase1,
            std :: initializer_list < __EnclosedType > const & aresSingle3RevCase2,
            std :: initializer_list < __EnclosedType > const & aresSingle3RevCase3,
            std :: initializer_list < __EnclosedType > const & aresSingle3RevCase4,

            std :: initializer_list < __EnclosedType > const & aresMultiple1Case1,
            std :: initializer_list < __EnclosedType > const & aresMultiple1Case2,
            std :: initializer_list < __EnclosedType > const & aresMultiple1Case3,
            std :: initializer_list < __EnclosedType > const & aresMultiple1Case4,
            std :: initializer_list < __EnclosedType > const & aresMultiple1RevCase1,
            std :: initializer_list < __EnclosedType > const & aresMultiple1RevCase2,
            std :: initializer_list < __EnclosedType > const & aresMultiple1RevCase3,
            std :: initializer_list < __EnclosedType > const & aresMultiple1RevCase4,

            std :: initializer_list < __EnclosedType > const & aresMultiple2Case1,
            std :: initializer_list < __EnclosedType > const & aresMultiple2Case2,
            std :: initializer_list < __EnclosedType > const & aresMultiple2Case3,
            std :: initializer_list < __EnclosedType > const & aresMultiple2Case4,
            std :: initializer_list < __EnclosedType > const & aresMultiple2RevCase1,
            std :: initializer_list < __EnclosedType > const & aresMultiple2RevCase2,
            std :: initializer_list < __EnclosedType > const & aresMultiple2RevCase3,
            std :: initializer_list < __EnclosedType > const & aresMultiple2RevCase4,

            std :: initializer_list < __EnclosedType > const & aresMultiple3Case1,
            std :: initializer_list < __EnclosedType > const & aresMultiple3Case2,
            std :: initializer_list < __EnclosedType > const & aresMultiple3Case3,
            std :: initializer_list < __EnclosedType > const & aresMultiple3Case4,
            std :: initializer_list < __EnclosedType > const & aresMultiple3RevCase1,
            std :: initializer_list < __EnclosedType > const & aresMultiple3RevCase2,
            std :: initializer_list < __EnclosedType > const & aresMultiple3RevCase3,
            std :: initializer_list < __EnclosedType > const & aresMultiple3RevCase4,

            std :: initializer_list < __EnclosedType > const & aresMultipleVCase1,
            std :: initializer_list < __EnclosedType > const & aresMultipleVCase2,
            std :: initializer_list < __EnclosedType > const & aresMultipleVCase3,
            std :: initializer_list < __EnclosedType > const & aresMultipleVCase4,
            std :: initializer_list < __EnclosedType > const & aresMultipleVRevCase1,
            std :: initializer_list < __EnclosedType > const & aresMultipleVRevCase2,
            std :: initializer_list < __EnclosedType > const & aresMultipleVRevCase3,
            std :: initializer_list < __EnclosedType > const & aresMultipleVRevCase4,
            __Values const & ... values
    ) -> bool {

        __TestedType < __EnclosedType > underTest = initValues;
        List < __EnclosedType > & lref = underTest;

        bool status = true;
        cds::uint32 tNo = 401U;
        
        status = relIns::singleInsBefAll <__EnclosedType, __TestedType, relIns::BeginPfn<__EnclosedType>, false> (
                tNo, initValues, pTestLib, & List<__EnclosedType>::begin,
                {case1Offset, case2Offset, case3Offset, case4Offset },
                { singleValue1, singleValue2, singleValue3 },
                {
                        { true, true, true, false },
                        { true, true, true, false },
                        { true, true, true, false }
                }, {
                        { resSingle1Case1, resSingle1Case2, resSingle1Case3, resSingle1Case4 },
                        { resSingle2Case1, resSingle2Case2, resSingle2Case3, resSingle2Case4 },
                        { resSingle3Case1, resSingle3Case2, resSingle3Case3, resSingle3Case4 }
                }
        );
        
        status = status && relIns::singleInsBefAll <__EnclosedType, __TestedType, relIns::RBeginPfn<__EnclosedType>, true> (
                tNo, initValues, pTestLib, & List<__EnclosedType>::rbegin,
                {case1Offset, case2Offset, case3Offset, case4Offset },
                { singleValue1, singleValue2, singleValue3 },
                {
                        { true, true, true, false },
                        { true, true, true, false },
                        { true, true, true, false }
                }, {
                        { resSingle1RevCase1, resSingle1RevCase2, resSingle1RevCase3, resSingle1RevCase4 },
                        { resSingle2RevCase1, resSingle2RevCase2, resSingle2RevCase3, resSingle2RevCase4 },
                        { resSingle3RevCase1, resSingle3RevCase2, resSingle3RevCase3, resSingle3RevCase4 }
                }
        );
        
        status = status && relIns::singleInsBefAll <__EnclosedType, __TestedType, relIns::CBeginPfn<__EnclosedType>, false> (
                tNo, initValues, pTestLib, & List<__EnclosedType>::cbegin,
                {case1Offset, case2Offset, case3Offset, case4Offset },
                { singleValue1, singleValue2, singleValue3 },
                {
                        { true, true, true, false },
                        { true, true, true, false },
                        { true, true, true, false }
                }, {
                        { resSingle1Case1, resSingle1Case2, resSingle1Case3, resSingle1Case4 },
                        { resSingle2Case1, resSingle2Case2, resSingle2Case3, resSingle2Case4 },
                        { resSingle3Case1, resSingle3Case2, resSingle3Case3, resSingle3Case4 }
                }
        );
        
        status = status && relIns::singleInsBefAll <__EnclosedType, __TestedType, relIns::CRBeginPfn<__EnclosedType>, true> (
                tNo, initValues, pTestLib, & List<__EnclosedType>::crbegin,
                {case1Offset, case2Offset, case3Offset, case4Offset },
                { singleValue1, singleValue2, singleValue3 },
                {
                        { true, true, true, false },
                        { true, true, true, false },
                        { true, true, true, false }
                }, {
                        { resSingle1RevCase1, resSingle1RevCase2, resSingle1RevCase3, resSingle1RevCase4 },
                        { resSingle2RevCase1, resSingle2RevCase2, resSingle2RevCase3, resSingle2RevCase4 },
                        { resSingle3RevCase1, resSingle3RevCase2, resSingle3RevCase3, resSingle3RevCase4 }
                }
        );
        
        status = status && relIns::singleInsAftAll <__EnclosedType, __TestedType, relIns::BeginPfn<__EnclosedType>, false> (
                tNo, initValues, pTestLib, & List<__EnclosedType>::begin,
                {case1Offset, case2Offset, case3Offset, case4Offset },
                { singleValue1, singleValue2, singleValue3 },
                {
                        { true, true, true, false },
                        { true, true, true, false },
                        { true, true, true, false }
                }, {
                        { aresSingle1Case1, aresSingle1Case2, aresSingle1Case3, aresSingle1Case4 },
                        { aresSingle2Case1, aresSingle2Case2, aresSingle2Case3, aresSingle2Case4 },
                        { aresSingle3Case1, aresSingle3Case2, aresSingle3Case3, aresSingle3Case4 }
                }
        );
        
        status = status && relIns::singleInsAftAll <__EnclosedType, __TestedType, relIns::RBeginPfn<__EnclosedType>, true> (
                tNo, initValues, pTestLib, & List<__EnclosedType>::rbegin,
                {case1Offset, case2Offset, case3Offset, case4Offset },
                { singleValue1, singleValue2, singleValue3 },
                {
                        { true, true, true, false },
                        { true, true, true, false },
                        { true, true, true, false }
                }, {
                        { aresSingle1RevCase1, aresSingle1RevCase2, aresSingle1RevCase3, aresSingle1RevCase4 },
                        { aresSingle2RevCase1, aresSingle2RevCase2, aresSingle2RevCase3, aresSingle2RevCase4 },
                        { aresSingle3RevCase1, aresSingle3RevCase2, aresSingle3RevCase3, aresSingle3RevCase4 }
                }
        );
        
        status = status && relIns::singleInsAftAll <__EnclosedType, __TestedType, relIns::CBeginPfn<__EnclosedType>, false> (
                tNo, initValues, pTestLib, & List<__EnclosedType>::cbegin,
                {case1Offset, case2Offset, case3Offset, case4Offset },
                { singleValue1, singleValue2, singleValue3 },
                {
                        { true, true, true, false },
                        { true, true, true, false },
                        { true, true, true, false }
                }, {
                        { aresSingle1Case1, aresSingle1Case2, aresSingle1Case3, aresSingle1Case4 },
                        { aresSingle2Case1, aresSingle2Case2, aresSingle2Case3, aresSingle2Case4 },
                        { aresSingle3Case1, aresSingle3Case2, aresSingle3Case3, aresSingle3Case4 }
                }
        );
        
        status = status && relIns::singleInsAftAll <__EnclosedType, __TestedType, relIns::CRBeginPfn<__EnclosedType>, true> (
                tNo, initValues, pTestLib, & List<__EnclosedType>::crbegin,
                {case1Offset, case2Offset, case3Offset, case4Offset },
                { singleValue1, singleValue2, singleValue3 },
                {
                        { true, true, true, false },
                        { true, true, true, false },
                        { true, true, true, false }
                }, {
                        { aresSingle1RevCase1, aresSingle1RevCase2, aresSingle1RevCase3, aresSingle1RevCase4 },
                        { aresSingle2RevCase1, aresSingle2RevCase2, aresSingle2RevCase3, aresSingle2RevCase4 },
                        { aresSingle3RevCase1, aresSingle3RevCase2, aresSingle3RevCase3, aresSingle3RevCase4 }
                }
        );
        
        status = status && relIns::mulInsBefAll <__EnclosedType, __TestedType, relIns::BeginPfn<__EnclosedType>, false> (
                tNo, initValues, pTestLib, & List<__EnclosedType>::begin,
                {case1Offset, case2Offset, case3Offset, case4Offset },
                { {multipleValues1}, {multipleValues2}, {multipleValues3} },
                {
                        { true, true, true, false },
                        { true, true, true, false },
                        { true, true, true, false }
                }, {
                        { resMultiple1Case1, resMultiple1Case2, resMultiple1Case3, resMultiple1Case4 },
                        { resMultiple2Case1, resMultiple2Case2, resMultiple2Case3, resMultiple2Case4 },
                        { resMultiple3Case1, resMultiple3Case2, resMultiple3Case3, resMultiple3Case4 },
                }
        );
        
        status = status && relIns::mulInsBefAll <__EnclosedType, __TestedType, relIns::RBeginPfn<__EnclosedType>, true> (
                tNo, initValues, pTestLib, & List<__EnclosedType>::rbegin,
                {case1Offset, case2Offset, case3Offset, case4Offset },
                { {multipleValues1}, {multipleValues2}, {multipleValues3} },
                {
                        { true, true, true, false },
                        { true, true, true, false },
                        { true, true, true, false }
                }, {
                        { resMultiple1RevCase1, resMultiple1RevCase2, resMultiple1RevCase3, resMultiple1RevCase4 },
                        { resMultiple2RevCase1, resMultiple2RevCase2, resMultiple2RevCase3, resMultiple2RevCase4 },
                        { resMultiple3RevCase1, resMultiple3RevCase2, resMultiple3RevCase3, resMultiple3RevCase4 },
                }
        );
        
        status = status && relIns::mulInsBefAll <__EnclosedType, __TestedType, relIns::CBeginPfn<__EnclosedType>, false> (
                tNo, initValues, pTestLib, & List<__EnclosedType>::cbegin,
                {case1Offset, case2Offset, case3Offset, case4Offset },
                { {multipleValues1}, {multipleValues2}, {multipleValues3} },
                {
                        { true, true, true, false },
                        { true, true, true, false },
                        { true, true, true, false }
                }, {
                        { resMultiple1Case1, resMultiple1Case2, resMultiple1Case3, resMultiple1Case4 },
                        { resMultiple2Case1, resMultiple2Case2, resMultiple2Case3, resMultiple2Case4 },
                        { resMultiple3Case1, resMultiple3Case2, resMultiple3Case3, resMultiple3Case4 },
                }
        );
        
        status = status && relIns::mulInsBefAll <__EnclosedType, __TestedType, relIns::CRBeginPfn<__EnclosedType>, true> (
                tNo, initValues, pTestLib, & List<__EnclosedType>::crbegin,
                {case1Offset, case2Offset, case3Offset, case4Offset },
                { {multipleValues1}, {multipleValues2}, {multipleValues3} },
                {
                        { true, true, true, false },
                        { true, true, true, false },
                        { true, true, true, false }
                }, {
                        { resMultiple1RevCase1, resMultiple1RevCase2, resMultiple1RevCase3, resMultiple1RevCase4 },
                        { resMultiple2RevCase1, resMultiple2RevCase2, resMultiple2RevCase3, resMultiple2RevCase4 },
                        { resMultiple3RevCase1, resMultiple3RevCase2, resMultiple3RevCase3, resMultiple3RevCase4 },
                }
        );
        
        status = status && relIns::mulInsAftAll <__EnclosedType, __TestedType, relIns::BeginPfn<__EnclosedType>, false> (
                tNo, initValues, pTestLib, & List<__EnclosedType>::begin,
                {case1Offset, case2Offset, case3Offset, case4Offset },
                { {multipleValues1}, {multipleValues2}, {multipleValues3} },
                {
                        { true, true, true, false },
                        { true, true, true, false },
                        { true, true, true, false }
                }, {
                        { aresMultiple1Case1, aresMultiple1Case2, aresMultiple1Case3, aresMultiple1Case4 },
                        { aresMultiple2Case1, aresMultiple2Case2, aresMultiple2Case3, aresMultiple2Case4 },
                        { aresMultiple3Case1, aresMultiple3Case2, aresMultiple3Case3, aresMultiple3Case4 },
                }
        );
        
        status = status && relIns::mulInsAftAll <__EnclosedType, __TestedType, relIns::RBeginPfn<__EnclosedType>, true> (
                tNo, initValues, pTestLib, & List<__EnclosedType>::rbegin,
                {case1Offset, case2Offset, case3Offset, case4Offset },
                { {multipleValues1}, {multipleValues2}, {multipleValues3} },
                {
                        { true, true, true, false },
                        { true, true, true, false },
                        { true, true, true, false }
                }, {
                        { aresMultiple1RevCase1, aresMultiple1RevCase2, aresMultiple1RevCase3, aresMultiple1RevCase4 },
                        { aresMultiple2RevCase1, aresMultiple2RevCase2, aresMultiple2RevCase3, aresMultiple2RevCase4 },
                        { aresMultiple3RevCase1, aresMultiple3RevCase2, aresMultiple3RevCase3, aresMultiple3RevCase4 },
                }
        );
        
        status = status && relIns::mulInsAftAll <__EnclosedType, __TestedType, relIns::CBeginPfn<__EnclosedType>, false> (
                tNo, initValues, pTestLib, & List<__EnclosedType>::cbegin,
                {case1Offset, case2Offset, case3Offset, case4Offset },
                { {multipleValues1}, {multipleValues2}, {multipleValues3} },
                {
                        { true, true, true, false },
                        { true, true, true, false },
                        { true, true, true, false }
                }, {
                        { aresMultiple1Case1, aresMultiple1Case2, aresMultiple1Case3, aresMultiple1Case4 },
                        { aresMultiple2Case1, aresMultiple2Case2, aresMultiple2Case3, aresMultiple2Case4 },
                        { aresMultiple3Case1, aresMultiple3Case2, aresMultiple3Case3, aresMultiple3Case4 },
                }
        );
        
        status = status && relIns::mulInsAftAll <__EnclosedType, __TestedType, relIns::CRBeginPfn<__EnclosedType>, true> (
                tNo, initValues, pTestLib, & List<__EnclosedType>::crbegin,
                {case1Offset, case2Offset, case3Offset, case4Offset },
                { {multipleValues1}, {multipleValues2}, {multipleValues3} },
                {
                        { true, true, true, false },
                        { true, true, true, false },
                        { true, true, true, false }
                }, {
                        { aresMultiple1RevCase1, aresMultiple1RevCase2, aresMultiple1RevCase3, aresMultiple1RevCase4 },
                        { aresMultiple2RevCase1, aresMultiple2RevCase2, aresMultiple2RevCase3, aresMultiple2RevCase4 },
                        { aresMultiple3RevCase1, aresMultiple3RevCase2, aresMultiple3RevCase3, aresMultiple3RevCase4 },
                }
        );
        
        status = status && relIns::packInsBefAll <__EnclosedType, __TestedType, relIns::BeginPfn<__EnclosedType>, false> (
                tNo, initValues, pTestLib, & List<__EnclosedType>::begin,
                {case1Offset, case2Offset, case3Offset, case4Offset },
                {true, true, true, false}, 
                {resMultipleVCase1, resMultipleVCase2, resMultipleVCase3, resMultipleVCase4},
                values ...
        );
        
        status = status && relIns::packInsBefAll <__EnclosedType, __TestedType, relIns::RBeginPfn<__EnclosedType>, true> (
                tNo, initValues, pTestLib, & List<__EnclosedType>::rbegin,
                {case1Offset, case2Offset, case3Offset, case4Offset },
                {true, true, true, false}, 
                {resMultipleVRevCase1, resMultipleVRevCase2, resMultipleVRevCase3, resMultipleVRevCase4},
                values ...
        );
        
        status = status && relIns::packInsBefAll <__EnclosedType, __TestedType, relIns::CBeginPfn<__EnclosedType>, false> (
                tNo, initValues, pTestLib, & List<__EnclosedType>::cbegin,
                {case1Offset, case2Offset, case3Offset, case4Offset },
                {true, true, true, false}, 
                {resMultipleVCase1, resMultipleVCase2, resMultipleVCase3, resMultipleVCase4},
                values ...
        );
        
        status = status && relIns::packInsBefAll <__EnclosedType, __TestedType, relIns::CRBeginPfn<__EnclosedType>, true> (
                tNo, initValues, pTestLib, & List<__EnclosedType>::crbegin,
                {case1Offset, case2Offset, case3Offset, case4Offset },
                {true, true, true, false}, 
                {resMultipleVRevCase1, resMultipleVRevCase2, resMultipleVRevCase3, resMultipleVRevCase4},
                values ...
        );
        
        status = status && relIns::packInsAftAll <__EnclosedType, __TestedType, relIns::BeginPfn<__EnclosedType>, false> (
                tNo, initValues, pTestLib, & List<__EnclosedType>::begin,
                {case1Offset, case2Offset, case3Offset, case4Offset },
                {true, true, true, false}, 
                {aresMultipleVCase1, aresMultipleVCase2, aresMultipleVCase3, aresMultipleVCase4},
                values ...
        );
        
        status = status && relIns::packInsAftAll <__EnclosedType, __TestedType, relIns::RBeginPfn<__EnclosedType>, true> (
                tNo, initValues, pTestLib, & List<__EnclosedType>::rbegin,
                {case1Offset, case2Offset, case3Offset, case4Offset },
                {true, true, true, false}, 
                {aresMultipleVRevCase1, aresMultipleVRevCase2, aresMultipleVRevCase3, aresMultipleVRevCase4},
                values ...
        );
        
        status = status && relIns::packInsAftAll <__EnclosedType, __TestedType, relIns::CBeginPfn<__EnclosedType>, false> (
                tNo, initValues, pTestLib, & List<__EnclosedType>::cbegin,
                {case1Offset, case2Offset, case3Offset, case4Offset },
                {true, true, true, false}, 
                {aresMultipleVCase1, aresMultipleVCase2, aresMultipleVCase3, aresMultipleVCase4},
                values ...
        );
        
        status = status && relIns::packInsAftAll <__EnclosedType, __TestedType, relIns::CRBeginPfn<__EnclosedType>, true> (
                tNo, initValues, pTestLib, & List<__EnclosedType>::crbegin,
                {case1Offset, case2Offset, case3Offset, case4Offset },
                {true, true, true, false}, 
                {aresMultipleVRevCase1, aresMultipleVRevCase2, aresMultipleVRevCase3, aresMultipleVRevCase4},
                values ...
        );

        return status;
    }
}

auto ListTest::tests_00400_00599 () noexcept -> bool {

    bool allOk = true;

    this->executeSubtest ( "ListTestGroup-RelativeInsertion-" __CDS_cpplang_core_version_name " : LTG-00400-RI-" __CDS_cpplang_core_version_name " : IntArray", [this, & allOk] {

        allOk = allOk && listTestGroupRelativeInsertion <
                Array,
                int
        > (
                this,
                { 1, 2, 3, 4, 5 },
                & List < int > :: begin,
                & List < int > :: end,
                & List < int > :: cbegin,
                & List < int > :: cend,
                & List < int > :: rbegin,
                & List < int > :: rend,
                & List < int > :: crbegin,
                & List < int > :: crend,
                0,
                2,
                4,
                6,
                7, 9, 20,
                { 1, 2, 3 }, { 20, 30, 40 }, { 100, 200, 300 },

                { 7, 1, 2, 3, 4, 5 },
                { 1, 2, 7, 3, 4, 5 },
                { 1, 2, 3, 4, 7, 5 },
                { 1, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 5, 7 },
                { 1, 2, 3, 7, 4, 5 },
                { 1, 7, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 5 },

                { 9, 1, 2, 3, 4, 5 },
                { 1, 2, 9, 3, 4, 5 },
                { 1, 2, 3, 4, 9, 5 },
                { 1, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 5, 9 },
                { 1, 2, 3, 9, 4, 5 },
                { 1, 9, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 5 },

                { 20, 1, 2, 3, 4, 5 },
                { 1, 2, 20, 3, 4, 5 },
                { 1, 2, 3, 4, 20, 5 },
                { 1, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 5, 20 },
                { 1, 2, 3, 20, 4, 5 },
                { 1, 20, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 5 },

                { 1, 2, 3, 1, 2, 3, 4, 5 },
                { 1, 2, 1, 2, 3, 3, 4, 5 },
                { 1, 2, 3, 4, 1, 2, 3, 5 },
                { 1, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 5, 1, 2, 3 },
                { 1, 2, 3, 1, 2, 3, 4, 5 },
                { 1, 1, 2, 3, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 5 },

                { 20, 30, 40, 1, 2, 3, 4, 5 },
                { 1, 2, 20, 30, 40, 3, 4, 5 },
                { 1, 2, 3, 4, 20, 30, 40, 5 },
                { 1, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 5, 20, 30, 40 },
                { 1, 2, 3, 20, 30, 40, 4, 5 },
                { 1, 20, 30, 40, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 5 },

                { 100, 200, 300, 1, 2, 3, 4, 5 },
                { 1, 2, 100, 200, 300, 3, 4, 5 },
                { 1, 2, 3, 4, 100, 200, 300, 5 },
                { 1, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 5, 100, 200, 300 },
                { 1, 2, 3, 100, 200, 300, 4, 5 },
                { 1, 100, 200, 300, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 5 },

                { 1000, 2000, 3000, 4000, 1, 2, 3, 4, 5 },
                { 1, 2, 1000, 2000, 3000, 4000, 3, 4, 5 },
                { 1, 2, 3, 4, 1000, 2000, 3000, 4000, 5 },
                { 1, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 5, 1000, 2000, 3000, 4000 },
                { 1, 2, 3, 1000, 2000, 3000, 4000, 4, 5 },
                { 1, 1000, 2000, 3000, 4000, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 5 },

                { 1, 7, 2, 3, 4, 5 },
                { 1, 2, 3, 7, 4, 5 },
                { 1, 2, 3, 4, 5, 7 },
                { 1, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 7, 5 },
                { 1, 2, 7, 3, 4, 5 },
                { 7, 1, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 5 },

                { 1, 9, 2, 3, 4, 5 },
                { 1, 2, 3, 9, 4, 5 },
                { 1, 2, 3, 4, 5, 9 },
                { 1, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 9, 5 },
                { 1, 2, 9, 3, 4, 5 },
                { 9, 1, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 5 },

                { 1, 20, 2, 3, 4, 5 },
                { 1, 2, 3, 20, 4, 5 },
                { 1, 2, 3, 4, 5, 20 },
                { 1, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 20, 5 },
                { 1, 2, 20, 3, 4, 5 },
                { 20, 1, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 5 },

                { 1, 1, 2, 3, 2, 3, 4, 5 },
                { 1, 2, 3, 1, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 5, 1, 2, 3 },
                { 1, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 1, 2, 3, 5 },
                { 1, 2, 1, 2, 3, 3, 4, 5 },
                { 1, 2, 3, 1, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 5 },

                { 1, 20, 30, 40, 2, 3, 4, 5 },
                { 1, 2, 3, 20, 30, 40, 4, 5 },
                { 1, 2, 3, 4, 5, 20, 30, 40 },
                { 1, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 20, 30, 40, 5 },
                { 1, 2, 20, 30, 40, 3, 4, 5 },
                { 20, 30, 40, 1, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 5 },

                { 1, 100, 200, 300, 2, 3, 4, 5 },
                { 1, 2, 3, 100, 200, 300, 4, 5 },
                { 1, 2, 3, 4, 5, 100, 200, 300 },
                { 1, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 100, 200, 300, 5 },
                { 1, 2, 100, 200, 300, 3, 4, 5 },
                { 100, 200, 300, 1, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 5 },

                { 1, 1000, 2000, 3000, 4000, 2, 3, 4, 5 },
                { 1, 2, 3, 1000, 2000, 3000, 4000, 4, 5 },
                { 1, 2, 3, 4, 5, 1000, 2000, 3000, 4000 },
                { 1, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 1000, 2000, 3000, 4000, 5 },
                { 1, 2, 1000, 2000, 3000, 4000, 3, 4, 5 },
                { 1000, 2000, 3000, 4000, 1, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 5 },

                1000, 2000, 3000, 4000
        );
    });
    this->executeSubtest ( "ListTestGroup-RelativeInsertion-" __CDS_cpplang_core_version_name " : LTG-00400-RI-" __CDS_cpplang_core_version_name " : IntLinkedList", [this, & allOk] {

        allOk = allOk && listTestGroupRelativeInsertion <
                LinkedList,
                int
        > (
                this,
                { 1, 2, 3, 4, 5 },
                & List < int > :: begin,
                & List < int > :: end,
                & List < int > :: cbegin,
                & List < int > :: cend,
                & List < int > :: rbegin,
                & List < int > :: rend,
                & List < int > :: crbegin,
                & List < int > :: crend,
                0,
                2,
                4,
                6,
                7, 9, 20,
                { 1, 2, 3 }, { 20, 30, 40 }, { 100, 200, 300 },

                { 7, 1, 2, 3, 4, 5 },
                { 1, 2, 7, 3, 4, 5 },
                { 1, 2, 3, 4, 7, 5 },
                { 1, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 5, 7 },
                { 1, 2, 3, 7, 4, 5 },
                { 1, 7, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 5 },

                { 9, 1, 2, 3, 4, 5 },
                { 1, 2, 9, 3, 4, 5 },
                { 1, 2, 3, 4, 9, 5 },
                { 1, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 5, 9 },
                { 1, 2, 3, 9, 4, 5 },
                { 1, 9, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 5 },

                { 20, 1, 2, 3, 4, 5 },
                { 1, 2, 20, 3, 4, 5 },
                { 1, 2, 3, 4, 20, 5 },
                { 1, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 5, 20 },
                { 1, 2, 3, 20, 4, 5 },
                { 1, 20, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 5 },

                { 1, 2, 3, 1, 2, 3, 4, 5 },
                { 1, 2, 1, 2, 3, 3, 4, 5 },
                { 1, 2, 3, 4, 1, 2, 3, 5 },
                { 1, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 5, 1, 2, 3 },
                { 1, 2, 3, 1, 2, 3, 4, 5 },
                { 1, 1, 2, 3, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 5 },

                { 20, 30, 40, 1, 2, 3, 4, 5 },
                { 1, 2, 20, 30, 40, 3, 4, 5 },
                { 1, 2, 3, 4, 20, 30, 40, 5 },
                { 1, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 5, 20, 30, 40 },
                { 1, 2, 3, 20, 30, 40, 4, 5 },
                { 1, 20, 30, 40, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 5 },

                { 100, 200, 300, 1, 2, 3, 4, 5 },
                { 1, 2, 100, 200, 300, 3, 4, 5 },
                { 1, 2, 3, 4, 100, 200, 300, 5 },
                { 1, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 5, 100, 200, 300 },
                { 1, 2, 3, 100, 200, 300, 4, 5 },
                { 1, 100, 200, 300, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 5 },

                { 1000, 2000, 3000, 4000, 1, 2, 3, 4, 5 },
                { 1, 2, 1000, 2000, 3000, 4000, 3, 4, 5 },
                { 1, 2, 3, 4, 1000, 2000, 3000, 4000, 5 },
                { 1, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 5, 1000, 2000, 3000, 4000 },
                { 1, 2, 3, 1000, 2000, 3000, 4000, 4, 5 },
                { 1, 1000, 2000, 3000, 4000, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 5 },

                { 1, 7, 2, 3, 4, 5 },
                { 1, 2, 3, 7, 4, 5 },
                { 1, 2, 3, 4, 5, 7 },
                { 1, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 7, 5 },
                { 1, 2, 7, 3, 4, 5 },
                { 7, 1, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 5 },

                { 1, 9, 2, 3, 4, 5 },
                { 1, 2, 3, 9, 4, 5 },
                { 1, 2, 3, 4, 5, 9 },
                { 1, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 9, 5 },
                { 1, 2, 9, 3, 4, 5 },
                { 9, 1, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 5 },

                { 1, 20, 2, 3, 4, 5 },
                { 1, 2, 3, 20, 4, 5 },
                { 1, 2, 3, 4, 5, 20 },
                { 1, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 20, 5 },
                { 1, 2, 20, 3, 4, 5 },
                { 20, 1, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 5 },

                { 1, 1, 2, 3, 2, 3, 4, 5 },
                { 1, 2, 3, 1, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 5, 1, 2, 3 },
                { 1, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 1, 2, 3, 5 },
                { 1, 2, 1, 2, 3, 3, 4, 5 },
                { 1, 2, 3, 1, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 5 },

                { 1, 20, 30, 40, 2, 3, 4, 5 },
                { 1, 2, 3, 20, 30, 40, 4, 5 },
                { 1, 2, 3, 4, 5, 20, 30, 40 },
                { 1, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 20, 30, 40, 5 },
                { 1, 2, 20, 30, 40, 3, 4, 5 },
                { 20, 30, 40, 1, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 5 },

                { 1, 100, 200, 300, 2, 3, 4, 5 },
                { 1, 2, 3, 100, 200, 300, 4, 5 },
                { 1, 2, 3, 4, 5, 100, 200, 300 },
                { 1, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 100, 200, 300, 5 },
                { 1, 2, 100, 200, 300, 3, 4, 5 },
                { 100, 200, 300, 1, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 5 },

                { 1, 1000, 2000, 3000, 4000, 2, 3, 4, 5 },
                { 1, 2, 3, 1000, 2000, 3000, 4000, 4, 5 },
                { 1, 2, 3, 4, 5, 1000, 2000, 3000, 4000 },
                { 1, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 1000, 2000, 3000, 4000, 5 },
                { 1, 2, 1000, 2000, 3000, 4000, 3, 4, 5 },
                { 1000, 2000, 3000, 4000, 1, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 5 },

                1000, 2000, 3000, 4000
        );
    });
    this->executeSubtest ( "ListTestGroup-RelativeInsertion-" __CDS_cpplang_core_version_name " : LTG-00400-RI-" __CDS_cpplang_core_version_name " : StringArray", [this, & allOk] {

        allOk = allOk && listTestGroupRelativeInsertion <
                Array,
                String
        > (
                this,
                { 1, 2, 3, 4, 5 },
                & List < String > :: begin,
                & List < String > :: end,
                & List < String > :: cbegin,
                & List < String > :: cend,
                & List < String > :: rbegin,
                & List < String > :: rend,
                & List < String > :: crbegin,
                & List < String > :: crend,
                0,
                2,
                4,
                6,
                7, 9, 20,
                { 1, 2, 3 }, { 20, 30, 40 }, { 100, 200, 300 },

                { 7, 1, 2, 3, 4, 5 },
                { 1, 2, 7, 3, 4, 5 },
                { 1, 2, 3, 4, 7, 5 },
                { 1, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 5, 7 },
                { 1, 2, 3, 7, 4, 5 },
                { 1, 7, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 5 },

                { 9, 1, 2, 3, 4, 5 },
                { 1, 2, 9, 3, 4, 5 },
                { 1, 2, 3, 4, 9, 5 },
                { 1, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 5, 9 },
                { 1, 2, 3, 9, 4, 5 },
                { 1, 9, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 5 },

                { 20, 1, 2, 3, 4, 5 },
                { 1, 2, 20, 3, 4, 5 },
                { 1, 2, 3, 4, 20, 5 },
                { 1, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 5, 20 },
                { 1, 2, 3, 20, 4, 5 },
                { 1, 20, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 5 },

                { 1, 2, 3, 1, 2, 3, 4, 5 },
                { 1, 2, 1, 2, 3, 3, 4, 5 },
                { 1, 2, 3, 4, 1, 2, 3, 5 },
                { 1, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 5, 1, 2, 3 },
                { 1, 2, 3, 1, 2, 3, 4, 5 },
                { 1, 1, 2, 3, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 5 },

                { 20, 30, 40, 1, 2, 3, 4, 5 },
                { 1, 2, 20, 30, 40, 3, 4, 5 },
                { 1, 2, 3, 4, 20, 30, 40, 5 },
                { 1, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 5, 20, 30, 40 },
                { 1, 2, 3, 20, 30, 40, 4, 5 },
                { 1, 20, 30, 40, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 5 },

                { 100, 200, 300, 1, 2, 3, 4, 5 },
                { 1, 2, 100, 200, 300, 3, 4, 5 },
                { 1, 2, 3, 4, 100, 200, 300, 5 },
                { 1, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 5, 100, 200, 300 },
                { 1, 2, 3, 100, 200, 300, 4, 5 },
                { 1, 100, 200, 300, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 5 },

                { 1000, 2000, 3000, 4000, 1, 2, 3, 4, 5 },
                { 1, 2, 1000, 2000, 3000, 4000, 3, 4, 5 },
                { 1, 2, 3, 4, 1000, 2000, 3000, 4000, 5 },
                { 1, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 5, 1000, 2000, 3000, 4000 },
                { 1, 2, 3, 1000, 2000, 3000, 4000, 4, 5 },
                { 1, 1000, 2000, 3000, 4000, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 5 },

                { 1, 7, 2, 3, 4, 5 },
                { 1, 2, 3, 7, 4, 5 },
                { 1, 2, 3, 4, 5, 7 },
                { 1, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 7, 5 },
                { 1, 2, 7, 3, 4, 5 },
                { 7, 1, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 5 },

                { 1, 9, 2, 3, 4, 5 },
                { 1, 2, 3, 9, 4, 5 },
                { 1, 2, 3, 4, 5, 9 },
                { 1, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 9, 5 },
                { 1, 2, 9, 3, 4, 5 },
                { 9, 1, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 5 },

                { 1, 20, 2, 3, 4, 5 },
                { 1, 2, 3, 20, 4, 5 },
                { 1, 2, 3, 4, 5, 20 },
                { 1, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 20, 5 },
                { 1, 2, 20, 3, 4, 5 },
                { 20, 1, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 5 },

                { 1, 1, 2, 3, 2, 3, 4, 5 },
                { 1, 2, 3, 1, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 5, 1, 2, 3 },
                { 1, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 1, 2, 3, 5 },
                { 1, 2, 1, 2, 3, 3, 4, 5 },
                { 1, 2, 3, 1, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 5 },

                { 1, 20, 30, 40, 2, 3, 4, 5 },
                { 1, 2, 3, 20, 30, 40, 4, 5 },
                { 1, 2, 3, 4, 5, 20, 30, 40 },
                { 1, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 20, 30, 40, 5 },
                { 1, 2, 20, 30, 40, 3, 4, 5 },
                { 20, 30, 40, 1, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 5 },

                { 1, 100, 200, 300, 2, 3, 4, 5 },
                { 1, 2, 3, 100, 200, 300, 4, 5 },
                { 1, 2, 3, 4, 5, 100, 200, 300 },
                { 1, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 100, 200, 300, 5 },
                { 1, 2, 100, 200, 300, 3, 4, 5 },
                { 100, 200, 300, 1, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 5 },

                { 1, 1000, 2000, 3000, 4000, 2, 3, 4, 5 },
                { 1, 2, 3, 1000, 2000, 3000, 4000, 4, 5 },
                { 1, 2, 3, 4, 5, 1000, 2000, 3000, 4000 },
                { 1, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 1000, 2000, 3000, 4000, 5 },
                { 1, 2, 1000, 2000, 3000, 4000, 3, 4, 5 },
                { 1000, 2000, 3000, 4000, 1, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 5 },

                1000, 2000, 3000, 4000
        );
    });
    this->executeSubtest ( "ListTestGroup-RelativeInsertion-" __CDS_cpplang_core_version_name " : LTG-00400-RI-" __CDS_cpplang_core_version_name " : StringLinkedList", [this, & allOk] {

        allOk = allOk && listTestGroupRelativeInsertion <
                LinkedList,
                String
        > (
                this,
                { 1, 2, 3, 4, 5 },
                & List < String > :: begin,
                & List < String > :: end,
                & List < String > :: cbegin,
                & List < String > :: cend,
                & List < String > :: rbegin,
                & List < String > :: rend,
                & List < String > :: crbegin,
                & List < String > :: crend,
                0,
                2,
                4,
                6,
                7, 9, 20,
                { 1, 2, 3 }, { 20, 30, 40 }, { 100, 200, 300 },

                { 7, 1, 2, 3, 4, 5 },
                { 1, 2, 7, 3, 4, 5 },
                { 1, 2, 3, 4, 7, 5 },
                { 1, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 5, 7 },
                { 1, 2, 3, 7, 4, 5 },
                { 1, 7, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 5 },

                { 9, 1, 2, 3, 4, 5 },
                { 1, 2, 9, 3, 4, 5 },
                { 1, 2, 3, 4, 9, 5 },
                { 1, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 5, 9 },
                { 1, 2, 3, 9, 4, 5 },
                { 1, 9, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 5 },

                { 20, 1, 2, 3, 4, 5 },
                { 1, 2, 20, 3, 4, 5 },
                { 1, 2, 3, 4, 20, 5 },
                { 1, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 5, 20 },
                { 1, 2, 3, 20, 4, 5 },
                { 1, 20, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 5 },

                { 1, 2, 3, 1, 2, 3, 4, 5 },
                { 1, 2, 1, 2, 3, 3, 4, 5 },
                { 1, 2, 3, 4, 1, 2, 3, 5 },
                { 1, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 5, 1, 2, 3 },
                { 1, 2, 3, 1, 2, 3, 4, 5 },
                { 1, 1, 2, 3, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 5 },

                { 20, 30, 40, 1, 2, 3, 4, 5 },
                { 1, 2, 20, 30, 40, 3, 4, 5 },
                { 1, 2, 3, 4, 20, 30, 40, 5 },
                { 1, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 5, 20, 30, 40 },
                { 1, 2, 3, 20, 30, 40, 4, 5 },
                { 1, 20, 30, 40, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 5 },

                { 100, 200, 300, 1, 2, 3, 4, 5 },
                { 1, 2, 100, 200, 300, 3, 4, 5 },
                { 1, 2, 3, 4, 100, 200, 300, 5 },
                { 1, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 5, 100, 200, 300 },
                { 1, 2, 3, 100, 200, 300, 4, 5 },
                { 1, 100, 200, 300, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 5 },

                { 1000, 2000, 3000, 4000, 1, 2, 3, 4, 5 },
                { 1, 2, 1000, 2000, 3000, 4000, 3, 4, 5 },
                { 1, 2, 3, 4, 1000, 2000, 3000, 4000, 5 },
                { 1, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 5, 1000, 2000, 3000, 4000 },
                { 1, 2, 3, 1000, 2000, 3000, 4000, 4, 5 },
                { 1, 1000, 2000, 3000, 4000, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 5 },

                { 1, 7, 2, 3, 4, 5 },
                { 1, 2, 3, 7, 4, 5 },
                { 1, 2, 3, 4, 5, 7 },
                { 1, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 7, 5 },
                { 1, 2, 7, 3, 4, 5 },
                { 7, 1, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 5 },

                { 1, 9, 2, 3, 4, 5 },
                { 1, 2, 3, 9, 4, 5 },
                { 1, 2, 3, 4, 5, 9 },
                { 1, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 9, 5 },
                { 1, 2, 9, 3, 4, 5 },
                { 9, 1, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 5 },

                { 1, 20, 2, 3, 4, 5 },
                { 1, 2, 3, 20, 4, 5 },
                { 1, 2, 3, 4, 5, 20 },
                { 1, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 20, 5 },
                { 1, 2, 20, 3, 4, 5 },
                { 20, 1, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 5 },

                { 1, 1, 2, 3, 2, 3, 4, 5 },
                { 1, 2, 3, 1, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 5, 1, 2, 3 },
                { 1, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 1, 2, 3, 5 },
                { 1, 2, 1, 2, 3, 3, 4, 5 },
                { 1, 2, 3, 1, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 5 },

                { 1, 20, 30, 40, 2, 3, 4, 5 },
                { 1, 2, 3, 20, 30, 40, 4, 5 },
                { 1, 2, 3, 4, 5, 20, 30, 40 },
                { 1, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 20, 30, 40, 5 },
                { 1, 2, 20, 30, 40, 3, 4, 5 },
                { 20, 30, 40, 1, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 5 },

                { 1, 100, 200, 300, 2, 3, 4, 5 },
                { 1, 2, 3, 100, 200, 300, 4, 5 },
                { 1, 2, 3, 4, 5, 100, 200, 300 },
                { 1, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 100, 200, 300, 5 },
                { 1, 2, 100, 200, 300, 3, 4, 5 },
                { 100, 200, 300, 1, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 5 },

                { 1, 1000, 2000, 3000, 4000, 2, 3, 4, 5 },
                { 1, 2, 3, 1000, 2000, 3000, 4000, 4, 5 },
                { 1, 2, 3, 4, 5, 1000, 2000, 3000, 4000 },
                { 1, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 1000, 2000, 3000, 4000, 5 },
                { 1, 2, 1000, 2000, 3000, 4000, 3, 4, 5 },
                { 1000, 2000, 3000, 4000, 1, 2, 3, 4, 5 },
                { 1, 2, 3, 4, 5 },

                1000, 2000, 3000, 4000
        );
    });

    return allOk;
}
