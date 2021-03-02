//
// Created by loghin on 15.01.2021.
//

#ifndef CDS_COLLECTION_HPP
#define CDS_COLLECTION_HPP

#include <functional>

#ifdef COLLECTION_FORCE_EXPLICIT_CONVERSIONS
#ifndef COLLECTION_EXPLICIT_CONVERSION
#define COLLECTION_EXPLICIT_CONVERSION explicit
#endif
#else
#ifndef COLLECTION_EXPLICIT_CONVERSION
#define COLLECTION_EXPLICIT_CONVERSION
#endif
#endif

#include <std-types.h>

#if defined(__cpp_concepts)
template <typename T>
concept Comparable = requires ( const T & a, const T & b ) {
    std::is_convertible < decltype(a > b), bool >::value &&
    std::is_convertible < decltype(a < b), bool >::value;
};
#endif

#include <type_traits>
#include <CDS/Object>

#if defined(__cpp_concepts)
template <class T>
concept Callable = std::is_invocable<T>::value;

template <typename T>
concept UniqueIdentifiableByObject = requires {
    std::is_base_of < Object, T >::value;
};

template <typename T>
concept UniqueIdentifiableByOperator = requires ( T const & a, T const & b ) {
    a == b;
};

template <typename T>
concept UniqueIdentifiable = requires ( T const & a, T const & b ) {
    UniqueIdentifiableByObject<T> || UniqueIdentifiableByOperator<T>;
};
#endif

template <class T>
class Comparator {
public:
    virtual auto operator () (const T &, const T &) const noexcept -> bool = 0;
};

template <class T>
class Collection : public Object {
public:

protected:
    class CollectionOutOfBounds : public std::exception {
    public:
        virtual auto what() const noexcept -> StringLiteral override {
            return "Accessed Collection Iterator/Index Out of Range";
        }
    };

    Collection() noexcept = default;

public:

    class Iterator {
    protected:
        Iterator() noexcept = default;
        Iterator(const Iterator &) noexcept = default;
        Iterator(Iterator &&) noexcept = default;
    public:
        virtual ~Iterator() noexcept = default;

#if __cpp_constexpr >= 201907
        constexpr inline virtual auto next (  ) noexcept -> Iterator & = 0;
        constexpr inline virtual auto equals ( const Iterator & ) const noexcept -> bool = 0;
        constexpr inline virtual auto value() const noexcept -> T& = 0;

        virtual constexpr inline auto operator ++ () noexcept -> Iterator & { this->next(); return * this; }
#else
        virtual auto next (  ) noexcept -> Iterator & = 0;
        virtual auto equals ( const Iterator & ) const noexcept -> bool = 0;
        virtual auto value() const noexcept -> T& = 0;

        virtual auto operator ++ () noexcept -> Iterator & { this->next(); return * this; }
#endif
        constexpr inline auto operator == ( const Iterator & o ) const noexcept -> bool { return this->equals(o ); }
        constexpr inline auto operator != ( const Iterator & o ) const noexcept -> bool { return ! this->equals(o ); }
        constexpr inline auto operator * () const noexcept -> T& { return this->value(); }
    };

    class ConstIterator {
    protected:
        ConstIterator() noexcept = default;
        ConstIterator(const ConstIterator &) noexcept = default;
        ConstIterator(ConstIterator &&) noexcept = default;
    public:
        virtual ~ConstIterator() noexcept = default;

#if __cpp_constexpr >= 201907
        constexpr inline virtual auto next (  ) noexcept -> ConstIterator & = 0;
        constexpr inline virtual auto equals ( const ConstIterator & ) const noexcept -> bool = 0;
        constexpr inline virtual auto value () const noexcept -> const T& = 0;

        virtual constexpr inline auto operator ++ () noexcept -> ConstIterator & { this->next(); return * this; }
#else
        virtual auto next (  ) noexcept -> ConstIterator & = 0;
        virtual auto equals ( const ConstIterator & ) const noexcept -> bool = 0;
        virtual auto value () const noexcept -> const T& = 0;

        virtual auto operator ++ () noexcept -> ConstIterator & { this->next(); return * this; }
#endif
        constexpr inline auto operator == ( const ConstIterator & o ) const noexcept -> bool { return this->equals(o ); }
        constexpr inline auto operator != ( const ConstIterator & o ) const noexcept -> bool { return ! this->equals(o ); }
        constexpr inline auto operator * () const noexcept -> const T& { return this->value(); }
    };
protected:
    virtual auto beginPtr () noexcept -> Iterator * = 0;
    virtual auto endPtr () noexcept -> Iterator * = 0;
    virtual auto beginPtr () const noexcept -> ConstIterator * = 0;
    virtual auto endPtr () const noexcept -> ConstIterator * = 0;

    static inline auto beginPtr ( Collection < T > & o ) noexcept -> Iterator * { return o.beginPtr(); }
    static inline auto endPtr ( Collection < T > & o ) noexcept -> Iterator * { return o.endPtr(); }
    static inline auto beginPtr ( const Collection < T > & o ) noexcept -> ConstIterator * { return o.beginPtr(); }
    static inline auto endPtr ( const Collection < T > & o ) noexcept -> ConstIterator * { return o.endPtr(); }

//    virtual auto findPtr ( T & ) noexcept -> Iterator & = 0;
//    virtual auto findPtr ( const T & ) const noexcept -> ConstIterator & = 0;

public:
    virtual auto remove ( const T &, Size ) noexcept -> bool = 0;
    virtual auto inline removeAll ( const T & o ) noexcept -> bool { return this->remove( o, this->size() ); }
    virtual auto inline removeFirst ( const T & o ) noexcept -> bool { return this->remove( o, 1 ); }
    virtual auto removeLast ( const T & o ) noexcept -> bool = 0;

    virtual auto removeOf ( const Collection &, Size ) noexcept -> bool = 0;
    virtual auto inline removeFirstOf ( const Collection & o ) noexcept -> bool { return this->removeOf( o, 1 ); }
    virtual auto inline removeAllOf ( const Collection & o ) noexcept -> bool { return this->removeOf ( o, this->size() ); }
    virtual auto removeLastOf ( const Collection & ) noexcept -> bool = 0;

    virtual auto removeNotOf ( const Collection &, Size ) noexcept -> bool = 0;
    virtual auto inline removeFirstNotOf ( const Collection & o ) noexcept -> bool { return this->removeNotOf ( o, 1 ); }
    virtual auto inline removeAllNotOf ( const Collection & o ) noexcept -> bool  { return this->removeNotOf( o, this->size() ); }
    virtual auto removeLastNotOf ( const Collection & ) noexcept -> bool = 0;

    virtual auto removeOf ( const std::initializer_list<T> &, Size ) noexcept -> bool = 0;
    virtual auto inline removeFirstOf ( const std::initializer_list<T> & o ) noexcept -> bool { return this->removeOf( o, 1 ); }
    virtual auto inline removeAllOf ( const std::initializer_list<T> & o ) noexcept -> bool { return this->removeOf ( o, this->size() ); }
    virtual auto removeLastOf ( const std::initializer_list<T> & ) noexcept -> bool = 0;

    virtual auto removeNotOf ( const std::initializer_list<T> &, Size ) noexcept -> bool = 0;
    virtual auto inline removeFirstNotOf ( const std::initializer_list<T> & o ) noexcept -> bool { return this->removeNotOf ( o, 1 ); }
    virtual auto inline removeAllNotOf ( const std::initializer_list<T> & o ) noexcept -> bool  { return this->removeNotOf( o, this->size() ); }
    virtual auto removeLastNotOf ( const std::initializer_list<T> & ) noexcept -> bool = 0;

    virtual auto replace ( const T &, const T &, Size ) noexcept -> void = 0;
    virtual auto inline replaceFirst ( const T & what, const T & with ) noexcept -> void { return this->replace(what, with, 1); }
    virtual auto inline replaceAll ( const T & what, const T & with ) noexcept -> void { return this->replace(what, with, this->size()); }
    virtual auto replaceLast ( const T &, const T & ) noexcept -> void = 0;

    virtual auto replaceOf ( const Collection &, const T &, Size ) noexcept -> void = 0;
    virtual auto inline replaceFirstOf ( const Collection & what, const T & with ) noexcept -> void { return this->replaceOf(what, with, 1); }
    virtual auto inline replaceAllOf ( const Collection & what, const T & with ) noexcept -> void { return this->replaceOf(what, with, this->size()); }
    virtual auto replaceLastOf ( const Collection &, const T & ) noexcept -> void = 0;

    virtual auto replaceNotOf ( const Collection &, const T &, Size ) noexcept -> void = 0;
    virtual auto inline replaceFirstNotOf ( const Collection & what, const T & with ) noexcept -> void { return this->replaceNotOf(what, with, 1); }
    virtual auto inline replaceAllNotOf ( const Collection & what, const T & with ) noexcept -> void { return this->replaceNotOf(what, with, this->size()); }
    virtual auto replaceLastNotOf ( const Collection &, const T & ) noexcept -> void = 0;

    virtual auto replaceOf ( const std::initializer_list<T> &, const T &, Size ) noexcept -> void = 0;
    virtual auto inline replaceFirstOf ( const std::initializer_list<T> & what, const T & with ) noexcept -> void { return this->replaceOf(what, with, 1); }
    virtual auto inline replaceAllOf ( const std::initializer_list<T> & what, const T & with ) noexcept -> void { return this->replaceOf(what, with, this->size()); }
    virtual auto replaceLastOf ( const std::initializer_list<T> &, const T & ) noexcept -> void = 0;

    virtual auto replaceNotOf ( const std::initializer_list<T> &, const T &, Size ) noexcept -> void = 0;
    virtual auto inline replaceFirstNotOf ( const std::initializer_list<T> & what, const T & with ) noexcept -> void { return this->replaceNotOf(what, with, 1); }
    virtual auto inline replaceAllNotOf ( const std::initializer_list<T> & what, const T & with ) noexcept -> void { return this->replaceNotOf(what, with, this->size()); }
    virtual auto replaceLastNotOf ( const std::initializer_list<T> &, const T & ) noexcept -> void = 0;

    virtual auto back () noexcept (false) -> T & = 0;
    virtual auto back () const noexcept (false) -> const T & = 0;

#if __cpp_constexpr >= 201907
    constexpr virtual inline auto front () const noexcept (false) -> const T & = 0;
    constexpr virtual inline auto front () noexcept (false) -> T & = 0;

    [[nodiscard]] constexpr virtual inline auto empty () const noexcept -> bool = 0;
#else
    virtual inline auto front () const noexcept (false) -> const T & = 0;
    virtual inline auto front () noexcept (false) -> T & = 0;

    [[nodiscard]] virtual inline auto empty () const noexcept -> bool = 0;
#endif

    virtual auto clear () noexcept -> void = 0;

    [[nodiscard]] virtual auto size () const noexcept -> Size = 0;
    virtual auto makeUnique () noexcept -> void = 0;

    virtual auto contains ( const T & ) const noexcept -> bool = 0;

#define PARAM_DELIM() ,
#define NO_PARAM_DELIM()
#define FORCE_COMMA ,

#define GEN_FUNCTION_DECLARATIONS(_fName, _group, _retType, _paramName, _paramDelim, _otherParams, _preParams, _impl) \
    _preParams auto _fName ( dataTypes::Value ## _group <T> _paramName _paramDelim() _otherParams) const noexcept -> _retType  _impl  \
    _preParams auto _fName ( dataTypes::Reference ## _group <T> _paramName _paramDelim() _otherParams) noexcept -> _retType _impl  \
    _preParams auto _fName ( dataTypes::ConstReference ## _group <T> _paramName _paramDelim() _otherParams) const noexcept -> _retType  _impl  \
    _preParams auto _fName ( dataTypes::ThrowValue ## _group <T> _paramName _paramDelim() _otherParams) const noexcept (false) -> _retType  _impl  \
    _preParams auto _fName ( dataTypes::ThrowReference ## _group <T> _paramName  _paramDelim() _otherParams) noexcept (false) -> _retType _impl  \
    _preParams auto _fName ( dataTypes::ThrowConstReference ## _group <T> _paramName _paramDelim() _otherParams) const noexcept (false) -> _retType _impl \
    _preParams auto _fName ( auto _paramName _paramDelim() _otherParams ) noexcept -> _retType _impl                  \
    _preParams auto _fName ( auto _paramName _paramDelim() _otherParams ) const noexcept -> _retType _impl

#define GEN_FUNCTION_DECLARATIONS_6(_fName, _group, _retType, _paramName, _paramDelim, _otherParams, _preParams, _impl1, _impl2, _impl3, _impl4, _impl5, _impl6) \
    _preParams auto _fName ( dataTypes::Value ## _group <T> _paramName _paramDelim() _otherParams) const noexcept -> _retType  _impl1  \
    _preParams auto _fName ( dataTypes::Reference ## _group <T> _paramName _paramDelim() _otherParams) noexcept -> _retType _impl2  \
    _preParams auto _fName ( dataTypes::ConstReference ## _group <T> _paramName _paramDelim() _otherParams) const noexcept -> _retType  _impl3  \
    _preParams auto _fName ( dataTypes::ThrowValue ## _group <T> _paramName _paramDelim() _otherParams) const noexcept (false) -> _retType  _impl4  \
    _preParams auto _fName ( dataTypes::ThrowReference ## _group <T> _paramName  _paramDelim() _otherParams) noexcept (false) -> _retType _impl5  \
    _preParams auto _fName ( dataTypes::ThrowConstReference ## _group <T> _paramName _paramDelim() _otherParams) const noexcept (false) -> _retType  _impl6 \
    _preParams auto _fName ( auto _paramName _paramDelim() _otherParams ) noexcept -> _retType _impl2 \
    _preParams auto _fName ( auto _paramName _paramDelim() _otherParams ) const noexcept -> _retType _impl3

#if defined(__cpp_concepts)
    GEN_FUNCTION_DECLARATIONS(forEach, Action, void, , NO_PARAM_DELIM, , , ;)
    GEN_FUNCTION_DECLARATIONS(some, Predicate, bool, , PARAM_DELIM, Size, , ;)
    GEN_FUNCTION_DECLARATIONS(any, Predicate, bool, p, NO_PARAM_DELIM, , inline, { return this->some(p FORCE_COMMA 1); } )
    GEN_FUNCTION_DECLARATIONS_6(
            all, Predicate, bool, p, NO_PARAM_DELIM, , inline,
            { return ! this->any ([&p](T e) noexcept -> bool { return !p(e); }); },
            { return ! this->any ([&p](T & e) noexcept -> bool { return !p(e); }); },
            { return ! this->any ([&p](T const & e) noexcept -> bool { return !p(e); }); },
            { return ! this->any ([&p](T e) noexcept (false) -> bool { return !p(e); }); },
            { return ! this->any ([&p](T & e) noexcept (false) -> bool { return !p(e); }); },
            { return ! this->any ([&p](T const & e) noexcept (false) -> bool { return !p(e); }); }
    )
    GEN_FUNCTION_DECLARATIONS(count, Predicate, Size, , NO_PARAM_DELIM, , , ;)
#endif

#undef GEN_FUNCTION_DECLARATIONS
#undef GEN_FUNCTION_DECLARATIONS_6

    virtual inline auto operator == ( const Collection & o ) const noexcept -> bool {
        return this == & o;
    }

    virtual inline auto operator != ( const Collection & o ) const noexcept -> bool {
        return this != &o;
    }

    virtual COLLECTION_EXPLICIT_CONVERSION operator bool () const noexcept {
        return this->size() != 0;
    }

    virtual auto toString () const noexcept -> String = 0;

    inline operator String () const noexcept{
        return this->toString();
    }

    ~Collection() noexcept override = default;

    friend inline auto operator << ( std::ostream & o, const Collection & c ) noexcept -> std::ostream & {
         return ( o << c.toString() );
    }
};

#define _GEN_FUNCTION_IMPLEMENTATION(_fName, _group, _retType, _exceptSpec, _preExceptSpec, _paramName, _paramDelim, _otherParams, _impl)                                                                                              \
    template <class T> auto Collection<T>::_fName ( dataTypes:: _preExceptSpec ## Value ## _group <T> _paramName _paramDelim() _otherParams ) const _exceptSpec -> _retType _impl                \
    template <class T> auto Collection<T>::_fName ( dataTypes:: _preExceptSpec ## Reference ## _group <T> _paramName _paramDelim() _otherParams ) _exceptSpec -> _retType _impl                  \
    template <class T> auto Collection<T>::_fName ( dataTypes:: _preExceptSpec ## ConstReference ## _group <T> _paramName _paramDelim() _otherParams ) const _exceptSpec -> _retType _impl

#define _GEN_FUNCTION_GROUP(_fName, _group, _retType, _paramName, _paramDelim, _otherParams, _impl)                                \
    _GEN_FUNCTION_IMPLEMENTATION(_fName, _group, _retType, noexcept, ,_paramName, _paramDelim, _otherParams, _impl)                \
    _GEN_FUNCTION_IMPLEMENTATION(_fName, _group, _retType, noexcept(false), Throw, _paramName, _paramDelim, _otherParams, _impl)   \
    template <class T> auto Collection<T>::_fName ( auto _paramName _paramDelim() _otherParams ) noexcept -> _retType _impl        \
    template <class T> auto Collection<T>::_fName ( auto _paramName _paramDelim() _otherParams ) const noexcept -> _retType _impl

#if defined(__cpp_concepts)
_GEN_FUNCTION_GROUP(forEach, Action, void, a, NO_PARAM_DELIM, , {
    auto begin = this->beginPtr();
    auto end = this->endPtr();

    for ( auto it = begin; ! it->equals( * end ); it->next() )
        a ( it->value() );

    delete begin;
    delete end;
})

_GEN_FUNCTION_GROUP(some, Predicate, bool, p, PARAM_DELIM, Size count, {
    Size trueCount = 0;

    auto begin = this->beginPtr();
    auto end = this->endPtr();

    for ( auto it = begin; ! it->equals( * end ) && trueCount < count; it->next() )
        if ( p ( it->value() ) )
            trueCount ++;

    delete begin;
    delete end;

    return count == trueCount;
})

_GEN_FUNCTION_GROUP(count, Predicate, Size, p, NO_PARAM_DELIM, , {
    Size trueCount = 0;

    auto pBegin = this->beginPtr();
    auto pEnd = this->endPtr();

    for ( auto it = pBegin; ! it->equals( * pEnd ); it->next() )
        if ( p ( it->value() ) )
            trueCount ++;

    delete pBegin;
    delete pEnd;

    return trueCount;
})
#endif

#undef _GEN_FUNCTION_GROUP
#undef _GEN_FUNCTION_IMPLEMENTATION
#undef PARAM_DELIM
#undef NO_PARAM_DELIM
#undef FORCE_COMMA


#endif //CDS_COLLECTION_HPP
