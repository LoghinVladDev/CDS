//
// Created by loghin on 6/16/22.
//

#ifndef __CDS_EX_MAP_ENTRY_IMPL_HPP__
#define __CDS_EX_MAP_ENTRY_IMPL_HPP__

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental { // NOLINT(modernize-concat-nested-namespaces)
        namespace __hidden { // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier)
            namespace __impl { // NOLINT(bugprone-reserved-identifier)

                template < typename __Type > // NOLINT(bugprone-reserved-identifier)
                constexpr __ForwardContainer < __Type > :: __ForwardContainer () noexcept :
                        _forward ( false ),
                        _pAny ( nullptr ) {

                }


                template < typename __Type > // NOLINT(bugprone-reserved-identifier)
                constexpr __ForwardContainer < __Type > :: __ForwardContainer (
                        __Type * pObject
                ) noexcept :
                        _pObject ( pObject ),
                        _forward ( true ) {

                }


                template < typename __Type > // NOLINT(bugprone-reserved-identifier)
                constexpr __ForwardContainer < __Type > :: __ForwardContainer (
                        __Type const * pObject
                ) noexcept :
                        _pConstObject ( pObject ),
                        _forward ( false ) {

                }


                template < typename __KeyType, typename __ValueType >   // NOLINT(bugprone-reserved-identifier)
                template <
                        typename __TKeyType,                            // NOLINT(bugprone-reserved-identifier)
                        cds :: meta :: EnableIf <
                                cds :: meta :: isCopyConstructible < __TKeyType > () &&
                                cds :: meta :: isMoveConstructible < __TKeyType > ()
                        >
                > __CDS_cpplang_ConstexprPlacementNew auto __MapEntry < __KeyType, __ValueType > :: moveOrCopyKeyTo (
                        __MapEntry * pEntry
                ) noexcept -> void {

                    if ( this->_key._forward ) {
                        pEntry->_key._pObject = new ( pEntry->_key._pObject ) __KeyType ( std :: move ( * this->_key._pObject ) );
                        return;
                    }

                    pEntry->_key._pObject = new  ( pEntry->_key._pObject ) __KeyType ( * this->_key._pConstObject );
                }


                template < typename __KeyType, typename __ValueType >   // NOLINT(bugprone-reserved-identifier)
                template <
                        typename __TKeyType,                            // NOLINT(bugprone-reserved-identifier)
                        cds :: meta :: EnableIf <
                                cds :: meta :: isCopyConstructible < __TKeyType > () &&
                                ! cds :: meta :: isMoveConstructible < __TKeyType > ()
                        >
                > __CDS_cpplang_ConstexprPlacementNew auto __MapEntry < __KeyType, __ValueType > :: moveOrCopyKeyTo (
                        __MapEntry * pEntry
                ) noexcept -> void {

                    pEntry->_key._pObject = new  ( pEntry->_key._pObject ) __KeyType ( * this->_key._pConstObject );
                }


                template < typename __KeyType, typename __ValueType >   // NOLINT(bugprone-reserved-identifier)
                template <
                        typename __TKeyType,                            // NOLINT(bugprone-reserved-identifier)
                        cds :: meta :: EnableIf <
                                ! cds :: meta :: isCopyConstructible < __TKeyType > () &&
                                cds :: meta :: isMoveConstructible < __TKeyType > ()
                        >
                > __CDS_cpplang_ConstexprPlacementNew auto __MapEntry < __KeyType, __ValueType > :: moveOrCopyKeyTo (
                        __MapEntry * pEntry
                ) noexcept -> void {

                    pEntry->_key._pObject = new ( pEntry->_key._pObject ) __KeyType ( std :: move ( * this->_key._pObject ) );
                }


                template < typename __KeyType, typename __ValueType >   // NOLINT(bugprone-reserved-identifier)
                template <
                        typename __TKeyType,                            // NOLINT(bugprone-reserved-identifier)
                        cds :: meta :: EnableIf <
                                ! cds :: meta :: isCopyConstructible < __TKeyType > () &&
                                ! cds :: meta :: isMoveConstructible < __TKeyType > ()
                        >
                > constexpr auto __MapEntry < __KeyType, __ValueType > :: moveOrCopyKeyTo (
                        __MapEntry * pEntry
                ) noexcept -> void {

                    /// do nothing, as this in an unreachable point
                }


                template < typename __KeyType, typename __ValueType >   // NOLINT(bugprone-reserved-identifier)
                template <
                        typename __TValueType,                          // NOLINT(bugprone-reserved-identifier)
                        cds :: meta :: EnableIf <
                                cds :: meta :: isCopyConstructible < __TValueType > () &&
                                cds :: meta :: isMoveConstructible < __TValueType > ()
                        >
                > __CDS_cpplang_ConstexprPlacementNew auto __MapEntry < __KeyType, __ValueType > :: moveOrCopyValueTo (
                        __MapEntry * pEntry
                ) noexcept -> void {

                    if ( this->_value._forward ) {
                        pEntry->_value._pObject->~__ValueType();
                        pEntry->_value._pObject      = new ( pEntry->_value._pObject ) __ValueType ( std :: move ( * this->_value._pObject ) );

                        return;
                    }

                    pEntry->_value._pObject->~__ValueType();
                    pEntry->_value._pObject      = new ( pEntry->_value._pObject ) __ValueType ( * this->_value._pConstObject );
                }


                template < typename __KeyType, typename __ValueType >   // NOLINT(bugprone-reserved-identifier)
                template <
                        typename __TValueType,                          // NOLINT(bugprone-reserved-identifier)
                        cds :: meta :: EnableIf <
                                cds :: meta :: isCopyConstructible < __TValueType > () &&
                                ! cds :: meta :: isMoveConstructible < __TValueType > ()
                        >
                > __CDS_cpplang_ConstexprPlacementNew auto __MapEntry < __KeyType, __ValueType > :: moveOrCopyValueTo (
                        __MapEntry * pEntry
                ) noexcept -> void {

                    pEntry->_value._pObject->~__ValueType();
                    pEntry->_value._pObject      = new ( pEntry->_value._pObject ) __ValueType ( * this->_value._pConstObject );
                }


                template < typename __KeyType, typename __ValueType >   // NOLINT(bugprone-reserved-identifier)
                template <
                        typename __TValueType,                          // NOLINT(bugprone-reserved-identifier)
                        cds :: meta :: EnableIf <
                                ! cds :: meta :: isCopyConstructible < __TValueType > () &&
                                cds :: meta :: isMoveConstructible < __TValueType > ()
                        >
                > __CDS_cpplang_ConstexprPlacementNew auto __MapEntry < __KeyType, __ValueType > :: moveOrCopyValueTo (
                        __MapEntry * pEntry
                ) noexcept -> void {

                    pEntry->_value._pObject->~__ValueType();
                    pEntry->_value._pObject      = new ( pEntry->_value._pObject ) __ValueType ( std :: move ( * this->_value._pObject ) );
                }


                template < typename __KeyType, typename __ValueType >   // NOLINT(bugprone-reserved-identifier)
                template <
                        typename __TValueType,                          // NOLINT(bugprone-reserved-identifier)
                        cds :: meta :: EnableIf <
                                ! cds :: meta :: isCopyConstructible < __TValueType > () &&
                                ! cds :: meta :: isMoveConstructible < __TValueType > ()
                        >
                > constexpr auto __MapEntry < __KeyType, __ValueType > :: moveOrCopyValueTo (
                        __MapEntry * pEntry
                ) noexcept -> void {

                    /// do nothing, unreachable point
                }


                template < typename __KeyType, typename __ValueType >   // NOLINT(bugprone-reserved-identifier)
                constexpr auto __MapEntry < __KeyType, __ValueType > :: empty () const noexcept -> bool {

                    return this->_key._pAny == nullptr;
                }


                template < typename __KeyType, typename __ValueType >   // NOLINT(bugprone-reserved-identifier)
                constexpr auto __MapEntry < __KeyType, __ValueType > :: operator == (
                        __MapEntry const & entry
                ) const noexcept -> bool {

                    if ( this == & entry ) {
                        return true;
                    }

                    return
                            this->_key._pConstObject == entry._key._pConstObject;
                }


                template < typename __KeyType, typename __ValueType >   // NOLINT(bugprone-reserved-identifier)
                constexpr auto __MapEntry < __KeyType, __ValueType > :: hash () const noexcept -> Size {

                    return this->_key._pAny == nullptr ?
                            0ULL :
                            cds :: hash ( * this->_key._pConstObject );
                }


                template < typename __KeyType, typename __ValueType >   // NOLINT(bugprone-reserved-identifier)
                __CDS_OptimalInline auto __MapEntry < __KeyType, __ValueType > :: toString () const noexcept -> String {

                    if ( this->empty() ) {
                        return "()";
                    }

                    std :: stringstream oss;
                    cds :: meta :: print ( cds :: meta :: print ( oss << "( ", * this->_key._pConstObject ) << ", ", * this->_value._pConstObject ) << " )";
                    return oss.str();
                }


                template < typename __KeyType, typename __ValueType > // NOLINT(bugprone-reserved-identifier)
                constexpr __MapEntry < __KeyType, __ValueType > :: __MapEntry (
                        KeyType     const & key,
                        ValueType   const & value
                ) noexcept :
                        _key ( & key ),
                        _value ( & value ) {

                }


                template < typename __KeyType, typename __ValueType > // NOLINT(bugprone-reserved-identifier)
                constexpr __MapEntry < __KeyType, __ValueType > :: __MapEntry (
                        KeyType     const & key,
                        ValueType       && value
                ) noexcept :
                        _key ( & key ),
                        _value ( & value ) {

                }


                template < typename __KeyType, typename __ValueType > // NOLINT(bugprone-reserved-identifier)
                constexpr __MapEntry < __KeyType, __ValueType > :: __MapEntry (
                        KeyType          && key,
                        ValueType   const & value
                ) noexcept :
                        _key ( & key ),
                        _value ( & value ) {

                }


                template < typename __KeyType, typename __ValueType > // NOLINT(bugprone-reserved-identifier)
                constexpr __MapEntry < __KeyType, __ValueType > :: __MapEntry (
                        KeyType          && key,
                        ValueType        && value
                ) noexcept :
                        _key ( & key ),
                        _value ( & value ) {

                }


                template < typename __KeyType, typename __ValueType > // NOLINT(bugprone-reserved-identifier)
                constexpr auto __MapEntry < __KeyType, __ValueType > :: key () const noexcept -> KeyType const & {

                    return * this->_key._pConstObject;
                }


                template < typename __KeyType, typename __ValueType > // NOLINT(bugprone-reserved-identifier)
                constexpr auto __MapEntry < __KeyType, __ValueType > :: value () const noexcept -> ValueType const & {

                    return * this->_value._pConstObject;
                }


                template < typename __KeyType, typename __ValueType > // NOLINT(bugprone-reserved-identifier)
                __CDS_cpplang_NonConstConstexprMemberFunction auto __MapEntry < __KeyType, __ValueType > :: value () noexcept -> ValueType & {

                    return * this->_value._pObject;
                }


                template < typename __KeyType, typename __ValueType > // NOLINT(bugprone-reserved-identifier)
                constexpr auto __MapEntry < __KeyType, __ValueType > :: first () const noexcept -> KeyType const & {

                    return this->key();
                }


                template < typename __KeyType, typename __ValueType > // NOLINT(bugprone-reserved-identifier)
                constexpr auto __MapEntry < __KeyType, __ValueType > :: second () const noexcept -> ValueType const & {

                    return this->value();
                }


                template < typename __KeyType, typename __ValueType > // NOLINT(bugprone-reserved-identifier)
                __CDS_cpplang_NonConstConstexprMemberFunction auto __MapEntry < __KeyType, __ValueType > :: second () noexcept -> ValueType & {

                    return this->value();
                }


                template < typename __KeyType, typename __ValueType > // NOLINT(bugprone-reserved-identifier)
                constexpr auto __MapEntry < __KeyType, __ValueType > :: getFirst () const noexcept -> KeyType const & {

                    return this->key();
                }


                template < typename __KeyType, typename __ValueType > // NOLINT(bugprone-reserved-identifier)
                constexpr auto __MapEntry < __KeyType, __ValueType > :: getSecond () const noexcept -> ValueType const & {

                    return this->value();
                }


                template < typename __KeyType, typename __ValueType > // NOLINT(bugprone-reserved-identifier)
                __CDS_cpplang_NonConstConstexprMemberFunction auto __MapEntry < __KeyType, __ValueType > :: getSecond () noexcept -> ValueType & {

                    return this->value();
                }

            }
        }
    }
}

#endif // __CDS_EX_MAP_ENTRY_IMPL_HPP__
