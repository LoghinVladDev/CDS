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
            namespace __impl {  // NOLINT(bugprone-reserved-identifier)

                template < typename __Type >    // NOLINT(bugprone-reserved-identifier)
                class __ForwardContainer {      // NOLINT(bugprone-reserved-identifier)

                public:
                    union {
                        __Type       * _pObject;
                        __Type const * _pConstObject;

                        void   const * _pAny;
                    };

                public:
                    bool      _forward { false };

                public:
                    constexpr __ForwardContainer () noexcept;

                public:
                    __CDS_Explicit constexpr __ForwardContainer (
                            __Type * pObject
                    ) noexcept;

                public:
                    __CDS_Explicit constexpr __ForwardContainer (
                            __Type const * pObject
                    ) noexcept;
                };

                template < typename __KeyType, typename __ValueType > // NOLINT(bugprone-reserved-identifier)
                class __MapEntry { // NOLINT(bugprone-reserved-identifier)

                private:
                    template <
                            typename __TKeyType, // NOLINT(bugprone-reserved-identifier)
                            typename __TValueType // NOLINT(bugprone-reserved-identifier)
                    > friend class cds :: experimental :: Map; // NOLINT(bugprone-reserved-identifier)

                private:
                    template <
                            typename __TKeyType = __KeyType, // NOLINT(bugprone-reserved-identifier)
                            cds :: meta :: EnableIf <
                                    cds :: meta :: isCopyConstructible < __TKeyType > () &&
                                    cds :: meta :: isMoveConstructible < __TKeyType > ()
                            > = 0
                    > __CDS_cpplang_ConstexprPlacementNew auto moveOrCopyKeyTo (
                            __MapEntry * entry
                    ) noexcept -> void;

                private:
                    template <
                            typename __TKeyType = __KeyType, // NOLINT(bugprone-reserved-identifier)
                            cds :: meta :: EnableIf <
                                    cds :: meta :: isCopyConstructible < __TKeyType > () &&
                                    ! cds :: meta :: isMoveConstructible < __TKeyType > ()
                            > = 0
                    > __CDS_cpplang_ConstexprPlacementNew auto moveOrCopyKeyTo (
                            __MapEntry * entry
                    ) noexcept -> void;

                private:
                    template <
                            typename __TKeyType = __KeyType, // NOLINT(bugprone-reserved-identifier)
                            cds :: meta :: EnableIf <
                                    ! cds :: meta :: isCopyConstructible < __TKeyType > () &&
                                    cds :: meta :: isMoveConstructible < __TKeyType > ()
                            > = 0
                    > __CDS_cpplang_ConstexprPlacementNew auto moveOrCopyKeyTo (
                            __MapEntry * entry
                    ) noexcept -> void;

                private:
                    template <
                            typename __TKeyType = __KeyType, // NOLINT(bugprone-reserved-identifier)
                            cds :: meta :: EnableIf <
                                    ! cds :: meta :: isCopyConstructible < __TKeyType > () &&
                                    ! cds :: meta :: isMoveConstructible < __TKeyType > ()
                            > = 0
                    > constexpr auto moveOrCopyKeyTo (
                            __MapEntry * entry
                    ) noexcept -> void;

                private:
                    template <
                            typename __TValueType = __ValueType, // NOLINT(bugprone-reserved-identifier)
                            cds :: meta :: EnableIf <
                                    cds :: meta :: isCopyConstructible < __TValueType > () &&
                                    cds :: meta :: isMoveConstructible < __TValueType > ()
                            > = 0
                    > __CDS_cpplang_ConstexprPlacementNew auto moveOrCopyValueTo (
                            __MapEntry * entry,
                            bool         isNew
                    ) noexcept -> void;

                private:
                    template <
                            typename __TValueType = __ValueType, // NOLINT(bugprone-reserved-identifier)
                            cds :: meta :: EnableIf <
                                    cds :: meta :: isCopyConstructible < __TValueType > () &&
                                    ! cds :: meta :: isMoveConstructible < __TValueType > ()
                            > = 0
                    > __CDS_cpplang_ConstexprPlacementNew auto moveOrCopyValueTo (
                            __MapEntry * entry,
                            bool         isNew
                    ) noexcept -> void;

                private:
                    template <
                            typename __TValueType = __ValueType, // NOLINT(bugprone-reserved-identifier)
                            cds :: meta :: EnableIf <
                                    ! cds :: meta :: isCopyConstructible < __TValueType > () &&
                                    cds :: meta :: isMoveConstructible < __TValueType > ()
                            > = 0
                    > __CDS_cpplang_ConstexprPlacementNew auto moveOrCopyValueTo (
                            __MapEntry * entry,
                            bool         isNew
                    ) noexcept -> void;

                private:
                    template <
                            typename __TValueType = __ValueType, // NOLINT(bugprone-reserved-identifier)
                            cds :: meta :: EnableIf <
                                    ! cds :: meta :: isCopyConstructible < __TValueType > () &&
                                    ! cds :: meta :: isMoveConstructible < __TValueType > ()
                            > = 0
                    > constexpr auto moveOrCopyValueTo (
                            __MapEntry * entry,
                            bool         isNew
                    ) noexcept -> void;

                private:
                    __CDS_NoDiscard constexpr auto empty () const noexcept -> bool;

                public:
                    using KeyType   = __KeyType;

                public:
                    using ValueType = __ValueType;

                private:
                    __ForwardContainer < KeyType > _key;

                private:
                    __ForwardContainer < ValueType > _value;

                public:
                    constexpr __MapEntry () noexcept = default;

                public:
                    constexpr __MapEntry (
                            KeyType     const & key,
                            ValueType   const & value
                    ) noexcept;

                public:
                    constexpr __MapEntry (
                            KeyType     const & key,
                            ValueType        && value
                    ) noexcept;

                public:
                    constexpr __MapEntry (
                            KeyType          && key,
                            ValueType   const & value
                    ) noexcept;

                public:
                    constexpr __MapEntry (
                            KeyType          && key,
                            ValueType        && value
                    ) noexcept;

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
