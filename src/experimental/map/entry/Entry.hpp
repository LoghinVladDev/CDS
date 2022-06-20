//
// Created by loghin on 6/15/22.
//

#ifndef __CDS_EX_MAP_ENTRY_HPP__
#define __CDS_EX_MAP_ENTRY_HPP__

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental { // NOLINT(modernize-concat-nested-namespaces)

        template < typename __KeyType, typename __ValueType > // NOLINT(bugprone-reserved-identifier)
        class Map;

        namespace __hidden { // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier)
            namespace __impl { // NOLINT(bugprone-reserved-identifier)

                template <
                        typename __KeyType, // NOLINT(bugprone-reserved-identifier)
                        typename __ValueType, // NOLINT(bugprone-reserved-identifier)
                        typename __KeySetType, // NOLINT(bugprone-reserved-identifier)
                        typename __ValueCollectionType, // NOLINT(bugprone-reserved-identifier)
                        typename __EntryAssociatorType, // NOLINT(bugprone-reserved-identifier)
                        cds :: meta :: EnableIf <
                                cds :: meta :: isDerivedFrom < __KeySetType, cds :: experimental :: Set < __KeyType > > () &&
                                cds :: meta :: isDerivedFrom < __ValueCollectionType, cds :: experimental :: Collection < __ValueType > > ()
                        > = 0
                > class __BaseMap; // NOLINT(bugprone-reserved-identifier)

                template < typename __Type > // NOLINT(bugprone-reserved-identifier)
                class __ForwardContainer { // NOLINT(bugprone-reserved-identifier)

                public:
                    union {
                        __Type       * _pObject;
                        __Type const * _pConstObject;

                        void   const * _pAny;
                    };

                public:
                    bool      _forward;

                public:
                    constexpr __ForwardContainer () noexcept :
                            _forward ( false ),
                            _pAny ( nullptr ) {

                    }
//                    constexpr __ForwardContainer (
//                            __ForwardContainer const & container
//                    ) noexcept;

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
                    template < typename __TKeyType = __KeyType, cds :: meta :: EnableIf < cds :: meta :: isCopyConstructible < __TKeyType > () && cds :: meta :: isMoveConstructible < __TKeyType > () > = 0 >
                    __CDS_OptimalInline auto moveOrCopyKeyTo (
                            __MapEntry * entry
                    ) noexcept -> void {

                        if ( entry->_key._pObject != nullptr ) {
                            return;
                        }

                        if ( this->_key._forward ) {
                            entry->_key._pObject = Memory :: instance().create < KeyType > ( std :: move ( * this->_key._pObject ) );
                            return;
                        }

                        entry->_key._pObject = Memory :: instance().create < KeyType > ( * this->_key._pConstObject );
                    }

                private:
                    template < typename __TKeyType = __KeyType, cds :: meta :: EnableIf < cds :: meta :: isCopyConstructible < __TKeyType > () && ! cds :: meta :: isMoveConstructible < __TKeyType > () > = 0 >
                    __CDS_OptimalInline auto moveOrCopyKeyTo (
                            __MapEntry * entry
                    ) noexcept -> void {

                        if ( entry->_key._pObject != nullptr ) {
                            return;
                        }

                        entry->_key._pObject = Memory :: instance().create < KeyType > ( * this->_key._pConstObject );
                    }

                private:
                    template < typename __TKeyType = __KeyType, cds :: meta :: EnableIf < ! cds :: meta :: isCopyConstructible < __TKeyType > () && cds :: meta :: isMoveConstructible < __TKeyType > () > = 0 >
                    __CDS_OptimalInline auto moveOrCopyKeyTo (
                            __MapEntry * entry
                    ) noexcept -> void {

                        if ( entry->_key._pObject != nullptr ) {
                            return;
                        }

                        entry->_key._pObject = Memory :: instance().create < KeyType > ( std :: move ( * this->_key._pObject ) );
                    }

                private:
                    template < typename __TKeyType = __KeyType, cds :: meta :: EnableIf < ! cds :: meta :: isCopyConstructible < __TKeyType > () && ! cds :: meta :: isMoveConstructible < __TKeyType > () > = 0 >
                    __CDS_OptimalInline auto moveOrCopyKeyTo (
                            __MapEntry * entry
                    ) noexcept -> void {

                        /// do nothing, as this is an unreachable point
                    }

                private:
                    template <
                            typename __TValueType = __ValueType,
                            cds :: meta :: EnableIf <
                                    cds :: meta :: isCopyConstructible < __TValueType > () &&
                                    cds :: meta :: isMoveConstructible < __TValueType > ()
                            > = 0
                    > __CDS_OptimalInline auto moveOrCopyValueTo (
                            __MapEntry * entry
                    ) noexcept -> void {

                        if ( this->_value._forward ) {
                            if ( entry->_value._pAny == nullptr ) {
                                entry->_value._pObject      = Memory :: instance().create < ValueType > ( std :: move ( * this->_value._pObject ) );
                            } else {
                                entry->_value._pObject->~__ValueType();
                                entry->_value._pObject      = new ( entry->_value._pObject ) __ValueType ( std :: move ( * this->_value._pObject ) );
                            }

                            return;
                        }

                        if ( entry->_value._pAny == nullptr ) {
                            entry->_value._pObject      = Memory :: instance().create < ValueType > ( * this->_value._pConstObject );
                        } else {
                            entry->_value._pObject->~__ValueType();
                            entry->_value._pObject      = new ( entry->_value._pObject ) __ValueType ( * this->_value._pConstObject );
                        }
                    }

                private:
                    template <
                            typename __TValueType = __ValueType,
                            cds :: meta :: EnableIf <
                                    cds :: meta :: isCopyConstructible < __TValueType > () &&
                                    ! cds :: meta :: isMoveConstructible < __TValueType > ()
                            > = 0
                    > __CDS_OptimalInline auto moveOrCopyValueTo (
                            __MapEntry * entry
                    ) noexcept -> void {

                        if ( entry->_value._pAny == nullptr ) {
                            entry->_value._pObject      = Memory :: instance().create < ValueType > ( * this->_value._pConstObject );
                        } else {
                            entry->_value._pObject->~__ValueType();
                            entry->_value._pObject      = new ( entry->_value._pObject ) __ValueType ( * this->_value._pConstObject );
                        }
                    }

                private:
                    template <
                            typename __TValueType = __ValueType,
                            cds :: meta :: EnableIf <
                                    ! cds :: meta :: isCopyConstructible < __TValueType > () &&
                                    cds :: meta :: isMoveConstructible < __TValueType > ()
                            > = 0
                    > __CDS_OptimalInline auto moveOrCopyValueTo (
                            __MapEntry * entry
                    ) noexcept -> void {

                        if ( entry->_value._pAny == nullptr ) {
                            entry->_value._pObject      = Memory :: instance().create < ValueType > ( std :: move ( * this->_value._pObject ) );
                        } else {
                            entry->_value._pObject->~__ValueType();
                            entry->_value._pObject      = new ( entry->_value._pObject ) __ValueType ( std :: move ( * this->_value._pObject ) );
                        }
                    }

                private:
                    template <
                            typename __TValueType = __ValueType,
                            cds :: meta :: EnableIf <
                                    ! cds :: meta :: isCopyConstructible < __TValueType > () &&
                                    ! cds :: meta :: isMoveConstructible < __TValueType > ()
                            > = 0
                    > __CDS_OptimalInline auto moveOrCopyValueTo (
                            __MapEntry * entry
                    ) noexcept -> void {

                        /// do nothing, unreachable point
                    }

                private:
                    __CDS_NoDiscard constexpr auto empty () const noexcept -> bool {

                        return this->_key._pAny == nullptr;
                    }

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
                    ) const noexcept -> bool {

                        if ( this == & entry ) {
                            return true;
                        }

                        return
                                this->_key._pConstObject == entry._key._pConstObject;
                    }

                public:
                    constexpr auto key () const noexcept -> KeyType const &;

                public:
                    constexpr auto value () const noexcept -> ValueType const &;

                public:
                    __CDS_cpplang_NonConstConstexprMemberFunction auto value () noexcept -> ValueType &;

                private:
                    __CDS_OptimalInline auto copyTo (
                            __MapEntry * entry
                    ) const noexcept -> void {

                        entry->_key._forward     = false;
                        entry->_key._pObject     = Memory :: instance().create < __KeyType > ( * this->_key._pConstObject );

                        entry->_value._forward   = false;
                        entry->_value._pObject   = Memory :: instance().create < __ValueType > ( * this->_value._pConstObject );
                    }
                };

            }
        }
    }
}

#endif // __CDS_EX_MAP_ENTRY_HPP__
