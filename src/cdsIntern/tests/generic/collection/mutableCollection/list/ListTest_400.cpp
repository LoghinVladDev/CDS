#include "ListTest_common.hpp"

#include <CDS/Tuple>

namespace {
    namespace relIns {

        using cds::Tuple;

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

        __CDS_NoDiscard inline auto tFlagsToTData (cds::uint32 flags) noexcept -> TData {

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
                Tuple <cds::uint32, C<E>, Test const *> testData,
                F pfnBegin,
                cds::uint32 offset,
                E const & singleValue,
                bool opStatus,
                R const & opResult
        ) noexcept -> bool {

            auto const tData = tFlagsToTData(testData.template get <0> ());
            auto const pTestLib = testData.template get <2>();
            List <E> & lRef = testData.template get <1> ();

            auto it = (lRef.*pfnBegin) ();
            for (int i = 0; i < offset; ++ i) {
                ++ it;
            }

            if (
                    (opStatus != lRef.insertBefore (it, singleValue)) ||
                    (! equals (lRef, opResult))
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
                Tuple <
                        cds::Array <cds::Size>, 
                        cds::Array <E>, 
                        cds::Array <cds::Array <bool>>, 
                        cds::Array <cds::Array <cds::Array <E>>>
                > const & data
        ) -> bool {

            auto const & offsets = data.template get <0> ();
            auto const & singleValues = data.template get <1> ();
            auto const & statuses = data.template get <2> ();
            auto const & results = data.template get <3> ();

            bool result = true;
            cds::Array <TFlags> const offsetDatas = {OffsetCase1, OffsetCase2, OffsetCase3, OffsetCase4};
            cds::Array <TFlags> const valueDatas = {ValueCase1, ValueCase2, ValueCase3};

            auto const svSize = singleValues.size();
            auto const oSize = offsets.size();
            for (cds::uint32 vIdx = 0; vIdx < svSize; ++ vIdx) {
                for (cds::uint32 offIdx = 0; offIdx < oSize; ++ offIdx) {
                    result = result && singleInsBefIt <E, C, IGen> (
                            { 
                                    tNo                                                     | 
                                            ItCaseDet <IGen, reversed> :: itCase            | 
                                            static_cast <cds::uint32> (valueDatas [vIdx])   | 
                                            static_cast <cds::uint32> (offsetDatas [offIdx]), 
                                    initValues,
                                    pTestLib 
                            },
                            pfn, static_cast <cds::uint32> (offsets [offIdx]), singleValues [vIdx],
                            statuses [vIdx] [offIdx], results [vIdx] [offIdx]
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
                Tuple <cds::uint32, C<E>, Test const *> testData,
                F pfnBegin,
                cds::uint32 offset,
                E const & singleValue,
                bool opStatus,
                R const & opResult
        ) noexcept -> bool {

            auto const tData = tFlagsToTData(testData.template get <0> ());
            auto const pTestLib = testData.template get <2>();
            List <E> & lRef = testData.template get <1> ();

            auto it = (lRef.*pfnBegin) ();
            for (int i = 0; i < offset; ++ i) {
                ++ it;
            }

            if (
                    (opStatus != lRef.insertAfter (it, singleValue)) ||
                    (! equals (lRef, opResult))
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
                Tuple <
                        cds::Array <cds::Size>, 
                        cds::Array <E>, 
                        cds::Array <cds::Array <bool>>, 
                        cds::Array <cds::Array <cds::Array <E>>>
                > const & data
        ) -> bool {

            auto const & offsets = data.template get <0> ();
            auto const & singleValues = data.template get <1> ();
            auto const & statuses = data.template get <2> ();
            auto const & results = data.template get <3> ();

            bool result = true;
            cds::Array <TFlags> const offsetDatas = {OffsetCase1, OffsetCase2, OffsetCase3, OffsetCase4};
            cds::Array <TFlags> const valueDatas = {ValueCase1, ValueCase2, ValueCase3};

            auto const svSize = singleValues.size();
            auto const oSize = offsets.size();
            for (cds::uint32 vIdx = 0; vIdx < svSize; ++ vIdx) {
                for (cds::uint32 offIdx = 0; offIdx < oSize; ++ offIdx) {
                    result = result && singleInsAftIt <E, C, IGen> (
                            {
                                    tNo                                                     | 
                                            ItCaseDet <IGen, reversed> :: itCase            | 
                                            static_cast <cds::uint32> (valueDatas [vIdx])   | 
                                            static_cast <cds::uint32> (offsetDatas [offIdx]),
                                    initValues, pTestLib
                            },
                            pfn, static_cast <cds::uint32> (offsets [offIdx]), singleValues [vIdx],
                            statuses [vIdx] [offIdx], results [vIdx] [offIdx]
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
                Tuple <cds::uint32, C<E>, Test const *> testData,
                F pfnBegin,
                cds::uint32 offset,
                cds::Array <E> const & mValues,
                bool opStatus,
                R const & opResult
        ) noexcept -> bool {

            auto const tData = tFlagsToTData(testData.template get <0> ());
            auto const pTestLib = testData.template get <2>();
            List <E> & lRef = testData.template get <1> ();

            auto it = (lRef.*pfnBegin) ();
            for (int i = 0; i < offset; ++ i) {
                ++ it;
            }

            if (
                    (opStatus != lRef.insertAllOfBefore (it, mValues)) ||
                    (! equals (lRef, opResult))
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
                Tuple <
                        cds::Array <cds::Size>, 
                        cds::Array <cds::Array <E>>, 
                        cds::Array <cds::Array <bool>>, 
                        cds::Array <cds::Array <cds::Array <E>>>
                > const & data
        ) -> bool {

            auto const & offsets = data.template get <0> ();
            auto const & mValues = data.template get <1> ();
            auto const & statuses = data.template get <2> ();
            auto const & results = data.template get <3> ();

            bool result = true;
            cds::Array <TFlags> const offsetDatas = {OffsetCase1, OffsetCase2, OffsetCase3, OffsetCase4};
            cds::Array <TFlags> const valueDatas = {ValueCase1, ValueCase2, ValueCase3};

            auto const mSize = mValues.size();
            auto const oSize = offsets.size();
            for (cds::uint32 vIdx = 0; vIdx < mSize; ++ vIdx) {
                for (cds::uint32 offIdx = 0; offIdx < oSize; ++ offIdx) {
                    result = result && mulInsBefIt <E, C, IGen> (
                            {
                                    tNo                                                     |
                                            ItCaseDet <IGen, reversed> :: itCase            |
                                            static_cast <cds::uint32> (valueDatas[vIdx])    |
                                            static_cast <cds::uint32> (offsetDatas[offIdx]),
                                    initValues, pTestLib
                            },
                            pfn, static_cast <cds::uint32> (offsets [offIdx]), mValues [vIdx],
                            statuses [vIdx] [offIdx], results [vIdx] [offIdx]
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
                Tuple <cds::uint32, C<E>, Test const *> testData,
                F pfnBegin,
                cds::uint32 offset,
                cds::Array <E> const & mValues,
                bool opStatus,
                R const & opResult
        ) noexcept -> bool {

            auto const tData = tFlagsToTData(testData.template get <0> ());
            auto const pTestLib = testData.template get <2>();
            List <E> & lRef = testData.template get <1> ();

            auto it = (lRef.*pfnBegin) ();
            for (int i = 0; i < offset; ++ i) {
                ++ it;
            }

            if (
                    (opStatus != lRef.insertAllOfAfter (it, mValues)) ||
                    (! equals (lRef, opResult))
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
                Tuple <
                        cds::Array <cds::Size>, 
                        cds::Array <cds::Array <E>>, 
                        cds::Array <cds::Array <bool>>, 
                        cds::Array <cds::Array <cds::Array <E>>>
                > const & data
        ) -> bool {

            auto const & offsets = data.template get <0> ();
            auto const & mValues = data.template get <1> ();
            auto const & statuses = data.template get <2> ();
            auto const & results = data.template get <3> ();

            bool result = true;
            cds::Array <TFlags> const offsetDatas = {OffsetCase1, OffsetCase2, OffsetCase3, OffsetCase4};
            cds::Array <TFlags> const valueDatas = {ValueCase1, ValueCase2, ValueCase3};

            auto const mSize = mValues.size();
            auto const oSize = offsets.size();
            for (cds::uint32 vIdx = 0; vIdx < mSize; ++ vIdx) {
                for (cds::uint32 offIdx = 0; offIdx < oSize; ++ offIdx) {
                    result = result && mulInsAftIt <E, C, IGen> (
                            {
                                    tNo                                                     |
                                            ItCaseDet <IGen, reversed> :: itCase            |
                                            static_cast <cds::uint32> (valueDatas[vIdx])    |
                                            static_cast <cds::uint32> (offsetDatas[offIdx]),
                                    initValues, pTestLib
                            },
                            pfn, static_cast <cds::uint32> (offsets [offIdx]), mValues [vIdx],
                            statuses [vIdx] [offIdx], results [vIdx] [offIdx]
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
                Tuple <cds::uint32, C<E>, Test const *> testData,
                F pfnBegin,
                cds::uint32 offset,
                bool opStatus,
                R const & opResult,
                P && ... pack
        ) noexcept -> bool {

            auto const tData = tFlagsToTData(testData.template get <0> ());
            auto const pTestLib = testData.template get <2>();
            List <E> & lRef = testData.template get <1> ();

            auto it = (lRef.*pfnBegin) ();
            for (int i = 0; i < offset; ++ i) {
                ++ it;
            }

            if (
                    (opStatus != lRef.insertAllBefore (it, std::forward <P> (pack) ...)) ||
                    (! equals (lRef, opResult))
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
                Tuple <
                        cds::Array <cds::Size>,
                        cds::Array <bool>, 
                        cds::Array <cds::Array <E>>
                > const & data,
                P const & ... pack
        ) -> bool {

            auto const & offsets = data.template get <0> ();
            auto const & statuses = data.template get <1> ();
            auto const & results = data.template get <2> ();

            bool result = true;
            cds::Array <TFlags> const offsetDatas = {OffsetCase1, OffsetCase2, OffsetCase3, OffsetCase4};

            auto const oSize = offsets.size();
            for (cds::uint32 offIdx = 0; offIdx < oSize; ++ offIdx) {
                result = result && packInsBefIt <E, C, IGen> (
                        {
                                tNo                                                     |
                                        ItCaseDet <IGen, reversed> :: itCase            |
                                        ValueCase1                                      |
                                        static_cast <cds::uint32> (offsetDatas[offIdx]),
                                initValues, pTestLib
                        },
                        pfn, static_cast <cds::uint32> (offsets [offIdx]),  statuses [offIdx],
                        results [offIdx], pack ...
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
                Tuple <cds::uint32, C<E>, Test const *> testData,
                F pfnBegin,
                cds::uint32 offset,
                bool opStatus,
                R const & opResult,
                P && ... pack
        ) noexcept -> bool {

            auto const tData = tFlagsToTData(testData.template get <0> ());
            auto const pTestLib = testData.template get <2>();
            List <E> & lRef = testData.template get <1> ();

            auto it = (lRef.*pfnBegin) ();
            for (int i = 0; i < offset; ++ i) {
                ++ it;
            }

            if (
                    (opStatus != lRef.insertAllAfter (it, std::forward <P> (pack) ...)) ||
                    (! equals (lRef, opResult))
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
                Tuple <
                        cds::Array <cds::Size>,
                        cds::Array <bool>, 
                        cds::Array <cds::Array <E>>
                > const & data,
                P const & ... pack
        ) -> bool {

            auto const & offsets = data.template get <0> ();
            auto const & statuses = data.template get <1> ();
            auto const & results = data.template get <2> ();

            bool result = true;
            cds::Array <TFlags> const offsetDatas = {OffsetCase1, OffsetCase2, OffsetCase3, OffsetCase4};

            auto const oSize = offsets.size();
            for (cds::uint32 offIdx = 0; offIdx < oSize; ++ offIdx) {
                result = result && packInsAftIt <E, C, IGen> (
                        {
                                tNo                                                     |
                                        ItCaseDet <IGen, reversed> :: itCase            |
                                        ValueCase1                                      |
                                        static_cast <cds::uint32> (offsetDatas[offIdx]),
                                initValues, pTestLib
                        },
                        pfn, static_cast <cds::uint32> (offsets [offIdx]), statuses [offIdx],
                        results [offIdx], pack ...
                );

                tNo ++;
            }

            return result;
        }

    }


    using cds::Tuple;
    using cds::Array;
    using RelOffsetPack     = Tuple <Size, Size, Size, Size>;

    template <typename E>
    using RelSingleValPack  = Tuple <E, E, E>;

    template <typename E>
    using RelCaseResPack    = Tuple <Array <E>, Array <E>, Array <E>, Array <E>>;

    template <typename E>
    using RelItCaseResPack  = Tuple <RelCaseResPack <E>, RelCaseResPack <E>>;

    template <typename E>
    using RelSCaseResPack   = Tuple <RelItCaseResPack <E>, RelItCaseResPack <E>, RelItCaseResPack <E>>;

    template <typename E>
    using RelSingleValueCaseData    = Tuple <RelOffsetPack, RelSingleValPack <E>, RelSCaseResPack <E>>;

    template <typename E>
    using RelSingleValueBefAftData  = Tuple <RelOffsetPack, RelSingleValPack <E>, RelSCaseResPack <E>, RelSCaseResPack <E>>;


    /* ListTestGroup-RelativeInsertion-cpp-xx : LTG-00400-RI-cpp-xx. Tests LTC-00401-RI to LTC-00624-RI */
    template <
            template < typename ... > class __TestedType,
            typename __EnclosedType
    > auto listTestGroupRelativeInsertionSingleValuesBefore (
            cds::uint32 & tNo,
            Test * pTestLib,
            std :: initializer_list < __EnclosedType > const & initValues,
            RelSingleValueCaseData <__EnclosedType> const & data
    ) -> bool {

        auto const & offsetPack = data.template get <0> ();
        auto const & valuePack = data.template get <1> ();
        auto const & svResultPack = data.template get <2> ();

        auto case1Offset = offsetPack.template get<0> ();
        auto case2Offset = offsetPack.template get<1> ();
        auto case3Offset = offsetPack.template get<2> ();
        auto case4Offset = offsetPack.template get<3> ();

        auto const & singleValue1 = valuePack.template get<0> ();
        auto const & singleValue2 = valuePack.template get<1> ();
        auto const & singleValue3 = valuePack.template get<2> ();

        auto const & sv1ItResultPack = svResultPack.template get <0> ();
        auto const & sv2ItResultPack = svResultPack.template get <1> ();
        auto const & sv3ItResultPack = svResultPack.template get <2> ();

        auto const & sv1FwdResultPack = sv1ItResultPack.template get <0> ();
        auto const & sv2FwdResultPack = sv2ItResultPack.template get <0> ();
        auto const & sv3FwdResultPack = sv3ItResultPack.template get <0> ();
        auto const & sv1BwdResultPack = sv1ItResultPack.template get <1> ();;
        auto const & sv2BwdResultPack = sv2ItResultPack.template get <1> ();;
        auto const & sv3BwdResultPack = sv3ItResultPack.template get <1> ();

        auto const & resSingle1Case1 = sv1FwdResultPack.template get <0> ();
        auto const & resSingle1Case2 = sv1FwdResultPack.template get <1> ();
        auto const & resSingle1Case3 = sv1FwdResultPack.template get <2> ();
        auto const & resSingle1Case4 = sv1FwdResultPack.template get <3> ();
        auto const & resSingle2Case1 = sv2FwdResultPack.template get <0> ();
        auto const & resSingle2Case2 = sv2FwdResultPack.template get <1> ();
        auto const & resSingle2Case3 = sv2FwdResultPack.template get <2> ();
        auto const & resSingle2Case4 = sv2FwdResultPack.template get <3> ();
        auto const & resSingle3Case1 = sv3FwdResultPack.template get <0> ();
        auto const & resSingle3Case2 = sv3FwdResultPack.template get <1> ();
        auto const & resSingle3Case3 = sv3FwdResultPack.template get <2> ();
        auto const & resSingle3Case4 = sv3FwdResultPack.template get <3> ();

        auto const & resSingle1RevCase1 = sv1BwdResultPack.template get <0> ();
        auto const & resSingle1RevCase2 = sv1BwdResultPack.template get <1> ();
        auto const & resSingle1RevCase3 = sv1BwdResultPack.template get <2> ();
        auto const & resSingle1RevCase4 = sv1BwdResultPack.template get <3> ();
        auto const & resSingle2RevCase1 = sv2BwdResultPack.template get <0> ();
        auto const & resSingle2RevCase2 = sv2BwdResultPack.template get <1> ();
        auto const & resSingle2RevCase3 = sv2BwdResultPack.template get <2> ();
        auto const & resSingle2RevCase4 = sv2BwdResultPack.template get <3> ();
        auto const & resSingle3RevCase1 = sv3BwdResultPack.template get <0> ();
        auto const & resSingle3RevCase2 = sv3BwdResultPack.template get <1> ();
        auto const & resSingle3RevCase3 = sv3BwdResultPack.template get <2> ();
        auto const & resSingle3RevCase4 = sv3BwdResultPack.template get <3> ();

        bool status = true;
        
        status = relIns::singleInsBefAll <__EnclosedType, __TestedType, relIns::BeginPfn<__EnclosedType>, false> (
                tNo, initValues, pTestLib, & List<__EnclosedType>::begin,
                cds::makeTuple <cds::Array <cds::Size>, cds::Array <__EnclosedType>, cds::Array <cds::Array <bool>>, cds::Array <cds::Array <cds::Array <__EnclosedType>>>> (
                        { case1Offset, case2Offset, case3Offset, case4Offset },
                        { singleValue1, singleValue2, singleValue3 },
                        { { true, true, true, false }, { true, true, true, false }, { true, true, true, false } }, {
                                { resSingle1Case1, resSingle1Case2, resSingle1Case3, resSingle1Case4 },
                                { resSingle2Case1, resSingle2Case2, resSingle2Case3, resSingle2Case4 },
                                { resSingle3Case1, resSingle3Case2, resSingle3Case3, resSingle3Case4 }
                        }
                )
        );
        
        status = status && relIns::singleInsBefAll <__EnclosedType, __TestedType, relIns::RBeginPfn<__EnclosedType>, true> (
                tNo, initValues, pTestLib, & List<__EnclosedType>::rbegin,
                cds::makeTuple <cds::Array <cds::Size>, cds::Array <__EnclosedType>, cds::Array <cds::Array <bool>>, cds::Array <cds::Array <cds::Array <__EnclosedType>>>> (
                        { case1Offset, case2Offset, case3Offset, case4Offset },
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
                )
        );
        
        status = status && relIns::singleInsBefAll <__EnclosedType, __TestedType, relIns::CBeginPfn<__EnclosedType>, false> (
                tNo, initValues, pTestLib, & List<__EnclosedType>::cbegin,
                cds::makeTuple <cds::Array <cds::Size>, cds::Array <__EnclosedType>, cds::Array <cds::Array <bool>>, cds::Array <cds::Array <cds::Array <__EnclosedType>>>> (
                        { case1Offset, case2Offset, case3Offset, case4Offset },
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
                )
        );
        
        status = status && relIns::singleInsBefAll <__EnclosedType, __TestedType, relIns::CRBeginPfn<__EnclosedType>, true> (
                tNo, initValues, pTestLib, & List<__EnclosedType>::crbegin,
                cds::makeTuple <cds::Array <cds::Size>, cds::Array <__EnclosedType>, cds::Array <cds::Array <bool>>, cds::Array <cds::Array <cds::Array <__EnclosedType>>>> (
                        { case1Offset, case2Offset, case3Offset, case4Offset },
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
                )
        );

        return status;
    }


    /* ListTestGroup-RelativeInsertion-cpp-xx : LTG-00400-RI-cpp-xx. Tests LTC-00401-RI to LTC-00624-RI */
    template <
            template < typename ... > class __TestedType,
            typename __EnclosedType
    > auto listTestGroupRelativeInsertionSingleValuesAfter (
            cds::uint32 & tNo,
            Test * pTestLib,
            std :: initializer_list < __EnclosedType > const & initValues,
            RelSingleValueCaseData <__EnclosedType> const & data
    ) -> bool {

        auto const & offsetPack = data.template get <0> ();
        auto const & valuePack = data.template get <1> ();
        auto const & svResultPack = data.template get <2> ();

        auto case1Offset = offsetPack.template get<0> ();
        auto case2Offset = offsetPack.template get<1> ();
        auto case3Offset = offsetPack.template get<2> ();
        auto case4Offset = offsetPack.template get<3> ();

        auto const & singleValue1 = valuePack.template get<0> ();
        auto const & singleValue2 = valuePack.template get<1> ();
        auto const & singleValue3 = valuePack.template get<2> ();

        auto const & sv1ItResultPack = svResultPack.template get <0> ();
        auto const & sv2ItResultPack = svResultPack.template get <1> ();
        auto const & sv3ItResultPack = svResultPack.template get <2> ();

        auto const & sv1FwdResultPack = sv1ItResultPack.template get <0> ();
        auto const & sv1BwdResultPack = sv1ItResultPack.template get <1> ();;

        auto const & sv2FwdResultPack = sv2ItResultPack.template get <0> ();
        auto const & sv2BwdResultPack = sv2ItResultPack.template get <1> ();;

        auto const & sv3FwdResultPack = sv3ItResultPack.template get <0> ();
        auto const & sv3BwdResultPack = sv3ItResultPack.template get <1> ();

        auto const & aresSingle1Case1 = sv1FwdResultPack.template get <0> ();
        auto const & aresSingle1Case2 = sv1FwdResultPack.template get <1> ();
        auto const & aresSingle1Case3 = sv1FwdResultPack.template get <2> ();
        auto const & aresSingle1Case4 = sv1FwdResultPack.template get <3> ();

        auto const & aresSingle1RevCase1 = sv1BwdResultPack.template get <0> ();
        auto const & aresSingle1RevCase2 = sv1BwdResultPack.template get <1> ();
        auto const & aresSingle1RevCase3 = sv1BwdResultPack.template get <2> ();
        auto const & aresSingle1RevCase4 = sv1BwdResultPack.template get <3> ();

        auto const & aresSingle2Case1 = sv2FwdResultPack.template get <0> ();
        auto const & aresSingle2Case2 = sv2FwdResultPack.template get <1> ();
        auto const & aresSingle2Case3 = sv2FwdResultPack.template get <2> ();
        auto const & aresSingle2Case4 = sv2FwdResultPack.template get <3> ();

        auto const & aresSingle2RevCase1 = sv2BwdResultPack.template get <0> ();
        auto const & aresSingle2RevCase2 = sv2BwdResultPack.template get <1> ();
        auto const & aresSingle2RevCase3 = sv2BwdResultPack.template get <2> ();
        auto const & aresSingle2RevCase4 = sv2BwdResultPack.template get <3> ();

        auto const & aresSingle3Case1 = sv3FwdResultPack.template get <0> ();
        auto const & aresSingle3Case2 = sv3FwdResultPack.template get <1> ();
        auto const & aresSingle3Case3 = sv3FwdResultPack.template get <2> ();
        auto const & aresSingle3Case4 = sv3FwdResultPack.template get <3> ();

        auto const & aresSingle3RevCase1 = sv3BwdResultPack.template get <0> ();
        auto const & aresSingle3RevCase2 = sv3BwdResultPack.template get <1> ();
        auto const & aresSingle3RevCase3 = sv3BwdResultPack.template get <2> ();
        auto const & aresSingle3RevCase4 = sv3BwdResultPack.template get <3> ();
        
        bool status = true;
        
        status = status && relIns::singleInsAftAll <__EnclosedType, __TestedType, relIns::BeginPfn<__EnclosedType>, false> (
                tNo, initValues, pTestLib, & List<__EnclosedType>::begin,
                cds::makeTuple <cds::Array <cds::Size>, cds::Array <__EnclosedType>, cds::Array <cds::Array <bool>>, cds::Array <cds::Array <cds::Array <__EnclosedType>>>> (
                        { case1Offset, case2Offset, case3Offset, case4Offset },
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
                )
        );
        
        status = status && relIns::singleInsAftAll <__EnclosedType, __TestedType, relIns::RBeginPfn<__EnclosedType>, true> (
                tNo, initValues, pTestLib, & List<__EnclosedType>::rbegin,
                cds::makeTuple <cds::Array <cds::Size>, cds::Array <__EnclosedType>, cds::Array <cds::Array <bool>>, cds::Array <cds::Array <cds::Array <__EnclosedType>>>>(
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
                )
        );
        
        status = status && relIns::singleInsAftAll <__EnclosedType, __TestedType, relIns::CBeginPfn<__EnclosedType>, false> (
                tNo, initValues, pTestLib, & List<__EnclosedType>::cbegin,
                cds::makeTuple <cds::Array <cds::Size>, cds::Array <__EnclosedType>, cds::Array <cds::Array <bool>>, cds::Array <cds::Array <cds::Array <__EnclosedType>>>>(
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
                )
        );
        
        status = status && relIns::singleInsAftAll <__EnclosedType, __TestedType, relIns::CRBeginPfn<__EnclosedType>, true> (
                tNo, initValues, pTestLib, & List<__EnclosedType>::crbegin,
                cds::makeTuple <cds::Array <cds::Size>, cds::Array <__EnclosedType>, cds::Array <cds::Array <bool>>, cds::Array <cds::Array <cds::Array <__EnclosedType>>>>(
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
                )
        );

        return status;
    }


    /* ListTestGroup-RelativeInsertion-cpp-xx : LTG-00400-RI-cpp-xx. Tests LTC-00401-RI to LTC-00624-RI */
    template <
            template < typename ... > class __TestedType,
            typename __EnclosedType
    > auto listTestGroupRelativeInsertionSingleValues (
            cds::uint32 & tNo,
            Test * pTestLib,
            std :: initializer_list < __EnclosedType > const & initValues,
            RelSingleValueBefAftData <__EnclosedType> const & data
    ) -> bool {

        auto const & offsetPack = data.template get <0> ();
        auto const & valuePack = data.template get <1> ();
        auto const & beforeData = data.template get <2> ();
        auto const & afterData = data.template get <3> ();


        return listTestGroupRelativeInsertionSingleValuesBefore <
                __TestedType,
                __EnclosedType 
        > (
                tNo, pTestLib, initValues,
                cds::makeTuple (
                        offsetPack, valuePack, beforeData
                )
        ) && listTestGroupRelativeInsertionSingleValuesAfter <
                __TestedType,
                __EnclosedType 
        > (
                tNo, pTestLib, initValues,
                cds::makeTuple (
                        offsetPack, valuePack, afterData
                )
        );
    }


    /* ListTestGroup-RelativeInsertion-cpp-xx : LTG-00400-RI-cpp-xx. Tests LTC-00401-RI to LTC-00624-RI */
    template <
            template < typename ... > class __TestedType,
            typename __EnclosedType
    > auto listTestGroupRelativeInsertionMultipleValuesBefore (
            cds::uint32 & tNo,
            Test * pTestLib,
            std :: initializer_list < __EnclosedType > const & initValues,
            Size case1Offset,
            Size case2Offset,
            Size case3Offset,
            Size case4Offset,
            std :: initializer_list < __EnclosedType > const & multipleValues1,
            std :: initializer_list < __EnclosedType > const & multipleValues2,
            std :: initializer_list < __EnclosedType > const & multipleValues3,

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
            std :: initializer_list < __EnclosedType > const & resMultiple3RevCase4
    ) -> bool {

        bool status = true;
        
        status = status && relIns::mulInsBefAll <__EnclosedType, __TestedType, relIns::BeginPfn<__EnclosedType>, false> (
                tNo, initValues, pTestLib, & List<__EnclosedType>::begin,
                cds::makeTuple <cds::Array <cds::Size>, cds::Array <cds::Array <__EnclosedType>>, cds::Array <cds::Array <bool>>, cds::Array <cds::Array <cds::Array <__EnclosedType>>>>(
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
                )
        );
        
        status = status && relIns::mulInsBefAll <__EnclosedType, __TestedType, relIns::RBeginPfn<__EnclosedType>, true> (
                tNo, initValues, pTestLib, & List<__EnclosedType>::rbegin,
                cds::makeTuple <cds::Array <cds::Size>, cds::Array <cds::Array <__EnclosedType>>, cds::Array <cds::Array <bool>>, cds::Array <cds::Array <cds::Array <__EnclosedType>>>>(
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
                )
        );
        
        status = status && relIns::mulInsBefAll <__EnclosedType, __TestedType, relIns::CBeginPfn<__EnclosedType>, false> (
                tNo, initValues, pTestLib, & List<__EnclosedType>::cbegin,
                cds::makeTuple <cds::Array <cds::Size>, cds::Array <cds::Array <__EnclosedType>>, cds::Array <cds::Array <bool>>, cds::Array <cds::Array <cds::Array <__EnclosedType>>>> (
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
                )
        );
        
        status = status && relIns::mulInsBefAll <__EnclosedType, __TestedType, relIns::CRBeginPfn<__EnclosedType>, true> (
                tNo, initValues, pTestLib, & List<__EnclosedType>::crbegin,
                cds::makeTuple <cds::Array <cds::Size>, cds::Array <cds::Array <__EnclosedType>>, cds::Array <cds::Array <bool>>, cds::Array <cds::Array <cds::Array <__EnclosedType>>>>(
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
                )
        );

        return status;
    }


    /* ListTestGroup-RelativeInsertion-cpp-xx : LTG-00400-RI-cpp-xx. Tests LTC-00401-RI to LTC-00624-RI */
    template <
            template < typename ... > class __TestedType,
            typename __EnclosedType
    > auto listTestGroupRelativeInsertionMultipleValuesAfter (
            cds::uint32 & tNo,
            Test * pTestLib,
            std :: initializer_list < __EnclosedType > const & initValues,
            Size case1Offset,
            Size case2Offset,
            Size case3Offset,
            Size case4Offset,
            std :: initializer_list < __EnclosedType > const & multipleValues1,
            std :: initializer_list < __EnclosedType > const & multipleValues2,
            std :: initializer_list < __EnclosedType > const & multipleValues3,

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
            std :: initializer_list < __EnclosedType > const & aresMultiple3RevCase4
    ) -> bool {

        bool status = true;
        
        status = status && relIns::mulInsAftAll <__EnclosedType, __TestedType, relIns::BeginPfn<__EnclosedType>, false> (
                tNo, initValues, pTestLib, & List<__EnclosedType>::begin,
                cds::makeTuple <cds::Array <cds::Size>, cds::Array <cds::Array <__EnclosedType>>, cds::Array <cds::Array <bool>>, cds::Array <cds::Array <cds::Array <__EnclosedType>>>> (
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
                )
        );
        
        status = status && relIns::mulInsAftAll <__EnclosedType, __TestedType, relIns::RBeginPfn<__EnclosedType>, true> (
                tNo, initValues, pTestLib, & List<__EnclosedType>::rbegin,
                cds::makeTuple <cds::Array <cds::Size>, cds::Array <cds::Array <__EnclosedType>>, cds::Array <cds::Array <bool>>, cds::Array <cds::Array <cds::Array <__EnclosedType>>>> (
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
                )
        );
        
        status = status && relIns::mulInsAftAll <__EnclosedType, __TestedType, relIns::CBeginPfn<__EnclosedType>, false> (
                tNo, initValues, pTestLib, & List<__EnclosedType>::cbegin,
                cds::makeTuple <cds::Array <cds::Size>, cds::Array <cds::Array <__EnclosedType>>, cds::Array <cds::Array <bool>>, cds::Array <cds::Array <cds::Array <__EnclosedType>>>> (
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
                )
        );
        
        status = status && relIns::mulInsAftAll <__EnclosedType, __TestedType, relIns::CRBeginPfn<__EnclosedType>, true> (
                tNo, initValues, pTestLib, & List<__EnclosedType>::crbegin,
                cds::makeTuple <cds::Array <cds::Size>, cds::Array <cds::Array <__EnclosedType>>, cds::Array <cds::Array <bool>>, cds::Array <cds::Array <cds::Array <__EnclosedType>>>> (
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
                )
        );

        return status;
    }


    /* ListTestGroup-RelativeInsertion-cpp-xx : LTG-00400-RI-cpp-xx. Tests LTC-00401-RI to LTC-00624-RI */
    template <
            template < typename ... > class __TestedType,
            typename __EnclosedType
    > auto listTestGroupRelativeInsertionMultipleValues (
            cds::uint32 & tNo,
            Test * pTestLib,
            std :: initializer_list < __EnclosedType > const & initValues,
            Size case1Offset,
            Size case2Offset,
            Size case3Offset,
            Size case4Offset,
            std :: initializer_list < __EnclosedType > const & multipleValues1,
            std :: initializer_list < __EnclosedType > const & multipleValues2,
            std :: initializer_list < __EnclosedType > const & multipleValues3,

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
            std :: initializer_list < __EnclosedType > const & aresMultiple3RevCase4
    ) -> bool {

        return 
                listTestGroupRelativeInsertionMultipleValuesBefore <
                        __TestedType,
                        __EnclosedType
                > (
                        tNo, pTestLib, initValues,
                        case1Offset,
                        case2Offset,
                        case3Offset,
                        case4Offset,
                        multipleValues1,
                        multipleValues2,
                        multipleValues3,

                        resMultiple1Case1,
                        resMultiple1Case2,
                        resMultiple1Case3,
                        resMultiple1Case4,
                        resMultiple1RevCase1,
                        resMultiple1RevCase2,
                        resMultiple1RevCase3,
                        resMultiple1RevCase4,

                        resMultiple2Case1,
                        resMultiple2Case2,
                        resMultiple2Case3,
                        resMultiple2Case4,
                        resMultiple2RevCase1,
                        resMultiple2RevCase2,
                        resMultiple2RevCase3,
                        resMultiple2RevCase4,

                        resMultiple3Case1,
                        resMultiple3Case2,
                        resMultiple3Case3,
                        resMultiple3Case4,
                        resMultiple3RevCase1,
                        resMultiple3RevCase2,
                        resMultiple3RevCase3,
                        resMultiple3RevCase4
                ) && listTestGroupRelativeInsertionMultipleValuesAfter <
                        __TestedType,
                        __EnclosedType
                > (
                        tNo, pTestLib, initValues,
                        case1Offset,
                        case2Offset,
                        case3Offset,
                        case4Offset,
                        multipleValues1,
                        multipleValues2,
                        multipleValues3,

                        aresMultiple1Case1,
                        aresMultiple1Case2,
                        aresMultiple1Case3,
                        aresMultiple1Case4,
                        aresMultiple1RevCase1,
                        aresMultiple1RevCase2,
                        aresMultiple1RevCase3,
                        aresMultiple1RevCase4,

                        aresMultiple2Case1,
                        aresMultiple2Case2,
                        aresMultiple2Case3,
                        aresMultiple2Case4,
                        aresMultiple2RevCase1,
                        aresMultiple2RevCase2,
                        aresMultiple2RevCase3,
                        aresMultiple2RevCase4,

                        aresMultiple3Case1,
                        aresMultiple3Case2,
                        aresMultiple3Case3,
                        aresMultiple3Case4,
                        aresMultiple3RevCase1,
                        aresMultiple3RevCase2,
                        aresMultiple3RevCase3,
                        aresMultiple3RevCase4
                );
    }


    /* ListTestGroup-RelativeInsertion-cpp-xx : LTG-00400-RI-cpp-xx. Tests LTC-00401-RI to LTC-00624-RI */
    template <
            template < typename ... > class __TestedType,
            typename __EnclosedType,
            typename ... __Values
    > auto listTestGroupRelativeInsertionPackBefore (
            cds::uint32 & tNo,
            Test * pTestLib,
            std :: initializer_list < __EnclosedType > const & initValues,
            Size case1Offset,
            Size case2Offset,
            Size case3Offset,
            Size case4Offset,

            std :: initializer_list < __EnclosedType > const & resMultipleVCase1,
            std :: initializer_list < __EnclosedType > const & resMultipleVCase2,
            std :: initializer_list < __EnclosedType > const & resMultipleVCase3,
            std :: initializer_list < __EnclosedType > const & resMultipleVCase4,
            std :: initializer_list < __EnclosedType > const & resMultipleVRevCase1,
            std :: initializer_list < __EnclosedType > const & resMultipleVRevCase2,
            std :: initializer_list < __EnclosedType > const & resMultipleVRevCase3,
            std :: initializer_list < __EnclosedType > const & resMultipleVRevCase4,

            __Values const & ... values
    ) -> bool {

        bool status = true;
        
        status = status && relIns::packInsBefAll <__EnclosedType, __TestedType, relIns::BeginPfn<__EnclosedType>, false> (
                tNo, initValues, pTestLib, & List<__EnclosedType>::begin,
                cds::makeTuple <cds::Array <cds::Size>, cds::Array <bool>, cds::Array <cds::Array <__EnclosedType>>> (
                        {case1Offset, case2Offset, case3Offset, case4Offset },
                        {true, true, true, false}, 
                        {resMultipleVCase1, resMultipleVCase2, resMultipleVCase3, resMultipleVCase4}
                ),
                values ...
        );
        
        status = status && relIns::packInsBefAll <__EnclosedType, __TestedType, relIns::RBeginPfn<__EnclosedType>, true> (
                tNo, initValues, pTestLib, & List<__EnclosedType>::rbegin,
                cds::makeTuple <cds::Array <cds::Size>, cds::Array <bool>, cds::Array <cds::Array <__EnclosedType>>> (
                        {case1Offset, case2Offset, case3Offset, case4Offset },
                        {true, true, true, false}, 
                        {resMultipleVRevCase1, resMultipleVRevCase2, resMultipleVRevCase3, resMultipleVRevCase4}
                ),
                values ...
        );
        
        status = status && relIns::packInsBefAll <__EnclosedType, __TestedType, relIns::CBeginPfn<__EnclosedType>, false> (
                tNo, initValues, pTestLib, & List<__EnclosedType>::cbegin,
                cds::makeTuple <cds::Array <cds::Size>, cds::Array <bool>, cds::Array <cds::Array <__EnclosedType>>> (
                        {case1Offset, case2Offset, case3Offset, case4Offset },
                        {true, true, true, false}, 
                        {resMultipleVCase1, resMultipleVCase2, resMultipleVCase3, resMultipleVCase4}
                ),
                values ...
        );
        
        status = status && relIns::packInsBefAll <__EnclosedType, __TestedType, relIns::CRBeginPfn<__EnclosedType>, true> (
                tNo, initValues, pTestLib, & List<__EnclosedType>::crbegin,
                cds::makeTuple <cds::Array <cds::Size>, cds::Array <bool>, cds::Array <cds::Array <__EnclosedType>>> (
                        {case1Offset, case2Offset, case3Offset, case4Offset },
                        {true, true, true, false}, 
                        {resMultipleVRevCase1, resMultipleVRevCase2, resMultipleVRevCase3, resMultipleVRevCase4}
                ),
                values ...
        );

        return status;
    }


    /* ListTestGroup-RelativeInsertion-cpp-xx : LTG-00400-RI-cpp-xx. Tests LTC-00401-RI to LTC-00624-RI */
    template <
            template < typename ... > class __TestedType,
            typename __EnclosedType,
            typename ... __Values
    > auto listTestGroupRelativeInsertionPackAfter (
            cds::uint32 & tNo,
            Test * pTestLib,
            std :: initializer_list < __EnclosedType > const & initValues,
            Size case1Offset,
            Size case2Offset,
            Size case3Offset,
            Size case4Offset,

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

        bool status = true;
        
        status = status && relIns::packInsAftAll <__EnclosedType, __TestedType, relIns::BeginPfn<__EnclosedType>, false> (
                tNo, initValues, pTestLib, & List<__EnclosedType>::begin,
                cds::makeTuple <cds::Array <cds::Size>, cds::Array <bool>, cds::Array <cds::Array <__EnclosedType>>> (
                        {case1Offset, case2Offset, case3Offset, case4Offset },
                        {true, true, true, false}, 
                        {aresMultipleVCase1, aresMultipleVCase2, aresMultipleVCase3, aresMultipleVCase4}
                ),
                values ...
        );
        
        status = status && relIns::packInsAftAll <__EnclosedType, __TestedType, relIns::RBeginPfn<__EnclosedType>, true> (
                tNo, initValues, pTestLib, & List<__EnclosedType>::rbegin,
                cds::makeTuple <cds::Array <cds::Size>, cds::Array <bool>, cds::Array <cds::Array <__EnclosedType>>> (
                        {case1Offset, case2Offset, case3Offset, case4Offset },
                        {true, true, true, false}, 
                        {aresMultipleVRevCase1, aresMultipleVRevCase2, aresMultipleVRevCase3, aresMultipleVRevCase4}
                ),
                values ...
        );
        
        status = status && relIns::packInsAftAll <__EnclosedType, __TestedType, relIns::CBeginPfn<__EnclosedType>, false> (
                tNo, initValues, pTestLib, & List<__EnclosedType>::cbegin,
                cds::makeTuple <cds::Array <cds::Size>, cds::Array <bool>, cds::Array <cds::Array <__EnclosedType>>> (
                        {case1Offset, case2Offset, case3Offset, case4Offset },
                        {true, true, true, false}, 
                        {aresMultipleVCase1, aresMultipleVCase2, aresMultipleVCase3, aresMultipleVCase4}
                ),
                values ...
        );
        
        status = status && relIns::packInsAftAll <__EnclosedType, __TestedType, relIns::CRBeginPfn<__EnclosedType>, true> (
                tNo, initValues, pTestLib, & List<__EnclosedType>::crbegin,
                cds::makeTuple <cds::Array <cds::Size>, cds::Array <bool>, cds::Array <cds::Array <__EnclosedType>>> (
                        {case1Offset, case2Offset, case3Offset, case4Offset },
                        {true, true, true, false}, 
                        {aresMultipleVRevCase1, aresMultipleVRevCase2, aresMultipleVRevCase3, aresMultipleVRevCase4}
                ),
                values ...
        );

        return status;
    }


    /* ListTestGroup-RelativeInsertion-cpp-xx : LTG-00400-RI-cpp-xx. Tests LTC-00401-RI to LTC-00624-RI */
    template <
            template < typename ... > class __TestedType,
            typename __EnclosedType,
            typename ... __Values
    > auto listTestGroupRelativeInsertionPack (
            cds::uint32 & tNo,
            Test * pTestLib,
            std :: initializer_list < __EnclosedType > const & initValues,
            Size case1Offset,
            Size case2Offset,
            Size case3Offset,
            Size case4Offset,

            std :: initializer_list < __EnclosedType > const & resMultipleVCase1,
            std :: initializer_list < __EnclosedType > const & resMultipleVCase2,
            std :: initializer_list < __EnclosedType > const & resMultipleVCase3,
            std :: initializer_list < __EnclosedType > const & resMultipleVCase4,
            std :: initializer_list < __EnclosedType > const & resMultipleVRevCase1,
            std :: initializer_list < __EnclosedType > const & resMultipleVRevCase2,
            std :: initializer_list < __EnclosedType > const & resMultipleVRevCase3,
            std :: initializer_list < __EnclosedType > const & resMultipleVRevCase4,

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

        return
                listTestGroupRelativeInsertionPackBefore <
                        __TestedType,
                        __EnclosedType
                > (
                        tNo, pTestLib, initValues,
                        case1Offset, case2Offset, case3Offset, case4Offset, 
                        
                        resMultipleVCase1,
                        resMultipleVCase2,
                        resMultipleVCase3,
                        resMultipleVCase4,
                        resMultipleVRevCase1,
                        resMultipleVRevCase2,
                        resMultipleVRevCase3,
                        resMultipleVRevCase4,

                        values ...
                ) && listTestGroupRelativeInsertionPackAfter <
                        __TestedType,
                        __EnclosedType
                > (
                        tNo, pTestLib, initValues,
                        case1Offset, case2Offset, case3Offset, case4Offset,
                
                        aresMultipleVCase1,
                        aresMultipleVCase2,
                        aresMultipleVCase3,
                        aresMultipleVCase4,
                        aresMultipleVRevCase1,
                        aresMultipleVRevCase2,
                        aresMultipleVRevCase3,
                        aresMultipleVRevCase4,

                        values ...
                );
    }


    /* ListTestGroup-RelativeInsertion-cpp-xx : LTG-00400-RI-cpp-xx. Tests LTC-00401-RI to LTC-00624-RI */
    template <
            template < typename ... > class __TestedType,
            typename __EnclosedType,
            typename ... __Values
    > auto listTestGroupRelativeInsertion (
            Test * pTestLib,
            std :: initializer_list < __EnclosedType > const & initValues,
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

        cds::uint32 tNo = 401U;
        using E = __EnclosedType;

        return listTestGroupRelativeInsertionSingleValues <
                __TestedType,
                E
        > (
                tNo, pTestLib, initValues,
                cds::makeTuple <
                        RelOffsetPack,
                        RelSingleValPack <E>,
                        RelSCaseResPack <E>,
                        RelSCaseResPack <E>
                > (

                        cds::makeTuple (
                                case1Offset, 
                                case2Offset,
                                case3Offset,
                                case4Offset
                        ),

                        cds::makeTuple (
                                singleValue1, 
                                singleValue2, 
                                singleValue3
                        ),

                        cds::makeTuple <RelItCaseResPack <E>, RelItCaseResPack <E>, RelItCaseResPack <E>> (
                                cds::makeTuple <RelCaseResPack <E>, RelCaseResPack <E>> (
                                        cds::makeTuple <Array <E>, Array <E>, Array <E>, Array <E>> (
                                                resSingle1Case1, 
                                                resSingle1Case2,
                                                resSingle1Case3,
                                                resSingle1Case4
                                        ),
                                        cds::makeTuple <Array <E>, Array <E>, Array <E>, Array <E>> (
                                                resSingle1RevCase1,
                                                resSingle1RevCase2,
                                                resSingle1RevCase3,
                                                resSingle1RevCase4
                                        )
                                ),

                                cds::makeTuple <RelCaseResPack <E>, RelCaseResPack <E>> (
                                        cds::makeTuple <Array <E>, Array <E>, Array <E>, Array <E>> (
                                                resSingle2Case1,
                                                resSingle2Case2,
                                                resSingle2Case3,
                                                resSingle2Case4
                                        ),
                                        cds::makeTuple <Array <E>, Array <E>, Array <E>, Array <E>> (
                                                resSingle2RevCase1,
                                                resSingle2RevCase2,
                                                resSingle2RevCase3,
                                                resSingle2RevCase4
                                        )
                                ),

                                cds::makeTuple <RelCaseResPack <E>, RelCaseResPack <E>> (
                                        cds::makeTuple <Array <E>, Array <E>, Array <E>, Array <E>> (
                                                resSingle3Case1,
                                                resSingle3Case2,
                                                resSingle3Case3,
                                                resSingle3Case4
                                        ),
                                        cds::makeTuple <Array <E>, Array <E>, Array <E>, Array <E>> (
                                                resSingle3RevCase1,
                                                resSingle3RevCase2,
                                                resSingle3RevCase3,
                                                resSingle3RevCase4
                                        )
                                )
                        ),

                        cds::makeTuple <RelItCaseResPack <E>, RelItCaseResPack <E>, RelItCaseResPack <E>> (
                                cds::makeTuple <RelCaseResPack <E>, RelCaseResPack <E>> (
                                        cds::makeTuple <Array <E>, Array <E>, Array <E>, Array <E>> (
                                                aresSingle1Case1, 
                                                aresSingle1Case2,
                                                aresSingle1Case3,
                                                aresSingle1Case4
                                        ),
                                        cds::makeTuple <Array <E>, Array <E>, Array <E>, Array <E>> (
                                                aresSingle1RevCase1,
                                                aresSingle1RevCase2,
                                                aresSingle1RevCase3,
                                                aresSingle1RevCase4
                                        )
                                ),

                                cds::makeTuple <RelCaseResPack <E>, RelCaseResPack <E>> (
                                        cds::makeTuple <Array <E>, Array <E>, Array <E>, Array <E>> (
                                                aresSingle2Case1,
                                                aresSingle2Case2,
                                                aresSingle2Case3,
                                                aresSingle2Case4
                                        ),
                                        cds::makeTuple <Array <E>, Array <E>, Array <E>, Array <E>> (
                                                aresSingle2RevCase1,
                                                aresSingle2RevCase2,
                                                aresSingle2RevCase3,
                                                aresSingle2RevCase4
                                        )
                                ),

                                cds::makeTuple <RelCaseResPack <E>, RelCaseResPack <E>> (
                                        cds::makeTuple <Array <E>, Array <E>, Array <E>, Array <E>> (
                                                aresSingle3Case1,
                                                aresSingle3Case2,
                                                aresSingle3Case3,
                                                aresSingle3Case4
                                        ),
                                        cds::makeTuple <Array <E>, Array <E>, Array <E>, Array <E>> (
                                                aresSingle3RevCase1,
                                                aresSingle3RevCase2,
                                                aresSingle3RevCase3,
                                                aresSingle3RevCase4
                                        )
                                )
                        )
                )
        ) && listTestGroupRelativeInsertionMultipleValues <
                __TestedType,
                __EnclosedType
        > (
                tNo, pTestLib, initValues,
                case1Offset,
                case2Offset,
                case3Offset,
                case4Offset,
                multipleValues1,
                multipleValues2,
                multipleValues3,

                resMultiple1Case1,
                resMultiple1Case2,
                resMultiple1Case3,
                resMultiple1Case4,
                resMultiple1RevCase1,
                resMultiple1RevCase2,
                resMultiple1RevCase3,
                resMultiple1RevCase4,

                resMultiple2Case1,
                resMultiple2Case2,
                resMultiple2Case3,
                resMultiple2Case4,
                resMultiple2RevCase1,
                resMultiple2RevCase2,
                resMultiple2RevCase3,
                resMultiple2RevCase4,

                resMultiple3Case1,
                resMultiple3Case2,
                resMultiple3Case3,
                resMultiple3Case4,
                resMultiple3RevCase1,
                resMultiple3RevCase2,
                resMultiple3RevCase3,
                resMultiple3RevCase4,

                aresMultiple1Case1,
                aresMultiple1Case2,
                aresMultiple1Case3,
                aresMultiple1Case4,
                aresMultiple1RevCase1,
                aresMultiple1RevCase2,
                aresMultiple1RevCase3,
                aresMultiple1RevCase4,

                aresMultiple2Case1,
                aresMultiple2Case2,
                aresMultiple2Case3,
                aresMultiple2Case4,
                aresMultiple2RevCase1,
                aresMultiple2RevCase2,
                aresMultiple2RevCase3,
                aresMultiple2RevCase4,

                aresMultiple3Case1,
                aresMultiple3Case2,
                aresMultiple3Case3,
                aresMultiple3Case4,
                aresMultiple3RevCase1,
                aresMultiple3RevCase2,
                aresMultiple3RevCase3,
                aresMultiple3RevCase4
        ) && listTestGroupRelativeInsertionPack <
                __TestedType,
                __EnclosedType
        > (
                tNo, pTestLib, initValues,
                case1Offset, case2Offset, case3Offset, case4Offset, 
                
                resMultipleVCase1,
                resMultipleVCase2,
                resMultipleVCase3,
                resMultipleVCase4,
                resMultipleVRevCase1,
                resMultipleVRevCase2,
                resMultipleVRevCase3,
                resMultipleVRevCase4,
                
                aresMultipleVCase1,
                aresMultipleVCase2,
                aresMultipleVCase3,
                aresMultipleVCase4,
                aresMultipleVRevCase1,
                aresMultipleVRevCase2,
                aresMultipleVRevCase3,
                aresMultipleVRevCase4,

                values ...
        );
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
