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

            }
        }
    }
}

#endif // __CDS_EX_MAP_ENTRY_IMPL_HPP__
