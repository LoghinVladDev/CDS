/*
 * Created by loghin on 04/12/22.
 */

#ifndef __CDS_UNION_VARIADIC_UNION_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_UNION_VARIADIC_UNION_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

namespace cds {             /* NOLINT(modernize-concat-nested-namespaces) */
    namespace __hidden {    /* NOLINT(bugprone-reserved-identifier, modernize-concat-nested-namespaces, cert-dcl37-c, cert-dcl51-cpp) */
        namespace __impl {  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            template < uint32 ... >
            struct __VariadicUnionCallTableIndexSequenceType {};    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */


            template < uint32, typename >                               /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            struct __VariadicUnionCallTableIndexSequenceConcatenate {}; /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */


            template < uint32 __length, uint32 ... __indexSequence >                                                                                    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            struct __VariadicUnionCallTableIndexSequenceConcatenate < __length, __VariadicUnionCallTableIndexSequenceType < __indexSequence ... > > {   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

                using __Type = __VariadicUnionCallTableIndexSequenceType < __indexSequence ..., ( __length + __indexSequence ) ... >;                   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            };


            template < bool, typename __IndexSequenceType >                     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            struct __VariadicUnionCallTableIndexSequenceLogSplitConditional {   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

                using __Type = __IndexSequenceType;                             /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            };


            template < uint32 ... __indexSequence >                                                                                                         /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            struct __VariadicUnionCallTableIndexSequenceLogSplitConditional < true, __VariadicUnionCallTableIndexSequenceType < __indexSequence ... > > {   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

                using __Type = __VariadicUnionCallTableIndexSequenceType < __indexSequence ..., sizeof ... ( __indexSequence ) >;                           /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            };


            template < uint32 __length >                        /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            struct __VariadicUnionCallTableIndexSequenceImpl {  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

                using __Type = typename __VariadicUnionCallTableIndexSequenceLogSplitConditional <
                        __length % 2U == 1U,
                        typename __VariadicUnionCallTableIndexSequenceConcatenate <
                                __length / 2U,
                                typename __VariadicUnionCallTableIndexSequenceImpl < __length / 2U > :: __Type
                        > :: __Type
                > :: __Type;
            };


            template <>
            struct __VariadicUnionCallTableIndexSequenceImpl < 0U > {           /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

                using __Type = __VariadicUnionCallTableIndexSequenceType <>;    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            };


            struct __VariadicUnionInterfaceEntryCallTable { /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-member-init) */

                cds :: functional :: ConsumerFunction   < void *,           void const * >  _copyConstructor;
                cds :: functional :: ConsumerFunction   < void *,           void * >        _moveConstructor;
                cds :: functional :: ConsumerFunction   < void *,           void const * >  _copyAssigner;
                cds :: functional :: ConsumerFunction   < void *,           void * >        _moveAssigner;
                cds :: functional :: ConsumerFunction   < void * >                          _destructor;
                cds :: functional :: MapperFunction     < cds :: String,    void const * >  _toString;
                cds :: functional :: MapperFunction     < Size,             void const * >  _hash;
                cds :: functional :: PredicateFunction  < void const *,     void const * >  _equals;
            };


            template < typename __ElementType, uint32 __index, typename ... __EmptyTypePack >   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            struct __UnionPackTypeTraitsImpl {                                                  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

                constexpr static bool const     __directInit        = false;                    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                constexpr static bool const     __convertInit       = false;                    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                constexpr static uint32 const   __directInitIndex   = __index;                  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                constexpr static uint32 const   __convertInitIndex  = __index;                  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                using                           __DirectInitType    = void;                     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                using                           __ConvertInitType   = void;                     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            };


            template < typename __ElementType, uint32 __index, typename __FirstType, typename ... __RemainingTypes >                                        /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            struct __UnionPackTypeTraitsImpl < __ElementType, __index, __FirstType, __RemainingTypes ... > {

                using __NextEntry = __UnionPackTypeTraitsImpl < __ElementType, __index + 1U, __RemainingTypes ... >;                                        /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

                constexpr static bool const __currentDirectInit = cds :: meta :: isSame < cds :: meta :: Decay < __ElementType >, __FirstType > ();         /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                constexpr static bool const __currentConvertInit = cds :: meta :: isConvertible < cds :: meta :: Decay < __ElementType >, __FirstType > (); /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

                constexpr static bool const __directInit    =                                                                                               /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        __currentDirectInit ||
                        __NextEntry :: __directInit;

                constexpr static bool const __convertInit   =                                                                                               /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        __currentConvertInit ||
                        __NextEntry :: __convertInit;

                constexpr static uint32 const __directInitIndex = cds :: minOf (                                                                            /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        ( __currentDirectInit ? __index : __NextEntry :: __directInitIndex ),
                        __NextEntry :: __directInitIndex
                );

                constexpr static uint32 const __convertInitIndex    = cds :: minOf (                                                                        /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        ( __currentConvertInit ? __index : __NextEntry :: __convertInitIndex ),
                        __NextEntry :: __convertInitIndex
                );

                using __DirectInitType = cds :: meta :: Conditional <                                                                                       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        __currentDirectInit,
                        __FirstType,
                        typename __NextEntry :: __DirectInitType
                >;

                using __ConvertInitType = cds :: meta :: Conditional <                                                                                      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        __currentConvertInit,
                        __FirstType,
                        typename __NextEntry :: __ConvertInitType
                >;
            };


            template < uint32, uint32 __entryIndex, typename ... __EmptyTypePack >  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            struct __UnionPackIndexTraitsImpl {                                     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

                using __Type = void;                                                /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            };


            template < uint32 __seekIndex, uint32 __entryIndex, typename __FirstType, typename ... __RemainingTypes >           /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            struct __UnionPackIndexTraitsImpl < __seekIndex, __entryIndex, __FirstType, __RemainingTypes ... > {                /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

                using __NextEntry = __UnionPackIndexTraitsImpl < __seekIndex, __entryIndex + 1U, __RemainingTypes ... >;        /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

                using __Type = cds :: meta :: Conditional <                                                                     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        __seekIndex == __entryIndex,
                        __FirstType,
                        typename __NextEntry :: __Type
                >;
            };


            template < uint32, typename ... __EmptyTypePack >                   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            struct __VariadicUnionInterfaceEntryImpl {                          /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

                constexpr static bool const __entryCopyConstructible    = true; /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                constexpr static bool const __entryMoveConstructible    = true; /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                constexpr static bool const __entryCopyAssignable       = true; /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                constexpr static bool const __entryMoveAssignable       = true; /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

                constexpr static bool const __copyConstructible         = true; /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                constexpr static bool const __moveConstructible         = true; /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                constexpr static bool const __copyAssignable            = true; /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                constexpr static bool const __moveAssignable            = true; /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

                constexpr static Size const __memoryRequired        = 0ULL;     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

                __CDS_cpplang_ConstexprNonLiteralReturn static auto __destructor (      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        void * /* pObject */
                ) noexcept -> void;

                __CDS_cpplang_ConstexprNonLiteralReturn static auto __copyConstructor ( /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        void       * /* pTo */,
                        void const * /* pFrom */
                ) noexcept -> void;

                __CDS_cpplang_ConstexprNonLiteralReturn static auto __moveConstructor ( /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        void * /* pTo */,
                        void * /* pFrom */
                ) noexcept -> void;

                __CDS_cpplang_ConstexprNonLiteralReturn static auto __copyAssigner (    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        void       * /* pTo */,
                        void const * /* pFrom */
                ) noexcept -> void;

                __CDS_cpplang_ConstexprNonLiteralReturn static auto __moveAssigner (    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        void * /* pTo */,
                        void * /* pFrom */
                ) noexcept -> void;

                static auto __toString (                                                /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        void const * /* pObject */
                ) noexcept -> String;

                constexpr static auto __hash (                                          /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        void const * /* pObject */
                ) noexcept -> Size;

                constexpr static auto __equals (                                        /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        void const * /* pObject */,
                        void const * /* pOtherObject */
                ) noexcept -> bool;

                constexpr static auto __vuie_acquireCallTable (                         /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        uint32 /* holderIndex */
                ) noexcept -> __VariadicUnionInterfaceEntryCallTable const *;

                constexpr static __VariadicUnionInterfaceEntryCallTable const _entryCallTable {
                        & __VariadicUnionInterfaceEntryImpl :: __copyConstructor,
                        & __VariadicUnionInterfaceEntryImpl :: __moveConstructor,
                        & __VariadicUnionInterfaceEntryImpl :: __copyAssigner,
                        & __VariadicUnionInterfaceEntryImpl :: __moveAssigner,
                        & __VariadicUnionInterfaceEntryImpl :: __destructor,
                        & __VariadicUnionInterfaceEntryImpl :: __toString,
                        & __VariadicUnionInterfaceEntryImpl :: __hash,
                        & __VariadicUnionInterfaceEntryImpl :: __equals
                };
            };


            template < uint32 __entryIndex, typename __EntryType, typename ... __RemainingTypes >                                               /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            struct __VariadicUnionInterfaceEntryImpl < __entryIndex, __EntryType, __RemainingTypes ... > {                                      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

                using __NextEntry = __VariadicUnionInterfaceEntryImpl < __entryIndex + 1U, __RemainingTypes ... >;                              /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

                constexpr static bool const __entryCopyConstructible    = cds :: meta :: isCopyConstructible < __EntryType > ();                /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                constexpr static bool const __entryMoveConstructible    = cds :: meta :: isMoveConstructible < __EntryType > ();                /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                constexpr static bool const __entryCopyAssignable       = cds :: meta :: isCopyAssignable < __EntryType > ();                   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                constexpr static bool const __entryMoveAssignable       = cds :: meta :: isMoveAssignable < __EntryType > ();                   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

                constexpr static bool const __copyConstructible         = __entryCopyConstructible  && __NextEntry :: __copyConstructible;      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                constexpr static bool const __moveConstructible         = __entryMoveConstructible  && __NextEntry :: __moveConstructible;      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                constexpr static bool const __copyAssignable            = __entryCopyAssignable     && __NextEntry :: __copyAssignable;         /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                constexpr static bool const __moveAssignable            = __entryMoveAssignable     && __NextEntry :: __moveAssignable;         /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

                constexpr static Size const __memoryRequired        = cds :: maxOf ( sizeof ( __EntryType ), __NextEntry :: __memoryRequired ); /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

                __CDS_cpplang_ConstexprNonLiteralReturn static auto __destructor (      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        void * pObject
                ) noexcept -> void;

                __CDS_cpplang_ConstexprNonLiteralReturn static auto __copyConstructor ( /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        void       * pTo,
                        void const * pFrom
                ) noexcept -> void;

                __CDS_cpplang_ConstexprNonLiteralReturn static auto __moveConstructor ( /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        void * pTo,
                        void * pFrom
                ) noexcept -> void;

                __CDS_cpplang_ConstexprNonLiteralReturn static auto __copyAssigner (    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        void       * pTo,
                        void const * pFrom
                ) noexcept -> void;

                __CDS_cpplang_ConstexprNonLiteralReturn static auto __moveAssigner (    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        void * pTo,
                        void * pFrom
                ) noexcept -> void;

                static auto __toString (                                                /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        void const * pObject
                ) noexcept -> String;

                constexpr static auto __hash (                                          /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        void const * pObject
                ) noexcept -> Size;

                constexpr static auto __equals (                                        /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        void const * pObject,
                        void const * pOtherObject
                ) noexcept -> bool;

                constexpr static auto __vuie_acquireCallTable (                         /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        uint32 holderIndex
                ) noexcept -> __VariadicUnionInterfaceEntryCallTable const *;

                constexpr static __VariadicUnionInterfaceEntryCallTable const _entryCallTable {
                        & __VariadicUnionInterfaceEntryImpl :: __copyConstructor,
                        & __VariadicUnionInterfaceEntryImpl :: __moveConstructor,
                        & __VariadicUnionInterfaceEntryImpl :: __copyAssigner,
                        & __VariadicUnionInterfaceEntryImpl :: __moveAssigner,
                        & __VariadicUnionInterfaceEntryImpl :: __destructor,
                        & __VariadicUnionInterfaceEntryImpl :: __toString,
                        & __VariadicUnionInterfaceEntryImpl :: __hash,
                        & __VariadicUnionInterfaceEntryImpl :: __equals
                };
            };


            template < typename __ElementType, typename ... __Types >                                       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            struct __UnionPackTypeTraits : __UnionPackTypeTraitsImpl < __ElementType, 0U, __Types ... > {}; /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */


            template < uint32 __seekIndex, typename ... __Types >                                           /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            struct __UnionPackIndexTraits : __UnionPackIndexTraitsImpl < __seekIndex, 0U, __Types ... > {}; /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */


            template < typename ... __Types >                                                                   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            struct __VariadicUnionInterfaceEntry : __VariadicUnionInterfaceEntryImpl < 0U, __Types ... > {};    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */


            template < uint32 __length >                                                                                                    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            using __VariadicUnionCallTableIndexSequence = typename __VariadicUnionCallTableIndexSequenceImpl < __length + 1U > :: __Type;   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */


            template < typename ... __Types >   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            class __VariadicUnion {             /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-member-functions, *-member-init) */

            private:                                                                                                /* NOLINT(readability-redundant-access-specifiers) */
                using __CallTableIndexSequence = __VariadicUnionCallTableIndexSequence < sizeof ... (__Types) >;    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            private:                                                                        /* NOLINT(readability-redundant-access-specifiers) */
                using __InterfaceEntryList = __VariadicUnionInterfaceEntry < __Types ... >; /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            private:                                    /* NOLINT(readability-redundant-access-specifiers) */
                template < uint32 ... __indexSequence > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                struct __CallTable {                    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

                    constexpr static __VariadicUnionInterfaceEntryCallTable const * const _callTable [sizeof ... (__Types) + 1U] = { /* NOLINT(*-avoid-c-arrays) */
                            __InterfaceEntryList :: __vuie_acquireCallTable ( __indexSequence ) ...
                    };
                };

            private:                                                                        /* NOLINT(readability-redundant-access-specifiers) */
                constexpr static uint32 const __vu_valuelessHolder = sizeof ... (__Types);  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            private:    /* NOLINT(readability-redundant-access-specifiers) */
                uint32 _holder { __VariadicUnion :: __vu_valuelessHolder };

            private:    /* NOLINT(readability-redundant-access-specifiers) */
                uint8  _memory [ __InterfaceEntryList :: __memoryRequired ];

            protected:  /* NOLINT(readability-redundant-access-specifiers) */
                __VariadicUnion () noexcept = default;

            protected:                                                              /* NOLINT(readability-redundant-access-specifiers) */
                __CDS_cpplang_ConstexprConstructorNonEmptyBody __VariadicUnion (    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        __VariadicUnion const & object
                ) noexcept;

            protected:                                                              /* NOLINT(readability-redundant-access-specifiers) */
                __CDS_cpplang_ConstexprConstructorNonEmptyBody __VariadicUnion (    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        __VariadicUnion && object
                ) noexcept;

            protected:                                                                                                      /* NOLINT(readability-redundant-access-specifiers) */
                template <
                        typename __TargetElementType,                                                                       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        typename __UnionTargetPackTypeTraits = __UnionPackTypeTraits < __TargetElementType, __Types ... >,  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        cds :: meta :: EnableIf <
                                ! cds :: meta :: isSame < cds :: meta :: Decay < __TargetElementType >, __VariadicUnion < __Types ... > > () &&
                                __UnionTargetPackTypeTraits :: __directInit
                        > = 0
                > __CDS_cpplang_ConstexprConstructorNonEmptyBody __VariadicUnion (
                        __TargetElementType && element
                ) noexcept;

            protected:                                                                                                      /* NOLINT(readability-redundant-access-specifiers) */
                template <
                        typename __TargetElementType,                                                                       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        typename __UnionTargetPackTypeTraits = __UnionPackTypeTraits < __TargetElementType, __Types ... >,  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        cds :: meta :: EnableIf <
                                ! cds :: meta :: isSame < cds :: meta :: Decay < __TargetElementType >, __VariadicUnion < __Types ... > > () &&
                                ! __UnionTargetPackTypeTraits :: __directInit &&
                                        __UnionTargetPackTypeTraits :: __convertInit
                        > = 0
                > __CDS_cpplang_ConstexprConstructorNonEmptyBody __VariadicUnion (
                        __TargetElementType && element
                ) noexcept;

            protected:                                                                                                      /* NOLINT(readability-redundant-access-specifiers) */
                template <
                        typename __TargetElementType,                                                                       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        typename __UnionTargetPackTypeTraits = __UnionPackTypeTraits < __TargetElementType, __Types ... >,  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        cds :: meta :: EnableIf <
                                ! cds :: meta :: isSame < cds :: meta :: Decay < __TargetElementType >, __VariadicUnion < __Types ... > > () &&
                                ! __UnionTargetPackTypeTraits :: __directInit &&
                                ! __UnionTargetPackTypeTraits :: __convertInit
                        > = 0
                > __CDS_cpplang_ConstexprConstructorNonEmptyBody __VariadicUnion (
                        __TargetElementType && /* element */
                ) noexcept;

            public:                                                             /* NOLINT(readability-redundant-access-specifiers) */
                __CDS_cpplang_ConstexprDestructor ~__VariadicUnion () noexcept; /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            public:                                                             /* NOLINT(readability-redundant-access-specifiers) */
                __CDS_cpplang_NonConstConstexprMemberFunction auto operator = ( /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-copy-assignment-signature, *-assign-operator) */
                        __VariadicUnion const & object
                ) noexcept -> __VariadicUnion &;

            public:                                                             /* NOLINT(readability-redundant-access-specifiers) */
                __CDS_cpplang_NonConstConstexprMemberFunction auto operator = ( /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-copy-assignment-signature, *-assign-operator) */
                        __VariadicUnion && object
                ) noexcept -> __VariadicUnion &;

            private:                                                    /* NOLINT(readability-redundant-access-specifiers) */
                template < uint32 ... __indexSequence >                 /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                __CDS_NoDiscard constexpr static auto __vu_callTable (  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        uint32                                                                  holder,
                        __VariadicUnionCallTableIndexSequenceType < __indexSequence ... >    /* ignored */
                ) noexcept -> __VariadicUnionInterfaceEntryCallTable const *;

            protected:                                                                      /* NOLINT(readability-redundant-access-specifiers) */
                __CDS_NoDiscard constexpr auto __vu_valueless () const noexcept -> bool;    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            protected:                                                                  /* NOLINT(readability-redundant-access-specifiers) */
                __CDS_NoDiscard constexpr auto __vu_holder () const noexcept -> uint32; /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            protected:                                                                                                      /* NOLINT(readability-redundant-access-specifiers) */
                template <
                        typename __TargetElementType,                                                                       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        typename __UnionTargetPackTypeTraits = __UnionPackTypeTraits < __TargetElementType, __Types ... >,  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        cds :: meta :: EnableIf <
                                ! cds :: meta :: isSame < cds :: meta :: Decay < __TargetElementType >, __VariadicUnion < __Types ... > > () &&
                                        __UnionTargetPackTypeTraits :: __directInit
                        > = 0
                > __CDS_cpplang_NonConstConstexprMemberFunction auto __vu_reset (                                           /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        __TargetElementType && element
                ) noexcept -> void;

            protected:                                                                                                      /* NOLINT(readability-redundant-access-specifiers) */
                template <
                        typename __TargetElementType,                                                                       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        typename __UnionTargetPackTypeTraits = __UnionPackTypeTraits < __TargetElementType, __Types ... >,  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        cds :: meta :: EnableIf <
                                ! cds :: meta :: isSame < cds :: meta :: Decay < __TargetElementType >, __VariadicUnion < __Types ... > > () &&
                                ! __UnionTargetPackTypeTraits :: __directInit &&
                                        __UnionTargetPackTypeTraits :: __convertInit
                        > = 0
                > __CDS_cpplang_NonConstConstexprMemberFunction auto __vu_reset (                                           /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        __TargetElementType && element
                ) noexcept -> void;

            protected:                                                                                                      /* NOLINT(readability-redundant-access-specifiers) */
                template <
                        typename __TargetElementType,                                                                       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        typename __UnionTargetPackTypeTraits = __UnionPackTypeTraits < __TargetElementType, __Types ... >,  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        cds :: meta :: EnableIf <
                                ! cds :: meta :: isSame < cds :: meta :: Decay < __TargetElementType >, __VariadicUnion < __Types ... > > () &&
                                ! __UnionTargetPackTypeTraits :: __directInit &&
                                ! __UnionTargetPackTypeTraits :: __convertInit
                        > = 0
                > __CDS_cpplang_NonConstConstexprMemberFunction auto __vu_reset (                                           /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        __TargetElementType && element
                ) noexcept -> void;

            protected:                                                              /* NOLINT(readability-redundant-access-specifiers) */
                template <
                        typename     __TargetElementType,                           /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        typename ... __ConstructionArguments                        /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                > __CDS_cpplang_NonConstConstexprMemberFunction auto __vu_emplace ( /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        __ConstructionArguments && ... arguments
                ) noexcept -> cds :: meta :: EnableIf <
                        __UnionPackTypeTraits < __TargetElementType, __Types ... > :: __directInit,
                        typename __UnionPackTypeTraits < __TargetElementType, __Types ... > :: __DirectInitType &
                >;

            protected:                                                              /* NOLINT(readability-redundant-access-specifiers) */
                template <
                        typename     __TargetElementType,                           /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        typename ... __ConstructionArguments                        /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                > __CDS_cpplang_NonConstConstexprMemberFunction auto __vu_emplace ( /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        __ConstructionArguments && ... arguments
                ) noexcept -> cds :: meta :: EnableIf <
                        ! __UnionPackTypeTraits < __TargetElementType, __Types ... > :: __directInit,
                        __TargetElementType &
                >;

            protected:                                                                              /* NOLINT(readability-redundant-access-specifiers) */
                template < typename __ElementType >                                                 /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                __CDS_cpplang_ConstexprConditioned auto __vu_get () noexcept -> __ElementType *;    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            protected:                                                                                              /* NOLINT(readability-redundant-access-specifiers) */
                template < typename __ElementType >                                                                 /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                __CDS_cpplang_ConstexprConditioned auto __vu_getConst () const noexcept -> __ElementType const *;   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            protected:                                                          /* NOLINT(readability-redundant-access-specifiers) */
                __CDS_NoDiscard auto __vu_toString () const noexcept -> String; /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            protected:                                                              /* NOLINT(readability-redundant-access-specifiers) */
                __CDS_NoDiscard constexpr auto __vu_hash () const noexcept -> Size; /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            protected:                                          /* NOLINT(readability-redundant-access-specifiers) */
                __CDS_NoDiscard constexpr auto __vu_equals (    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        __VariadicUnion const & otherUnion
                ) const noexcept -> bool;
            };


            template < typename __ElementType, cds :: meta :: EnableIf < cds :: meta :: isCopyConstructible < __ElementType > () > = 0 >    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            __CDS_cpplang_ConstexprNonLiteralReturn static auto __variadicUnionInterfaceLateCopyConstruct (                                 /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    void       * pTo,
                    void const * pFrom
            ) noexcept -> void;

            template < typename __ElementType, cds :: meta :: EnableIf < ! cds :: meta :: isCopyConstructible < __ElementType > () > = 0 >  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            __CDS_cpplang_ConstexprNonLiteralReturn static auto __variadicUnionInterfaceLateCopyConstruct (                                 /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    void       * pTo,
                    void const * pFrom
            ) noexcept -> void;

            template < typename __ElementType, cds :: meta :: EnableIf < cds :: meta :: isMoveConstructible < __ElementType > () > = 0 >    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            __CDS_cpplang_ConstexprNonLiteralReturn static auto __variadicUnionInterfaceLateMoveConstruct (                                 /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    void * pTo,
                    void * pFrom
            ) noexcept -> void;

            template < typename __ElementType, cds :: meta :: EnableIf < ! cds :: meta :: isMoveConstructible < __ElementType > () > = 0 >  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            __CDS_cpplang_ConstexprNonLiteralReturn static auto __variadicUnionInterfaceLateMoveConstruct (                                 /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    void * pTo,
                    void * pFrom
            ) noexcept -> void;

            template < typename __ElementType, cds :: meta :: EnableIf < cds :: meta :: isCopyAssignable < __ElementType > () > = 0 >   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            __CDS_cpplang_ConstexprNonLiteralReturn static auto __variadicUnionInterfaceLateCopyAssign (                                /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    void       * pTo,
                    void const * pFrom
            ) noexcept -> void;

            template < typename __ElementType, cds :: meta :: EnableIf < ! cds :: meta :: isCopyAssignable < __ElementType > () > = 0 > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            __CDS_cpplang_ConstexprNonLiteralReturn static auto __variadicUnionInterfaceLateCopyAssign (                                /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    void       * pTo,
                    void const * pFrom
            ) noexcept -> void;

            template < typename __ElementType, cds :: meta :: EnableIf < cds :: meta :: isMoveAssignable < __ElementType > () > = 0 >   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            __CDS_cpplang_ConstexprNonLiteralReturn static auto __variadicUnionInterfaceLateMoveAssign (                                /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    void * pTo,
                    void * pFrom
            ) noexcept -> void;

            template < typename __ElementType, cds :: meta :: EnableIf < ! cds :: meta :: isMoveAssignable < __ElementType > () > = 0 > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            __CDS_cpplang_ConstexprNonLiteralReturn static auto __variadicUnionInterfaceLateMoveAssign (                                /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    void * pTo,
                    void * pFrom
            ) noexcept -> void;

        } /* namespace __impl */
    } /* namespace __hidden */
} /* namespace cds */

#endif /* __CDS_UNION_VARIADIC_UNION_HPP__ */
