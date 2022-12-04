/*
 * Created by loghin on 04/12/22.
 */

#ifndef __CDS_UNION_VARIADIC_UNION_IMPL_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_UNION_VARIADIC_UNION_IMPL_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

namespace cds {             /* NOLINT(modernize-concat-nested-namespaces) */
    namespace __hidden {    /* NOLINT(bugprone-reserved-identifier, modernize-concat-nested-namespaces, cert-dcl37-c, cert-dcl51-cpp) */
        namespace __impl {  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            template < uint32 __entryIndex, typename ... __EmptyTypePack >  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            __CDS_cpplang_ConstexprNonLiteralReturn auto __VariadicUnionInterfaceEntryImpl <
                    __entryIndex,
                    __EmptyTypePack ...
            > :: __copyConstructor (
                    void       * /* pTo */,
                    void const * /* pFrom */
            ) noexcept -> void {

                /* nothing, as this function is associated with a valueless variant. */
            }


            template < uint32 __entryIndex, typename ... __EmptyTypePack >  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            __CDS_cpplang_ConstexprNonLiteralReturn auto __VariadicUnionInterfaceEntryImpl <
                    __entryIndex,
                    __EmptyTypePack ...
            > :: __moveConstructor (
                    void * /* pTo */,
                    void * /* pFrom */
            ) noexcept -> void {

                /* nothing, as this function is associated with a valueless variant. */
            }


            template < uint32 __entryIndex, typename ... __EmptyTypePack >  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            __CDS_cpplang_ConstexprNonLiteralReturn auto __VariadicUnionInterfaceEntryImpl <
                    __entryIndex,
                    __EmptyTypePack ...
            > :: __destructor (
                    void * /* pObject */
            ) noexcept -> void {

                /* nothing, as this function is associated with a valueless variant. */
            }


            template < uint32 __entryIndex, typename ... __EmptyTypePack >  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            __CDS_cpplang_ConstexprNonLiteralReturn auto __VariadicUnionInterfaceEntryImpl <
                    __entryIndex,
                    __EmptyTypePack ...
            > :: __copyAssigner (
                    void       * /* pTo */,
                    void const * /* pFrom */
            ) noexcept -> void {

                /* nothing, as this function is associated with a valueless variant. */
            }


            template < uint32 __entryIndex, typename ... __EmptyTypePack >  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            __CDS_cpplang_ConstexprNonLiteralReturn auto __VariadicUnionInterfaceEntryImpl <
                    __entryIndex,
                    __EmptyTypePack ...
            > :: __moveAssigner (
                    void * /* pTo */,
                    void * /* pFrom */
            ) noexcept -> void {

                /* nothing, as this function is associated with a valueless variant. */
            }


            template < uint32 __entryIndex, typename ... __EmptyTypePack >  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            inline auto __VariadicUnionInterfaceEntryImpl <
                    __entryIndex,
                    __EmptyTypePack ...
            > :: __toString (
                    void const * /* pObject */
            ) noexcept -> String {

                /* return 'null' String, as this function is associated with a valueless variant. */
                return "null";
            }


            template < uint32 __entryIndex, typename ... __EmptyTypePack >  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            constexpr auto __VariadicUnionInterfaceEntryImpl <
                    __entryIndex,
                    __EmptyTypePack ...
            > :: __hash (
                    void const * /* pObject */
            ) noexcept -> Size {

                /* return 0U, nothing to Hash. */
                return 0U;
            }


            template < uint32 __entryIndex, typename ... __EmptyTypePack >  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            constexpr auto __VariadicUnionInterfaceEntryImpl <
                    __entryIndex,
                    __EmptyTypePack ...
            > :: __equals (
                    void const * /* pObject */,
                    void const * /* pOtherObject */
            ) noexcept -> bool {

                /* return true, two valueless variants are equal. */
                return true;
            }


            template < uint32 __entryIndex, typename ... __EmptyTypePack >  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            constexpr auto __VariadicUnionInterfaceEntryImpl <
                    __entryIndex,
                    __EmptyTypePack ...
            > :: __vuie_acquireCallTable (
                    uint32 /* holderIndex */
            ) noexcept -> __VariadicUnionInterfaceEntryCallTable const * {

                /* return call table associated with valueless variant(s). */
                return & __VariadicUnionInterfaceEntryImpl :: _entryCallTable;
            }


            template < uint32 __index, typename ... __EmptyTypePack >   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            constexpr __VariadicUnionInterfaceEntryCallTable const __VariadicUnionInterfaceEntryImpl <
                    __index,
                    __EmptyTypePack ...
            > :: _entryCallTable;


            template < uint32 __entryIndex, typename __EntryType, typename ... __RemainingTypes >  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            __CDS_cpplang_ConstexprNonLiteralReturn auto __VariadicUnionInterfaceEntryImpl <
                    __entryIndex,
                    __EntryType,
                    __RemainingTypes ...
            > :: __copyConstructor (
                    void       * pTo,
                    void const * pFrom
            ) noexcept -> void {

                __variadicUnionInterfaceLateCopyConstruct < __EntryType > (
                        pTo,
                        pFrom
                );
            }


            template < uint32 __entryIndex, typename __EntryType, typename ... __RemainingTypes >  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            __CDS_cpplang_ConstexprNonLiteralReturn auto __VariadicUnionInterfaceEntryImpl <
                    __entryIndex,
                    __EntryType,
                    __RemainingTypes ...
            > :: __moveConstructor (
                    void * pTo,
                    void * pFrom
            ) noexcept -> void {

                __variadicUnionInterfaceLateMoveConstruct < __EntryType > (
                        pTo,
                        pFrom
                );
            }


            template < uint32 __entryIndex, typename __EntryType, typename ... __RemainingTypes >  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            __CDS_cpplang_ConstexprNonLiteralReturn auto __VariadicUnionInterfaceEntryImpl <
                    __entryIndex,
                    __EntryType,
                    __RemainingTypes ...
            > :: __destructor (
                    void * pObject
            ) noexcept -> void {

                static_cast < __EntryType * > ( pObject )->~__EntryType ();
            }


            template < uint32 __entryIndex, typename __EntryType, typename ... __RemainingTypes >  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            __CDS_cpplang_ConstexprNonLiteralReturn auto __VariadicUnionInterfaceEntryImpl <
                    __entryIndex,
                    __EntryType,
                    __RemainingTypes ...
            > :: __copyAssigner (
                    void       * pTo,
                    void const * pFrom
            ) noexcept -> void {

                __variadicUnionInterfaceLateCopyAssign < __EntryType > ( pTo, pFrom );
            }


            template < uint32 __entryIndex, typename __EntryType, typename ... __RemainingTypes >  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            __CDS_cpplang_ConstexprNonLiteralReturn auto __VariadicUnionInterfaceEntryImpl <
                    __entryIndex,
                    __EntryType,
                    __RemainingTypes ...
            > :: __moveAssigner (
                    void * pTo,
                    void * pFrom
            ) noexcept -> void {

                __variadicUnionInterfaceLateMoveAssign < __EntryType > ( pTo, pFrom );
            }


            template < uint32 __entryIndex, typename __EntryType, typename ... __RemainingTypes >  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            inline auto __VariadicUnionInterfaceEntryImpl <
                    __entryIndex,
                    __EntryType,
                    __RemainingTypes ...
            > :: __toString (
                    void const * pObject
            ) noexcept -> String {

                std :: stringstream oss;
                cds :: streamPrint ( oss, * static_cast < __EntryType const * > ( pObject ) );
                return oss.str();
            }


            template < uint32 __entryIndex, typename __EntryType, typename ... __RemainingTypes >  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            constexpr auto __VariadicUnionInterfaceEntryImpl <
                    __entryIndex,
                    __EntryType,
                    __RemainingTypes ...
            > :: __hash (
                    void const * pObject
            ) noexcept -> Size {

                return cds :: Hash < __EntryType > :: hash ( * static_cast < __EntryType const * > ( pObject ) );
            }


            template < uint32 __entryIndex, typename __EntryType, typename ... __RemainingTypes >  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            constexpr auto __VariadicUnionInterfaceEntryImpl <
                    __entryIndex,
                    __EntryType,
                    __RemainingTypes ...
            > :: __equals (
                    void const * pObject,
                    void const * pOtherObject
            ) noexcept -> bool {

                return cds :: meta :: equals (
                        * static_cast < __EntryType const * > ( pObject ),
                        * static_cast < __EntryType const * > ( pOtherObject )
                );
            }


            template < uint32 __entryIndex, typename __EntryType, typename ... __RemainingTypes >  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            constexpr auto __VariadicUnionInterfaceEntryImpl <
                    __entryIndex,
                    __EntryType,
                    __RemainingTypes ...
            > :: __vuie_acquireCallTable (
                    uint32 holderIndex
            ) noexcept -> __VariadicUnionInterfaceEntryCallTable const * {

                return
                        holderIndex == __entryIndex ?
                        & __VariadicUnionInterfaceEntryImpl :: _entryCallTable :
                        __NextEntry :: __vuie_acquireCallTable ( holderIndex );
            }


            template < uint32 __entryIndex, typename __EntryType, typename ... __RemainingTypes >  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            constexpr __VariadicUnionInterfaceEntryCallTable const __VariadicUnionInterfaceEntryImpl <
                    __entryIndex,
                    __EntryType,
                    __RemainingTypes ...
            > :: _entryCallTable;


            template < typename __ElementType, cds :: meta :: EnableIf < cds :: meta :: isCopyConstructible < __ElementType > () > >    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            __CDS_cpplang_ConstexprNonLiteralReturn static auto __variadicUnionInterfaceLateCopyConstruct (                             /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    void       * pTo,
                    void const * pFrom
            ) noexcept -> void {

                new ( static_cast < __ElementType * > ( pTo ) ) __ElementType ( * static_cast < __ElementType const * > ( pFrom ) );
            }


            template < typename __ElementType, cds :: meta :: EnableIf < ! cds :: meta :: isCopyConstructible < __ElementType > () > >  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            __CDS_cpplang_ConstexprNonLiteralReturn static auto __variadicUnionInterfaceLateCopyConstruct (                             /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    void       * /* pTo */,
                    void const * /* pFrom */
            ) noexcept -> void {

                /* Nothing done. Assert done in class */
            }


            template < typename __ElementType, cds :: meta :: EnableIf < cds :: meta :: isMoveConstructible < __ElementType > () > >    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            __CDS_cpplang_ConstexprNonLiteralReturn static auto __variadicUnionInterfaceLateMoveConstruct (                             /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    void * pTo,
                    void * pFrom
            ) noexcept -> void {

                new ( static_cast < __ElementType * > ( pTo ) ) __ElementType ( std :: move ( * static_cast < __ElementType * > ( pFrom ) ) );
            }


            template < typename __ElementType, cds :: meta :: EnableIf < ! cds :: meta :: isMoveConstructible < __ElementType > () > >  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            __CDS_cpplang_ConstexprNonLiteralReturn static auto __variadicUnionInterfaceLateMoveConstruct (                             /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    void * /* pTo */,
                    void * /* pFrom */
            ) noexcept -> void {

                /* Nothing done. Assert done in class */
            }


            template < typename __ElementType, cds :: meta :: EnableIf < cds :: meta :: isCopyAssignable < __ElementType > () > >   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            __CDS_cpplang_ConstexprNonLiteralReturn static auto __variadicUnionInterfaceLateCopyAssign (                            /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    void       * pTo,
                    void const * pFrom
            ) noexcept -> void {

                * static_cast < __ElementType * > ( pTo ) = * static_cast < __ElementType const * > ( pFrom );
            }


            template < typename __ElementType, cds :: meta :: EnableIf < ! cds :: meta :: isCopyAssignable < __ElementType > () > > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            __CDS_cpplang_ConstexprNonLiteralReturn static auto __variadicUnionInterfaceLateCopyAssign (                            /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    void       * /* pTo */,
                    void const * /* pFrom */
            ) noexcept -> void {

                /* Nothing done. Assert done in class */
            }


            template < typename __ElementType, cds :: meta :: EnableIf < cds :: meta :: isMoveAssignable < __ElementType > () > >   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            __CDS_cpplang_ConstexprNonLiteralReturn static auto __variadicUnionInterfaceLateMoveAssign (                            /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    void * pTo,
                    void * pFrom
            ) noexcept -> void {

                * static_cast < __ElementType * > ( pTo ) = std :: move ( * static_cast < __ElementType * > ( pFrom ) );
            }


            template < typename __ElementType, cds :: meta :: EnableIf < ! cds :: meta :: isMoveAssignable < __ElementType > () > > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            __CDS_cpplang_ConstexprNonLiteralReturn static auto __variadicUnionInterfaceLateMoveAssign (                            /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    void * /* pTo */,
                    void * /* pFrom */
            ) noexcept -> void {

                /* Nothing done. Assert done in class */
            }


            template < typename ... __Types >
            __CDS_cpplang_ConstexprConstructorNonEmptyBody __VariadicUnion <
                    __Types ...
            > :: __VariadicUnion (
                    __VariadicUnion const & object
            ) noexcept :
                    _holder ( object._holder ) {

                static_assert (
                        __InterfaceEntryList :: __copyConstructible,
                        "For Union to be Copy Constructible, all of its' type variants must be Copy Constructible"
                );

                __VariadicUnion :: __vu_callTable (
                        this->_holder,
                        __VariadicUnion :: __CallTableIndexSequence ()
                )->_copyConstructor (
                        static_cast < void * > ( & this->_memory [0U] ),
                        static_cast < void const * > ( & object._memory [0U] )
                );
            }


            template < typename ... __Types >
            __CDS_cpplang_ConstexprConstructorNonEmptyBody __VariadicUnion <
                    __Types ...
            > :: __VariadicUnion (
                    __VariadicUnion && object
            ) noexcept :
                    _holder ( object._holder ) {

                static_assert (
                        __InterfaceEntryList :: __moveConstructible,
                        "For Union to be Move Constructible, all of its' type variants must be Move Constructible"
                );

                __VariadicUnion :: __vu_callTable (
                        this->_holder,
                        __VariadicUnion :: __CallTableIndexSequence ()
                )->_moveConstructor (
                        static_cast < void * > ( & this->_memory [0U] ),
                        static_cast < void * > ( & object._memory [0U] )
                );
            }


            template < typename ... __Types >
            template <
                    typename __TargetElementType,
                    typename __UnionTargetInitTraits,
                    cds :: meta :: EnableIf <
                            ! cds :: meta :: isSame < cds :: meta :: Decay < __TargetElementType >, __VariadicUnion < __Types ... > > () &&
                            __UnionTargetInitTraits :: __directInit
                    >
            > __CDS_cpplang_ConstexprConstructorNonEmptyBody __VariadicUnion <
                    __Types ...
            > :: __VariadicUnion (
                    __TargetElementType && element
            ) noexcept :
                    _holder ( __UnionTargetInitTraits :: __directInitIndex ) {

                (void) new ( & this->_memory [0U] ) typename __UnionTargetInitTraits :: __DirectInitType (
                        std :: forward < __TargetElementType > ( element )
                );
            }


            template < typename ... __Types >
            template <
                    typename __TargetElementType,
                    typename __UnionTargetInitTraits,
                    cds :: meta :: EnableIf <
                            ! cds :: meta :: isSame < cds :: meta :: Decay < __TargetElementType >, __VariadicUnion < __Types ... > > () &&
                            ! __UnionTargetInitTraits :: __directInit &&
                            __UnionTargetInitTraits :: __convertInit
                    >
            > __CDS_cpplang_ConstexprConstructorNonEmptyBody __VariadicUnion <
                    __Types ...
            > :: __VariadicUnion (
                    __TargetElementType && element
            ) noexcept :
                    _holder ( __UnionTargetInitTraits :: __convertInitIndex ) {

                (void) new ( & this->_memory [0U] ) typename __UnionTargetInitTraits :: __ConvertInitType (
                        std :: forward < __TargetElementType > ( element )
                );
            }


            template < typename ... __Types >
            template <
                    typename __TargetElementType,
                    typename __UnionTargetInitTraits,
                    cds :: meta :: EnableIf <
                            ! cds :: meta :: isSame < cds :: meta :: Decay < __TargetElementType >, __VariadicUnion < __Types ... > > () &&
                            ! __UnionTargetInitTraits :: __directInit &&
                            ! __UnionTargetInitTraits :: __convertInit
                    >
            > __CDS_cpplang_ConstexprConstructorNonEmptyBody __VariadicUnion <
                    __Types ...
            > :: __VariadicUnion (
                    __TargetElementType && /* element */
            ) noexcept {

                static_assert (
                        __UnionTargetInitTraits :: __directInit ||
                        __UnionTargetInitTraits :: __convertInit,
                        "Union cannot be constructed from given value due to none of its' variants "
                        "having a direct or conversion constructor for the requested value"
                );
            }


            template < typename ... __Types >
            __CDS_cpplang_ConstexprDestructor __VariadicUnion <
                    __Types ...
            > :: ~__VariadicUnion () noexcept {

                __VariadicUnion :: __vu_callTable (
                        this->_holder,
                        __VariadicUnion :: __CallTableIndexSequence ()
                )->_destructor (
                        static_cast < void * > ( & this->_memory [0U] )
                );
            }


            template < typename ... __Types >
            __CDS_cpplang_NonConstConstexprMemberFunction auto __VariadicUnion <
                    __Types ...
            > :: operator = (
                    __VariadicUnion const & object
            ) noexcept -> __VariadicUnion & {

                static_assert (
                        __InterfaceEntryList :: __copyConstructible && __InterfaceEntryList :: __copyAssignable,
                        "For Union to be Copy Assignable, all of its' type variants must be "
                        "Copy Constructible and Copy Assignable."
                );

                if ( this == & object ) {
                    return * this;
                }

                if ( this->_holder == object._holder ) {

                    __VariadicUnion :: __vu_callTable (
                            this->_holder,
                            __VariadicUnion :: __CallTableIndexSequence ()
                    )->_copyAssigner (
                            static_cast < void * > ( & this->_memory [0U] ),
                            static_cast < void const * > ( & object._memory [0U] )
                    );

                    return * this;
                }

                __VariadicUnion :: __vu_callTable (
                        this->_holder,
                        __VariadicUnion :: __CallTableIndexSequence ()
                )->_destructor (
                        static_cast < void * > ( & this->_memory [0U] )
                );

                this->_holder = object._holder;
                __VariadicUnion :: __vu_callTable (
                        this->_holder,
                        __VariadicUnion :: __CallTableIndexSequence ()
                )->_copyConstructor (
                        static_cast < void * > ( & this->_memory [0U] ),
                        static_cast < void const * > ( & object._memory [0U] )
                );

                return * this;
            }


            template < typename ... __Types >
            __CDS_cpplang_NonConstConstexprMemberFunction auto __VariadicUnion <
                    __Types ...
            > :: operator = (
                    __VariadicUnion && object
            ) noexcept -> __VariadicUnion & {

                static_assert (
                        __InterfaceEntryList :: __moveConstructible && __InterfaceEntryList :: __moveAssignable,
                        "For Union to be Move Assignable, all of its' type variants must be "
                        "Move Constructible and Move Assignable."
                );

                if ( this == & object ) {
                    return * this;
                }

                if ( this->_holder == object._holder ) {

                    this->_holder = cds :: exchange ( object._holder, __VariadicUnion :: __vu_valuelessHolder );
                    __VariadicUnion :: __vu_callTable (
                            this->_holder,
                            __VariadicUnion :: __CallTableIndexSequence ()
                    )->_moveAssigner (
                            static_cast < void * > ( & this->_memory [0U] ),
                            static_cast < void * > ( & object._memory [0U] )
                    );

                    return * this;
                }

                __VariadicUnion :: __vu_callTable (
                        this->_holder,
                        __VariadicUnion :: __CallTableIndexSequence ()
                )->_destructor (
                        static_cast < void * > ( & this->_memory [0U] )
                );

                this->_holder = cds :: exchange ( object._holder, __VariadicUnion :: __vu_valuelessHolder );
                __VariadicUnion :: __vu_callTable (
                        this->_holder,
                        __VariadicUnion :: __CallTableIndexSequence ()
                )->_moveConstructor (
                        static_cast < void * > ( & this->_memory [0U] ),
                        static_cast < void * > ( & object._memory [0U] )
                );

                return * this;
            }


            template < typename ... __Types >
            template < uint32 ... __indexSequence >
            constexpr auto __VariadicUnion <
                    __Types ...
            > :: __vu_callTable (
                    uint32                                                                  holder,
                    __VariadicUnionCallTableIndexSequenceType < __indexSequence ... >    /* ignored */
            ) noexcept -> __VariadicUnionInterfaceEntryCallTable const * {

                return __VariadicUnion :: __CallTable < __indexSequence ... > :: _callTable [ holder ];
            }


            template < typename ... __Types >
            constexpr auto __VariadicUnion <
                    __Types ...
            > :: __vu_valueless () const noexcept -> bool {

                return this->_holder == __VariadicUnion :: __vu_valuelessHolder;
            }


            template < typename ... __Types >
            constexpr auto __VariadicUnion <
                    __Types ...
            > :: __vu_holder () const noexcept -> uint32 {

                return this->_holder;
            }


            template < typename ... __Types >
            template <
                    typename __TargetElementType,           /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __UnionTargetPackTypeTraits,   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    cds :: meta :: EnableIf <
                            ! cds :: meta :: isSame < cds :: meta :: Decay < __TargetElementType >, __VariadicUnion < __Types ... > > () &&
                            __UnionTargetPackTypeTraits :: __directInit
                    >
            > __CDS_cpplang_NonConstConstexprMemberFunction auto __VariadicUnion <
                    __Types ...
            > :: __vu_reset (
                    __TargetElementType && element
            ) noexcept -> void {

                if ( this->_holder == __UnionTargetPackTypeTraits :: __directInitIndex ) {
                    * static_cast < typename __UnionTargetPackTypeTraits :: __DirectInitType * > ( static_cast < void * > ( & this->_memory [0U] ) ) = cds :: forward < __TargetElementType > ( element );
                    return;
                }

                __VariadicUnion :: __vu_callTable (
                        this->_holder,
                        __VariadicUnion :: __CallTableIndexSequence ()
                )->_destructor (
                        static_cast < void * > ( & this->_memory [0U] )
                );

                this->_holder = __UnionTargetPackTypeTraits :: __directInitIndex;
                (void) new ( & this->_memory [0U] ) typename __UnionTargetPackTypeTraits :: __DirectInitType (
                        std :: forward < __TargetElementType > ( element )
                );
            }


            template < typename ... __Types >
            template <
                    typename __TargetElementType,           /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __UnionTargetPackTypeTraits,   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    cds :: meta :: EnableIf <
                            ! cds :: meta :: isSame < cds :: meta :: Decay < __TargetElementType >, __VariadicUnion < __Types ... > > () &&
                            ! __UnionTargetPackTypeTraits :: __directInit &&
                            __UnionTargetPackTypeTraits :: __convertInit
                    >
            > __CDS_cpplang_NonConstConstexprMemberFunction auto __VariadicUnion <
                    __Types ...
            > :: __vu_reset (
                    __TargetElementType && element
            ) noexcept -> void {

                if ( this->_holder == __UnionTargetPackTypeTraits :: __convertInitIndex ) {
                    * static_cast < typename __UnionTargetPackTypeTraits :: __ConvertInitType * > ( static_cast < void * > ( & this->_memory [0U] ) ) = cds :: forward < __TargetElementType > ( element );
                    return;
                }

                __VariadicUnion :: __vu_callTable (
                        this->_holder,
                        __VariadicUnion :: __CallTableIndexSequence ()
                )->_destructor (
                        static_cast < void * > ( & this->_memory [0U] )
                );

                this->_holder = __UnionTargetPackTypeTraits :: __convertInitIndex;
                (void) new ( & this->_memory [0U] ) typename __UnionTargetPackTypeTraits :: __ConvertInitType (
                        std :: forward < __TargetElementType > ( element )
                );
            }


            template < typename ... __Types >
            template <
                    typename __TargetElementType,           /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __UnionTargetPackTypeTraits,   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    cds :: meta :: EnableIf <
                            ! cds :: meta :: isSame < cds :: meta :: Decay < __TargetElementType >, __VariadicUnion < __Types ... > > () &&
                            ! __UnionTargetPackTypeTraits :: __directInit &&
                            ! __UnionTargetPackTypeTraits :: __convertInit
                    >
            > __CDS_cpplang_NonConstConstexprMemberFunction auto __VariadicUnion <
                    __Types ...
            > :: __vu_reset (
                    __TargetElementType && element
            ) noexcept -> void {

                static_assert (
                        __UnionTargetPackTypeTraits :: __directInit || __UnionTargetPackTypeTraits :: __convertInit,
                        "Requested Value cannot be assigned to Union due to none of its' variants "
                        "having a direct constructor and assignment operator or a conversion "
                        "constructor and assignment operator for the requested value"
                );
            }


            template < typename ... __Types >
            template <
                    typename     __TargetElementType,                           /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename ... __ConstructionArguments                        /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > __CDS_cpplang_NonConstConstexprMemberFunction auto __VariadicUnion <
                    __Types ...
            > :: __vu_emplace (
                    __ConstructionArguments && ... arguments
            ) noexcept -> cds :: meta :: EnableIf <
                    __UnionPackTypeTraits < __TargetElementType, __Types ... > :: __directInit,
                    typename __UnionPackTypeTraits < __TargetElementType, __Types ... > :: __DirectInitType &
            > {

                using __UnionTargetPackTypeTraits = __UnionPackTypeTraits < __TargetElementType, __Types ... >;

                __VariadicUnion :: __vu_callTable (
                        this->_holder, __VariadicUnion :: __CallTableIndexSequence ()
                )->_destructor (
                        static_cast < void * > ( & this->_memory [0U] )
                );

                this->_holder = __UnionTargetPackTypeTraits :: __directInitIndex;
                return * new ( & this->_memory [0U] ) typename __UnionTargetPackTypeTraits :: __DirectInitType (
                        std :: forward < __ConstructionArguments > ( arguments ) ...
                );
            }


            template < typename ... __Types >
            template <
                    typename     __TargetElementType,                           /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename ... __ConstructionArguments                        /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > __CDS_cpplang_NonConstConstexprMemberFunction auto __VariadicUnion <
                    __Types ...
            > :: __vu_emplace (
                    __ConstructionArguments && ... arguments
            ) noexcept -> cds :: meta :: EnableIf <
                    ! __UnionPackTypeTraits < __TargetElementType, __Types ... > :: __directInit,
                    __TargetElementType &
            > {

                static_assert (
                        __UnionPackTypeTraits < __TargetElementType, __Types ... > :: __directInit,
                        "Union Emplace is not possible for requested Type due to it not being "
                        "a variant of this Union"
                );
            }


            template < typename ... __Types >
            template < typename __ElementType >
            __CDS_cpplang_NonConstConstexprMemberFunction auto __VariadicUnion <
                    __Types ...
            > :: __vu_get () noexcept -> __ElementType * {

                if ( this->_holder != __UnionPackTypeTraits < __ElementType, __Types ... > :: __directInitIndex ) {
                    return nullptr;
                }

                return static_cast < __ElementType * > ( static_cast < void * > ( & this->_memory [0U] ) );
            }


            template < typename ... __Types >
            template < typename __ElementType >
            __CDS_cpplang_NonConstConstexprMemberFunction auto __VariadicUnion <
                    __Types ...
            > :: __vu_getConst () const noexcept -> __ElementType const * {

                if ( this->_holder != __UnionPackTypeTraits < __ElementType, __Types ... > :: __directInitIndex ) {
                    return nullptr;
                }

                return static_cast < __ElementType const * > ( static_cast < void const * > ( & this->_memory [0U] ) );
            }


            template < typename ... __Types >
            __CDS_OptimalInline auto __VariadicUnion <
                    __Types ...
            > :: __vu_toString () const noexcept -> String {

                return __VariadicUnion :: __vu_callTable (
                        this->_holder,
                        __VariadicUnion :: __CallTableIndexSequence ()
                )->_toString (
                        static_cast < void const * > ( & this->_memory [0U] )
                );
            }


            template < typename ... __Types >
            constexpr auto __VariadicUnion <
                    __Types ...
            > :: __vu_hash () const noexcept -> Size {

                return __VariadicUnion :: __vu_callTable (
                        this->_holder,
                        __VariadicUnion :: __CallTableIndexSequence ()
                )->_hash (
                        static_cast < void const * > ( & this->_memory [0U] )
                );
            }


            template < typename ... __Types >
            constexpr auto __VariadicUnion <
                    __Types ...
            > :: __vu_equals (
                    __VariadicUnion const & otherUnion
            ) const noexcept -> bool {

                return
                        this->_holder == otherUnion._holder &&
                        __VariadicUnion :: __vu_callTable (
                                this->_holder,
                                __VariadicUnion :: __CallTableIndexSequence ()
                        )->_equals (
                                static_cast < void const * > ( & this->_memory [0U] ),
                                static_cast < void const * > ( & otherUnion._memory [0U] )
                        );
            }

            template < typename ... __Types >
            template < uint32 ... __indexSequence >
            constexpr __VariadicUnionInterfaceEntryCallTable const * const __VariadicUnion <
                    __Types ...
            > :: __CallTable <
                    __indexSequence ...
            > :: _callTable [sizeof ... (__Types) + 1U];

        } /* namespace __impl */
    } /* namespace __hidden */
} /* namespace cds */

#endif /* __CDS_UNION_VARIADIC_UNION_IMPL_HPP__ */
