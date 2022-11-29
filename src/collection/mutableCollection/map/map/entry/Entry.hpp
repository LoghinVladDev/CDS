/* NOLINT(llvm-header-guard)
 * Created by loghin on 6/15/22.
 */

#ifndef __CDS_MAP_ENTRY_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_MAP_ENTRY_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

namespace cds {             /* NOLINT(modernize-concat-nested-namespaces) */
    namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        namespace __impl {  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            template < typename __KeyType, typename __ValueType >   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            class __MapEntry {                                      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            private:
                template <
                        typename __TKeyType,                            /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        typename __TValueType                           /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                > friend class cds :: __hidden :: __impl :: __MapEntry; /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            public: /* NOLINT(readability-redundant-access-specifiers) */
                using KeyType   = __KeyType;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                using ValueType = __ValueType;

            private:    /* NOLINT(readability-redundant-access-specifiers) */
                __KeyType         _key;

            private:    /* NOLINT(readability-redundant-access-specifiers) */
                __ValueType       _value;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                constexpr __MapEntry () noexcept = delete;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                constexpr __MapEntry (
                        __MapEntry const & entry
                ) noexcept (
                        noexcept ( KeyType ( entry._key ) ) &&
                        noexcept ( ValueType ( entry._value ) )
                );

            public:                                                                                                 /* NOLINT(readability-redundant-access-specifiers) */
                template <
                        typename __DecayedKeyType = cds :: meta :: Decay < __KeyType >,                             /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        cds :: meta :: EnableIf < ! cds :: meta :: isSame < __DecayedKeyType, __KeyType > () > = 0  /* NOLINT(clion-misra-cpp2008-5-3-1) */
                > constexpr __MapEntry (                                                                            /* NOLINT(*-explicit-*) */
                        __MapEntry < __DecayedKeyType, __ValueType > const & entry
                ) noexcept (
                        noexcept ( KeyType ( entry.key() ) ) &&
                        noexcept ( ValueType ( entry.value() ) )
                );

            public:                                     /* NOLINT(readability-redundant-access-specifiers) */
                template <
                        typename __TKeyType,            /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        typename __TValueType           /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                > __CDS_Implicit constexpr __MapEntry ( /* NOLINT(*-explicit-*) */
                        cds :: Pair < __TKeyType, __TValueType > const & pair
                ) noexcept (
                        noexcept ( KeyType ( pair.first() ) ) &&
                        noexcept ( ValueType ( pair.second() ) )
                );

            public: /* NOLINT(readability-redundant-access-specifiers) */
                constexpr __MapEntry (
                        __MapEntry && entry
                ) noexcept (
                        noexcept ( KeyType ( std :: move ( entry._key ) ) ) &&
                        noexcept ( ValueType ( std :: move ( entry._value ) ) )
                );

            public:                                                                                                 /* NOLINT(readability-redundant-access-specifiers) */
                template <
                        typename __DecayedKeyType = cds :: meta :: Decay < __KeyType >,                             /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        cds :: meta :: EnableIf < ! cds :: meta :: isSame < __DecayedKeyType, __KeyType > () > = 0  /* NOLINT(clion-misra-cpp2008-5-3-1) */
                > constexpr __MapEntry (                                                                            /* NOLINT(*-explicit-*) */
                        __MapEntry < __DecayedKeyType, __ValueType > && entry
                ) noexcept (
                        noexcept ( KeyType ( std :: move ( entry._key ) ) ) &&
                        noexcept ( ValueType ( std :: move ( entry._value ) ) )
                );

            public:                                     /* NOLINT(readability-redundant-access-specifiers) */
                template <
                        typename __TKeyType,            /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        typename __TValueType           /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                > __CDS_Implicit constexpr __MapEntry ( /* NOLINT(*-explicit-*) */
                        cds :: Pair < __TKeyType, __TValueType > && pair
                ) noexcept (
                        noexcept ( KeyType ( std :: move ( pair._first ) ) ) &&
                        noexcept ( ValueType ( std :: move ( pair._second ) ) )
                );

            public: /* NOLINT(readability-redundant-access-specifiers) */
                ~__MapEntry () noexcept = default;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                __CDS_cpplang_NonConstConstexprMemberFunction auto operator = ( /* NOLINT(cppcoreguidelines-c-copy-assignment-signature, misc-unconventional-assign-operator) */
                        __MapEntry const & entry
                ) noexcept (
                        noexcept ( cds :: meta :: referenceOf < __ValueType > () = entry._value )
                ) -> __MapEntry &;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                __CDS_cpplang_NonConstConstexprMemberFunction auto operator = ( /* NOLINT(cppcoreguidelines-c-copy-assignment-signature, misc-unconventional-assign-operator) */
                        __MapEntry && entry
                ) noexcept (
                        noexcept ( cds :: meta :: referenceOf < __ValueType > () = std :: move ( entry._value ) )
                ) -> __MapEntry &;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                template < typename __TKeyType, typename __TValueType > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                constexpr __MapEntry (
                        __TKeyType      && key,
                        __TValueType    && value
                ) noexcept (
                        noexcept ( __KeyType ( std :: forward < __TKeyType > ( key ) ) ) &&
                        noexcept ( __ValueType ( std :: forward < __TValueType > ( value ) ) )
                );

            public: /* NOLINT(readability-redundant-access-specifiers) */
                __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator == ( /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-non-private-member-variables-in-classes) */
                        __MapEntry const & entry
                ) const noexcept -> bool;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator != ( /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-non-private-member-variables-in-classes) */
                        __MapEntry const & entry
                ) const noexcept -> bool;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                __CDS_NoDiscard constexpr auto hash () const noexcept -> Size;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                __CDS_NoDiscard constexpr auto key () const noexcept -> KeyType const &;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                __CDS_NoDiscard constexpr auto value () const noexcept -> ValueType const &;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto value () noexcept -> ValueType &;    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-non-private-member-variables-in-classes) */

            public: /* NOLINT(readability-redundant-access-specifiers) */
                __CDS_Deprecated __CDS_NoDiscard constexpr auto first () const noexcept -> KeyType const &; /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-non-private-member-variables-in-classes) */

            public: /* NOLINT(readability-redundant-access-specifiers) */
                __CDS_Deprecated __CDS_NoDiscard constexpr auto second () const noexcept -> ValueType const &;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                __CDS_Deprecated __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto second () noexcept -> ValueType &;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                __CDS_Deprecated __CDS_NoDiscard constexpr auto getFirst () const noexcept -> KeyType const &;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                __CDS_Deprecated __CDS_NoDiscard constexpr auto getSecond () const noexcept -> ValueType const &;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                __CDS_Deprecated __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto getSecond () noexcept -> ValueType &;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                __CDS_NoDiscard auto toString () const noexcept -> String;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                __CDS_NoDiscard __CDS_Implicit operator String () const noexcept;   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-non-private-member-variables-in-classes, *-explicit-*) */

            public: /* NOLINT(readability-redundant-access-specifiers) */
                template < typename __TKeyType, typename __TValueType > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                friend auto operator << (
                        std :: ostream                                & out,
                        __MapEntry < __TKeyType, __TValueType > const & object
                ) noexcept -> std::ostream &;
            };

        } /* namespace __impl */
    } /* namespace __hidden */
} /* namespace cds */

#endif /* __CDS_MAP_ENTRY_HPP__ */
