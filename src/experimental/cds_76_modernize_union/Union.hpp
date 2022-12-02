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


            template < typename __UnionType, typename ... __EmptyTypePack >
            struct __VariadicUnionEntry {

                constexpr static Size const __memoryRequired = 0ULL;
            };


            template < typename __UnionType, typename __FirstType, typename ... __RemainingTypes >
            struct __VariadicUnionEntry < __UnionType, __FirstType, __RemainingTypes ... > : __VariadicUnionEntry < __UnionType, __RemainingTypes ... > {

                using __NextEntry = __VariadicUnionEntry < __UnionType, __RemainingTypes ... >;

                constexpr static Size const __memoryRequired = cds :: maxOf ( sizeof ( __FirstType ), __VariadicUnionEntry < __UnionType, __RemainingTypes ... > :: __memoryRequired );
            };


            template < typename ... __Types >
            struct __VariadicUnion : __VariadicUnionEntry < __VariadicUnion < __Types ... >, __Types ... > {

                using __EntryList = __VariadicUnionEntry < __VariadicUnion < __Types ... >, __Types ... >;

                uint32 _holder { sizeof ... ( __Types ) };
                uint8  _memory [ __EntryList :: __memoryRequired ];

                template <
                        typename __TargetElementType,
                        typename __UnionTargetInitTraits = __UnionInitTraits < __TargetElementType, __Types ... >,
                        cds :: meta :: EnableIf <
                                ! cds :: meta :: isSame < cds :: meta :: Decay < __TargetElementType >, __VariadicUnion < __Types ... > > () &&
                                __UnionTargetInitTraits :: __directInit
                        > = 0
                > __CDS_cpplang_ConstexprConstructorNonEmptyBody __VariadicUnion (
                        __TargetElementType && element
                ) noexcept {

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
                ) noexcept {

                    (void) new ( & this->_memory [0U] ) typename __UnionTargetInitTraits :: __ConvertInitType ( std :: forward < __TargetElementType > ( element ) );
                }
            };

        }
    }

    template < typename ... __Types > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    class Union : public Object, private __hidden :: __impl :: __VariadicUnion < __Types ... > {

    public:
        Union () noexcept;

    public:
        template <
                typename __ElementType,
                cds :: meta :: EnableIf <
                        ! cds :: meta :: isSame < cds :: meta :: Decay < __ElementType >, Union < __Types ... > > () && (
                                __hidden :: __impl :: __UnionInitTraits < __ElementType, __Types ... > :: __directInit ||
                                __hidden :: __impl :: __UnionInitTraits < __ElementType, __Types ... > :: __convertInit
                        )
                > = 0
        > Union (
                __ElementType && value
        ) noexcept :
                __hidden :: __impl :: __VariadicUnion < __Types ... > ( std :: forward < __ElementType > ( value ) ) {

        }
    };

} /* namespace cds */

#endif /* __CDS_UNION_HPP__ */
