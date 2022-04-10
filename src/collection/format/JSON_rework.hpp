//
// Created by loghin on 4/9/22.
//

#ifndef __CDS_JSON_HPP__
#define __CDS_JSON_HPP__

#include <CDS/HashMap>
#include <CDS/Concepts>

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace json {

        namespace hidden { // NOLINT(modernize-concat-nested-namespaces)
            namespace impl {
                class JsonElement;

                using JsonCompatibleMap = Map < String, JsonElement >;
                using JsonBaseMap       = HashMap < String, JsonElement >;
            }
        }

        template < typename MapImplementationType = hidden :: impl :: JsonBaseMap > __CDS_Requires (
                DerivedFrom < MapImplementationType, hidden :: impl :: JsonCompatibleMap >
        ) class JsonObject;

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

                constexpr auto toString ( ElementType type ) noexcept -> StringLiteral {
                    switch ( type ) {
                        case ElementType :: Object:     return "Object";
                        case ElementType :: Array:      return "Array";
                        case ElementType :: String:     return "String";
                        case ElementType :: Bool:       return "Bool";
                        case ElementType :: Long:       return "Long";
                        case ElementType :: Float:      return "Float";
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

                template < typename T, typename = void >
                struct PrimitiveAdaptable {
                    constexpr static bool value = false;
                };

                template < typename T >
                struct PrimitiveAdaptable < T > {
                    constexpr static bool value = AdaptorProperties < T > :: adaptable && ( Type < T > :: isPrimitive || ( isSame < T, StringLiteral > () && Type < T > :: isBasicPointer ) );
                };

                template < typename T, typename = void >
                struct Adaptable {
                    constexpr static bool value = false;
                };

                template < typename T >
                struct Adaptable < T > {
                    constexpr static bool value = AdaptorProperties < T > :: adaptable && ! Type < T > :: isPrimitive && ! ( isSame < T, StringLiteral > () && Type < T > :: isBasicPointer );
                };

                constexpr auto implicitAdaptPossible ( ElementType from, ElementType to ) noexcept -> bool {
                    if ( from == ElementType :: Double && to == ElementType :: Long )   return true;
                    if ( from == ElementType :: Long && to == ElementType :: Double )   return true;
                    if ( from == ElementType :: Bool && to == ElementType :: Long )     return true;
                    if ( from == ElementType :: Long && to == ElementType :: Bool )     return true;
                    return false;
                }

                class JsonElement {
                private:
                    ElementType              type;
                    UniquePointer < Object > value;

                    template < typename T, typename U = T, EnableIf < Type < U > :: isPrimitive > = 0 >
                    __CDS_OptimalInline auto implicitAdapt () const noexcept (false) -> T {
                        switch ( this->type ) {
                            case ElementType::Bool:     return static_cast < T > ( reinterpret_cast < Boolean const * > ( this->value.get() )->get() );
                            case ElementType::Long:     return static_cast < T > ( reinterpret_cast < Long const * > ( this->value.get() )->get() );
                            case ElementType::Double:   return static_cast < T > ( reinterpret_cast < Double const * > ( this->value.get() )->get() );
                            case ElementType::String:
                            case ElementType::Array:
                            case ElementType::Object:
                            case ElementType::Invalid:  throw TypeException ( "Invalid Type For Key" );
                        }
                    }

                    template < typename T, typename U = T, EnableIf < ! Type < U > :: isPrimitive && Type < U > :: isBasicPointer && isSame < U, StringLiteral > > = 0 >
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

                public:
                    constexpr JsonElement () noexcept :
                            type ( ElementType :: Invalid ),
                            value ( nullptr ) {

                    }

                    __CDS_OptimalInline JsonElement ( JsonElement const & obj ) noexcept :
                            type ( obj.type ),
                            value ( obj.value->copy() ) {

                    }

                    __CDS_OptimalInline JsonElement ( JsonElement && obj ) noexcept :
                            type ( cds :: exchange ( obj.type, ElementType :: Invalid ) ),
                            value ( std :: move ( obj.value ) ) {

                    }

                    template < typename T, typename U = T, EnableIf < PrimitiveAdaptable < U > :: value > = 0 >
                    __CDS_OptimalInline JsonElement ( T object ) noexcept : // NOLINT(google-explicit-constructor)
                            type ( AdaptorProperties < T > :: adaptEnum ),
                            value ( typename AdaptorProperties < T > :: AdaptedType ( object ).copy() ){ // NOLINT(cppcoreguidelines-pro-type-member-init)

                    }

                    template < typename T, typename U = T, EnableIf < Adaptable < U > :: value > = 0 >
                    __CDS_OptimalInline JsonElement ( T const & object ) noexcept : // NOLINT(google-explicit-constructor)
                            type ( AdaptorProperties < T > :: adaptEnum ),
                            value ( typename AdaptorProperties < T > :: AdaptedType ( object ).copy() ){ // NOLINT(cppcoreguidelines-pro-type-member-init)

                    }

                    __CDS_OptimalInline ~JsonElement() noexcept = default;

                    template < typename T, typename U = T, EnableIf < Adaptable < U > :: value > = 0 >
                    __CDS_OptimalInline auto to () const noexcept (false) -> typename AdaptorProperties < U > :: AdaptedType const & {
                        if ( AdaptorProperties < T > :: adaptEnum != this->type ) {
                            throw TypeException ( String :: f ( "Type Cast Exception. Cannot Convert '%s' to '%s'", toString ( type ), Type < T > :: name() ) );
                        }

                        return * reinterpret_cast < typename AdaptorProperties < T > :: AdaptedType * > ( this->value.get() );
                    };

                    template < typename T, typename U = T, EnableIf < PrimitiveAdaptable < U > :: value > = 0 >
                    __CDS_OptimalInline auto to () const noexcept (false) -> T {
                        if ( AdaptorProperties < T > :: adaptEnum != this->type ) {
                            if ( implicitAdaptPossible ( AdaptorProperties < T > :: adaptEnum, this->type ) ) {
                                return this->implicitAdapt < T > ();
                            }

                            throw TypeException ( String :: f ( "Type Cast Exception. Cannot Convert '%s' to '%s'", toString ( type ), Type < T > :: name() ) );
                        }

                        return static_cast < T > ( * reinterpret_cast < typename AdaptorProperties < T > :: AdaptedType * > ( this->value.get() ) );
                    };

                    template < typename MapImplementationType = hidden :: impl :: JsonBaseMap >
                    __CDS_OptimalInline auto toJson () const noexcept (false) -> JsonObject < MapImplementationType > const & {
                        if ( this->type != ElementType :: Object ) {
                            throw TypeException ( String :: f ( "Type Cast Exception. Cannot Convert '%s' to '%s'", toString(type), "Object" ) );
                        }

                        return * reinterpret_cast < JsonObject < MapImplementationType > const * > ( this->value.get() );
                    }
                };
            }
        }

        using JsonElement = hidden :: impl :: JsonElement;

        template < typename MapImplementationType > __CDS_Requires (
                DerivedFrom < MapImplementationType, hidden :: impl :: JsonCompatibleMap >
        ) class JsonObject : private MapImplementationType {

            static_assert (
                    isDerivedFrom < MapImplementationType, hidden :: impl :: JsonCompatibleMap > :: type :: value,
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

            template < typename T, typename U = T, EnableIf < hidden :: impl :: PrimitiveAdaptable < U > :: value > = 0 >
            __CDS_OptimalInline auto put ( String label, T object ) noexcept -> JsonObject & {
                if ( ! this->orderedKeys.contains ( label ) ) {
                    this->orderedKeys.add ( label );
                }

                this-> MapImplementationType :: insert ( { std :: move ( label ), { object } } );
                return * this;
            }

            template < typename T, typename U = T, EnableIf < hidden :: impl :: Adaptable < U > :: value > = 0 >
            __CDS_OptimalInline auto put ( String label, T const & object ) noexcept -> JsonObject & {
                if ( ! this->orderedKeys.contains ( label ) ) {
                    this->orderedKeys.add ( label );
                }

                this-> MapImplementationType :: insert ( { std :: move ( label ), { object } } );
                return * this;
            }

            template < typename T, typename U = T, EnableIf < hidden :: impl :: Adaptable < U > :: value > = 0 >
            __CDS_NoDiscard __CDS_OptimalInline auto get ( String const & label ) const noexcept (false) -> typename hidden :: impl :: AdaptorProperties < T > :: AdaptedType const & {
                auto value = MapImplementationType :: find ( label );
                if ( ! value.hasValue() ) {
                    throw KeyException ( label );
                }

                return value.value() -> template to < T > ();
            }

            template < typename T, typename U = T, EnableIf < hidden :: impl :: PrimitiveAdaptable < U > :: value > = 0 >
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
        };

        namespace hidden { // NOLINT(modernize-concat-nested-namespaces)
            namespace impl {
                template < >
                struct AdaptorProperties < JsonObject < JsonBaseMap > > {
                    constexpr static bool           adaptable   = true;
                    constexpr static ElementType    adaptEnum   = ElementType :: Object;
                    using                           AdaptedType = JsonObject < JsonBaseMap >;
                };
            }
        }

    }
}

#endif // __CDS_JSON_HPP__
