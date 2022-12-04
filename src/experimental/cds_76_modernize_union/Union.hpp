/*
 * Created by loghin on 11.10.2021.
 */

#ifndef __CDS_UNION_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_UNION_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

#include <CDS/Object>
#include <CDS/FunctionalInterface>

namespace cds {

    namespace __hidden {
        namespace __impl {

            template < uint32 __index, typename __ElementType, typename ... __EmptyTypePack >
            struct __UnionInitTraitsImpl {

                constexpr static bool const     __directInit        = false;
                constexpr static bool const     __convertInit       = false;
                constexpr static uint32 const   __directInitIndex   = __index;
                constexpr static uint32 const   __convertInitIndex  = __index;
                using                           __DirectInitType    = void;
                using                           __ConvertInitType   = void;
            };


            template < uint32 __index, typename __ElementType, typename __FirstType, typename ... __RemainingTypes >
            struct __UnionInitTraitsImpl < __index, __ElementType, __FirstType, __RemainingTypes ... > {

                using __NextEntryTraits = __UnionInitTraitsImpl < __index + 1U, __ElementType, __RemainingTypes ... >;

                constexpr static bool const __currentDirectInit = cds :: meta :: isSame < cds :: meta :: Decay < __ElementType >, __FirstType > ();
                constexpr static bool const __currentConvertInit = cds :: meta :: isConvertible < cds :: meta :: Decay < __ElementType >, __FirstType > ();


                constexpr static bool const __directInit    =
                        __currentDirectInit ||
                        __NextEntryTraits :: __directInit;

                constexpr static bool const __convertInit   =
                        __currentConvertInit ||
                        __NextEntryTraits  :: __convertInit;

                constexpr static uint32 const __directInitIndex = cds :: minOf (
                        ( __currentDirectInit ? __index : __NextEntryTraits  :: __directInitIndex ),
                        __NextEntryTraits  :: __directInitIndex
                );

                constexpr static uint32 const __convertInitIndex    = cds :: minOf (
                        ( __currentConvertInit ? __index : __NextEntryTraits  :: __convertInitIndex ),
                        __NextEntryTraits  :: __convertInitIndex
                );

                using __DirectInitType = cds :: meta :: Conditional <
                        __currentDirectInit,
                        __FirstType,
                        typename __NextEntryTraits  :: __DirectInitType
                >;

                using __ConvertInitType = cds :: meta :: Conditional <
                        __currentConvertInit,
                        __FirstType,
                        typename __NextEntryTraits  :: __ConvertInitType
                >;
            };


            template < typename __ElementType, typename ... __Types >
            struct __UnionInitTraits : __UnionInitTraitsImpl < 0U, __ElementType, __Types ... > {};


            template < uint32, uint32 __index, typename ... __EmptyTypePack >
            struct __UnionIndexTraitsImpl {

                using __Type = void;
            };


            template < uint32 __requestedIndex, uint32 __index, typename __FirstType, typename ... __RemainingTypes >
            struct __UnionIndexTraitsImpl < __requestedIndex, __index, __FirstType, __RemainingTypes ... > {

                using __NextEntryTraits = __UnionIndexTraitsImpl < __requestedIndex, __index + 1U, __RemainingTypes ... >;

                using __Type = cds :: meta :: Conditional <
                        __requestedIndex == __index,
                        __FirstType,
                        typename __NextEntryTraits :: __Type
                >;
            };


            template < uint32 __requestedIndex, typename ... __Types >
            struct __UnionIndexTraits : __UnionIndexTraitsImpl < __requestedIndex, 0U, __Types ... > {};


            struct __VariadicUnionCallGroup {

                cds :: functional :: ConsumerFunction < void *, void const * >          _copyConstructor;
                cds :: functional :: ConsumerFunction < void *, void * >                _moveConstructor;
                cds :: functional :: ConsumerFunction < void *, void const * >          _copyAssigner;
                cds :: functional :: ConsumerFunction < void *, void * >                _moveAssigner;
                cds :: functional :: ConsumerFunction < void * >                        _destructor;
                cds :: functional :: MapperFunction < cds :: String, void const * >     _toString;
                cds :: functional :: MapperFunction < Size, void const * >              _hash;
                cds :: functional :: PredicateFunction < void const *, void const * >   _equals;
            };


            template < uint32 __index, typename ... __EmptyTypePack >
            struct __VariadicUnionEntryImpl {

                constexpr static bool const __entryCopyConstructible    = true;
                constexpr static bool const __entryMoveConstructible    = true;
                constexpr static bool const __entryCopyAssignable       = true;
                constexpr static bool const __entryMoveAssignable       = true;

                constexpr static bool const __copyConstructible         = true;
                constexpr static bool const __moveConstructible         = true;
                constexpr static bool const __copyAssignable            = true;
                constexpr static bool const __moveAssignable            = true;

                constexpr static Size const __memoryRequired        = 0ULL;

                __CDS_cpplang_ConstexprNonLiteralReturn static auto __vue_destructor (
                        void * /* pUncastedObject */
                ) noexcept -> void {

                    /* do nothing, nothing to destroy */
                }

                __CDS_cpplang_ConstexprNonLiteralReturn static auto __vue_copyConstructor (
                        void       * /* pTo */,
                        void const * /* pFrom */
                ) noexcept -> void {

                    /* do nothing, nothing to copy */
                }

                __CDS_cpplang_ConstexprNonLiteralReturn static auto __vue_moveConstructor (
                        void * /* pTo */,
                        void * /* pFrom */
                ) noexcept -> void {

                    /* do nothing, nothing to move */
                }

                __CDS_cpplang_ConstexprNonLiteralReturn static auto __vue_copyAssigner (
                        void       * /* pTo */,
                        void const * /* pFrom */
                ) noexcept -> void {

                    /* do nothing, nothing to copy */
                }

                __CDS_cpplang_ConstexprNonLiteralReturn static auto __vue_moveAssigner (
                        void * /* pTo */,
                        void * /* pFrom */
                ) noexcept -> void {

                    /* do nothing, nothing to move */
                }

                inline static auto __vue_toString (
                        void const * /* pObject */
                ) noexcept -> String {

                    return "null";
                }

                constexpr static auto __vue_hash (
                        void const * /* pObject */
                ) noexcept -> Size {

                    return 0ULL;
                }

                constexpr static auto __vue_equals (
                        void const *, /* pObject */
                        void const *  /* pOtherObject */
                ) noexcept -> bool {

                    return true;
                }


                constexpr static __VariadicUnionCallGroup const _callGroup {
                    & __VariadicUnionEntryImpl :: __vue_copyConstructor,
                    & __VariadicUnionEntryImpl :: __vue_moveConstructor,
                    & __VariadicUnionEntryImpl :: __vue_copyAssigner,
                    & __VariadicUnionEntryImpl :: __vue_moveAssigner,
                    & __VariadicUnionEntryImpl :: __vue_destructor,
                    & __VariadicUnionEntryImpl :: __vue_toString,
                    & __VariadicUnionEntryImpl :: __vue_hash,
                    & __VariadicUnionEntryImpl :: __vue_equals
                };


                constexpr static auto __vue_acquireCallGroup (
                        uint32 /* activeIndex */
                ) noexcept -> __VariadicUnionCallGroup const * {

                    return & __VariadicUnionEntryImpl :: _callGroup;
                }
            };


            template < typename __ElementType, cds :: meta :: EnableIf < cds :: meta :: isCopyConstructible < __ElementType > () > = 0 >
            __CDS_cpplang_ConstexprNonLiteralReturn static auto __variadicUnionLateCopyConstruct (
                    void       * pTo,
                    void const * pFrom
            ) noexcept -> void {

                new ( static_cast < __ElementType * > ( pTo ) ) __ElementType ( * static_cast < __ElementType const * > ( pFrom ) );
            }


            template < typename __ElementType, cds :: meta :: EnableIf < ! cds :: meta :: isCopyConstructible < __ElementType > () > = 0 >
            __CDS_cpplang_ConstexprNonLiteralReturn static auto __variadicUnionLateCopyConstruct (
                    void       * pTo,
                    void const * pFrom
            ) noexcept -> void {

                /* Nothing done. Assert done in class */
            }


            template < typename __ElementType, cds :: meta :: EnableIf < cds :: meta :: isMoveConstructible < __ElementType > () > = 0 >
            __CDS_cpplang_ConstexprNonLiteralReturn static auto __variadicUnionLateMoveConstruct (
                    void * pTo,
                    void * pFrom
            ) noexcept -> void {

                new ( static_cast < __ElementType * > ( pTo ) ) __ElementType ( std :: move ( * static_cast < __ElementType * > ( pFrom ) ) );
            }


            template < typename __ElementType, cds :: meta :: EnableIf < ! cds :: meta :: isMoveConstructible < __ElementType > () > = 0 >
            __CDS_cpplang_ConstexprNonLiteralReturn static auto __variadicUnionLateMoveConstruct (
                    void * pTo,
                    void * pFrom
            ) noexcept -> void {

                /* Nothing done. Assert done in class */
            }


            template < typename __ElementType, cds :: meta :: EnableIf < cds :: meta :: isCopyAssignable < __ElementType > () > = 0 >
            __CDS_cpplang_ConstexprNonLiteralReturn static auto __variadicUnionLateCopyAssign (
                    void       * pTo,
                    void const * pFrom
            ) noexcept -> void {

                * static_cast < __ElementType * > ( pTo ) = * static_cast < __ElementType const * > ( pFrom );
            }


            template < typename __ElementType, cds :: meta :: EnableIf < ! cds :: meta :: isCopyAssignable < __ElementType > () > = 0 >
            __CDS_cpplang_ConstexprNonLiteralReturn static auto __variadicUnionLateCopyAssign (
                    void       * pTo,
                    void const * pFrom
            ) noexcept -> void {

                /* Nothing done. Assert done in class */
            }


            template < typename __ElementType, cds :: meta :: EnableIf < cds :: meta :: isMoveAssignable < __ElementType > () > = 0 >
            __CDS_cpplang_ConstexprNonLiteralReturn static auto __variadicUnionLateMoveAssign (
                    void * pTo,
                    void * pFrom
            ) noexcept -> void {

                * static_cast < __ElementType * > ( pTo ) = std :: move ( * static_cast < __ElementType * > ( pFrom ) );
            }


            template < typename __ElementType, cds :: meta :: EnableIf < ! cds :: meta :: isMoveAssignable < __ElementType > () > = 0 >
            __CDS_cpplang_ConstexprNonLiteralReturn static auto __variadicUnionLateMoveAssign (
                    void * pTo,
                    void * pFrom
            ) noexcept -> void {

                /* Nothing done. Assert done in class */
            }


            template < uint32 __index, typename __FirstType, typename ... __RemainingTypes >
            struct __VariadicUnionEntryImpl < __index, __FirstType, __RemainingTypes ... > : __VariadicUnionEntryImpl < __index + 1U, __RemainingTypes ... > {

                using __NextEntry = __VariadicUnionEntryImpl < __index + 1U, __RemainingTypes ... >;

                constexpr static bool const __entryCopyConstructible    = cds :: meta :: isCopyConstructible < __FirstType > ();
                constexpr static bool const __entryMoveConstructible    = cds :: meta :: isMoveConstructible < __FirstType > ();
                constexpr static bool const __entryCopyAssignable       = cds :: meta :: isCopyAssignable < __FirstType > ();
                constexpr static bool const __entryMoveAssignable       = cds :: meta :: isMoveAssignable < __FirstType > ();

                constexpr static bool const __copyConstructible         = __entryCopyConstructible  && __NextEntry :: __copyConstructible;
                constexpr static bool const __moveConstructible         = __entryMoveConstructible  && __NextEntry :: __moveConstructible;
                constexpr static bool const __copyAssignable            = __entryCopyAssignable     && __NextEntry :: __copyAssignable;
                constexpr static bool const __moveAssignable            = __entryMoveAssignable     && __NextEntry :: __moveAssignable;

                constexpr static Size const __memoryRequired        = cds :: maxOf ( sizeof ( __FirstType ), __NextEntry :: __memoryRequired );

                __CDS_cpplang_ConstexprNonLiteralReturn static auto __vue_destructor (
                        void * pObject
                ) noexcept -> void {

                    static_cast < __FirstType * > ( pObject )->~__FirstType ();
                }

                __CDS_cpplang_ConstexprNonLiteralReturn static auto __vue_copyConstructor (
                        void       * pTo,
                        void const * pFrom
                ) noexcept -> void {

                    __variadicUnionLateCopyConstruct < __FirstType > ( pTo, pFrom );
                }

                __CDS_cpplang_ConstexprNonLiteralReturn static auto __vue_moveConstructor (
                        void * pTo,
                        void * pFrom
                ) noexcept -> void {

                    __variadicUnionLateMoveConstruct < __FirstType > ( pTo, pFrom );
                }

                __CDS_cpplang_ConstexprNonLiteralReturn static auto __vue_copyAssigner (
                        void       * pTo,
                        void const * pFrom
                ) noexcept -> void {

                    __variadicUnionLateCopyAssign < __FirstType > ( pTo, pFrom );
                }

                __CDS_cpplang_ConstexprNonLiteralReturn static auto __vue_moveAssigner (
                        void * pTo,
                        void * pFrom
                ) noexcept -> void {

                    __variadicUnionLateMoveAssign < __FirstType > ( pTo, pFrom );
                }

                inline static auto __vue_toString (
                        void const * pObject
                ) noexcept -> String {

                    std :: stringstream oss;
                    cds :: streamPrint ( oss, * static_cast < __FirstType const * > ( pObject ) );
                    return oss.str();
                }

                inline static auto __vue_hash (
                        void const * pObject
                ) noexcept -> Size {

                    return cds :: Hash < __FirstType > :: hash ( * static_cast < __FirstType const * > ( pObject ) );
                }

                inline static auto __vue_equals (
                        void const * pObject,
                        void const * pOtherObject
                ) noexcept -> bool {

                    return cds :: meta :: equals (
                            * static_cast < __FirstType const * > ( pObject ),
                            * static_cast < __FirstType const * > ( pOtherObject )
                    );
                }


                constexpr static __VariadicUnionCallGroup const _callGroup {
                        & __VariadicUnionEntryImpl :: __vue_copyConstructor,
                        & __VariadicUnionEntryImpl :: __vue_moveConstructor,
                        & __VariadicUnionEntryImpl :: __vue_copyAssigner,
                        & __VariadicUnionEntryImpl :: __vue_moveAssigner,
                        & __VariadicUnionEntryImpl :: __vue_destructor,
                        & __VariadicUnionEntryImpl :: __vue_toString,
                        & __VariadicUnionEntryImpl :: __vue_hash,
                        & __VariadicUnionEntryImpl :: __vue_equals
                };


                constexpr static auto __vue_acquireCallGroup (
                        uint32 activeIndex
                ) noexcept -> __VariadicUnionCallGroup const * {

                    return
                            activeIndex == __index ?
                            & __VariadicUnionEntryImpl :: _callGroup :
                            __NextEntry :: __vue_acquireCallGroup ( activeIndex );
                }
            };


            template < typename ... __Types >
            struct __VariadicUnionEntry : __VariadicUnionEntryImpl < 0U, __Types ... > {};


            template < uint32 ... > struct __VariadicUnionIndexSequenceType {};


            template < uint32, typename >
            struct __VariadicUnionIndexSequenceConcat;


            template < uint32 __n, uint32 ... __sequence >
            struct __VariadicUnionIndexSequenceConcat < __n, __VariadicUnionIndexSequenceType < __sequence ... > > {
                using __Type = __VariadicUnionIndexSequenceType < __sequence ..., (__n + __sequence) ... >;
            };


            template < bool, typename __Sequence >
            struct __VariadicUnionIndexSequenceLogConditional {
                using __Type = __Sequence;
            };


            template < uint32 ... __sequence >
            struct __VariadicUnionIndexSequenceLogConditional < true, __VariadicUnionIndexSequenceType < __sequence ... > > {
                using __Type = __VariadicUnionIndexSequenceType < __sequence ..., sizeof ... ( __sequence ) >;
            };


            template < uint32 __n >
            struct __VariadicUnionIndexSequence {
                using __Type = typename __VariadicUnionIndexSequenceLogConditional <
                        ( __n % 2U != 0U ),
                        typename __VariadicUnionIndexSequenceConcat <
                                __n / 2U,
                                typename __VariadicUnionIndexSequence < __n / 2U > :: __Type
                        > :: __Type
                > :: __Type;
            };


            template <>
            struct __VariadicUnionIndexSequence < 0U > {
                using __Type = __VariadicUnionIndexSequenceType <>;
            };


            template < typename ... __Types >
            struct __VariadicUnion {

                using __EntryList = __VariadicUnionEntry < __Types ... >;

                template < uint32 ... __sequence >
                struct __VariadicUnionCallTable {

                    constexpr static __VariadicUnionCallGroup const * const _callTable [] = {
                            __EntryList :: __vue_acquireCallGroup ( __sequence ) ...
                    };
                };

                template < uint32 ... __sequence >
                constexpr static auto __vu_callGroup (
                        uint32 index,
                        __VariadicUnionIndexSequenceType < __sequence ... >
                ) noexcept -> __VariadicUnionCallGroup const * {

                    return __VariadicUnionCallTable < __sequence ... > :: _callTable [index];
                }

                uint32 _holder { sizeof ... ( __Types ) };
                uint8  _memory [ __EntryList :: __memoryRequired ];

                constexpr static uint32 const __vu_valuelessHolder = sizeof ... (__Types);

                __CDS_NoDiscard constexpr auto __vu_valueless () const noexcept -> bool {

                    return this->_holder == __VariadicUnion :: __vu_valuelessHolder;
                }

                template <
                        typename __TargetElementType,
                        typename __UnionTargetInitTraits = __UnionInitTraits < __TargetElementType, __Types ... >,
                        cds :: meta :: EnableIf <
                                ! cds :: meta :: isSame < cds :: meta :: Decay < __TargetElementType >, __VariadicUnion < __Types ... > > () &&
                                __UnionTargetInitTraits :: __directInit
                        > = 0
                > __CDS_cpplang_ConstexprConstructorNonEmptyBody __VariadicUnion (
                        __TargetElementType && element
                ) noexcept :
                        _holder ( __UnionTargetInitTraits :: __directInitIndex ) {

                    (void) new ( & this->_memory [0U] ) typename __UnionTargetInitTraits :: __DirectInitType ( std :: forward < __TargetElementType > ( element ) );
                }


                template <
                        typename __TargetElementType,
                        typename __UnionTargetInitTraits = __UnionInitTraits < __TargetElementType, __Types ... >,
                        cds :: meta :: EnableIf <
                                ! cds :: meta :: isSame < cds :: meta :: Decay < __TargetElementType >, __VariadicUnion < __Types ... > > () &&
                                ! __UnionTargetInitTraits :: __directInit &&
                                __UnionTargetInitTraits :: __convertInit
                        > = 0
                > __CDS_cpplang_ConstexprConstructorNonEmptyBody __VariadicUnion (
                        __TargetElementType && element
                ) noexcept :
                        _holder ( __UnionTargetInitTraits :: __convertInitIndex ) {

                    (void) new ( & this->_memory [0U] ) typename __UnionTargetInitTraits :: __ConvertInitType ( std :: forward < __TargetElementType > ( element ) );
                }


                template <
                        typename __TargetElementType,
                        typename __UnionTargetInitTraits = __UnionInitTraits < __TargetElementType, __Types ... >,
                        cds :: meta :: EnableIf <
                                ! cds :: meta :: isSame < cds :: meta :: Decay < __TargetElementType >, __VariadicUnion < __Types ... > > () &&
                                ! __UnionTargetInitTraits :: __directInit &&
                                ! __UnionTargetInitTraits :: __convertInit
                        > = 0
                > __CDS_cpplang_ConstexprConstructorNonEmptyBody __VariadicUnion (
                        __TargetElementType && element
                ) noexcept {

                    static_assert (
                            __UnionTargetInitTraits :: __directInit ||
                            __UnionTargetInitTraits :: __convertInit,
                            "Union cannot be constructed from given value due to none of its' variants "
                            "having a direct or conversion constructor for the requested value"
                    );
                }


                __CDS_cpplang_ConstexprDestructor ~__VariadicUnion () noexcept {

                    __VariadicUnion :: __vu_callGroup ( this->_holder, typename __VariadicUnionIndexSequence < sizeof ... (__Types) + 1U > :: __Type () )->_destructor (
                            static_cast < void * > ( & this->_memory [0U] )
                    );
                }


                __VariadicUnion () noexcept = default;


                __CDS_cpplang_ConstexprConstructorNonEmptyBody __VariadicUnion (
                        __VariadicUnion const & object
                ) noexcept :
                        _holder ( object._holder ) {

                    static_assert (
                            __EntryList :: __copyConstructible,
                            "For Union to be Copy Constructible, all of its' type variants must be Copy Constructible"
                    );

                    __VariadicUnion :: __vu_callGroup ( this->_holder, typename __VariadicUnionIndexSequence < sizeof ... (__Types) + 1U > :: __Type () )->_copyConstructor (
                            static_cast < void * > ( & this->_memory [0U] ),
                            static_cast < void const * > ( & object._memory [0U] )
                    );
                }


                __CDS_cpplang_ConstexprConstructorNonEmptyBody __VariadicUnion (
                        __VariadicUnion && object
                ) noexcept :
                        _holder ( cds :: exchange ( object._holder, __VariadicUnion :: __vu_valuelessHolder ) ){

                    static_assert (
                            __EntryList :: __moveConstructible,
                            "For Union to be Move Constructible, all of its' type variants must be Move Constructible"
                    );

                    __VariadicUnion :: __vu_callGroup ( this->_holder, typename __VariadicUnionIndexSequence < sizeof ... (__Types) + 1U > :: __Type () )->_moveConstructor (
                            static_cast < void * > ( & this->_memory [0U] ),
                            static_cast < void * > ( & object._memory [0U] )
                    );
                }


                __CDS_cpplang_NonConstConstexprMemberFunction auto operator = (
                        __VariadicUnion const & object
                ) noexcept -> __VariadicUnion & {

                    static_assert (
                            __EntryList :: __copyConstructible && __EntryList :: __copyAssignable,
                            "For Union to be Copy Assignable, all of its' type variants must be "
                            "Copy Constructible and Copy Assignable."
                    );

                    if ( this == & object ) {
                        return * this;
                    }

                    if ( this->_holder == object._holder ) {

                        __VariadicUnion :: __vu_callGroup ( this->_holder, typename __VariadicUnionIndexSequence < sizeof ... (__Types) + 1U > :: __Type () )->_copyAssigner (
                                static_cast < void * > ( & this->_memory [0U] ),
                                static_cast < void const * > ( & object._memory [0U] )
                        );

                        return * this;
                    }

                    __VariadicUnion :: __vu_callGroup ( this->_holder, typename __VariadicUnionIndexSequence < sizeof ... (__Types) + 1U > :: __Type () )->_destructor (
                            static_cast < void * > ( & this->_memory [0U] )
                    );

                    this->_holder = object._holder;
                    __VariadicUnion :: __vu_callGroup ( this->_holder, typename __VariadicUnionIndexSequence < sizeof ... (__Types) + 1U > :: __Type () )->_copyConstructor (
                            static_cast < void * > ( & this->_memory [0U] ),
                            static_cast < void const * > ( & object._memory [0U] )
                    );

                    return * this;
                }


                __CDS_cpplang_NonConstConstexprMemberFunction auto operator = (
                        __VariadicUnion && object
                ) noexcept -> __VariadicUnion & {

                    static_assert (
                            __EntryList :: __moveConstructible && __EntryList :: __moveAssignable,
                            "For Union to be Move Assignable, all of its' type variants must be "
                            "Move Constructible and Move Assignable."
                    );

                    if ( this == & object ) {
                        return * this;
                    }

                    if ( this->_holder == object._holder ) {

                        this->_holder = cds :: exchange ( object._holder, __VariadicUnion :: __vu_valuelessHolder );
                        __VariadicUnion :: __vu_callGroup ( this->_holder, typename __VariadicUnionIndexSequence < sizeof ... (__Types) + 1U > :: __Type () )->_moveAssigner (
                                static_cast < void * > ( & this->_memory [0U] ),
                                static_cast < void * > ( & object._memory [0U] )
                        );

                        return * this;
                    }

                    __VariadicUnion :: __vu_callGroup ( this->_holder, typename __VariadicUnionIndexSequence < sizeof ... (__Types) + 1U > :: __Type () )->_destructor (
                            static_cast < void * > ( & this->_memory [0U] )
                    );

                    this->_holder = cds :: exchange ( object._holder, __VariadicUnion :: __vu_valuelessHolder );
                    __VariadicUnion :: __vu_callGroup ( this->_holder, typename __VariadicUnionIndexSequence < sizeof ... (__Types) + 1U > :: __Type () )->_moveConstructor (
                            static_cast < void * > ( & this->_memory [0U] ),
                            static_cast < void * > ( & object._memory [0U] )
                    );

                    return * this;
                }


                template <
                        typename __TargetElementType,
                        typename __UnionTargetInitTraits = __UnionInitTraits < __TargetElementType, __Types ... >,
                        cds :: meta :: EnableIf <
                                ! cds :: meta :: isSame < cds :: meta :: Decay < __TargetElementType >, __VariadicUnion < __Types ... > > () &&
                                __UnionTargetInitTraits :: __directInit
                        > = 0
                > __CDS_cpplang_NonConstConstexprMemberFunction auto __vu_reset (
                        __TargetElementType && element
                ) noexcept -> void {

                    if ( this->_holder == __UnionTargetInitTraits :: __directInitIndex ) {
                        * static_cast < typename __UnionTargetInitTraits :: __DirectInitType * > ( static_cast < void * > ( & this->_memory [0U] ) ) = cds :: forward < __TargetElementType > ( element );
                        return;
                    }

                    __VariadicUnion :: __vu_callGroup ( this->_holder, typename __VariadicUnionIndexSequence < sizeof ... (__Types) + 1U > :: __Type () )->_destructor (
                            static_cast < void * > ( & this->_memory [0U] )
                    );

                    this->_holder = __UnionTargetInitTraits :: __directInitIndex;
                    (void) new ( & this->_memory [0U] ) typename __UnionTargetInitTraits :: __DirectInitType ( std :: forward < __TargetElementType > ( element ) );
                }


                template <
                        typename __TargetElementType,
                        typename __UnionTargetInitTraits = __UnionInitTraits < __TargetElementType, __Types ... >,
                        cds :: meta :: EnableIf <
                                ! cds :: meta :: isSame < cds :: meta :: Decay < __TargetElementType >, __VariadicUnion < __Types ... > > () &&
                                ! __UnionTargetInitTraits :: __directInit &&
                                __UnionTargetInitTraits :: __convertInit
                        > = 0
                > __CDS_cpplang_NonConstConstexprMemberFunction auto __vu_reset (
                        __TargetElementType && element
                ) noexcept -> void {

                    if ( this->_holder == __UnionTargetInitTraits :: __convertInitIndex ) {
                        * static_cast < typename __UnionTargetInitTraits :: __ConvertInitType * > ( static_cast < void * > ( & this->_memory [0U] ) ) = cds :: forward < __TargetElementType > ( element );
                        return;
                    }

                    __VariadicUnion :: __vu_callGroup ( this->_holder, typename __VariadicUnionIndexSequence < sizeof ... (__Types) + 1U > :: __Type () )->_destructor (
                            static_cast < void * > ( & this->_memory [0U] )
                    );

                    this->_holder = __UnionTargetInitTraits :: __convertInitIndex;
                    (void) new ( & this->_memory [0U] ) typename __UnionTargetInitTraits :: __ConvertInitType ( std :: forward < __TargetElementType > ( element ) );
                }


                template <
                        typename __TargetElementType,
                        typename __UnionTargetInitTraits = __UnionInitTraits < __TargetElementType, __Types ... >,
                        cds :: meta :: EnableIf <
                                ! cds :: meta :: isSame < cds :: meta :: Decay < __TargetElementType >, __VariadicUnion < __Types ... > > () &&
                                ! __UnionTargetInitTraits :: __directInit &&
                                ! __UnionTargetInitTraits :: __convertInit
                        > = 0
                > __CDS_cpplang_NonConstConstexprMemberFunction auto __vu_reset (
                        __TargetElementType && element
                ) noexcept -> void {

                    static_assert (
                            __UnionTargetInitTraits :: __directInit ||
                            __UnionTargetInitTraits :: __convertInit,
                            "Requested Value cannot be assigned to Union due to none of its' variants "
                            "having a direct or conversion constructor and direct or conversion "
                            "assignment operator for the requested value"
                    );
                }


                template <
                        typename __TargetElementType,
                        typename ... __ConstructionArguments
                > __CDS_cpplang_NonConstConstexprMemberFunction auto __vu_emplace (
                        __ConstructionArguments && ... arguments
                ) noexcept -> cds :: meta :: EnableIf <
                        __UnionInitTraits < __TargetElementType, __Types ... > :: __directInit,
                        typename __UnionInitTraits < __TargetElementType, __Types ... > :: __DirectInitType &
                > {

                    using __UnionTargetInitTraits = __UnionInitTraits < __TargetElementType, __Types ... >;

                    __VariadicUnion :: __vu_callGroup ( this->_holder, typename __VariadicUnionIndexSequence < sizeof ... (__Types) + 1U > :: __Type () )->_destructor (
                            static_cast < void * > ( & this->_memory [0U] )
                    );

                    this->_holder = __UnionTargetInitTraits :: __directInitIndex;
                    return * new ( & this->_memory [0U] ) typename __UnionTargetInitTraits :: __DirectInitType ( std :: forward < __ConstructionArguments > ( arguments ) ... );
                }


                template <
                        typename __TargetElementType,
                        typename ... __ConstructionArguments
                > __CDS_cpplang_NonConstConstexprMemberFunction auto __vu_emplace (
                        __ConstructionArguments && ... arguments
                ) noexcept -> cds :: meta :: EnableIf <
                        ! __UnionInitTraits < __TargetElementType, __Types ... > :: __directInit,
                        __TargetElementType &
                > {

                    static_assert (
                            __UnionInitTraits < __TargetElementType, __Types ... > :: __directInit,
                            "Union Emplace is not possible for requested Type due to it not being "
                            "a variant of this Union"
                    );
                }


                template < typename __ElementType >
                __CDS_cpplang_ConstexprConditioned auto __vu_get () noexcept -> __ElementType * {

                    if ( this->_holder != __UnionInitTraits < __ElementType, __Types ... > :: __directInitIndex ) {
                        return nullptr;
                    }

                    return static_cast < __ElementType * > ( static_cast < void * > ( & this->_memory [0U] ) );
                }


                template < typename __ElementType >
                __CDS_cpplang_ConstexprConditioned auto __vu_getConst () const noexcept -> __ElementType const * {

                    if ( this->_holder != __UnionInitTraits < __ElementType, __Types ... > :: __directInitIndex ) {
                        return nullptr;
                    }

                    return static_cast < __ElementType const * > ( static_cast < void const * > ( & this->_memory [0U] ) );
                }


                __CDS_NoDiscard inline auto __vu_toString () const noexcept -> String {

                    return __VariadicUnion :: __vu_callGroup ( this->_holder, typename __VariadicUnionIndexSequence < sizeof ... ( __Types ) + 1U > :: __Type () )->_toString (
                            static_cast < void const * > ( & this->_memory [0U] )
                    );
                }


                __CDS_NoDiscard constexpr auto __vu_hash () const noexcept -> Size {

                    return __VariadicUnion :: __vu_callGroup ( this->_holder, typename __VariadicUnionIndexSequence < sizeof ... ( __Types ) + 1U > :: __Type () )->_hash (
                            static_cast < void const * > ( & this->_memory [0U] )
                    );
                }


                __CDS_NoDiscard constexpr auto __vu_equals (
                        __VariadicUnion const & otherUnion
                ) const noexcept -> bool {

                    return
                            this->_holder == otherUnion._holder &&
                            __VariadicUnion :: __vu_callGroup ( this->_holder, typename __VariadicUnionIndexSequence < sizeof ... ( __Types ) + 1U > :: __Type () )->_equals (
                                    static_cast < void const * > ( & this->_memory [0U] ),
                                    static_cast < void const * > ( & otherUnion._memory [0U] )
                            );
                }
            };

            template < uint32 __index, typename ... __EmptyTypePack >
            constexpr __VariadicUnionCallGroup const __VariadicUnionEntryImpl < __index, __EmptyTypePack ... > :: _callGroup;

            template < uint32 __index, typename __FirstType, typename ... __RemainingTypes >
            constexpr __VariadicUnionCallGroup const __VariadicUnionEntryImpl < __index, __FirstType, __RemainingTypes ... > :: _callGroup;

            template < typename ... __Types >
            template < uint32 ... __sequence >
            constexpr __VariadicUnionCallGroup const * const __VariadicUnion < __Types ... > :: __VariadicUnionCallTable < __sequence ... > :: _callTable [];

        }
    }

    template < typename ... __Types > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    class Union : public Object, private __hidden :: __impl :: __VariadicUnion < __Types ... > {

    public:
        Union () noexcept = default;

    public:
        Union (
                Union const & /* object */
        ) noexcept = default;

    public:
        Union (
                Union && /* object */
        ) noexcept = default;

    public:
        template <
                typename __ElementType,
                cds :: meta :: EnableIf <
                        ! cds :: meta :: isSame < cds :: meta :: Decay < __ElementType >, Union < __Types ... > > () && (
                                __hidden :: __impl :: __UnionInitTraits < __ElementType, __Types ... > :: __directInit ||
                                __hidden :: __impl :: __UnionInitTraits < __ElementType, __Types ... > :: __convertInit
                        )
                > = 0
        > __CDS_cpplang_ConstexprConstructorNonEmptyBody Union (
                __ElementType && value
        ) noexcept :
                __hidden :: __impl :: __VariadicUnion < __Types ... > ( std :: forward < __ElementType > ( value ) ) {

        }

    public:
        __CDS_cpplang_ConstexprDestructor ~Union () noexcept override = default;

    public:
        auto operator = (
                Union const & /* object */
        ) noexcept -> Union & = default;

    public:
        auto operator = (
                Union && /* object */
        ) noexcept -> Union & = default;

    public:
        template <
                typename __ElementType,
                cds :: meta :: EnableIf <
                        ! cds :: meta :: isSame < cds :: meta :: Decay < __ElementType >, Union < __Types ... > > ()
                > = 0
        > __CDS_cpplang_NonConstConstexprMemberFunction auto operator = (
                __ElementType && value
        ) noexcept -> Union & {

            this->__vu_reset ( std :: forward < __ElementType > ( value ) );
            return * this;
        }

    public:
        __CDS_NoDiscard constexpr auto index () const noexcept -> Size {

            return static_cast < Size > ( this->_holder );
        }

    public:
        __CDS_NoDiscard constexpr auto empty () const noexcept -> bool {

            return this->__vu_valueless();
        }

    public:
        template < typename __ElementType, typename ... __ConstructionArguments >
        __CDS_cpplang_NonConstConstexprMemberFunction auto emplace (
                __ConstructionArguments && ... arguments
        ) noexcept ( noexcept ( __ElementType ( std :: forward < __ConstructionArguments > ( arguments ) ... ) ) ) -> typename __hidden :: __impl :: __UnionInitTraits < __ElementType, __Types ... > :: __DirectInitType & {

            return this->template __vu_emplace < typename __hidden :: __impl :: __UnionInitTraits < __ElementType, __Types ... > :: __DirectInitType > ( std :: forward < __ConstructionArguments > ( arguments ) ... );
        }

    public:
        template < typename __ElementType, typename __ListElementType, typename ... __ConstructionArguments >
        __CDS_cpplang_NonConstConstexprMemberFunction auto emplace (
                std :: initializer_list < __ListElementType > const &       list,
                __ConstructionArguments                            &&   ... arguments
        ) noexcept ( noexcept ( __ElementType ( list, std :: forward < __ConstructionArguments > ( arguments ) ... ) ) ) -> typename __hidden :: __impl :: __UnionInitTraits < __ElementType, __Types ... > :: __DirectInitType & {

            return this->template __vu_emplace < typename __hidden :: __impl :: __UnionInitTraits < __ElementType, __Types ... > :: __DirectInitType > ( list, std :: forward < __ConstructionArguments > ( arguments ) ... );
        }

    public:
        template < Size __index, typename ... __ConstructionArguments >
        __CDS_cpplang_NonConstConstexprMemberFunction auto emplace (
                __ConstructionArguments && ... arguments
        ) noexcept ( noexcept ( __ElementType ( std :: forward < __ConstructionArguments > ( arguments ) ... ) ) ) -> typename __hidden :: __impl :: __UnionIndexTraits < __index, __Types ... > :: __Type & {

            return this->template __vu_emplace < typename __hidden :: __impl :: __UnionIndexTraits < __index, __Types ... > :: __Type > ( std :: forward < __ConstructionArguments > ( arguments ) ... );
        }

    public:
        template < Size __index, typename __ListElementType, typename ... __ConstructionArguments >
        __CDS_cpplang_NonConstConstexprMemberFunction auto emplace (
                std :: initializer_list < __ListElementType > const &       list,
                __ConstructionArguments                            &&   ... arguments
        ) noexcept ( noexcept ( __ElementType ( list, std :: forward < __ConstructionArguments > ( arguments ) ... ) ) ) -> typename __hidden :: __impl :: __UnionIndexTraits < __index, __Types ... > :: __Type & {

            return this->template __vu_emplace < typename __hidden :: __impl :: __UnionIndexTraits < __index, __Types ... > :: __Type > ( list, std :: forward < __ConstructionArguments > ( arguments ) ... );
        }

    public:
        template < typename __ElementType >
        __CDS_cpplang_ConstexprConditioned auto get () const noexcept (false) -> cds :: meta :: Decay < typename __hidden :: __impl :: __UnionInitTraits < __ElementType, __Types ... > :: __DirectInitType > const &  {

            auto pObject = this->template __vu_getConst < typename __hidden :: __impl :: __UnionInitTraits < __ElementType, __Types ... > :: __DirectInitType > ();
            if ( pObject == nullptr ) {
                throw TypeException ( String ( "Union does not contain requested Type. Current Type is Type at index : " ) + this->_holder );
            }

            return * pObject;
        }

    public:
        template < Size __index >
        __CDS_cpplang_ConstexprConditioned auto get () const noexcept (false) -> cds :: meta :: Decay < typename __hidden :: __impl :: __UnionIndexTraits < __index, __Types ... > :: __Type > const &  {

            auto pObject = this->template __vu_getConst < typename __hidden :: __impl :: __UnionIndexTraits < __index, __Types ... > :: __Type > ();
            if ( pObject == nullptr ) {
                throw TypeException ( String ( "Union does not contain requested Type. Current Type is Type at index : " ) + this->_holder );
            }

            return * pObject;
        }

    public:
        template < typename __ElementType >
        __CDS_cpplang_ConstexprConditioned auto get () noexcept (false) -> cds :: meta :: Decay < typename __hidden :: __impl :: __UnionInitTraits < __ElementType, __Types ... > :: __DirectInitType > &  {

            auto pObject = this->template __vu_get < typename __hidden :: __impl :: __UnionInitTraits < __ElementType, __Types ... > :: __DirectInitType > ();
            if ( pObject == nullptr ) {
                throw TypeException ( String ( "Union does not contain requested Type. Current Type is Type at index : " ) + this->_holder );
            }

            return * pObject;
        }

    public:
        template < Size __index >
        __CDS_cpplang_ConstexprConditioned auto get () noexcept (false) -> cds :: meta :: Decay < typename __hidden :: __impl :: __UnionIndexTraits < __index, __Types ... > :: __Type > &  {

            auto pObject = this->template __vu_get < typename __hidden :: __impl :: __UnionIndexTraits < __index, __Types ... > :: __Type > ();
            if ( pObject == nullptr ) {
                throw TypeException ( String ( "Union does not contain requested Type. Current Type is Type at index : " ) + this->_holder );
            }

            return * pObject;
        }

    public:
        template < typename __ElementType >
        __CDS_cpplang_ConstexprConditioned auto getPointer () const noexcept -> cds :: meta :: Decay < typename __hidden :: __impl :: __UnionInitTraits < __ElementType, __Types ... > :: __DirectInitType > const * {

            return this->template __vu_getConst < typename __hidden :: __impl :: __UnionInitTraits < __ElementType, __Types ... > :: __DirectInitType > ();
        }

    public:
        template < Size __index >
        __CDS_cpplang_ConstexprConditioned auto getPointer () const noexcept -> cds :: meta :: Decay < typename __hidden :: __impl :: __UnionIndexTraits < __index, __Types ... > :: __Type > const * {

            return this->template __vu_getConst < typename __hidden :: __impl :: __UnionIndexTraits < __index, __Types ... > :: __Type > ();
        }

    public:
        template < typename __ElementType >
        __CDS_cpplang_ConstexprConditioned auto getPointer () noexcept -> cds :: meta :: Decay < typename __hidden :: __impl :: __UnionInitTraits < __ElementType, __Types ... > :: __DirectInitType > * {

            return this->template __vu_get < typename __hidden :: __impl :: __UnionInitTraits < __ElementType, __Types ... > :: __DirectInitType > ();
        }

    public:
        template < Size __index >
        __CDS_cpplang_ConstexprConditioned auto getPointer () noexcept -> cds :: meta :: Decay < typename __hidden :: __impl :: __UnionIndexTraits < __index, __Types ... > :: __Type > * {

            return this->template __vu_get < typename __hidden :: __impl :: __UnionIndexTraits < __index, __Types ... > :: __Type > ();
        }

    public:
        template < typename __ElementType >
        constexpr auto is () const noexcept -> bool {

            return this->template is < __hidden :: __impl :: __UnionInitTraits < __ElementType > :: __directInitIndex > ();
        }

    public:
        template < Size __index >
        constexpr auto is () const noexcept -> bool {

            return __index == this->_holder;
        }

    public:
        template < typename __ElementType, typename __Consumer >
        __CDS_cpplang_ConstexprConditioned auto ifIs (
                __Consumer const & consumer
        ) noexcept ( noexcept ( consumer ( cds :: meta :: referenceOf < typename __hidden :: __impl :: __UnionInitTraits < __ElementType, __Types ... > :: __DirectInitType > () ) ) ) -> void {

            auto pObject = this->template __vu_get < typename __hidden :: __impl :: __UnionInitTraits < __ElementType, __Types ... > :: __DirectInitType > ();
            if ( pObject == nullptr ) {
                return;
            }

            consumer ( * pObject );
        }

    public:
        template < Size __index, typename __Consumer >
        __CDS_cpplang_ConstexprConditioned auto ifIs (
                __Consumer const & consumer
        ) noexcept ( noexcept ( consumer ( cds :: meta :: referenceOf < typename __hidden :: __impl :: __UnionIndexTraits < __index, __Types ... > :: __Type > () ) ) ) -> void {

            auto pObject = this->template __vu_get < typename __hidden :: __impl :: __UnionIndexTraits < __index, __Types ... > :: __Type > ();
            if ( pObject == nullptr ) {
                return;
            }

            consumer ( * pObject );
        }

    public:
        template < typename __ElementType, typename __Consumer >
        __CDS_cpplang_ConstexprConditioned auto ifIs (
                __Consumer const & consumer
        ) const noexcept ( noexcept ( consumer ( cds :: meta :: referenceOf < typename __hidden :: __impl :: __UnionInitTraits < __ElementType, __Types ... > :: __DirectInitType const > () ) ) ) -> void {

            auto pObject = this->template __vu_getConst < typename __hidden :: __impl :: __UnionInitTraits < __ElementType, __Types ... > :: __DirectInitType > ();
            if ( pObject == nullptr ) {
                return;
            }

            consumer ( * pObject );
        }

    public:
        template < Size __index, typename __Consumer >
        __CDS_cpplang_ConstexprConditioned auto ifIs (
                __Consumer const & consumer
        ) const noexcept ( noexcept ( consumer ( cds :: meta :: referenceOf < typename __hidden :: __impl :: __UnionIndexTraits < __index, __Types ... > :: __Type const > () ) ) ) -> void {

            auto pObject = this->template __vu_getConst < typename __hidden :: __impl :: __UnionIndexTraits < __index, __Types ... > :: __Type > ();
            if ( pObject == nullptr ) {
                return;
            }

            consumer ( * pObject );
        }

    public:
        __CDS_NoDiscard auto toString () const noexcept -> String override {

            return this->__vu_toString ();
        }

    public:
        __CDS_NoDiscard auto hash () const noexcept -> Size override {

            return this->__vu_hash ();
        }

    public:
        __CDS_NoDiscard auto equals (
                Object const & object
        ) const noexcept -> bool override {

            if ( this == & object ) {
                return true;
            }

            auto pUnion = dynamic_cast < decltype (this) > ( & object );
            if ( pUnion == nullptr ) {
                return false;
            }

            return this->__vu_equals ( * pUnion );
        }
    };

} /* namespace cds */

#endif /* __CDS_UNION_HPP__ */
