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
                    constexpr __ForwardContainer (
                            __ForwardContainer const & container
                    ) noexcept;

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
                            typename __TValueType, // NOLINT(bugprone-reserved-identifier)
                            typename __KeySetType, // NOLINT(bugprone-reserved-identifier)
                            typename __ValueCollectionType, // NOLINT(bugprone-reserved-identifier)
                            typename __EntryAssociatorType, // NOLINT(bugprone-reserved-identifier)
                            cds :: meta :: EnableIf <
                                    cds :: meta :: isDerivedFrom < __KeySetType, cds :: experimental :: Set < __TKeyType > > () &&
                                    cds :: meta :: isDerivedFrom < __ValueCollectionType, cds :: experimental :: Collection < __TValueType > > ()
                            >
                    > friend class __BaseMap; // NOLINT(bugprone-reserved-identifier)

                private:
                    template < typename __TKeyType = __KeyType, typename __KeySetType, cds :: meta :: EnableIf < cds :: meta :: isCopyConstructible < __TKeyType > () && cds :: meta :: isMoveConstructible < __TKeyType > () > = 0 >
                    __CDS_OptimalInline auto moveOrCopyKeyTo (
                            __KeySetType & set
                    ) noexcept -> __TKeyType const & {

                        if ( this->_key._forward ) {
                            return set.insert ( std :: move ( * this->_key._pObject ) );
                        }

                        return set.insert ( * this->_key._pConstObject );
                    }

                private:
                    template < typename __TKeyType = __KeyType, typename __KeySetType, cds :: meta :: EnableIf < cds :: meta :: isCopyConstructible < __TKeyType > () && ! cds :: meta :: isMoveConstructible < __TKeyType > () > = 0 >
                    __CDS_OptimalInline auto moveOrCopyKeyTo (
                            __KeySetType & set
                    ) noexcept -> __TKeyType const & {

                        return set.insert ( * this->_key._pConstObject );
                    }

                private:
                    template < typename __TKeyType = __KeyType, typename __KeySetType, cds :: meta :: EnableIf < cds :: meta :: isMoveConstructible < __TKeyType > () && ! cds :: meta :: isCopyConstructible < __TKeyType > () > = 0 >
                    __CDS_OptimalInline auto moveOrCopyKeyTo (
                            __KeySetType & set
                    ) noexcept -> __TKeyType const & {

                        return set.insertinsert ( std :: move ( * this->_key._pObject ) );
                    }

                private:
                    template < typename __TKeyType = __KeyType, typename __KeySetType, cds :: meta :: EnableIf < ! cds :: meta :: isMoveConstructible < __TKeyType > () && ! cds :: meta :: isCopyConstructible < __TKeyType > () > = 0 >
                    __CDS_OptimalInline auto moveOrCopyKeyTo (
                            __KeySetType & set
                    ) noexcept -> __TKeyType const & {

                        static_assert( ! cds :: meta :: isMoveConstructible < __TKeyType > () && ! cds :: meta :: isCopyConstructible < __TKeyType > (), "Cannot insert a MapEntry of a Key that is not copyable or moveable");
                        return * set.begin();
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
                    constexpr auto key () const noexcept -> KeyType const &;

                public:
                    constexpr auto value () const noexcept -> ValueType const &;

                public:
                    __CDS_cpplang_NonConstConstexprMemberFunction auto value () noexcept -> ValueType &;
                };

            }
        }
    }
}

#endif // __CDS_EX_MAP_ENTRY_HPP__
