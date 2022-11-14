/*
 * Created by loghin on 08/11/22.
 */

#ifndef __CDS_JSON_IMPL_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_JSON_IMPL_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

namespace cds {
    namespace json {

        namespace __hidden {
            namespace __impl {

                __CDS_NoDiscard constexpr auto implicitAdaptPossible (
                        __JsonElementType from,
                        __JsonElementType into
                ) noexcept -> bool {

                    return
                            ( from == __JsonElementType :: __jet_Double && into == __JsonElementType :: __jet_Long ) ||
                            ( from == __JsonElementType :: __jet_Long && into == __JsonElementType :: __jet_Double ) ||
                            ( from == __JsonElementType :: __jet_Bool && into == __JsonElementType :: __jet_Long ) ||
                            ( from == __JsonElementType :: __jet_Long && into == __JsonElementType :: __jet_Bool );
                }

            }
        }

        inline auto JsonElement :: copyData (
                __GenericData const & data
        ) noexcept -> void {

            switch ( this->_type ) {

                case __hidden :: __impl :: __JsonElementType :: __jet_Object: {

                    this->_data.data().pObject = new JsonObject (
                            * reinterpret_cast < JsonObject const * > ( data.pObject )
                    );
                    break;
                }

                case __hidden::__impl::__JsonElementType::__jet_Array: {

                    this->_data.data().pObject = new JsonArray (
                            * reinterpret_cast < JsonArray const * > ( data.pObject )
                    );
                    break;
                }

                case __hidden::__impl::__JsonElementType::__jet_String: {

                    this->_data.data().pObject = new String (
                            * reinterpret_cast < String const * > ( data.pObject )
                    );
                    break;
                }

                case __hidden::__impl::__JsonElementType::__jet_Bool:
                case __hidden::__impl::__JsonElementType::__jet_Long:
                case __hidden::__impl::__JsonElementType::__jet_Double: {

                    (void) std :: memcpy (
                            reinterpret_cast < void * > ( & this->_data._data [0U] ),
                            reinterpret_cast < void const * > ( & data ),
                            sizeof ( __GenericData )
                    );

                    break;
                }

                case __hidden::__impl::__JsonElementType::__jet_Invalid: {

                    break;
                }
            }
        }


        inline auto JsonElement :: moveData (
                __GenericData & data
        ) noexcept -> void {

            (void) std :: memcpy (
                    reinterpret_cast < void * > ( & this->_data._data [0U] ),
                    reinterpret_cast < void const * > ( & data ),
                    sizeof ( __GenericData )
            );

            (void) std :: memset (
                    reinterpret_cast < void * > ( & data ),
                    0U,
                    sizeof ( __GenericData )
            );
        }


        inline auto JsonElement :: clearData () noexcept -> void {

            if (
                    this->_type == json :: __hidden :: __impl :: __JsonElementType :: __jet_Object ||
                    this->_type == json :: __hidden :: __impl :: __JsonElementType :: __jet_String ||
                    this->_type == json :: __hidden :: __impl :: __JsonElementType :: __jet_Array
                    ) {

                delete this->_data.data().pObject;
            }
        }


        inline JsonElement :: JsonElement (
                JsonElement const & element
        ) noexcept :
                _type ( element._type ) {

            this->copyData ( element._data.data() );
        }


        __CDS_cpplang_ConstexprConstructorNonEmptyBody JsonElement :: JsonElement (
                JsonElement && element
        ) noexcept :
                _type ( cds :: exchange ( element._type, __hidden :: __impl :: __JsonElementType :: __jet_Invalid ) ) {

            this->moveData ( element._data.data() );
        }


        template <
                typename __ElementType,
                cds :: meta :: EnableIf < __hidden :: __impl :: __JsonElementPrimitiveAdaptable < __ElementType > :: __value >
        > inline JsonElement :: JsonElement (
                __ElementType value
        ) noexcept :
                _type ( __hidden :: __impl :: __JsonElementPrimitiveAdaptable < __ElementType > :: __type ) {

            * reinterpret_cast < __hidden :: __impl :: __JsonElementPrimitiveAdaptable < __ElementType > :: __AdaptedType > (
                    & this->_data._data [0U]
            ) = value;
        }


        template <
                typename __ElementType,
                cds :: meta :: EnableIf < __hidden :: __impl :: __JsonElementAdaptable < __ElementType > :: __value >
        > inline JsonElement :: JsonElement (
                __ElementType const & value
        ) noexcept :
                _type ( __hidden :: __impl :: __JsonElementAdaptable < __ElementType > :: __type ) {

            this->_data.data().pObject = new __hidden :: __impl :: __JsonElementAdaptable < __ElementType > :: __AdaptedType (
                    value
            );
        }


        template <
                typename __ElementType,
                cds :: meta :: EnableIf < __hidden :: __impl :: __JsonElementAdaptable < __ElementType > :: __value >
        > inline JsonElement :: JsonElement (
                __ElementType && value
        ) noexcept :
                _type ( __hidden :: __impl :: __JsonElementAdaptable < __ElementType > :: __type ) {

            this->_data.data().pObject = new __hidden :: __impl :: __JsonElementAdaptable < __ElementType > :: __AdaptedType (
                    std :: move ( value )
            );
        }


        inline JsonElement :: ~JsonElement () noexcept {

            this->clearData();
        }


        inline auto JsonElement :: operator = (
                JsonElement const & element
        ) noexcept -> JsonElement & {

            if ( this == & element ) {
                return * this;
            }

            this->clearData();

            this->_type = element._type;
            this->copyData ( element._data.data() );
            return * this;
        }


        inline auto JsonElement :: operator = (
                JsonElement && element
        ) noexcept -> JsonElement & {

            if ( this == & element ) {
                return * this;
            }

            this->clearData();

            this->_type = cds :: exchange ( element._type, json :: __hidden :: __impl :: __JsonElementType :: __jet_Invalid );
            this->moveData ( element._data.data() );
            return * this;
        }


        template <
                typename __ElementType,
                cds :: meta :: EnableIf < __hidden :: __impl :: __JsonElementPrimitiveAdaptable < __ElementType > :: __value >
        > inline auto JsonElement :: operator = (
                __ElementType value
        ) noexcept -> JsonElement & {

            this->clearData();

            * reinterpret_cast < __hidden :: __impl :: __JsonElementPrimitiveAdaptable < __ElementType > :: __AdaptedType > (
                    & this->_data._data [0U]
            ) = value;

            return * this;
        }


        template <
                typename __ElementType,
                cds :: meta :: EnableIf < __hidden :: __impl :: __JsonElementAdaptable < __ElementType > :: __value >
        > inline auto JsonElement :: operator = (
                __ElementType const & value
        ) noexcept -> JsonElement & {

            this->clearData();

            this->_data.data().pObject = new __hidden :: __impl :: __JsonElementAdaptable < __ElementType > :: __AdaptedType (
                    value
            );

            return * this;
        }


        template <
                typename __ElementType,
                cds :: meta :: EnableIf < __hidden :: __impl :: __JsonElementAdaptable < __ElementType > :: __value >
        > inline auto JsonElement :: operator = (
                __ElementType && value
        ) noexcept -> JsonElement & {

            this->clearData();

            this->_data.data().pObject = new __hidden :: __impl :: __JsonElementAdaptable < __ElementType > :: __AdaptedType (
                    std :: move ( value )
            );

            return * this;
        }


        template <
                typename __ElementType,
                cds :: meta :: EnableIf < __hidden :: __impl :: __JsonElementAdaptable < __ElementType > :: __value >
        > inline auto JsonElement :: to () noexcept -> JsonElement & {

            this->clearData();

            this->_data.data().pObject = new __hidden :: __impl :: __JsonElementAdaptable < __ElementType > :: __AdaptedType (
                    std :: move ( value )
            );

            return * this;
        }

    }
}

#endif /* __CDS_JSON_HPP__ */
