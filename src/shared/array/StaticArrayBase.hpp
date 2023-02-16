/*
 * Created by loghin on 16/02/23.
 */

#ifndef __CDS_STATIC_ARRAY_BASE_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_STATIC_ARRAY_BASE_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

namespace cds {             /* NOLINT(modernize-concat-nested-namespaces) */
    namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        namespace __impl {  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            constexpr static auto __staticArrayMemoryContainerStackLimit (  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    Size limit
            ) noexcept -> bool {

                return limit < 1024U; /* NOLINT(*-magic-numbers) */
            }


            template <
                    typename    __ElementType,      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    Size        __size,             /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    bool                        = __staticArrayMemoryContainerStackLimit (sizeof (__ElementType) * __size)
            > struct __StaticArrayMemoryContainer { /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            };


            template <
                    typename    __ElementType,  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    Size        __size          /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > struct __StaticArrayMemoryContainer < __ElementType, __size, true > {
                __ElementType _samc_data [__size]; /* NOLINT(*-c-arrays) */
            };


            template <
                    typename    __ElementType,  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    Size        __size          /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > struct __StaticArrayMemoryContainer < __ElementType, __size, false > {

                __ElementType * _samc_data;     /* NOLINT(misc-non-private-member-variables-in-classes) */

                __CDS_cpplang_ConstexprDynamicAllocation __StaticArrayMemoryContainer () {
                    this->_samc_data = __allocation :: __allocPrimitiveArray < __ElementType > (__size);
                }

                __CDS_cpplang_ConstexprDynamicAllocation ~__StaticArrayMemoryContainer () { /* NOLINT(*-default) */
                    __allocation :: __freePrimitiveArray ( this->_samc_data );
                }

                __StaticArrayMemoryContainer (__StaticArrayMemoryContainer const &) = delete;
                __StaticArrayMemoryContainer (__StaticArrayMemoryContainer &&) = delete;

                auto operator = (__StaticArrayMemoryContainer const &) -> __StaticArrayMemoryContainer & = delete;
                auto operator = (__StaticArrayMemoryContainer &&) -> __StaticArrayMemoryContainer & = delete;
            };


            template <
                    typename                                                                            __ElementType,      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    Size                                                                                __size,             /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: PredicateFunction < __ElementType const &, __ElementType const & >    __equals,           /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                            __MemoryContainer   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > class __StaticArrayBase {                                                                                     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-member-init) */

            protected:  /* NOLINT(readability-redundant-access-specifiers) */
                using ElementType                   = __ElementType;

            public:     /* NOLINT(readability-redundant-access-specifiers) */
                using __sab_Iterator                = ForwardAddressIterator < __ElementType >;

            public:     /* NOLINT(readability-redundant-access-specifiers) */
                using __sab_ConstIterator           = ForwardAddressIterator < __ElementType const >;

            public:     /* NOLINT(readability-redundant-access-specifiers) */
                using __sab_ReverseIterator         = BackwardAddressIterator < __ElementType >;

            public:     /* NOLINT(readability-redundant-access-specifiers) */
                using __sab_ConstReverseIterator    = BackwardAddressIterator < __ElementType const >;

            public:
                template < typename __ServerType >  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                class __Dispatcher;                 /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            private:    /* NOLINT(readability-redundant-access-specifiers) */
                __CDS_NoUniqueAddress __MemoryContainer _sab_memory;    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            protected:
                constexpr __StaticArrayBase () noexcept = default;

            protected:
                __StaticArrayBase (
                        __StaticArrayBase const &
                ) noexcept;

            protected:
                __StaticArrayBase (
                        __StaticArrayBase &&
                ) noexcept;

            public:
                constexpr ~__StaticArrayBase () noexcept = default;

            protected:
                auto operator = (
                        __StaticArrayBase const &
                ) noexcept -> __StaticArrayBase &;

            protected:
                auto operator = (
                        __StaticArrayBase &&
                ) noexcept -> __StaticArrayBase &;

            protected:
                __CDS_NoDiscard constexpr auto __sab_size () const noexcept -> Size;

            protected:
                __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto __sab_get (
                        Index index
                ) noexcept -> __ElementType *;

            protected:
                __CDS_NoDiscard constexpr auto __sab_get (
                        Index index
                ) const noexcept -> __ElementType const *;

            protected:
                __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto __sab_begin () noexcept -> __sab_Iterator;

            protected:
                __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto __sab_end () noexcept -> __sab_Iterator;

            protected:
                __CDS_NoDiscard constexpr auto __sab_cbegin () const noexcept -> __sab_ConstIterator;

            protected:
                __CDS_NoDiscard constexpr auto __sab_cend () const noexcept -> __sab_ConstIterator;

            protected:
                __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto __sab_rbegin () noexcept -> __sab_ReverseIterator;

            protected:
                __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto __sab_rend () noexcept -> __sab_ReverseIterator;

            protected:
                __CDS_NoDiscard constexpr auto __sab_crbegin () const noexcept -> __sab_ConstReverseIterator;

            protected:
                __CDS_NoDiscard constexpr auto __sab_crend () const noexcept -> __sab_ConstReverseIterator;

            protected:
                __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto __sab_data () noexcept -> __ElementType *;

            protected:
                __CDS_NoDiscard constexpr auto __sab_data () const noexcept -> __ElementType const *;

            protected:
                auto __sab_copy (
                        __StaticArrayBase const & array
                ) noexcept -> void;

            protected:
                auto __sab_move (
                        __StaticArrayBase && array
                ) noexcept -> void;

            protected:
                __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto __sab_equals (
                        __StaticArrayBase const & array
                ) noexcept -> bool;

            protected:
                template <
                        typename __Comparator = decltype ( & cds :: predicates :: lessThan < __ElementType > )
                > auto __sab_sort (
                        __Comparator const & comparator = & cds :: predicates :: lessThan < __ElementType >
                ) noexcept -> void;
            };


            template <
                    typename                                                                            __ElementType,      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    Size                                                                                __size,             /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: PredicateFunction < __ElementType const &, __ElementType const & >    __equals,           /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                            __MemoryContainer   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > template <
                    typename __ServerType
            > class __StaticArrayBase <
                    __ElementType,
                    __size,
                    __equals,
                    __MemoryContainer
            > :: __Dispatcher :
                    public __IterableServerDispatcher <
                            __ServerType,
                            __StaticArrayBase < __ElementType, __size, __equals, __MemoryContainer >,
                            __ElementType,
                            ForwardAddressIterator < __ElementType const >,
                            & __StaticArrayBase < __ElementType, __size, __equals, __MemoryContainer > :: __sab_cbegin,
                            & __StaticArrayBase < __ElementType, __size, __equals, __MemoryContainer > :: __sab_cend
                    > {};


        } /* namespace __impl */
    } /* namespace __hidden */
} /* namespace cds */

#endif /* __CDS_STATIC_ARRAY_BASE_HPP__ */
