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
                    friend class cds :: experimental :: Map < __KeyType, __ValueType >;

                public:
                    using KeyType   = __KeyType;

                public:
                    using ValueType = __ValueType;

                private:
                    __ForwardContainer < KeyType > _key;

                private:
                    __ForwardContainer < KeyType > _value;

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
