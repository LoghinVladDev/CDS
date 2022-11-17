/*
 * Created by loghin on 28.02.2021.
 */

#ifndef __CDS_JSON_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_JSON_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

#include <CDS/meta/TypeTraits>
#include <CDS/LinkedHashMap>
#include <CDS/Array>
#include <CDS/smartPointers/UniquePointer>

namespace cds { /* NOLINT(modernize-concat-nested-namespaces) */
    namespace json {

        class JsonElement;
        class JsonObject;
        class JsonArray;

        namespace __hidden {
            namespace __impl {

                using __JsonBaseMap             = cds :: Map < String, JsonElement >;
                using __JsonBaseArray           = cds :: Array < JsonElement >;

                using __JsonMapImplementation   = cds :: LinkedHashMap < String, JsonElement >;
                using __JsonArrayImplementation = cds :: Array < JsonElement >;

                enum class __JsonElementType {
                    __jet_Object,
                    __jet_Array,
                    __jet_String,
                    __jet_Bool,
                    __jet_Long,
                    __jet_Int       = __jet_Long,
                    __jet_Double,
                    __jet_Float     = __jet_Double,
                    __jet_Invalid
                };

                __CDS_cpplang_ConstexprMultipleReturn auto toString (
                        __JsonElementType type
                ) noexcept -> StringLiteral;

                template < typename __BaseType >
                struct __JsonElementAdapterPropertiesHelper {
                    constexpr static bool const __adaptable = false;
                };

                template <> struct __JsonElementAdapterPropertiesHelper < int > {
                    constexpr static bool               const __adaptable   = true;
                    constexpr static __JsonElementType  const __type        = __JsonElementType :: __jet_Long;
                    using                                     __AdaptedType = int;
                };

                template <> struct __JsonElementAdapterPropertiesHelper < long long > {
                    constexpr static bool               const __adaptable   = true;
                    constexpr static __JsonElementType  const __type        = __JsonElementType :: __jet_Long;
                    using                                     __AdaptedType = long long;
                };

                template <> struct __JsonElementAdapterPropertiesHelper < float > {
                    constexpr static bool               const __adaptable   = true;
                    constexpr static __JsonElementType  const __type        = __JsonElementType :: __jet_Double;
                    using                                     __AdaptedType = float;
                };

                template <> struct __JsonElementAdapterPropertiesHelper < double > {
                    constexpr static bool               const __adaptable   = true;
                    constexpr static __JsonElementType  const __type        = __JsonElementType :: __jet_Double;
                    using                                     __AdaptedType = double;
                };

                template <> struct __JsonElementAdapterPropertiesHelper < bool > {
                    constexpr static bool               const __adaptable   = true;
                    constexpr static __JsonElementType  const __type        = __JsonElementType :: __jet_Bool;
                    using                                     __AdaptedType = bool;
                };

                template <> struct __JsonElementAdapterPropertiesHelper < StringLiteral > {
                    constexpr static bool               const __adaptable   = true;
                    constexpr static __JsonElementType  const __type        = __JsonElementType :: __jet_String;
                    using                                     __AdaptedType = String;
                };

                template <> struct __JsonElementAdapterPropertiesHelper < StringView > {
                    constexpr static bool               const __adaptable   = true;
                    constexpr static __JsonElementType  const __type        = __JsonElementType :: __jet_String;
                    using                                     __AdaptedType = String;
                };

                template <> struct __JsonElementAdapterPropertiesHelper < String > {
                    constexpr static bool               const __adaptable   = true;
                    constexpr static __JsonElementType  const __type        = __JsonElementType :: __jet_String;
                    using                                     __AdaptedType = String;
                };

                template <> struct __JsonElementAdapterPropertiesHelper < JsonArray > {
                    constexpr static bool               const __adaptable   = true;
                    constexpr static __JsonElementType  const __type        = __JsonElementType :: __jet_Array;
                    using                                     __AdaptedType = JsonArray;
                };

                template <> struct __JsonElementAdapterPropertiesHelper < JsonObject > {
                    constexpr static bool               const __adaptable   = true;
                    constexpr static __JsonElementType  const __type        = __JsonElementType :: __jet_Object;
                    using                                     __AdaptedType = JsonObject;
                };

                template < typename __ToDecay > struct __JsonElementAdapterProperties : __JsonElementAdapterPropertiesHelper < cds :: meta :: Decay < __ToDecay > > {};

                template < typename __ElementType >
                struct __JsonElementPrimitiveAdaptable {
                    constexpr static bool const __value =
                            __JsonElementAdapterProperties < cds :: meta :: Decay < __ElementType > > :: __adaptable &&
                            cds :: meta :: isFundamental < cds :: meta :: Decay < __ElementType > > () || (
                                    ! cds :: meta :: isSame < cds :: meta :: Decay < __ElementType >, StringLiteral > () &&
                                    cds :: meta :: isBasicPointer < cds :: meta :: Decay < __ElementType > > ()
                            );
                };

                template < typename __ElementType >
                struct __JsonElementAdaptable {
                    constexpr static bool const __value =
                            __JsonElementAdapterProperties < cds :: meta :: Decay < __ElementType > > :: __adaptable &&
                            ! cds :: meta :: isFundamental < cds :: meta :: Decay < __ElementType > > () && ! (
                                    ! cds :: meta :: isSame < cds :: meta :: Decay < __ElementType >, StringLiteral > () &&
                                    cds :: meta :: isBasicPointer < cds :: meta :: Decay < __ElementType > > ()
                            );
                };

            }
        }

        class JsonElement : public Object {

        private:
            friend class JsonArray;

        private:
            friend class JsonObject;

        private:
            union __GenericData {
                bool            bValue;
                long long int   iValue;
                double          dValue;
                cds :: Object * pObject;
            };

        private:
            __hidden :: __impl :: __JsonElementType                                         _type { __hidden :: __impl :: __JsonElementType :: __jet_Invalid };

        private:
            cds :: __hidden :: __impl :: __allocation :: __RawContainer < __GenericData >   _data;

        private:
            auto copyData (
                    __GenericData const & genericData
            ) noexcept -> void;

        private:
            auto moveData (
                    __GenericData & genericData
            ) noexcept -> void;

        private:
            auto clearData () noexcept -> void;

        public:
            __CDS_cpplang_ConstexprConstructorNonEmptyBody JsonElement () noexcept = delete;

        public:
            JsonElement (
                    JsonElement const & element
            ) noexcept;

        public:
            JsonElement (
                    JsonElement && element
            ) noexcept;

        public:
            template <
                    typename __ElementType,
                    cds :: meta :: EnableIf < __hidden :: __impl :: __JsonElementPrimitiveAdaptable < __ElementType > :: __value > = 0
            > JsonElement (
                    __ElementType value
            ) noexcept;

        public:
            template <
                    typename __ElementType,
                    cds :: meta :: EnableIf < __hidden :: __impl :: __JsonElementAdaptable < __ElementType > :: __value > = 0
            > JsonElement (
                    __ElementType const & value
            ) noexcept;

        public:
            template <
                    typename __ElementType,
                    cds :: meta :: EnableIf < __hidden :: __impl :: __JsonElementAdaptable < __ElementType > :: __value > = 0
            > JsonElement (
                    __ElementType && value
            ) noexcept;

        public:
            ~JsonElement () noexcept;

        public:
            auto operator = (
                    JsonElement const & element
            ) noexcept -> JsonElement &;

        public:
            auto operator = (
                    JsonElement && element
            ) noexcept -> JsonElement &;

        public:
            template <
                    typename __ElementType,
                    cds :: meta :: EnableIf < __hidden :: __impl :: __JsonElementPrimitiveAdaptable < __ElementType > :: __value > = 0
            > auto operator = (
                    __ElementType value
            ) noexcept -> JsonElement &;

        public:
            template <
                    typename __ElementType,
                    cds :: meta :: EnableIf < __hidden :: __impl :: __JsonElementAdaptable < __ElementType > :: __value > = 0
            > auto operator = (
                    __ElementType const & value
            ) noexcept -> JsonElement &;

        public:
            template <
                    typename __ElementType,
                    cds :: meta :: EnableIf < __hidden :: __impl :: __JsonElementAdaptable < __ElementType > :: __value > = 0
            > auto operator = (
                    __ElementType && value
            ) noexcept -> JsonElement &;

        public:
            __CDS_NoDiscard auto toString () const noexcept -> String override;

        public:
            __CDS_NoDiscard auto hash () const noexcept -> Size override;

        public:
            __CDS_NoDiscard auto equals (
                    Object const & object
            ) const noexcept -> bool override;

        private:
            template < __hidden :: __impl :: __JsonElementType type >
            __CDS_NoDiscard constexpr auto is () const noexcept -> bool;

        public:
            __CDS_NoDiscard auto getInt () const noexcept (false) -> int;

        public:
            __CDS_NoDiscard auto getLong () const noexcept (false) -> long long int;

        public:
            __CDS_NoDiscard auto getFloat () const noexcept (false) -> float;

        public:
            __CDS_NoDiscard auto getDouble () const noexcept (false) -> double;

        public:
            __CDS_NoDiscard auto getBoolean () const noexcept (false) -> bool;

        public:
            __CDS_NoDiscard auto getString () const noexcept (false) -> String const &;

        public:
            __CDS_NoDiscard auto getJson () const noexcept (false) -> JsonObject const &;

        public:
            __CDS_NoDiscard auto getArray () const noexcept (false) -> JsonArray const &;

        public:
            __CDS_NoDiscard auto getString () noexcept (false) -> String &;

        public:
            __CDS_NoDiscard auto getJson () noexcept (false) -> JsonObject &;

        public:
            __CDS_NoDiscard auto getArray () noexcept (false) -> JsonArray &;

        public:
            __CDS_NoDiscard constexpr auto isInt () const noexcept -> bool;

        public:
            __CDS_NoDiscard constexpr auto isLong () const noexcept -> bool;

        public:
            __CDS_NoDiscard constexpr auto isFloat () const noexcept -> bool;

        public:
            __CDS_NoDiscard constexpr auto isDouble () const noexcept -> bool;

        public:
            __CDS_NoDiscard constexpr auto isBoolean () const noexcept -> bool;

        public:
            __CDS_NoDiscard constexpr auto isString () const noexcept -> bool;

        public:
            __CDS_NoDiscard constexpr auto isJson () const noexcept -> bool;

        public:
            __CDS_NoDiscard constexpr auto isArray () const noexcept -> bool;
        };


        class JsonObject : public __hidden :: __impl :: __JsonMapImplementation {

        private:
            using __Base = __hidden :: __impl :: __JsonMapImplementation;

        public:
            constexpr JsonObject () noexcept;

        public:
            JsonObject (
                    JsonObject const & object
            ) noexcept;

        public:
            constexpr JsonObject (
                    JsonObject && object
            ) noexcept;

        public:
            JsonObject (
                    Map < String, JsonElement > const & map
            ) noexcept;

        public:
            JsonObject (
                    String const & asString
            ) noexcept;

        public:
            ~JsonObject () noexcept;

        public:
            auto operator = (
                    JsonObject const & object
            ) noexcept -> JsonObject &;

        public:
            auto operator = (
                    JsonObject && object
            ) noexcept -> JsonObject &;

        public:
            auto operator = (
                    Map < String, JsonElement > const & map
            ) noexcept -> JsonObject &;

        public:
            template < typename __ElementType >
            auto put (
                    StringView          label,
                    __ElementType    && value
            ) noexcept -> JsonObject &;

        public:
            __CDS_NoDiscard auto getBoolean (
                    StringView label
            ) const noexcept (false) -> bool;

        public:
            __CDS_NoDiscard auto getInt (
                    StringView label
            ) const noexcept (false) -> int;

        public:
            __CDS_NoDiscard auto getLong (
                    StringView label
            ) const noexcept (false) -> long long int;

        public:
            __CDS_NoDiscard auto getFloat (
                    StringView label
            ) const noexcept (false) -> float;

        public:
            __CDS_NoDiscard auto getDouble (
                    StringView label
            ) const noexcept (false) -> double;

        public:
            __CDS_NoDiscard auto getString (
                    StringView label
            ) const noexcept (false) -> String const &;

        public:
            __CDS_NoDiscard auto getArray (
                    StringView label
            ) const noexcept (false) -> JsonArray const &;

        public:
            __CDS_NoDiscard auto getJson (
                    StringView label
            ) const noexcept (false) -> JsonObject const &;

        public:
            __CDS_NoDiscard auto getString (
                    StringView label
            ) noexcept (false) -> String &;

        public:
            __CDS_NoDiscard auto getArray (
                    StringView label
            ) noexcept (false) -> JsonArray &;

        public:
            __CDS_NoDiscard auto getJson (
                    StringView label
            ) noexcept (false) -> JsonObject &;
        };


        class JsonArray : public __hidden :: __impl :: __JsonArrayImplementation {

        private:
            using __Base = __hidden :: __impl :: __JsonArrayImplementation;

        public:
            constexpr JsonArray () noexcept;

        public:
            JsonArray (
                    JsonArray const & array
            ) noexcept;

        public:
            constexpr JsonArray (
                    JsonArray && array
            ) noexcept;

        public:
            JsonArray (
                    List < JsonElement > const & list
            ) noexcept;

        public:
            JsonArray (
                    String const & asString
            ) noexcept;

        public:
            ~JsonArray () noexcept;

        public:
            auto operator = (
                    JsonArray const & object
            ) noexcept -> JsonArray &;

        public:
            auto operator = (
                    JsonArray && object
            ) noexcept -> JsonArray &;

        public:
            auto operator = (
                    List < JsonElement > const & list
            ) noexcept -> JsonArray &;

        public:
            template < typename __ElementType >
            auto pushBack (
                    __ElementType && value
            ) noexcept -> JsonArray &;

        public:
            template < typename __ElementType >
            auto pushFront (
                    __ElementType && value
            ) noexcept -> JsonArray &;

        public:
            __CDS_NoDiscard auto getBoolean (
                    Index index
            ) const noexcept (false) -> bool;

        public:
            __CDS_NoDiscard auto getInt (
                    Index index
            ) const noexcept (false) -> int;

        public:
            __CDS_NoDiscard auto getLong (
                    Index index
            ) const noexcept (false) -> long long int;

        public:
            __CDS_NoDiscard auto getFloat (
                    Index index
            ) const noexcept (false) -> float;

        public:
            __CDS_NoDiscard auto getDouble (
                    Index index
            ) const noexcept (false) -> double;

        public:
            __CDS_NoDiscard auto getString (
                    Index index
            ) const noexcept (false) -> String const &;

        public:
            __CDS_NoDiscard auto getArray (
                    Index index
            ) const noexcept (false) -> JsonArray const &;

        public:
            __CDS_NoDiscard auto getJson (
                    Index index
            ) const noexcept (false) -> JsonObject const &;

        public:
            __CDS_NoDiscard auto getString (
                    Index index
            ) noexcept (false) -> String &;

        public:
            __CDS_NoDiscard auto getArray (
                    Index index
            ) noexcept (false) -> JsonArray &;

        public:
            __CDS_NoDiscard auto getJson (
                    Index index
            ) noexcept (false) -> JsonObject &;
        };

        __CDS_NoDiscard auto parseJson ( StringView asString ) noexcept (false) -> JsonObject;
        __CDS_NoDiscard auto parseJsonArray ( StringView asString ) noexcept (false) -> JsonArray;

        class JsonFormatException : public FormatException {

        public:
            JsonFormatException () noexcept : FormatException ( "JSON Input Format Exception" ) {}

        public:
            explicit JsonFormatException ( StringView message ) noexcept : FormatException ( message ) {}

        public:
            ~JsonFormatException () noexcept override = default;

        public:
            explicit JsonFormatException (
                    char expected,
                    char after,
                    char received
            ) noexcept :
                    FormatException (
                            String :: f (
                                    "JSON Input Format Exception : Expected '%c' after '%c', got '%c'",
                                    expected, after, received
                            )
                    ) {

            }

        public:
            explicit JsonFormatException (
                    char        expected,
                    StringView  after,
                    char        received
            ) noexcept :
                    FormatException (
                            String :: f (
                                    "JSON Input Format Exception : Expected '%c' after '%s', got '%c'",
                                    expected, after.cStr(), received
                            )
                    ) {

            }

        public:
            explicit JsonFormatException (
                    StringView  expected,
                    StringView  after,
                    StringView  reason
            ) noexcept :
                    FormatException (
                            String :: f (
                                    "JSON Input Format Exception : Expected '%s' after '%s', problem - '%s'",
                                    expected.cStr(), after.cStr(), reason.cStr()
                            )
                    ) {

            }
        };

    }
}

#include "json/impl/JSON.hpp"

#endif /* __CDS_JSON_HPP__ */
