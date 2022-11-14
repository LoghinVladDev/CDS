/*
 * Created by loghin on 08/11/22.
 */

#ifndef __CDS_JSON_IMPL_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_JSON_IMPL_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

namespace cds {
    namespace json {

        namespace __hidden {
            namespace __impl {

                __CDS_NoDiscard __CDS_cpplang_ConstexprMultipleReturn auto __jet_toString (
                        __JsonElementType type
                ) noexcept -> StringLiteral {

                    switch ( type ) {
                        case __JsonElementType :: __jet_Object: {
                            return "JsonObject";
                        }

                        case __JsonElementType :: __jet_Array: {
                            return "JsonArray";
                        }

                        case __JsonElementType :: __jet_String: {
                            return "String";
                        }

                        case __JsonElementType :: __jet_Bool: {
                            return "bool";
                        }

                        case __JsonElementType :: __jet_Long: {
                            return "long";
                        }

                        case __JsonElementType :: __jet_Double: {
                            return "double";
                        }

                        case __JsonElementType :: __jet_Invalid: {
                            return "invalid";
                        }

                    }
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

                case __hidden::__impl::__JsonElementType::__jet_Invalid:
                default: {

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


        inline JsonElement :: JsonElement (
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


        inline auto JsonElement :: toString () const noexcept -> String {

            switch ( this->_type ) {
                case __hidden :: __impl :: __JsonElementType :: __jet_Object:
                case __hidden :: __impl :: __JsonElementType :: __jet_Array: {
                    return this->_data.data().pObject->toString();
                }

                case __hidden :: __impl :: __JsonElementType :: __jet_String: {
                    return "\"" + this->_data.data().pObject->toString() + "\"";
                }

                case __hidden :: __impl :: __JsonElementType :: __jet_Bool: {
                    return this->_data.data().bValue ? "true" : "false";
                }

                case __hidden :: __impl :: __JsonElementType :: __jet_Long: {
                    return this->_data.data().iValue;
                }

                case __hidden :: __impl :: __JsonElementType :: __jet_Double: {
                    return this->_data.data().dValue;
                }

                case __hidden :: __impl :: __JsonElementType :: __jet_Invalid:
                default: {
                    return "Invalid";
                }
            }
        }


        inline auto JsonElement :: hash () const noexcept -> Size {

            switch ( this->_type ) {
                case __hidden :: __impl :: __JsonElementType :: __jet_Object:
                case __hidden :: __impl :: __JsonElementType :: __jet_Array: {
                    return this->_data.data().pObject->hash();
                }

                case __hidden :: __impl :: __JsonElementType :: __jet_Bool: {
                    return cds :: Hash < bool > :: hash ( this->_data.data().bValue );
                }

                case __hidden :: __impl :: __JsonElementType :: __jet_Long: {
                    return cds :: Hash < long long int > :: hash ( this->_data.data().iValue );
                }

                case __hidden :: __impl :: __JsonElementType :: __jet_Double: {
                    return cds :: Hash < double > :: hash ( this->_data.data().dValue );
                }

                case __hidden :: __impl :: __JsonElementType :: __jet_Invalid:
                default: {
                    return 0ULL;
                }
            }
        }


        inline auto JsonElement :: equals (
                Object const & object
        ) const noexcept -> bool {

            if ( this == & object ) {
                return true;
            }

            auto pJsonElement = dynamic_cast < decltype(this) > ( & object );
            if ( pJsonElement == nullptr ) {
                return false;
            }

            if ( this->_type != pJsonElement->_type ) {
                return false;
            }

            if (
                    this->_type == json :: __hidden :: __impl :: __JsonElementType :: __jet_Object ||
                    this->_type == json :: __hidden :: __impl :: __JsonElementType :: __jet_Array ||
                    this->_type == json :: __hidden :: __impl :: __JsonElementType :: __jet_String
            ) {

                return this->_data.data().pObject->equals ( * pJsonElement->_data.data().pObject );
            }

            return std :: memcmp (
                    reinterpret_cast < void const * > ( this->_data._data [0U] ),
                    reinterpret_cast < void const * > ( pJsonElement->_data._data [0U] ),
                    sizeof ( __GenericData )
            ) == 0;
        }


        template < __hidden :: __impl :: __JsonElementType type >
        constexpr auto JsonElement :: is () const noexcept -> bool {

            return this->_type == type;
        }


        constexpr auto JsonElement :: isInt () const noexcept -> bool {

            return this->is < __hidden :: __impl :: __JsonElementType :: __jet_Int > ();
        }


        constexpr auto JsonElement :: isLong () const noexcept -> bool {

            return this->is < __hidden :: __impl :: __JsonElementType :: __jet_Long > ();
        }


        constexpr auto JsonElement :: isFloat () const noexcept -> bool {

            return this->is < __hidden :: __impl :: __JsonElementType :: __jet_Float > ();
        }


        constexpr auto JsonElement :: isDouble () const noexcept -> bool {

            return this->is < __hidden :: __impl :: __JsonElementType :: __jet_Double > ();
        }


        constexpr auto JsonElement :: isBoolean () const noexcept -> bool {

            return this->is < __hidden :: __impl :: __JsonElementType :: __jet_Bool > ();
        }


        constexpr auto JsonElement :: isString () const noexcept -> bool {

            return this->is < __hidden :: __impl :: __JsonElementType :: __jet_String > ();
        }


        constexpr auto JsonElement :: isJson () const noexcept -> bool {

            return this->is < __hidden :: __impl :: __JsonElementType :: __jet_Object > ();
        }


        constexpr auto JsonElement :: isArray () const noexcept -> bool {

            return this->is < __hidden :: __impl :: __JsonElementType :: __jet_Array > ();
        }


        inline auto JsonElement :: getInt () const noexcept (false) -> int {

            if ( this->_type != __hidden :: __impl :: __JsonElementType :: __jet_Int ) {
                throw TypeException ( String :: f (
                        "Type Cast Exception. Cannot convert '%s' to '%s'",
                        __hidden :: __impl :: __jet_toString ( this->_type ),
                        "int"
                ));
            }

            return static_cast < int > ( this->_data.data().iValue );
        }


        inline auto JsonElement :: getLong () const noexcept (false) -> long long int {

            if ( this->_type != __hidden :: __impl :: __JsonElementType :: __jet_Long ) {
                throw TypeException ( String :: f (
                        "Type Cast Exception. Cannot convert '%s' to '%s'",
                        __hidden :: __impl :: __jet_toString ( this->_type ),
                        "long"
                ));
            }

            return this->_data.data().iValue;
        }


        inline auto JsonElement :: getFloat () const noexcept (false) -> float {

            if ( this->_type != __hidden :: __impl :: __JsonElementType :: __jet_Float ) {
                throw TypeException ( String :: f (
                        "Type Cast Exception. Cannot convert '%s' to '%s'",
                        __hidden :: __impl :: __jet_toString ( this->_type ),
                        "float"
                ));
            }

            return static_cast < float > ( this->_data.data().dValue );
        }


        inline auto JsonElement :: getDouble () const noexcept (false) -> double {

            if ( this->_type != __hidden :: __impl :: __JsonElementType :: __jet_Double ) {
                throw TypeException ( String :: f (
                        "Type Cast Exception. Cannot convert '%s' to '%s'",
                        __hidden :: __impl :: __jet_toString ( this->_type ),
                        "double"
                ));
            }

            return this->_data.data().dValue;
        }


        inline auto JsonElement :: getBoolean () const noexcept (false) -> bool {

            if ( this->_type != __hidden :: __impl :: __JsonElementType :: __jet_Bool ) {
                throw TypeException ( String :: f (
                        "Type Cast Exception. Cannot convert '%s' to '%s'",
                        __hidden :: __impl :: __jet_toString ( this->_type ),
                        "bool"
                ));
            }

            return this->_data.data().bValue;
        }


        inline auto JsonElement :: getString () const noexcept (false) -> String const & {

            if ( this->_type != __hidden :: __impl :: __JsonElementType :: __jet_String ) {
                throw TypeException ( String :: f (
                        "Type Cast Exception. Cannot convert '%s' to '%s'",
                        __hidden :: __impl :: __jet_toString ( this->_type ),
                        "String"
                ));
            }

            return * reinterpret_cast < String const * > ( this->_data.data().pObject );
        }


        inline auto JsonElement :: getJson () const noexcept (false) -> JsonObject const & {

            if ( this->_type != __hidden :: __impl :: __JsonElementType :: __jet_Object ) {
                throw TypeException ( String :: f (
                        "Type Cast Exception. Cannot convert '%s' to '%s'",
                        __hidden :: __impl :: __jet_toString ( this->_type ),
                        "JsonObject"
                ));
            }

            return * reinterpret_cast < JsonObject const * > ( this->_data.data().pObject );
        }


        inline auto JsonElement :: getArray () const noexcept (false) -> JsonArray const & {

            if ( this->_type != __hidden :: __impl :: __JsonElementType :: __jet_Array ) {
                throw TypeException ( String :: f (
                        "Type Cast Exception. Cannot convert '%s' to '%s'",
                        __hidden :: __impl :: __jet_toString ( this->_type ),
                        "JsonArray"
                ));
            }

            return * reinterpret_cast < JsonArray const * > ( this->_data.data().pObject );
        }


        inline auto JsonElement :: getString () noexcept (false) -> String & {

            if ( this->_type != __hidden :: __impl :: __JsonElementType :: __jet_String ) {
                throw TypeException ( String :: f (
                        "Type Cast Exception. Cannot convert '%s' to '%s'",
                        __hidden :: __impl :: __jet_toString ( this->_type ),
                        "String"
                ));
            }

            return * reinterpret_cast < String * > ( this->_data.data().pObject );
        }


        inline auto JsonElement :: getJson () noexcept (false) -> JsonObject & {

            if ( this->_type != __hidden :: __impl :: __JsonElementType :: __jet_Object ) {
                throw TypeException ( String :: f (
                        "Type Cast Exception. Cannot convert '%s' to '%s'",
                        __hidden :: __impl :: __jet_toString ( this->_type ),
                        "JsonObject"
                ));
            }

            return * reinterpret_cast < JsonObject * > ( this->_data.data().pObject );
        }


        inline auto JsonElement :: getArray () noexcept (false) -> JsonArray & {

            if ( this->_type != __hidden :: __impl :: __JsonElementType :: __jet_Array ) {
                throw TypeException ( String :: f (
                        "Type Cast Exception. Cannot convert '%s' to '%s'",
                        __hidden :: __impl :: __jet_toString ( this->_type ),
                        "JsonArray"
                ));
            }

            return * reinterpret_cast < JsonArray * > ( this->_data.data().pObject );
        }

    }
}

#endif /* __CDS_JSON_HPP__ */
