//
// Created by loghin on 4/9/22.
//

#ifndef __CDS_EX_JSON_HPP__
#define __CDS_EX_JSON_HPP__

#include <CDS/meta/TypeTraits>
#include <CDS/HashMap>
#include <CDS/Concepts>
#include <CDS/Path>
#include <sstream>
#include <fstream>

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace json {

        namespace hidden { // NOLINT(modernize-concat-nested-namespaces)
            namespace impl {
                class JsonElement;

                using JsonCompatibleMap     = Map < String, JsonElement >;
                using JsonBaseMap           = HashMap < String, JsonElement >;

                using JsonCompatibleList    = List < JsonElement >;
                using JsonBaseList          = Array < JsonElement >;

#if __CDS_cpplang_Concepts_available

                template < typename T >
                concept ValidJsonObjectBaseClass    = DerivedFrom < T, JsonCompatibleMap >;

                template < typename T >
                concept ValidJsonArrayBaseClass     = DerivedFrom < T, JsonCompatibleList >;

#endif

            }
        }

        template < typename MapImplementationType = hidden :: impl :: JsonBaseMap > __CDS_Requires (
                hidden :: impl :: ValidJsonObjectBaseClass < MapImplementationType >
        ) class JsonObject;

        template < typename ArrayImplementationType = hidden :: impl :: JsonBaseList > __CDS_Requires (
                hidden :: impl :: ValidJsonArrayBaseClass < ArrayImplementationType >
        ) class JsonArray;

        namespace hidden { // NOLINT(modernize-concat-nested-namespaces)
            namespace impl {

                enum class ElementType {
                    Object,
                    Array,
                    String,
                    Bool,
                    Long,
                    Int = Long,
                    Double,
                    Float = Double,
                    Invalid,
                };

                __CDS_cpplang_ConstexprMultipleReturn auto toString ( ElementType type ) noexcept -> StringLiteral {
                    switch ( type ) {
                        case ElementType :: Object:     return "Object";
                        case ElementType :: Array:      return "Array";
                        case ElementType :: String:     return "String";
                        case ElementType :: Bool:       return "Bool";
                        case ElementType :: Long:       return "Long";
                        case ElementType :: Float:      return "Float";
                        default:
                        case ElementType :: Invalid:    return "Invalid";
                    }
                }

                template < typename T, typename = void >
                struct AdaptorProperties {
                    constexpr static bool adaptable = false;
                };

                template < >
                struct AdaptorProperties < int > {
                    constexpr static bool           adaptable   = true;
                    constexpr static ElementType    adaptEnum   = ElementType :: Long;
                    using                           AdaptedType = Long;
                };

                template < >
                struct AdaptorProperties < Integer > {
                    constexpr static bool           adaptable   = true;
                    constexpr static ElementType    adaptEnum   = ElementType :: Long;
                    using                           AdaptedType = Long;
                };

                template < >
                struct AdaptorProperties < long long > {
                    constexpr static bool           adaptable   = true;
                    constexpr static ElementType    adaptEnum   = ElementType :: Long;
                    using                           AdaptedType = Long;
                };

                template < >
                struct AdaptorProperties < Long > {
                    constexpr static bool           adaptable   = true;
                    constexpr static ElementType    adaptEnum   = ElementType :: Long;
                    using                           AdaptedType = Long;
                };

                template < >
                struct AdaptorProperties < float > {
                    constexpr static bool           adaptable   = true;
                    constexpr static ElementType    adaptEnum   = ElementType :: Double;
                    using                           AdaptedType = Double;
                };

                template < >
                struct AdaptorProperties < Float > {
                    constexpr static bool           adaptable   = true;
                    constexpr static ElementType    adaptEnum   = ElementType :: Double;
                    using                           AdaptedType = Double;
                };

                template < >
                struct AdaptorProperties < double > {
                    constexpr static bool           adaptable   = true;
                    constexpr static ElementType    adaptEnum   = ElementType :: Double;
                    using                           AdaptedType = Double;
                };

                template < >
                struct AdaptorProperties < Double > {
                    constexpr static bool           adaptable   = true;
                    constexpr static ElementType    adaptEnum   = ElementType :: Double;
                    using                           AdaptedType = Double;
                };

                template < >
                struct AdaptorProperties < bool > {
                    constexpr static bool           adaptable   = true;
                    constexpr static ElementType    adaptEnum   = ElementType :: Bool;
                    using                           AdaptedType = Boolean;
                };

                template < >
                struct AdaptorProperties < Boolean > {
                    constexpr static bool           adaptable   = true;
                    constexpr static ElementType    adaptEnum   = ElementType :: Bool;
                    using                           AdaptedType = Boolean;
                };

                template < >
                struct AdaptorProperties < String > {
                    constexpr static bool           adaptable   = true;
                    constexpr static ElementType    adaptEnum   = ElementType :: String;
                    using                           AdaptedType = String;
                };

                template < >
                struct AdaptorProperties < StringLiteral > {
                    constexpr static bool           adaptable   = true;
                    constexpr static ElementType    adaptEnum   = ElementType :: String;
                    using                           AdaptedType = String;
                };

                template < >
                struct AdaptorProperties < JsonObject < JsonBaseMap > > {
                    constexpr static bool           adaptable   = true;
                    constexpr static ElementType    adaptEnum   = ElementType :: Object;
                    using                           AdaptedType = JsonObject < JsonBaseMap >;
                };

                template < >
                struct AdaptorProperties < JsonArray < JsonBaseList > > {
                    constexpr static bool           adaptable   = true;
                    constexpr static ElementType    adaptEnum   = ElementType :: Array;
                    using                           AdaptedType = JsonArray < JsonBaseList >;
                };

                template < typename T, typename = void >
                struct PrimitiveAdaptable {
                    constexpr static bool value = false;
                };

                template < typename T >
                struct PrimitiveAdaptable < T > {
                    constexpr static bool value =
                            AdaptorProperties < T > :: adaptable && (
                                    experimental :: meta :: isFundamental < T > () || (
                                            experimental :: meta :: isSame < T, StringLiteral > () &&
                                            experimental :: meta :: isBasicPointer < T > ()
                                    )
                            );
                };

                template < typename T, typename = void >
                struct Adaptable {
                    constexpr static bool value = false;
                };

                template < typename T >
                struct Adaptable < T > {
                    constexpr static bool value =
                            AdaptorProperties < T > :: adaptable &&
                            ! experimental :: meta :: isFundamental < T > () && ! (
                                    experimental :: meta ::  isSame < T, StringLiteral > () &&
                                    experimental :: meta :: isBasicPointer < T > ()
                            );
                };

                __CDS_cpplang_ConstexprMultipleReturn auto implicitAdaptPossible ( ElementType from, ElementType to ) noexcept -> bool {
                    if ( from == ElementType :: Double && to == ElementType :: Long )   return true;
                    if ( from == ElementType :: Long && to == ElementType :: Double )   return true;
                    if ( from == ElementType :: Bool && to == ElementType :: Long )     return true;
                    if ( from == ElementType :: Long && to == ElementType :: Bool )     return true;
                    return false;
                }

                class JsonElement {
                private:
                    ElementType                     type;
                    cds :: UniquePointer < Object > value;

                    template < typename T, typename U = T, experimental :: meta :: EnableIf < experimental :: meta :: isFundamental < U > () > = 0 >
                    __CDS_OptimalInline auto implicitAdapt () const noexcept (false) -> T {
                        switch ( this->type ) {
                            case ElementType::Bool:     return static_cast < T > ( reinterpret_cast < Boolean const * > ( this->value.get() )->get() );
                            case ElementType::Long:     return static_cast < T > ( reinterpret_cast < Long const * > ( this->value.get() )->get() );
                            case ElementType::Double:   return static_cast < T > ( reinterpret_cast < Double const * > ( this->value.get() )->get() );
                            case ElementType::String:
                            case ElementType::Array:
                            case ElementType::Object:
                            case ElementType::Invalid:  throw TypeException ( "Invalid Type For K" );
                        }
                    }

                    template < typename T, typename U = T, experimental :: meta :: EnableIf < ! experimental :: meta :: isFundamental < U > () && experimental :: meta :: isBasicPointer < U > () && experimental :: meta :: isSame < U, StringLiteral > () > = 0 >
                    __CDS_OptimalInline auto implicitAdapt () const noexcept (false) -> T {
                        switch ( this->type ) {
                            case ElementType::Bool:
                            case ElementType::Long:
                            case ElementType::Double:
                            case ElementType::String:
                            case ElementType::Array:
                            case ElementType::Object:
                            case ElementType::Invalid:  throw NotImplementedException ( "To String conversion in JSON not implemented" );
                        }
                    }

                    __CDS_OptimalInline static auto copyByType ( JsonElement const & obj ) noexcept -> Object *;

                public:
                    constexpr JsonElement () noexcept :
                            type ( ElementType :: Invalid ),
                            value ( nullptr ) {

                    }

                    __CDS_OptimalInline JsonElement ( JsonElement const & obj ) noexcept :
                            type ( obj.type ),
                            value ( this->copyByType ( obj ) ) {

                    }

                    __CDS_OptimalInline JsonElement ( JsonElement && obj ) noexcept :
                            type ( cds :: exchange ( obj.type, ElementType :: Invalid ) ),
                            value ( std :: move ( obj.value ) ) {

                    }

                    template < typename T, typename U = T, experimental :: meta :: EnableIf < PrimitiveAdaptable < U > :: value > = 0 >
                    __CDS_OptimalInline JsonElement ( T object ) noexcept : // NOLINT(google-explicit-constructor)
                            type ( AdaptorProperties < T > :: adaptEnum ),
                            value ( cds :: copy < typename AdaptorProperties < T > :: AdaptedType > ( object ) ) { // NOLINT(cppcoreguidelines-pro-type-member-init)

                    }

                    template < typename T, typename U = T, experimental :: meta :: EnableIf < Adaptable < U > :: value && experimental :: meta :: isSame < typename AdaptorProperties < T > :: AdaptedType, T > () > = 0 >
                    __CDS_OptimalInline JsonElement ( T const & object ) noexcept : // NOLINT(google-explicit-constructor)
                            type ( AdaptorProperties < T > :: adaptEnum ),
                            value ( cds :: copy ( object ) ) { // NOLINT(cppcoreguidelines-pro-type-member-init)

                    }

                    template < typename T, typename U = T, experimental :: meta :: EnableIf < Adaptable < U > :: value && ! experimental :: meta :: isSame < typename AdaptorProperties < T > :: AdaptedType, T > () > = 0 >
                    __CDS_OptimalInline JsonElement ( T const & object ) noexcept : // NOLINT(google-explicit-constructor)
                            type ( AdaptorProperties < T > :: adaptEnum ),
                            value ( cds :: copy < typename AdaptorProperties < T > :: AdaptedType > ( object ) ) { // NOLINT(cppcoreguidelines-pro-type-member-init)

                    }

                    __CDS_OptimalInline ~JsonElement() noexcept = default;

                    template < typename T, typename U = T, experimental :: meta :: EnableIf < Adaptable < U > :: value > = 0 >
                    __CDS_OptimalInline auto to () const noexcept (false) -> typename AdaptorProperties < U > :: AdaptedType const & {
                        if ( AdaptorProperties < T > :: adaptEnum != this->type ) {
                            throw TypeException ( String :: f ( "Type Cast Exception. Cannot Convert '%s' to '%s'", impl :: toString ( type ), Type < T > :: name() ) );
                        }

                        return * reinterpret_cast < typename AdaptorProperties < T > :: AdaptedType * > ( this->value.get() );
                    };

                    template < typename T, typename U = T, experimental :: meta :: EnableIf < PrimitiveAdaptable < U > :: value > = 0 >
                    __CDS_OptimalInline auto to () const noexcept (false) -> T {
                        if ( AdaptorProperties < T > :: adaptEnum != this->type ) {
                            if ( implicitAdaptPossible ( AdaptorProperties < T > :: adaptEnum, this->type ) ) {
                                return this->implicitAdapt < T > ();
                            }

                            throw TypeException ( String :: f ( "Type Cast Exception. Cannot Convert '%s' to '%s'", impl :: toString ( type ), Type < T > :: name() ) );
                        }

                        return static_cast < T > ( * reinterpret_cast < typename AdaptorProperties < T > :: AdaptedType * > ( this->value.get() ) );
                    };

                    template < typename MapImplementationType = hidden :: impl :: JsonBaseMap >
                    __CDS_OptimalInline auto toJson () const noexcept (false) -> JsonObject < MapImplementationType > const & {
                        if ( this->type != ElementType :: Object ) {
                            throw TypeException ( String :: f ( "Type Cast Exception. Cannot Convert '%s' to '%s'", impl :: toString(type), "Object" ) );
                        }

                        return * reinterpret_cast < JsonObject < MapImplementationType > const * > ( this->value.get() );
                    }

                    template < typename ListImplementationType = hidden :: impl :: JsonBaseList >
                    __CDS_OptimalInline auto toArray () const noexcept (false) -> JsonArray < ListImplementationType > const & {
                        if ( this->type != ElementType :: Array ) {
                            throw TypeException ( String :: f ( "Type Cast Exception. Cannot Convert '%s' to '%s'", impl :: toString(type), "Array" ) );
                        }

                        return * reinterpret_cast < JsonArray < ListImplementationType > const * > ( this->value.get() );
                    }

                    __CDS_OptimalInline auto toString () const noexcept -> String {
                        if ( this->type == ElementType :: String ) {
                            return "\"" + this->value->toString() + "\"";
                        }

                        return this->value->toString();
                    }

                    __CDS_NoDiscard __CDS_OptimalInline auto is ( ElementType t ) const noexcept -> bool {
                        return this->type == t;
                    }
                };

                class JsonElementConstWrapper : public Object {
                private:
                    JsonElement const * pElement;
                public:
                    constexpr explicit JsonElementConstWrapper ( JsonElement const * pElement ) noexcept : pElement ( pElement ) {

                    }

                    constexpr JsonElementConstWrapper () noexcept : pElement ( nullptr ) {

                    }

                    constexpr JsonElementConstWrapper ( JsonElementConstWrapper const & wrapper ) noexcept : pElement ( wrapper.pElement ) {

                    }

                    constexpr JsonElementConstWrapper ( JsonElementConstWrapper && obj ) noexcept :
                            pElement ( cds :: exchange ( obj.pElement, nullptr ) ) {

                    }

                    __CDS_cpplang_NonConstConstexprMemberFunction auto operator = ( JsonElement const * pNewElement ) noexcept -> JsonElementConstWrapper & {
                        this->pElement = pNewElement;
                        return * this;
                    }

                    __CDS_cpplang_NonConstConstexprMemberFunction auto operator = ( JsonElementConstWrapper const & obj ) noexcept -> JsonElementConstWrapper & {
                        if ( this == & obj ) {
                            return * this;
                        }

                        this->pElement = obj.pElement;
                        return * this;
                    }

                    __CDS_cpplang_NonConstConstexprMemberFunction auto operator = ( JsonElementConstWrapper && obj ) noexcept -> JsonElementConstWrapper & {
                        if ( this == & obj ) {
                            return * this;
                        }

                        this->pElement = cds :: exchange ( obj.pElement, nullptr );
                        return * this;
                    }

                    __CDS_NoDiscard __CDS_OptimalInline auto getInt () const noexcept (false) -> Integer {
                        return this->pElement-> template to < int > ();
                    }

                    __CDS_NoDiscard __CDS_OptimalInline auto getLong () const noexcept (false) -> Long {
                        return this->pElement-> template to < long long > ();
                    }

                    __CDS_NoDiscard __CDS_OptimalInline auto getBoolean () const noexcept (false) -> Boolean {
                        return this->pElement-> template to < bool > ();
                    }

                    __CDS_NoDiscard __CDS_OptimalInline auto getFloat () const noexcept (false) -> Float {
                        return this->pElement-> template to < float > ();
                    }

                    __CDS_NoDiscard __CDS_OptimalInline auto getDouble () const noexcept (false) -> Double {
                        return this->pElement-> template to < double > ();
                    }

                    __CDS_NoDiscard __CDS_OptimalInline auto getString () const noexcept (false) -> String const & {
                        return this->pElement-> template to < String > ();
                    }

                    template < typename MapImplementationType = hidden :: impl :: JsonBaseMap >
                    __CDS_NoDiscard __CDS_OptimalInline auto getJson () const noexcept (false) -> JsonObject < MapImplementationType > const & {
                        return this->pElement-> template toJson < MapImplementationType > ();
                    }

                    template < typename ListImplementationType = hidden :: impl :: JsonBaseList >
                    __CDS_NoDiscard __CDS_OptimalInline auto getArray () const noexcept (false) -> JsonArray < ListImplementationType > const & {
                        return this->pElement->template toArray < ListImplementationType > ();
                    }

                    __CDS_NoDiscard __CDS_OptimalInline auto isInt () const noexcept -> bool {
                        return this->pElement-> is ( ElementType :: Int );
                    }

                    __CDS_NoDiscard __CDS_OptimalInline auto isLong () const noexcept -> bool {
                        return this->pElement-> is ( ElementType :: Long );
                    }

                    __CDS_NoDiscard __CDS_OptimalInline auto isBoolean () const noexcept -> bool {
                        return this->pElement-> is ( ElementType :: Bool );
                    }

                    __CDS_NoDiscard __CDS_OptimalInline auto isFloat () const noexcept -> bool {
                        return this->pElement-> is ( ElementType :: Float );
                    }

                    __CDS_NoDiscard __CDS_OptimalInline auto isDouble () const noexcept -> bool {
                        return this->pElement-> is ( ElementType :: Double );
                    }

                    __CDS_NoDiscard __CDS_OptimalInline auto isString () const noexcept -> bool {
                        return this->pElement-> is ( ElementType :: String );
                    }

                    __CDS_NoDiscard __CDS_OptimalInline auto isJson () const noexcept -> bool {
                        return this->pElement-> is ( ElementType :: Object );
                    }

                    __CDS_NoDiscard __CDS_OptimalInline auto isArray () const noexcept -> bool {
                        return this->pElement-> is ( ElementType :: Array );
                    }

                    __CDS_NoDiscard __CDS_MaybeUnused auto is ( ElementType type ) const noexcept -> bool {
                        return this->pElement->is ( type );
                    }

                    __CDS_NoDiscard __CDS_OptimalInline auto toString () const noexcept -> String override {
                        return this->pElement->toString();
                    }
                };
            }
        }

        using JsonElement       = hidden :: impl :: JsonElement;
        using JsonElementType   = hidden :: impl :: ElementType;

        template < typename MapImplementationType > __CDS_Requires (
                hidden :: impl :: ValidJsonObjectBaseClass < MapImplementationType >
        ) class JsonObject : public MapImplementationType {

            static_assert (
                    experimental :: meta :: isDerivedFrom < MapImplementationType, hidden :: impl :: JsonCompatibleMap > (),
                    "json :: Object requires a Map < String, hidden :: impl :: Element > compatible template parameter to be used"
            );

        private:
            Array < String > orderedKeys;
            friend class hidden :: impl :: JsonElement;

        public:
            JsonObject () noexcept = default;

            JsonObject ( JsonObject const & obj ) noexcept :
                    MapImplementationType ( obj ),
                    orderedKeys ( obj.orderedKeys ) {

            }

            __CDS_OptimalInline auto copy () const noexcept -> JsonObject * override {
                return Memory :: instance().create < JsonObject > ( * this );
            }

            template < typename T, typename U = T, experimental :: meta :: EnableIf < hidden :: impl :: PrimitiveAdaptable < U > :: value > = 0 >
            __CDS_OptimalInline auto put ( String label, T object ) noexcept -> JsonObject & {
                if ( ! this->orderedKeys.contains ( label ) ) {
                    this->orderedKeys.add ( label );
                }

                this-> MapImplementationType :: insert ( { std :: move ( label ), { object } } );
                return * this;
            }

            template < typename T, typename U = T, experimental :: meta :: EnableIf < hidden :: impl :: Adaptable < U > :: value > = 0 >
            __CDS_OptimalInline auto put ( String label, T const & object ) noexcept -> JsonObject & {
                if ( ! this->orderedKeys.contains ( label ) ) {
                    this->orderedKeys.add ( label );
                }

                this-> MapImplementationType :: insert ( { std :: move ( label ), { object } } );
                return * this;
            }

            template < typename T, typename U = T, experimental :: meta :: EnableIf < hidden :: impl :: Adaptable < U > :: value > = 0 >
            __CDS_NoDiscard __CDS_OptimalInline auto get ( String const & label ) const noexcept (false) -> typename hidden :: impl :: AdaptorProperties < T > :: AdaptedType const & {
                auto value = MapImplementationType :: find ( label );
                if ( ! value.hasValue() ) {
                    throw KeyException ( label );
                }

                return value.value() -> template to < T > ();
            }

            template < typename T, typename U = T, experimental :: meta :: EnableIf < hidden :: impl :: PrimitiveAdaptable < U > :: value > = 0 >
            __CDS_NoDiscard __CDS_OptimalInline auto get ( String const & label ) const noexcept (false) -> T {
                auto value = MapImplementationType :: find ( label );
                if ( ! value.hasValue() ) {
                    throw KeyException ( label );
                }

                return value.value() -> template to < T > ();
            }

            __CDS_NoDiscard __CDS_OptimalInline auto getInt ( String const & key ) const noexcept (false) -> Integer {
                return this->get < int > ( key );
            }

            __CDS_NoDiscard __CDS_OptimalInline auto getLong ( String const & key ) const noexcept (false) -> Long {
                return this->get < long long > ( key );
            }

            __CDS_NoDiscard __CDS_OptimalInline auto getFloat ( String const & key ) const noexcept (false) -> Float {
                return this->get < float > ( key );
            }

            __CDS_NoDiscard __CDS_OptimalInline auto getDouble ( String const & key ) const noexcept (false) -> Double {
                return this->get < double > ( key );
            }

            __CDS_NoDiscard __CDS_OptimalInline auto getBoolean ( String const & key ) const noexcept (false) -> Boolean {
                return this->get < bool > ( key );
            }

            __CDS_NoDiscard __CDS_OptimalInline auto getString ( String const & key ) const noexcept (false) -> String const & {
                return this->get < String > ( key );
            }

            __CDS_NoDiscard __CDS_OptimalInline auto getJson ( String const & key ) const noexcept (false) -> JsonObject const & {
                auto value = MapImplementationType :: find ( key );
                if ( ! value.hasValue() ) {
                    throw KeyException ( key );
                }

                return value.value()->toJson ();
            }

            template < typename ListImplementationType = hidden :: impl :: JsonBaseList >
            __CDS_NoDiscard __CDS_OptimalInline auto getArray ( String const & key ) const noexcept (false) -> JsonArray < ListImplementationType > const & {
                auto value = MapImplementationType :: find ( key );
                if ( ! value.hasValue() ) {
                    throw KeyException ( key );
                }

                return value.value()-> template toArray < ListImplementationType > ();
            }

            __CDS_NoDiscard auto toString () const noexcept -> String override {
                String result;

                for ( auto const & key : this->orderedKeys ) {
                    result += R"(")" + key + R"(" : )" + this-> MapImplementationType :: get ( key ).toString () + ", ";
                }

                if ( result.empty() ) {
                    return "{}";
                }

                return "{ "_s + result.removeSuffix(", ") + " }";
            }

            __CDS_NoDiscard __CDS_OptimalInline auto keys ( int = 0 ) const noexcept -> Array < String > const & {
                return this->orderedKeys;
            }

            class ConstIterator {
            private:
                Array < String > :: ConstIterator baseIterator;
                JsonObject                const * pBaseObject;
            public:
                __CDS_OptimalInline explicit ConstIterator (
                        Array < String > :: ConstIterator const & iterator,
                        JsonObject                        const * pBaseObject
                ) noexcept :
                        baseIterator ( iterator ),
                        pBaseObject ( pBaseObject ) {

                }

                __CDS_NoDiscard __CDS_OptimalInline auto operator * () const noexcept -> Pair < String, hidden :: impl :: JsonElementConstWrapper > {
                    return { * this->baseIterator, hidden :: impl :: JsonElementConstWrapper ( & ( this->pBaseObject->MapImplementationType :: get( * this->baseIterator ) ) ) };
                }

                __CDS_NoDiscard __CDS_OptimalInline auto operator != ( ConstIterator const & it ) const noexcept -> bool {
                    return this->baseIterator != it.baseIterator;
                }

                __CDS_OptimalInline auto operator ++ () noexcept -> ConstIterator & {
                    ++ this->baseIterator;
                    return * this;
                }

                __CDS_OptimalInline auto operator ++ (int) noexcept -> ConstIterator {
                    auto copy = * this;
                    ++ this->baseIterator;
                    return * copy;
                }
            };

            __CDS_NoDiscard __CDS_OptimalInline auto begin () const noexcept -> ConstIterator {
                return ConstIterator ( this->orderedKeys.begin(), this );
            }

            __CDS_NoDiscard __CDS_OptimalInline auto end () const noexcept -> ConstIterator {
                return ConstIterator ( this->orderedKeys.end(), this );
            }

            __CDS_NoDiscard __CDS_OptimalInline auto empty () const noexcept -> bool override {
                return this->orderedKeys.empty();
            }

            __CDS_OptimalInline auto clear () noexcept -> void override {
                this-> MapImplementationType :: clear ();
                this->orderedKeys.clear();
            }
        };

        template < typename ListImplementationType > __CDS_Requires (
                hidden :: impl :: ValidJsonArrayBaseClass < ListImplementationType >
        ) class JsonArray : public ListImplementationType {

            static_assert (
                    experimental :: meta :: isDerivedFrom < ListImplementationType, hidden :: impl :: JsonCompatibleList > (),
                    "json :: Array requires a List < hidden :: impl :: Element > compatible template parameter to be used"
            );

        private:
            friend class hidden :: impl :: JsonElement;

        public:
            JsonArray () noexcept = default;

            JsonArray ( JsonArray const & obj ) noexcept :
                    ListImplementationType (obj) {

            }

            __CDS_OptimalInline auto copy () const noexcept -> JsonArray * override {
                return Memory :: instance ().create < JsonArray > ( * this );
            }

            template < typename T, typename U = T, experimental :: meta :: EnableIf < hidden :: impl :: PrimitiveAdaptable < U > :: value > = 0 >
            __CDS_OptimalInline auto add ( T object ) -> JsonArray & {
                this->Collection < JsonElement > :: add ( object );
                return * this;
            }

            template < typename T, typename U = T, experimental :: meta :: EnableIf < hidden :: impl :: Adaptable < U > :: value > = 0 >
            __CDS_OptimalInline auto add ( T const & object ) -> JsonArray & {
                this->Collection < JsonElement > :: add ( object );
                return * this;
            }

            template < typename T, typename U = T, experimental :: meta :: EnableIf < hidden :: impl :: PrimitiveAdaptable < U > :: value > = 0 >
            __CDS_OptimalInline auto pushBack ( T object ) -> JsonArray & {
                this->ListImplementationType :: pushBack ( object );
                return * this;
            }

            template < typename T, typename U = T, experimental :: meta :: EnableIf < hidden :: impl :: Adaptable < U > :: value > = 0 >
            __CDS_OptimalInline auto pushBack ( T const & object ) -> JsonArray & {
                this->ListImplementationType :: pushBack ( object );
                return * this;
            }

            template < typename T, typename U = T, experimental :: meta :: EnableIf < hidden :: impl :: PrimitiveAdaptable < U > :: value > = 0 >
            __CDS_OptimalInline auto pushFront ( T object ) -> JsonArray & {
                this->ListImplementationType :: pushFront ( object );
                return * this;
            }

            template < typename T, typename U = T, experimental :: meta :: EnableIf < hidden :: impl :: Adaptable < U > :: value > = 0 >
            __CDS_OptimalInline auto pushFront ( T const & object ) -> JsonArray & {
                this->ListImplementationType :: pushFront ( object );
                return * this;
            }

            template < typename T, typename U = T, experimental :: meta :: EnableIf < hidden :: impl :: Adaptable < U > :: value > = 0 >
            __CDS_NoDiscard __CDS_OptimalInline auto get ( Index index ) const noexcept (false) -> typename hidden :: impl :: AdaptorProperties < T > :: AdaptedType const & {
                return ListImplementationType :: get ( index ). template to < T > ();
            }

            template < typename T, typename U = T, experimental :: meta :: EnableIf < hidden :: impl :: PrimitiveAdaptable < U > :: value > = 0 >
            __CDS_NoDiscard __CDS_OptimalInline auto get ( Index index ) const noexcept (false) -> T {
                return ListImplementationType :: get ( index ). template to < T > ();
            }

            __CDS_NoDiscard __CDS_OptimalInline auto getInt ( Index index ) const noexcept (false) -> Integer {
                return this->get < int > ( index );
            }

            __CDS_NoDiscard __CDS_OptimalInline auto getLong ( Index index ) const noexcept (false) -> Long {
                return this->get < long long > ( index );
            }

            __CDS_NoDiscard __CDS_OptimalInline auto getFloat ( Index index ) const noexcept (false) -> Float {
                return this->get < float > ( index );
            }

            __CDS_NoDiscard __CDS_OptimalInline auto getDouble ( Index index ) const noexcept (false) -> Double {
                return this->get < double > ( index );
            }

            __CDS_NoDiscard __CDS_OptimalInline auto getBoolean ( Index index ) const noexcept (false) -> Boolean {
                return this->get < bool > ( index );
            }

            __CDS_NoDiscard __CDS_OptimalInline auto getString ( Index index ) const noexcept (false) -> String const & {
                return this->get < String > ( index );
            }

            template < typename MapImplementationType = hidden :: impl :: JsonBaseMap >
            __CDS_NoDiscard __CDS_OptimalInline auto getJson ( Index index ) const noexcept (false) -> JsonObject < MapImplementationType > const & {
                return this->ListImplementationType :: get (index).template toJson < MapImplementationType > ();
            }

            __CDS_NoDiscard __CDS_OptimalInline auto getArray ( Index index ) const noexcept (false) -> JsonArray const & {
                return this->ListImplementationType :: get (index).toArray();
            }

            __CDS_NoDiscard auto toString () const noexcept -> String override {
                String result;

                for ( auto it = this -> ListImplementationType :: begin(); it != this-> ListImplementationType :: end (); ++ it ) {
                    result += (* it).toString() + ", ";
                }

                if ( result.empty() ) {
                    return "[]";
                }

                return "[ "_s + result.removeSuffix(", ") + " ]";
            }

            class ConstIterator {
            private:
                typename ListImplementationType :: ConstIterator    baseIterator;
                hidden :: impl :: JsonElementConstWrapper           wrapper;
            public:
                constexpr ConstIterator () noexcept = default;

                explicit ConstIterator ( typename ListImplementationType :: ConstIterator const & it ) noexcept :
                        baseIterator ( it ) {

                    if ( it.isValid() ) {
                        this->wrapper = & ( * it );
                    }
                }

                __CDS_NoDiscard __CDS_OptimalInline auto operator * () const noexcept -> hidden :: impl :: JsonElementConstWrapper const & {
                    return this->wrapper;
                }

                __CDS_NoDiscard __CDS_OptimalInline auto operator -> () const noexcept -> hidden :: impl :: JsonElementConstWrapper const * {
                    return & this->wrapper;
                }

                __CDS_NoDiscard __CDS_OptimalInline auto operator != ( ConstIterator const & it ) const noexcept -> bool {
                    return this->baseIterator != it.baseIterator;
                }

                __CDS_NoDiscard __CDS_OptimalInline auto operator == ( ConstIterator const & it ) const noexcept -> bool {
                    return this->baseIterator == it.baseIterator;
                }

                __CDS_OptimalInline auto operator ++ () noexcept -> ConstIterator & {
                    ++ this->baseIterator;
                    this->wrapper = hidden :: impl :: JsonElementConstWrapper { & ( * this->baseIterator ) };
                    return * this;
                }

                __CDS_OptimalInline auto operator ++ ( int ) noexcept -> ConstIterator {
                    auto copy = * this;
                    ++ this->baseIterator;
                    this->wrapper = hidden :: impl :: JsonElementConstWrapper { & ( * this->baseIterator ) };
                    return copy;
                }
            };

            __CDS_OptimalInline auto begin () const noexcept -> ConstIterator {
                return ConstIterator ( this-> ListImplementationType :: begin () );
            }

            __CDS_OptimalInline auto end () const noexcept -> ConstIterator {
                return ConstIterator ( this-> ListImplementationType :: end () );
            }
        };

        template <
                typename MapImplementationType = hidden :: impl :: JsonBaseMap,
                typename ListImplementationType = hidden :: impl :: JsonBaseList
        > __CDS_OptionalInline auto parseJson ( String jsonAsString ) noexcept (false) -> JsonObject < MapImplementationType >;

        template <
                typename MapImplementationType = hidden :: impl :: JsonBaseMap,
                typename ListImplementationType = hidden :: impl :: JsonBaseList
        > __CDS_OptimalInline auto parseJsonArray ( String ) noexcept (false) -> JsonArray < ListImplementationType >;

        namespace hidden { // NOLINT(modernize-concat-nested-namespaces)
            namespace impl {
                template <
                        typename MapImplementationType,
                        typename ListImplementationType
                > __CDS_OptimalInline auto identifyAndEmplace (
                        String                              const & label,
                        String                              const & data,
                        JsonObject < MapImplementationType >      & json
                ) noexcept (false) -> void {
                    if ( data.front() == '{' ) {
                        json.put ( label, parseJson < MapImplementationType, ListImplementationType > ( data ) );
                    } else if ( data.front() == '[' ) {
                        json.put ( label, parseJsonArray < MapImplementationType, ListImplementationType > ( data ) );
                    } else if ( data.findFirst('"') != String :: INVALID_POS ) {
                        json.put ( label, data.trim ( '"' ) );
                    } else if ( data.findFirst( '.' ) != String :: INVALID_POS ) {
                        json.put ( label, Double :: parse ( data ) );
                    } else if ( data.findFirst( "true" ) != String::INVALID_POS || data.findFirst( "false" ) != String::INVALID_POS ) {
                        json.put ( label, data == "true" );
                    } else {
                        json.put ( label, Long :: parse ( data ) );
                    }
                }

                template <
                        typename MapImplementationType,
                        typename ListImplementationType
                > __CDS_OptimalInline auto identifyAndPushBack (
                        String                              const & data,
                        JsonArray < ListImplementationType >      & array
                ) noexcept (false) -> void {
                    if ( data.front() == '{' ) {
                        array.add ( json :: parseJson < MapImplementationType, ListImplementationType > ( data ) );
                    } else if ( data.front() == '[' ) {
                        array.add ( json :: parseJsonArray < MapImplementationType, ListImplementationType > ( data ) );
                    } else if ( data.findFirst('"') != String :: INVALID_POS ) {
                        array.add ( data.trim ( '"' ) );
                    } else if ( data.findFirst( '.' ) != String :: INVALID_POS ) {
                        array.add ( Double :: parse ( data ) );
                    } else if ( data.findFirst( "true" ) != String::INVALID_POS || data.findFirst( "false" ) != String::INVALID_POS ) {
                        array.add ( data == "true" );
                    } else {
                        array.add ( Long :: parse ( data ) );
                    }
                }
            }
        }

        template <
                typename MapImplementationType,
                typename ListImplementationType
        > __CDS_OptionalInline auto parseJson ( String jsonAsString ) noexcept (false) -> JsonObject < MapImplementationType > {
            constexpr StringLiteral whitespace = " \r\n\t\f";
            JsonObject < MapImplementationType > result;

            jsonAsString.replace ( 0, static_cast < Size > ( jsonAsString.findFirst ( '{' ) + 1 ), "" );
            jsonAsString.replace ( jsonAsString.findLast('}'), jsonAsString.size(), "" );

            while ( ! jsonAsString.empty() ) {
                auto labelSeparatorPosition = jsonAsString.findFirst(':');
                auto label = jsonAsString.substr ( 0, labelSeparatorPosition );
                auto afterLabel = jsonAsString.substr ( labelSeparatorPosition + 1 ).trim(whitespace);

                label.replace(0, static_cast < Size > ( label.findFirst ( '"' ) + 1 ), "");
                label.replace( label.findFirst('"'), label.size(), "" );

                sint32 arrayBracketCount = 0;
                sint32 objectBracketCount = 0;
                sint32 segmentLength = 0;

                String dataAsString;

                for ( auto character : afterLabel ) {
                    if ( arrayBracketCount == 0 && objectBracketCount == 0 && character == ',' ) {
                        break;
                    } else {
                        if      ( character == '{' ) { ++ objectBracketCount; }
                        else if ( character == '}' ) { -- objectBracketCount; }
                        else if ( character == '[' ) { ++ arrayBracketCount; }
                        else if ( character == ']' ) { -- arrayBracketCount; }
                        else { }

                        dataAsString += character;
                        ++ segmentLength;
                    }
                }

                afterLabel.replace ( 0, segmentLength + 1, "" );
                hidden :: impl :: identifyAndEmplace < MapImplementationType, ListImplementationType > ( label, dataAsString.trim(whitespace), result );
                jsonAsString = afterLabel;
            }

            return result;
        }

        template <
                typename MapImplementationType = hidden :: impl :: JsonBaseMap,
                typename ListImplementationType = hidden :: impl :: JsonBaseList
        > __CDS_OptimalInline auto loadJson ( Path const & path ) noexcept (false) -> JsonObject < MapImplementationType > {
            return parseJson < MapImplementationType, ListImplementationType > ( ( std :: stringstream () << std :: ifstream ( path.toString().cStr() ).rdbuf() ).str() );
        }

        template <
                typename MapImplementationType,
                typename ListImplementationType
        > __CDS_OptimalInline auto parseJsonArray ( String arrayAsString ) noexcept (false) -> JsonArray < ListImplementationType > {
            constexpr StringLiteral whitespace = " \t\r\n\f";
            JsonArray < ListImplementationType > result;

            arrayAsString.replace ( 0, static_cast < Size > ( arrayAsString.findFirst('[') + 1 ), "" );
            arrayAsString.replace ( arrayAsString.findLast(']'), arrayAsString.size(), "" );

            while ( ! arrayAsString.empty() ) {
                arrayAsString.trim(whitespace);

                sint32 arrayBracketCount = 0;
                sint32 objectBracketCount = 0;
                sint32 segmentLength = 0;

                String dataAsString;

                for ( auto character : arrayAsString ) {
                    if ( arrayBracketCount == 0 && objectBracketCount == 0 && character == ',' ) {
                        break;
                    } else {
                        if      ( character == '{' ) { ++ objectBracketCount; }
                        else if ( character == '}' ) { -- objectBracketCount; }
                        else if ( character == '[' ) { ++ arrayBracketCount; }
                        else if ( character == ']' ) { -- arrayBracketCount; }
                        else { }

                        dataAsString += character;
                        ++ segmentLength;
                    }
                }

                arrayAsString.replace(0, segmentLength + 1, "");
                hidden :: impl :: identifyAndPushBack < MapImplementationType, ListImplementationType > ( dataAsString, result );
            }

            return result;
        }

        template <
                typename MapImplementationType = hidden :: impl :: JsonBaseMap,
                typename ListImplementationType = hidden :: impl :: JsonBaseList
        > __CDS_OptimalInline auto loadJsonArray ( Path const & path ) noexcept (false) -> JsonArray < ListImplementationType > {
            return parseJsonArray < MapImplementationType, ListImplementationType > ( ( std :: stringstream () << std :: ifstream ( path.toString().cStr() ).rdbuf() ).str() );
        }

        namespace hidden { // NOLINT(modernize-concat-nested-namespaces)
            namespace impl {
                template < typename MapImplementationType = hidden :: impl :: JsonBaseMap >
                using ObjectIterableValue = decltype ( Type < typename JsonObject < MapImplementationType > :: ConstIterator > :: unsafeAddress ()->operator* () );

                template < typename ListImplementationType = hidden :: impl :: JsonBaseList >
                using ArrayIterableValue = decltype ( Type < typename JsonArray < ListImplementationType > :: ConstIterator > :: unsafeAddress ()->operator* () );

                template <
                        typename MapImplementationType = hidden :: impl :: JsonBaseMap,
                        typename ListImplementationType = hidden :: impl :: JsonBaseList
                > __CDS_OptimalInline auto dumpIndented ( ObjectIterableValue < MapImplementationType > const & value, int indent, int depth ) noexcept -> String {
                    String common = R"(")" + value.first() + "\" : ";

                    if ( value.second().isJson () ) {
                        return common + "\n" + (" "_s * ( indent * ( depth ) )) +
                               dumpIndented < MapImplementationType, ListImplementationType > ( value.second().getJson(), indent, depth );
                    } else if ( value.second().isArray() ) {
                        return common + "\n" + (" "_s * ( indent * ( depth ) )) +
                               dumpIndented < MapImplementationType, ListImplementationType > ( value.second().getArray(), indent, depth );
                    } else {
                        return common + value.second().toString ();
                    }
                }

                template <
                        typename MapImplementationType = hidden :: impl :: JsonBaseMap,
                        typename ListImplementationType = hidden :: impl :: JsonBaseList
                > __CDS_OptimalInline auto dumpIndented ( ArrayIterableValue < ListImplementationType > const & value, int indent, int depth ) noexcept -> String {
                    if ( value.isJson () ) {
                        return dumpIndented < MapImplementationType, ListImplementationType > ( value.getJson(), indent, depth );
                    } else if ( value.isArray() ) {
                        return dumpIndented < MapImplementationType, ListImplementationType > ( value.getArray(), indent, depth );
                    } else {
                        return value.toString ();
                    }
                }

                template <
                        typename MapImplementationType = hidden :: impl :: JsonBaseMap,
                        typename ListImplementationType = hidden :: impl :: JsonBaseList
                > __CDS_OptimalInline auto dumpIndented ( JsonObject < MapImplementationType > const & object, int indent, int depth ) noexcept -> String {
                    String indentation = " "_s * (indent * depth);
                    String futureIndentation = indentation + " "_s * indent;

                    String result = "{\n";
                    for ( auto const & element : object ) {
                        result += futureIndentation + dumpIndented < MapImplementationType, ListImplementationType > ( element, indent, depth + 1 ) + ",\n";
                    }

                    if ( object.empty () ) {
                        return "{}";
                    }

                    return result.replace ( static_cast < Index > (result.size()) - 2, 2U, "\n" ) + indentation + "}";
                }

                template <
                        typename MapImplementationType = hidden :: impl :: JsonBaseMap,
                        typename ListImplementationType = hidden :: impl :: JsonBaseList
                > __CDS_OptimalInline auto dumpIndented ( JsonArray < ListImplementationType > const & array, int indent, int depth ) noexcept -> String {
                    String indentation = " "_s * (indent * depth);
                    String futureIndentation = indentation + " "_s * indent;

                    String result = "[\n";
                    for ( auto const & element : array ) {
                        result += futureIndentation + dumpIndented < MapImplementationType, ListImplementationType > ( element, indent, depth + 1 ) + ",\n";
                    }

                    if ( array.empty () ) {
                        return "[]";
                    }

                    return result.replace ( static_cast < Index > (result.size()) - 2, 2U, "\n" ) + indentation + "]";
                }
            }
        }

        template <
                typename MapImplementationType = hidden :: impl :: JsonBaseMap,
                typename ListImplementationType = hidden :: impl :: JsonBaseList
        > __CDS_OptimalInline auto dump ( JsonObject < MapImplementationType > const & object, int indent = 4 ) noexcept -> String {
            return hidden :: impl :: dumpIndented < MapImplementationType, ListImplementationType > ( object, indent, 0 );
        }

        template <
                typename MapImplementationType = hidden :: impl :: JsonBaseMap,
                typename ListImplementationType = hidden :: impl :: JsonBaseList
        > __CDS_OptimalInline auto dump ( JsonArray < ListImplementationType > const & array, int indent = 4 ) noexcept -> String {
            return hidden :: impl :: dumpIndented < MapImplementationType, ListImplementationType > ( array, indent, 0 );
        }

        namespace standard {

            using JsonObject    = json :: JsonObject < json :: hidden :: impl :: JsonBaseMap >;
            using JsonArray     = json :: JsonArray < json :: hidden :: impl :: JsonBaseList >;

        }

        namespace hidden {
            namespace impl {
                __CDS_OptimalInline auto JsonElement :: copyByType ( JsonElement const & obj ) noexcept -> Object * {
                    switch ( obj.type ) {
                        case ElementType::Bool:     return cds :: copy ( * reinterpret_cast  < AdaptorProperties < Boolean > :: AdaptedType * > ( obj.value.get() ) );
                        case ElementType::Long:     return cds :: copy ( * reinterpret_cast  < AdaptorProperties < Long > :: AdaptedType * > ( obj.value.get() ) );
                        case ElementType::Double:   return cds :: copy ( * reinterpret_cast  < AdaptorProperties < Double > :: AdaptedType * > ( obj.value.get() ) );
                        case ElementType::String:   return cds :: copy ( * reinterpret_cast  < AdaptorProperties < String > :: AdaptedType * > ( obj.value.get() ) );
                        case ElementType::Array:    return cds :: copy ( * reinterpret_cast  < AdaptorProperties < JsonArray < JsonBaseList > > :: AdaptedType * > ( obj.value.get() ) );
                        case ElementType::Object:   return cds :: copy ( * reinterpret_cast  < AdaptorProperties < JsonObject < JsonBaseMap > > :: AdaptedType * > ( obj.value.get() ) );
                        case ElementType::Invalid:  return nullptr;
                    }
                }
            }
        }

    }
}

#endif // __CDS_EX_JSON_HPP__
