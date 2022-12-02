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

                constexpr static auto __vue_acquireDestructor (
                        uint32 /* activeIndex */
                ) noexcept -> cds :: functional :: ConsumerFunction < void * > {

                    return & __VariadicUnionEntryImpl :: __vue_destructor;
                }


                constexpr static auto __vue_acquireCopyConstructor (
                        uint32 /* activeIndex */
                ) noexcept -> cds :: functional :: ConsumerFunction < void *, void const * > {

                    return & __VariadicUnionEntryImpl :: __vue_copyConstructor;
                }


                constexpr static auto __vue_acquireMoveConstructor (
                        uint32 /* activeIndex */
                ) noexcept -> cds :: functional :: ConsumerFunction < void *, void * > {

                    return & __VariadicUnionEntryImpl :: __vue_moveConstructor;
                }


                constexpr static auto __vue_acquireCopyAssigner (
                        uint32 /* activeIndex */
                ) noexcept -> cds :: functional :: ConsumerFunction < void *, void const * > {

                    return & __VariadicUnionEntryImpl :: __vue_copyAssigner;
                }


                constexpr static auto __vue_acquireMoveAssigner (
                        uint32 /* activeIndex */
                ) noexcept -> cds :: functional :: ConsumerFunction < void *, void * > {

                    return & __VariadicUnionEntryImpl :: __vue_moveAssigner;
                }
            };


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

                    new ( static_cast < __FirstType * > ( pTo ) ) __FirstType ( * static_cast < __FirstType const * > ( pFrom ) );
                }

                __CDS_cpplang_ConstexprNonLiteralReturn static auto __vue_moveConstructor (
                        void * pTo,
                        void * pFrom
                ) noexcept -> void {

                    new ( static_cast < __FirstType * > ( pTo ) ) __FirstType ( std :: move ( * static_cast < __FirstType * > ( pFrom ) ) );
                }

                __CDS_cpplang_ConstexprNonLiteralReturn static auto __vue_copyAssigner (
                        void       * pTo,
                        void const * pFrom
                ) noexcept -> void {

                    * static_cast < __FirstType * > ( pTo ) = * static_cast < __FirstType const * > ( pFrom );
                }

                __CDS_cpplang_ConstexprNonLiteralReturn static auto __vue_moveAssigner (
                        void * pTo,
                        void * pFrom
                ) noexcept -> void {

                    * static_cast < __FirstType * > ( pTo ) = std :: move ( * static_cast < __FirstType * > ( pFrom ) );
                }

                constexpr static auto __vue_acquireDestructor (
                        uint32 activeIndex
                ) noexcept -> cds :: functional :: ConsumerFunction < void * > {

                    if ( activeIndex == __index ) {
                        return & __VariadicUnionEntryImpl :: __vue_destructor;
                    }

                    return __NextEntry :: __vue_acquireDestructor ( activeIndex );
                }

                constexpr static auto __vue_acquireCopyConstructor (
                        uint32 activeIndex
                ) noexcept -> cds :: functional :: ConsumerFunction < void *, void const * > {

                    if ( activeIndex == __index ) {
                        return & __VariadicUnionEntryImpl :: __vue_copyConstructor;
                    }

                    return __NextEntry :: __vue_acquireCopyConstructor ( activeIndex );
                }

                constexpr static auto __vue_acquireMoveConstructor (
                        uint32 activeIndex
                ) noexcept -> cds :: functional :: ConsumerFunction < void *, void * > {

                    if ( activeIndex == __index ) {
                        return & __VariadicUnionEntryImpl :: __vue_moveConstructor;
                    }

                    return __NextEntry :: __vue_acquireMoveConstructor ( activeIndex );
                }

                constexpr static auto __vue_acquireCopyAssigner (
                        uint32 activeIndex
                ) noexcept -> cds :: functional :: ConsumerFunction < void *, void const * > {

                    if ( activeIndex == __index ) {
                        return & __VariadicUnionEntryImpl :: __vue_copyAssigner;
                    }

                    return __NextEntry :: __vue_acquireCopyAssigner ( activeIndex );
                }

                constexpr static auto __vue_acquireMoveAssigner (
                        uint32 activeIndex
                ) noexcept -> cds :: functional :: ConsumerFunction < void *, void * > {

                    if ( activeIndex == __index ) {
                        return & __VariadicUnionEntryImpl :: __vue_moveAssigner;
                    }

                    return __NextEntry :: __vue_acquireMoveAssigner ( activeIndex );
                }
            };


            template < typename ... __Types >
            struct __VariadicUnionEntry : __VariadicUnionEntryImpl < 0U, __Types ... > {};


            template < typename ... __Types >
            struct __VariadicUnion {

                using __EntryList = __VariadicUnionEntry < __Types ... >;

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

                    __EntryList :: __vue_acquireDestructor ( this->_holder ) ( static_cast < void * > ( & this->_memory [0U] ) );
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

                    __EntryList :: __vue_acquireCopyConstructor ( object._holder ) (
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

                    __EntryList :: __vue_acquireMoveConstructor ( this->_holder ) (
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

                        __EntryList :: __vue_acquireCopyAssigner ( this->_holder ) (
                                static_cast < void * > ( & this->_memory [0U] ),
                                static_cast < void const * > ( & object._memory [0U] )
                        );
                        return * this;
                    }

                    __EntryList :: __vue_acquireDestructor ( this->_holder ) (
                            static_cast < void * > ( & this->_memory [0U] )
                    );

                    this->_holder = object._holder;
                    __EntryList :: __vue_acquireCopyConstructor ( this->_holder ) (
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

                        __EntryList :: __vue_acquireMoveAssigner ( this->_holder ) (
                                static_cast < void * > ( & this->_memory [0U] ),
                                static_cast < void * > ( & object._memory [0U] )
                        );
                        return * this;
                    }

                    __EntryList :: __vue_acquireDestructor ( this->_holder ) (
                            static_cast < void * > ( & this->_memory [0U] )
                    );

                    this->_holder = cds :: exchange ( object._holder, __VariadicUnion :: __vu_valuelessHolder );
                    __EntryList :: __vue_acquireMoveConstructor ( this->_holder ) (
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
                    }

                    __EntryList :: __vue_acquireDestructor ( this->_holder ) (
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
                    }

                    __EntryList :: __vue_acquireDestructor ( this->_holder ) (
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
            };

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
    };

} /* namespace cds */

#endif /* __CDS_UNION_HPP__ */
