//
// Created by loghin on 11.10.2021.
//

#ifndef CDS_UNION_HPP
#define CDS_UNION_HPP

#include <CDS/Object>
#include <CDS/Warnings>

__CDS_WarningSuppression_UnsafeDeleteVoidPtr_SuppressEnable

template < typename FirstType, typename ... RemainingTypes >
class Union;

namespace Utility { // NOLINT(modernize-concat-nested-namespaces)
    namespace Detail { // NOLINT(modernize-concat-nested-namespaces)
        namespace UnionImpl { // NOLINT(modernize-concat-nested-namespaces)

            using NoneType = void;

            template < sint32 pos, typename T, typename ... Rest >
            struct IndexOfTypeInPackImpl {
                constexpr static auto index () noexcept -> sint32 {
                    return -1;
                }
            };

            template < sint32 pos, typename T, typename Head, typename ... Rest >
            struct IndexOfTypeInPackImpl < pos, T, Head, Rest ... > {

                template < typename A = T, typename B = Head, typename std :: enable_if < std :: is_same < A, B > :: value, int > :: type = 0 >
                constexpr static auto index () noexcept -> sint32 {
                    return pos;
                }

                template < typename A = T, typename B = Head, typename std :: enable_if < ! std :: is_same < A, B > :: value, int > :: type = 0 >
                constexpr static auto index () noexcept -> sint32 {
                    return IndexOfTypeInPackImpl < pos + 1, T, Rest ...>::index();
                }
            };

            template < typename T, typename Head, typename ... Rest >
            using IndexOfTypeInPack = IndexOfTypeInPackImpl < 0, T, Head, Rest ... >;

            template < sint32 current, sint32 index, typename ... Rest >
            struct TypeAtIndexInPackImpl {
                using type = NoneType;
            };

            template < sint32 current, sint32 index, typename Head, typename ... Rest >
            struct TypeAtIndexInPackImpl < current, index, Head, Rest ... > {
                using type = typename std :: conditional <
                        current == index,
                        Head,
                        typename TypeAtIndexInPackImpl < current + 1, index, Rest ... > :: type
                > :: type;
            };

            template < sint32 index, typename Head, typename ... Rest >
            using TypeAtIndexInPack = TypeAtIndexInPackImpl < 0, index, Head, Rest ... >;

            template < typename Type, typename ... List >
            struct PackContains : std :: false_type {};

            template < typename Type, typename Head, typename ... Rest >
            struct PackContains < Type, Head, Rest ... > :
                    std :: conditional <
                        std :: is_same < Type, Head > :: value,
                        std :: true_type,
                        PackContains < Type, Rest ... >
                    > :: type {};



            template < typename Type, typename ... List >
            struct PackContainsThenTypeOrNone {
                using type = NoneType;
            };

            template < typename Type, typename Head, typename ... Rest >
            struct PackContainsThenTypeOrNone < Type, Head, Rest ... > {
                using type = typename std::conditional <
                        std::is_same<Type, Head>::value,
                        Type,
                        typename PackContainsThenTypeOrNone < Type, Rest ... > :: type
                    >::type;
            };

            template < typename T, typename FirstType, typename ... RemainingTypes >
            auto get ( Union < FirstType, RemainingTypes ... > & ) noexcept ->
                    typename PackContainsThenTypeOrNone < T, FirstType, RemainingTypes ... > :: type &;

        }
    }
}


template < typename FirstType, typename ... RemainingTypes >
class Union : public Object { //: public Utility :: Detail :: UnionImpl :: UnionRecurrentBase < -1, 0, FirstType, RemainingTypes ... > {
private:
    void * pInstance {nullptr};
    Index _activeTypeIndex { -1 };

    __CDS_cpplang_ConstexprDestructor static auto typesAsString () noexcept -> String {
        if ( sizeof...(RemainingTypes) > 36 )
            return "Too Many Types in Union to deduce";

#define TYPES_AS_STR_CASE(_i) if ( i == _i ) types += String(Utility :: TypeParseTraits < typename Utility :: Detail :: UnionImpl :: TypeAtIndexInPack < _i, FirstType, RemainingTypes ... > :: type > :: name ) + ", ";

#define TYPES_AS_STR_CASE2(_i) \
    else TYPES_AS_STR_CASE((_i))     \
    else TYPES_AS_STR_CASE((_i) + 1)

#define TYPES_AS_STR_CASE4(_i) \
    TYPES_AS_STR_CASE2((_i))     \
    TYPES_AS_STR_CASE2((_i) + 2)

        String types = "";
        for ( sint32 i = 0; i < sizeof...(RemainingTypes) + 1; ++ i )
            TYPES_AS_STR_CASE(0)
            TYPES_AS_STR_CASE4(1)
            TYPES_AS_STR_CASE4(5)
            TYPES_AS_STR_CASE4(9)
            TYPES_AS_STR_CASE4(13)
            TYPES_AS_STR_CASE4(17)
            TYPES_AS_STR_CASE4(21)
            TYPES_AS_STR_CASE4(25)
            TYPES_AS_STR_CASE4(29)
            TYPES_AS_STR_CASE4(33)

#undef TYPES_AS_STR_CASE
#undef TYPES_AS_STR_CASE2
#undef TYPES_AS_STR_CASE4

        return types.removeSuffix(", ");
    }

public:

    Union () noexcept = default;

    __CDS_MaybeUnused inline Union ( Union && value ) noexcept :
            pInstance(std::exchange(value.pInstance, nullptr)),
            _activeTypeIndex(std::exchange(value._activeTypeIndex, -1)) {

    }

    template < typename T, typename std :: enable_if < Utility :: Detail :: UnionImpl :: PackContains < T, FirstType, RemainingTypes ... > :: value && Type < T > :: isFundamental, int > :: type = 0 >
    inline Union ( T value ) noexcept : // NOLINT(google-explicit-constructor)
            pInstance ( new T (value) ),
            _activeTypeIndex ( Utility :: Detail :: UnionImpl :: IndexOfTypeInPack < T, FirstType, RemainingTypes ... > :: index() ) {

    }

    template < typename T, typename std :: enable_if < Utility :: Detail :: UnionImpl :: PackContains < T, FirstType, RemainingTypes ... > :: value && ! Type < T > :: isFundamental && Type < T > :: copyConstructible, int > :: type = 0 >
    inline Union ( T const & value ) noexcept :  // NOLINT(google-explicit-constructor)
            pInstance ( new T (value) ),
            _activeTypeIndex ( Utility :: Detail :: UnionImpl :: IndexOfTypeInPack < T, FirstType, RemainingTypes ... > :: index() ) {

    }

    template < typename T, typename std :: enable_if < Utility :: Detail :: UnionImpl :: PackContains < T, FirstType, RemainingTypes ... > :: value && ! Type < T > :: isFundamental && ! Type < T > :: copyConstructible && Type < T > :: defaultConstructible && Type < T > :: copyAssignable, int > :: type = 0 >
    inline Union ( T const & value ) noexcept :  // NOLINT(google-explicit-constructor)
            pInstance ( new T ),
            _activeTypeIndex ( Utility :: Detail :: UnionImpl :: IndexOfTypeInPack < T, FirstType, RemainingTypes ... > :: index() ) {

        * reinterpret_cast < T * > ( this->pInstance ) = value;
    }

    template < typename T, typename std :: enable_if < Utility :: Detail :: UnionImpl :: PackContains < T, FirstType, RemainingTypes ... > :: value && ! Type < T > :: isFundamental && Type < T > :: moveConstructible, int > :: type = 0 >
    __CDS_MaybeUnused inline Union ( T && value ) noexcept :  // NOLINT(google-explicit-constructor, bugprone-forwarding-reference-overload)
            pInstance ( new T ( std :: forward < T > ( value ) ) ),
            _activeTypeIndex ( Utility :: Detail :: UnionImpl :: IndexOfTypeInPack < T, FirstType, RemainingTypes ... > :: index() ) {

    }

    template < typename T, typename std :: enable_if < Utility :: Detail :: UnionImpl :: PackContains < T, FirstType, RemainingTypes ... > :: value && ! Type < T > :: isFundamental && ! Type < T > :: moveConstructible && Type < T > :: defaultConstructible && Type < T > :: moveAssignable, int > :: type = 0 >
    __CDS_MaybeUnused inline Union ( T && value ) noexcept :  // NOLINT(google-explicit-constructor, bugprone-forwarding-reference-overload)
            pInstance ( new T ),
            _activeTypeIndex ( Utility :: Detail :: UnionImpl :: IndexOfTypeInPack < T, FirstType, RemainingTypes ... > :: index() ) {

        * reinterpret_cast < T * > ( this->pInstance ) = std :: forward < T > ( value );
    }


#define UNION_DELETE(_i) \
        if ( this->_activeTypeIndex == _i ) \
            delete reinterpret_cast < typename Utility :: Detail :: UnionImpl :: TypeAtIndexInPack < _i, FirstType, RemainingTypes ... > :: type * > ( this->pInstance );

#define UNION_DELETE2(_i) \
        else UNION_DELETE(_i) \
        else UNION_DELETE((_i) + 1)

#define UNION_DELETE4(_i) \
        UNION_DELETE2(_i) \
        UNION_DELETE2((_i) + 2)

#define UNION_DELETE36 \
        UNION_DELETE(0)\
        UNION_DELETE4(1)\
        UNION_DELETE4(5)\
        UNION_DELETE4(9)\
        UNION_DELETE4(13)\
        UNION_DELETE4(17)\
        UNION_DELETE4(21)\
        UNION_DELETE4(25)\
        UNION_DELETE4(29)\
        UNION_DELETE4(33)


#if __CDS_cpplang_core_version >= __CDS_cpplang_core_version_17

    inline Union (Union const & value) noexcept (false) { // NOLINT(google-explicit-constructor)
        * this = value;
    }

    template < typename std :: enable_if < sizeof ... (RemainingTypes) <= 36, int > :: type = 0 >
    inline auto operator = ( Union const & value ) noexcept (false) -> Union & {
        if ( this == & value ) return * this;

        UNION_DELETE36

#define UNION_COPY(_i) \
    if ( this->_activeTypeIndex == _i ) { \
        using Type ## _i = typename Utility :: Detail :: UnionImpl :: TypeAtIndexInPack < _i, FirstType, RemainingTypes ... > :: type;\
        if constexpr ( Type < Type ## _i > :: copyConstructible ) {                                                                 \
            this->pInstance = new Type ## _i ( * reinterpret_cast < Type ## _i const * > ( value.pInstance ) );                          \
        } else if constexpr ( Type < Type ## _i > :: copyAssignable ) {                                                             \
            this->pInstance = new Type ## _i;                                                                                       \
            * reinterpret_cast < Type ## _i * > ( this->pInstance ) = * reinterpret_cast < Type ## _i const * > ( value.pInstance );\
        } else         \
            throw TypeException ( String::f("Type '%s' is not copyable", Utility :: TypeParseTraits < Type ## _i > :: name) ); \
    }

        UNION_COPY(0)
        else UNION_COPY(1)
        else UNION_COPY(2)
        else UNION_COPY(3)
        else UNION_COPY(4)
        else UNION_COPY(5)
        else UNION_COPY(6)
        else UNION_COPY(7)
        else UNION_COPY(8)
        else UNION_COPY(9)
        else UNION_COPY(10)
        else UNION_COPY(11)
        else UNION_COPY(12)
        else UNION_COPY(13)
        else UNION_COPY(14)
        else UNION_COPY(15)
        else UNION_COPY(16)
        else UNION_COPY(17)
        else UNION_COPY(18)
        else UNION_COPY(19)
        else UNION_COPY(20)
        else UNION_COPY(21)
        else UNION_COPY(22)
        else UNION_COPY(23)
        else UNION_COPY(24)
        else UNION_COPY(25)
        else UNION_COPY(26)
        else UNION_COPY(27)
        else UNION_COPY(28)
        else UNION_COPY(29)
        else UNION_COPY(30)
        else UNION_COPY(31)
        else UNION_COPY(32)
        else UNION_COPY(33)
        else UNION_COPY(34)
        else UNION_COPY(35)
        else UNION_COPY(36)

        return * this;

#undef UNION_COPY

    }

#else

    inline Union (Union const &) noexcept = delete;
    inline auto operator = (Union const &) noexcept -> Union & = delete;

#endif

    template < typename std :: enable_if < sizeof ... (RemainingTypes) <= 36, int > :: type = 0 >
    __CDS_MaybeUnused inline auto operator = ( Union && value ) noexcept -> Union & {
        if ( this == & value ) return * this;

        UNION_DELETE36

        this->pInstance = std :: exchange ( value.pInstance, nullptr );
        this->_activeTypeIndex = std :: exchange ( value._activeTypeIndex, -1 );

        return * this;
    }

    template < typename T, typename std :: enable_if < Utility :: Detail :: UnionImpl :: PackContains < T, FirstType, RemainingTypes ... > :: value && Type < T > :: isFundamental && sizeof ... (RemainingTypes) <= 36, int > :: type = 0 >
    inline auto operator = ( T value ) noexcept -> Union & {

        UNION_DELETE36

        this->pInstance = new T (value);
        this->_activeTypeIndex = Utility :: Detail :: UnionImpl :: IndexOfTypeInPack < T, FirstType, RemainingTypes ... > :: index();

        return * this;
    }

    template < typename T, typename std :: enable_if < Utility :: Detail :: UnionImpl :: PackContains < T, FirstType, RemainingTypes ... > :: value && ! Type < T > :: isFundamental && Type < T > :: copyConstructible, int > :: type = 0 >
    inline auto operator = ( T const & value ) noexcept -> Union & {

        UNION_DELETE36

        this->pInstance = new T (value);
        this->_activeTypeIndex = Utility :: Detail :: UnionImpl :: IndexOfTypeInPack < T, FirstType, RemainingTypes ... > :: index();

        return * this;
    }

    template < typename T, typename std :: enable_if < Utility :: Detail :: UnionImpl :: PackContains < T, FirstType, RemainingTypes ... > :: value && ! Type < T > :: isFundamental && ! Type < T > :: copyConstructible && Type < T > :: defaultConstructible && Type < T > :: copyAssignable, int > :: type = 0 >
    inline auto operator = ( T const & value ) noexcept -> Union & {

        UNION_DELETE36

        this->pInstance = new T;
        this->_activeTypeIndex = Utility :: Detail :: UnionImpl :: IndexOfTypeInPack < T, FirstType, RemainingTypes ... > :: index();
        * reinterpret_cast < T * > ( this->pInstance ) = value;

        return * this;
    }

    template < typename T, typename std :: enable_if < Utility :: Detail :: UnionImpl :: PackContains < T, FirstType, RemainingTypes ... > :: value && ! Type < T > :: isFundamental && Type < T > :: moveConstructible, int > :: type = 0 >
    __CDS_MaybeUnused inline auto operator = ( T && value ) noexcept -> Union & {

        UNION_DELETE36

        this->pInstance = new T ( std :: forward < T > ( value ) );
        this->_activeTypeIndex = Utility :: Detail :: UnionImpl :: IndexOfTypeInPack < T, FirstType, RemainingTypes ... > :: index();

        return * this;
    }

    template < typename T, typename std :: enable_if < Utility :: Detail :: UnionImpl :: PackContains < T, FirstType, RemainingTypes ... > :: value && ! Type < T > :: isFundamental && ! Type < T > :: moveConstructible && Type < T > :: defaultConstructible && Type < T > :: moveAssignable, int > :: type = 0 >
    __CDS_MaybeUnused inline auto operator = ( T && value ) noexcept -> Union & {

        UNION_DELETE36

        this->pInstance = new T;
        this->_activeTypeIndex = Utility :: Detail :: UnionImpl :: IndexOfTypeInPack < T, FirstType, RemainingTypes ... > :: index();
        * reinterpret_cast < T * > ( this->pInstance ) = std :: forward < T > ( value );

        return * this;
    }

#undef UNION_DELETE
#undef UNION_DELETE2
#undef UNION_DELETE4
#undef UNION_DELETE36

    template < typename T, typename std :: enable_if < Utility :: Detail :: UnionImpl :: PackContains < T, FirstType, RemainingTypes ... > :: value, int > :: type = 0 >
    inline auto get () noexcept (false) -> T & {
        auto typeNames = Union :: typesAsString();
        constexpr auto typeIndex = Utility :: Detail :: UnionImpl :: IndexOfTypeInPack < T, FirstType, RemainingTypes ... > :: index();

        if ( this->_activeTypeIndex == -1 ) throw TypeException (
                "No Assigned Value to Union, no Active Type"
            );
//        if ( typeIndex == -1 ) throw TypeException (
//                String::f(
//                    "Type '%s' is not defined as part of this Union Type, with types : '%s'",
//                    Type < T > :: name(),
//                    typeNames.cStr()
//                )
//            );

        if ( this->_activeTypeIndex != typeIndex ) throw TypeException (
                String :: f (
                    "Type '%s' is the current type, cannot convert to '%s'",
                    typeNames.split(",")[this->_activeTypeIndex].trim().cStr(),
                    Type < T > :: name()
                )
            );

        return * reinterpret_cast < T * > ( this->pInstance );
    }

private:
    template < typename T, typename std :: enable_if < std :: is_same < T, void > :: value, int > :: type = 0 >
    constexpr static auto buildSafeDereferenceWrapper ( T * addr __CDS_MaybeUnused ) noexcept -> int  { return 0; }

    template < typename T, typename std :: enable_if < ! std :: is_same < T, void > :: value, int > :: type = 0 >
    constexpr static auto buildSafeDereferenceWrapper ( T * addr ) noexcept -> T & { return * addr; }

public:

#define TYPE_AS_STRING(_i, _typeName, _valueAsString) \
    if ( this->_activeTypeIndex == _i ) { \
        _typeName = Utility::TypeParseTraits < typename Utility::Detail::UnionImpl::TypeAtIndexInPack < _i, FirstType, RemainingTypes ... > :: type > :: name; \
        _valueAsString = String (                     \
            buildSafeDereferenceWrapper < typename Utility::Detail::UnionImpl::TypeAtIndexInPack < _i, FirstType, RemainingTypes ... > :: type > (             \
                reinterpret_cast < typename Utility::Detail::UnionImpl::TypeAtIndexInPack < _i, FirstType, RemainingTypes ... > :: type * > ( this->pInstance )\
            ) \
        );                                                  \
    }

#define TYPE_AS_STRING2(_i, _typename, _valueAsString) \
    else TYPE_AS_STRING(_i, _typename, _valueAsString) \
    else TYPE_AS_STRING((_i) + 1, _typename, _valueAsString)

#define TYPE_AS_STRING4(_i, _typename, _valueAsString) \
    TYPE_AS_STRING2(_i, _typename, _valueAsString)  \
    TYPE_AS_STRING2((_i) + 2, _typename, _valueAsString)

#define TYPE_AS_STRING36(_typename, _valueAsString) \
    TYPE_AS_STRING(0, _typename, _valueAsString)               \
    TYPE_AS_STRING4(1, _typename, _valueAsString)\
    TYPE_AS_STRING4(5, _typename, _valueAsString)\
    TYPE_AS_STRING4(9, _typename, _valueAsString)\
    TYPE_AS_STRING4(13, _typename, _valueAsString)\
    TYPE_AS_STRING4(17, _typename, _valueAsString)\
    TYPE_AS_STRING4(21, _typename, _valueAsString)\
    TYPE_AS_STRING4(25, _typename, _valueAsString)\
    TYPE_AS_STRING4(29, _typename, _valueAsString)\
    TYPE_AS_STRING4(33, _typename, _valueAsString)

    __CDS_NoDiscard inline auto toString () const noexcept -> String override {
        if ( sizeof ... (RemainingTypes) >= 36 ) return "Union { <unable to determine type data due to hardcoded limit> };";

        StringLiteral activeTypeName = nullptr; String valAsStr;
        TYPE_AS_STRING36(activeTypeName, valAsStr)

        String allTypes = Union::typesAsString();

        return String::f(
                "Union { types = [ %s ], activeType = %s, value = %s }",
                allTypes.cStr(),
                activeTypeName,
                valAsStr.cStr()
        );
    }

#undef TYPE_AS_STRING
#undef TYPE_AS_STRING2
#undef TYPE_AS_STRING4
#undef TYPE_AS_STRING36
};

__CDS_WarningSuppression_UnsafeDeleteVoidPtr_SuppressDisable

namespace Utility {
    template< typename FirstType, typename ... RemainingTypes >
    struct TypeParseTraits < Union < FirstType, RemainingTypes ... > > {
        constexpr static StringLiteral name = "Union";
    };
}



#endif //CDS_UNION_HPP
