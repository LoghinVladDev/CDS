/*
 * Created by loghin on 6/15/22.
 */

#ifndef __CDS_MAP_ENTRY_HPP__
#define __CDS_MAP_ENTRY_HPP__ /* NOLINT(bugprone-reserved-identifier) */

namespace cds {             /* NOLINT(modernize-concat-nested-namespaces) */
    namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier) */
        namespace __impl {  /* NOLINT(bugprone-reserved-identifier) */

            template < typename __KeyType, typename __ValueType >   /* NOLINT(bugprone-reserved-identifier) */
            class __MapEntry {                                      /* NOLINT(bugprone-reserved-identifier) */

            public:
                using KeyType   = __KeyType;

            public:
                using ValueType = __ValueType;

            private:
                __KeyType         _key;

            private:
                __ValueType       _value;

            public:
                constexpr __MapEntry () noexcept = delete;

            public:
                constexpr __MapEntry (
                        __MapEntry const & entry
                ) noexcept (
                        noexcept ( KeyType ( entry._key ) ) &&
                        noexcept ( ValueType ( entry._value ) )
                );

            public:
                constexpr __MapEntry (
                        __MapEntry && entry
                ) noexcept (
                        noexcept ( KeyType ( std :: move ( entry._key ) ) ) &&
                        noexcept ( ValueType ( std :: move ( entry._value ) ) )
                );

            public:
                __CDS_cpplang_NonConstConstexprMemberFunction auto operator = (
                        __MapEntry const & entry
                ) noexcept (
                        noexcept ( cds :: meta :: referenceOf < __ValueType > () = entry._value )
                ) -> __MapEntry &;

            public:
                __CDS_cpplang_NonConstConstexprMemberFunction auto operator = (
                        __MapEntry && entry
                ) noexcept (
                        noexcept ( cds :: meta :: referenceOf < __ValueType > () = std :: move ( entry._value ) )
                ) -> __MapEntry &;

            public:
                template < typename __TKeyType, typename __TValueType > /* NOLINT(bugprone-reserved-identifier) */
                constexpr __MapEntry (
                        __TKeyType      && key,
                        __TValueType    && value
                ) noexcept (
                        noexcept ( __KeyType ( std :: forward < __TKeyType > ( key ) ) ) &&
                        noexcept ( __ValueType ( std :: forward < __TValueType > ( value ) ) )
                );

            public:
                __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator == (
                        __MapEntry const & entry
                ) const noexcept -> bool;

            public:
                __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator != (
                        __MapEntry const & entry
                ) const noexcept -> bool;

            public:
                __CDS_NoDiscard constexpr auto hash () const noexcept -> Size;

            public:
                __CDS_NoDiscard constexpr auto key () const noexcept -> KeyType const &;

            public:
                __CDS_NoDiscard constexpr auto value () const noexcept -> ValueType const &;

            public:
                __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto value () noexcept -> ValueType &;

            public:
                __CDS_Deprecated __CDS_NoDiscard constexpr auto first () const noexcept -> KeyType const &;

            public:
                __CDS_Deprecated __CDS_NoDiscard constexpr auto second () const noexcept -> ValueType const &;

            public:
                __CDS_Deprecated __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto second () noexcept -> ValueType &;

            public:
                __CDS_Deprecated __CDS_NoDiscard constexpr auto getFirst () const noexcept -> KeyType const &;

            public:
                __CDS_Deprecated __CDS_NoDiscard constexpr auto getSecond () const noexcept -> ValueType const &;

            public:
                __CDS_Deprecated __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto getSecond () noexcept -> ValueType &;

            public:
                __CDS_NoDiscard auto toString () const noexcept -> String;

            public:
                __CDS_NoDiscard __CDS_Implicit operator String () const noexcept;

            public:
                template < typename __TKeyType, typename __TValueType > /* NOLINT(bugprone-reserved-identifier) */
                friend auto operator << (
                        std :: ostream                                & out,
                        __MapEntry < __TKeyType, __TValueType > const & object
                ) noexcept -> std::ostream &;
            };

        }
    }
}

#endif /* __CDS_MAP_ENTRY_HPP__ */
