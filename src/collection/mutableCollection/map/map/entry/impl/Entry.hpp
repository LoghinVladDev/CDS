/*
 * Created by loghin on 6/16/22.
 */

#ifndef __CDS_MAP_ENTRY_IMPL_HPP__
#define __CDS_MAP_ENTRY_IMPL_HPP__ /* NOLINT(bugprone-reserved-identifier) */

namespace cds {             /* NOLINT(modernize-concat-nested-namespaces) */
    namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier) */
        namespace __impl {  /* NOLINT(bugprone-reserved-identifier) */

            template < typename __KeyType, typename __ValueType >   /* NOLINT(bugprone-reserved-identifier) */
            __CDS_cpplang_ConstexprConditioned auto __MapEntry < __KeyType, __ValueType > :: operator == (
                    __MapEntry const & entry
            ) const noexcept -> bool {

                if ( this == & entry ) {
                    return true;
                }

                return
                        cds :: meta :: equals ( this->_key, entry._key ) &&
                        cds :: meta :: equals ( this->_value, entry._value );
            }

            template < typename __KeyType, typename __ValueType >   /* NOLINT(bugprone-reserved-identifier) */
            __CDS_cpplang_ConstexprConditioned auto __MapEntry < __KeyType, __ValueType > :: operator != (
                    __MapEntry const & entry
            ) const noexcept -> bool {

                if ( this == & entry ) {
                    return false;
                }

                return
                        ! cds :: meta :: equals ( this->_key, entry._key ) ||
                        ! cds :: meta :: equals ( this->_value, entry._value );
            }


            template < typename __KeyType, typename __ValueType >   /* NOLINT(bugprone-reserved-identifier) */
            constexpr auto __MapEntry < __KeyType, __ValueType > :: hash () const noexcept -> Size {

                return cds :: hash ( this->_key ) ^ cds :: hash ( this->_value );
            }


            template < typename __KeyType, typename __ValueType >   /* NOLINT(bugprone-reserved-identifier) */
            __CDS_OptimalInline auto __MapEntry < __KeyType, __ValueType > :: toString () const noexcept -> String {

                std :: stringstream oss;
                cds :: meta :: print ( cds :: meta :: print ( oss << "( ", this->_key ) << ", ", this->_value ) << " )";
                return oss.str();
            }


            template < typename __KeyType, typename __ValueType >   /* NOLINT(bugprone-reserved-identifier) */
            __CDS_OptimalInline __MapEntry < __KeyType, __ValueType > :: operator String () const noexcept {

                return this->toString();
            }


            template < typename __KeyType, typename __ValueType > /* NOLINT(bugprone-reserved-identifier) */
            constexpr __MapEntry < __KeyType, __ValueType > :: __MapEntry (
                    __MapEntry const & entry
            ) noexcept (
                    noexcept ( KeyType ( entry._key ) ) &&
                    noexcept ( ValueType ( entry._value ) )
            ) :
                    _key ( entry._key ),
                    _value ( entry._value ) {

            }


            template < typename __KeyType, typename __ValueType > /* NOLINT(bugprone-reserved-identifier) */
            constexpr __MapEntry < __KeyType, __ValueType > :: __MapEntry (
                    __MapEntry && entry
            ) noexcept (
                    noexcept ( KeyType ( std :: move ( entry._key ) ) ) &&
                    noexcept ( ValueType ( std :: move ( entry._value ) ) )
            ) :
                    _key ( std :: move ( entry._key ) ),
                    _value ( std :: move ( entry._value ) ) {

            }


            template < typename __KeyType, typename __ValueType > /* NOLINT(bugprone-reserved-identifier) */
            template < typename __TKeyType, typename __TValueType > /* NOLINT(bugprone-reserved-identifier) */
            constexpr __MapEntry < __KeyType, __ValueType > :: __MapEntry (
                    __TKeyType      && key,
                    __TValueType    && value
            ) noexcept (
                    noexcept ( KeyType ( std :: forward < __TKeyType > ( key ) ) ) &&
                    noexcept ( ValueType ( std :: forward < __TValueType > ( value ) ) )
            ) :
                    _key ( std :: forward < __TKeyType > ( key ) ),
                    _value ( std :: forward < __TValueType > ( value ) ) {

            }


            template < typename __KeyType, typename __ValueType > /* NOLINT(bugprone-reserved-identifier) */
            constexpr auto __MapEntry < __KeyType, __ValueType > :: key () const noexcept -> KeyType const & {

                return this->_key;
            }


            template < typename __KeyType, typename __ValueType > /* NOLINT(bugprone-reserved-identifier) */
            constexpr auto __MapEntry < __KeyType, __ValueType > :: value () const noexcept -> ValueType const & {

                return this->_value;
            }


            template < typename __KeyType, typename __ValueType > /* NOLINT(bugprone-reserved-identifier) */
            __CDS_cpplang_NonConstConstexprMemberFunction auto __MapEntry < __KeyType, __ValueType > :: value () noexcept -> ValueType & {

                return this->_value;
            }


            template < typename __KeyType, typename __ValueType > /* NOLINT(bugprone-reserved-identifier) */
            constexpr auto __MapEntry < __KeyType, __ValueType > :: first () const noexcept -> KeyType const & {

                return this->key();
            }


            template < typename __KeyType, typename __ValueType > /* NOLINT(bugprone-reserved-identifier) */
            constexpr auto __MapEntry < __KeyType, __ValueType > :: second () const noexcept -> ValueType const & {

                return this->value();
            }


            template < typename __KeyType, typename __ValueType > /* NOLINT(bugprone-reserved-identifier) */
            __CDS_cpplang_NonConstConstexprMemberFunction auto __MapEntry < __KeyType, __ValueType > :: second () noexcept -> ValueType & {

                return this->value();
            }


            template < typename __KeyType, typename __ValueType > /* NOLINT(bugprone-reserved-identifier) */
            constexpr auto __MapEntry < __KeyType, __ValueType > :: getFirst () const noexcept -> KeyType const & {

                return this->key();
            }


            template < typename __KeyType, typename __ValueType > /* NOLINT(bugprone-reserved-identifier) */
            constexpr auto __MapEntry < __KeyType, __ValueType > :: getSecond () const noexcept -> ValueType const & {

                return this->value();
            }


            template < typename __KeyType, typename __ValueType > /* NOLINT(bugprone-reserved-identifier) */
            __CDS_cpplang_NonConstConstexprMemberFunction auto __MapEntry < __KeyType, __ValueType > :: getSecond () noexcept -> ValueType & {

                return this->value();
            }


            template < typename __TKeyType, typename __TValueType > /* NOLINT(bugprone-reserved-identifier) */
            __CDS_OptimalInline auto operator << (
                    std :: ostream                                & out,
                    __MapEntry < __TKeyType, __TValueType > const & object
            ) noexcept -> std :: ostream & {

                return cds :: meta :: print ( cds :: meta :: print ( out << "( ", object.key() ) << ", ", object.value() ) << " )";
            }

        }
    }

    template <
            typename __KeyType,     /* NOLINT(bugprone-reserved-identifier) */
            typename __ValueType    /* NOLINT(bugprone-reserved-identifier) */
    > struct Hash < cds :: __hidden :: __impl :: __MapEntry < __KeyType, __ValueType > > {

        __CDS_NoDiscard constexpr static auto hash (
                cds :: __hidden :: __impl :: __MapEntry < __KeyType, __ValueType > const & entry
        ) noexcept -> Size {

            return entry.hash();
        }
    };
}

#endif /* __CDS_MAP_ENTRY_IMPL_HPP__ */
