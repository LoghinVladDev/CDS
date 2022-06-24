//
// Created by loghin on 6/15/22.
//

#ifndef __CDS_EX_MAP_ENTRY_HPP__
#define __CDS_EX_MAP_ENTRY_HPP__

namespace cds {                 // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {    // NOLINT(modernize-concat-nested-namespaces)

        template < typename __KeyType, typename __ValueType > // NOLINT(bugprone-reserved-identifier)
        class Map;

        namespace __hidden {    // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier)
            namespace __impl {

                template < typename __KeyType, typename __ValueType > // NOLINT(bugprone-reserved-identifier)
                class __MapEntry { // NOLINT(bugprone-reserved-identifier)

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
                    template <
                            typename __TKeyType = KeyType,      // NOLINT(bugprone-reserved-identifier)
                            typename __TValueType = ValueType,  // NOLINT(bugprone-reserved-identifier)
                            cds :: meta :: EnableIf <
                                    cds :: meta :: isCopyConstructible < __TKeyType > () &&
                                    cds :: meta :: isCopyConstructible < __TValueType > ()
                            > = 0
                    > __CDS_Implicit constexpr __MapEntry ( // NOLINT(google-explicit-constructor)
                            __MapEntry const & entry
                    ) noexcept (
                            noexcept ( KeyType ( entry._key ) ) &&
                            noexcept ( ValueType ( entry._value ) )
                    );

                public:
                    template <
                            typename __TKeyType = KeyType,      // NOLINT(bugprone-reserved-identifier)
                            typename __TValueType = ValueType,  // NOLINT(bugprone-reserved-identifier)
                            cds :: meta :: EnableIf <
                                    cds :: meta :: isMoveConstructible < __TKeyType > () &&
                                    cds :: meta :: isMoveConstructible < __TValueType > ()
                            > = 0
                    > __CDS_Implicit constexpr __MapEntry ( // NOLINT(google-explicit-constructor)
                            __MapEntry && entry
                    ) noexcept (
                            noexcept ( KeyType ( std :: move ( entry._key ) ) ) &&
                            noexcept ( ValueType ( std :: move ( entry._value ) ) )
                    );

                public:
                    template < typename __TKeyType, typename __TValueType > // NOLINT(bugprone-reserved-identifier)
                    constexpr __MapEntry (
                            __TKeyType      && key,
                            __TValueType    && value
                    ) noexcept (
                            noexcept ( __KeyType ( std :: forward < __TKeyType > ( key ) ) ) &&
                            noexcept ( __ValueType ( std :: forward < __TValueType > ( value ) ) )
                    );

                public:
                    __CDS_NoDiscard constexpr auto operator == (
                            __MapEntry const & entry
                    ) const noexcept -> bool;

                public:
                    __CDS_NoDiscard constexpr auto hash () const noexcept -> Size;

                public:
                    constexpr auto key () const noexcept -> KeyType const &;

                public:
                    constexpr auto value () const noexcept -> ValueType const &;

                public:
                    __CDS_cpplang_NonConstConstexprMemberFunction auto value () noexcept -> ValueType &;

                public:
                    __CDS_Deprecated constexpr auto first () const noexcept -> KeyType const &;

                public:
                    __CDS_Deprecated constexpr auto second () const noexcept -> ValueType const &;

                public:
                    __CDS_Deprecated __CDS_cpplang_NonConstConstexprMemberFunction auto second () noexcept -> ValueType &;

                public:
                    __CDS_Deprecated constexpr auto getFirst () const noexcept -> KeyType const &;

                public:
                    __CDS_Deprecated constexpr auto getSecond () const noexcept -> ValueType const &;

                public:
                    __CDS_Deprecated __CDS_cpplang_NonConstConstexprMemberFunction auto getSecond () noexcept -> ValueType &;

                public:
                    __CDS_NoDiscard auto toString () const noexcept -> String;
                };

            }
        }
    }
}

#endif // __CDS_EX_MAP_ENTRY_HPP__
