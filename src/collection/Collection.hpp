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

#include "../std-types.h"

#if defined(__cpp_concepts) && !defined(_MSC_VER)
template <typename T>
concept Comparable = requires ( const T & a, const T & b ) {
//    std::is_convertible < decltype(a > b), bool >::value &&
    std::is_convertible < decltype(a < b), bool >::value;
};
#endif

#include <type_traits>
#include <CDS/Object>

#include <CDS/Traits>
#include <CDS/Concepts>

template <class T>
class Comparator {
public:
    virtual auto operator () (const T &, const T &) const noexcept -> bool = 0;
};

template <typename T>
class View;

template < typename C >
class Sequence;

template <class T>
class Collection : public Object {
public:
    using ElementType = T;

protected:
    class CollectionOutOfBounds : public std::exception {
    public:
        [[nodiscard]] auto what() const noexcept -> StringLiteral override {
            return "Accessed Collection Iterator/Index Out of Range";
        }
    };

    Collection() noexcept = default;

public:

    class Iterator : public Object {
    protected:
        Iterator() noexcept = default;
        Iterator(const Iterator &) noexcept = default;
        Iterator(Iterator &&) noexcept = default;
    public:
        ~Iterator() noexcept override = default;

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

        [[nodiscard]] auto copy () const noexcept -> Iterator * override = 0;
    };

    class ConstIterator : public Object {
    protected:
        ConstIterator() noexcept = default;
        ConstIterator(const ConstIterator &) noexcept = default;
        ConstIterator(ConstIterator &&) noexcept = default;
    public:
        ~ConstIterator() noexcept override = default;

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

        [[nodiscard]] auto copy () const noexcept -> ConstIterator * override = 0;
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
    virtual auto front () const noexcept (false) -> const T & = 0;
    virtual auto front () noexcept (false) -> T & = 0;

    [[nodiscard]] virtual auto empty () const noexcept -> bool = 0;
#endif

    virtual auto add (ElementType const &) noexcept -> void = 0;
    virtual auto add (ElementType &&) noexcept -> void = 0;

    virtual auto clear () noexcept -> void = 0;

    [[nodiscard]] virtual auto size () const noexcept -> Size = 0;
    virtual auto makeUnique () noexcept -> void = 0;

    virtual auto contains ( const T & ) const noexcept -> bool = 0;

#define COMMA ,

    template < typename Action >
    auto forEach ( Action const & ) noexcept ( noexcept ( dataTypes::unsafeAddress < Action >()->operator()( * dataTypes::unsafeAddress < T > () ) ) ) -> void REQUIRES ( IsActionOver < Action COMMA T > );
    template < typename Action >
    auto forEach ( Action const & ) const noexcept ( noexcept ( dataTypes::unsafeAddress < Action >()->operator()( * dataTypes::unsafeAddress < T > () ) ) ) -> void REQUIRES ( IsActionOver < Action COMMA T > );

    template < typename Predicate >
    auto some ( Predicate const &, Size ) noexcept ( noexcept ( dataTypes::unsafeAddress < Predicate >()->operator()( * dataTypes::unsafeAddress < T > () ) ) ) -> bool REQUIRES( IsPredicateOver < Predicate COMMA T > );
    template < typename Predicate >
    auto some ( Predicate const &, Size ) const noexcept ( noexcept ( dataTypes::unsafeAddress < Predicate >()->operator()( * dataTypes::unsafeAddress < T > () ) ) ) -> bool REQUIRES( IsPredicateOver < Predicate COMMA T > );

    template < typename Predicate >
    auto count ( Predicate const & ) noexcept ( noexcept ( dataTypes::unsafeAddress < Predicate >()->operator()( * dataTypes::unsafeAddress < T > () ) ) ) -> Size REQUIRES( IsPredicateOver < Predicate COMMA T > );

    template < typename Predicate >
    auto count ( Predicate const & ) const noexcept ( noexcept ( dataTypes::unsafeAddress < Predicate >()->operator()( * dataTypes::unsafeAddress < T > () ) ) ) -> Size REQUIRES( IsPredicateOver < Predicate COMMA T > );

    template < typename Predicate >
    inline auto any ( Predicate const & p ) noexcept ( noexcept ( dataTypes::unsafeAddress < Predicate >()->operator()( * dataTypes::unsafeAddress < T > () ) ) ) -> bool REQUIRES( IsPredicateOver < Predicate COMMA T > ) { return this->some ( p, 1 ); }
    template < typename Predicate >
    inline auto any ( Predicate const & p ) const noexcept ( noexcept ( dataTypes::unsafeAddress < Predicate >()->operator()( * dataTypes::unsafeAddress < T > () ) ) ) -> bool REQUIRES( IsPredicateOver < Predicate COMMA T > ) { return this->some ( p, 1 ); }

    template < typename Predicate >
    inline auto all ( Predicate const & p ) noexcept ( noexcept ( dataTypes::unsafeAddress < Predicate >()->operator()( * dataTypes::unsafeAddress < T > () ) ) ) -> bool REQUIRES( IsPredicateOver < Predicate COMMA T > ) { return ! this->any ( [&p] (T & e) noexcept -> bool { return ! p(e); } ); }
    template < typename Predicate >
    inline auto all ( Predicate const & p ) const noexcept ( noexcept ( dataTypes::unsafeAddress < Predicate >()->operator()( * dataTypes::unsafeAddress < T > () ) ) ) -> bool REQUIRES( IsPredicateOver < Predicate COMMA T > ) { return ! this->any ( [&p] (T const & e) noexcept -> bool { return ! p(e); } ); }

#undef COMMA

    virtual COLLECTION_EXPLICIT_CONVERSION operator bool () const noexcept { // NOLINT(google-explicit-constructor)
        return this->size() != 0;
    }

    [[nodiscard]] auto toString () const noexcept -> String override = 0;

    ~Collection() noexcept override = default;

    friend inline auto operator << ( std::ostream & o, const Collection & c ) noexcept -> std::ostream & {
         return ( o << c.toString() );
    }
};

#define COMMA ,

template < typename T >
template < typename Action >
auto Collection<T>::forEach ( Action const & a ) noexcept ( noexcept ( dataTypes::unsafeAddress < Action >()->operator()( * dataTypes::unsafeAddress < T > () ) ) ) -> void REQUIRES( IsActionOver < Action COMMA T > ) {
    auto begin = this->beginPtr();
    auto end = this->endPtr();

    for ( auto it = begin; ! it->equals( * end ); it->next() )
        a ( it->value() );

    delete begin;
    delete end;
}

template < typename T >
template < typename Action >
auto Collection<T>::forEach ( Action const & a ) const noexcept ( noexcept ( dataTypes::unsafeAddress < Action >()->operator()( * dataTypes::unsafeAddress < T > () ) ) ) -> void REQUIRES( IsActionOver < Action COMMA T > ) {
    auto begin = this->beginPtr();
    auto end = this->endPtr();

    for ( auto it = begin; ! it->equals( * end ); it->next() )
        a ( it->value() );

    delete begin;
    delete end;
}

template < typename T >
template < typename Predicate >
auto Collection<T>::some ( Predicate const & p, Size count ) noexcept ( noexcept ( dataTypes::unsafeAddress < Predicate >()->operator()( * dataTypes::unsafeAddress < T > () ) ) ) -> bool REQUIRES( IsPredicateOver < Predicate COMMA T > ) {
    Size trueCount = 0;

    auto begin = this->beginPtr();
    auto end = this->endPtr();

    for ( auto it = begin; ! it->equals( * end ) && trueCount < count; it->next() )
        if ( p ( it->value() ) )
            trueCount ++;

    delete begin;
    delete end;

    return count == trueCount;
}

template < typename T >
template < typename Predicate >
auto Collection<T>::some ( Predicate const & p, Size count ) const noexcept ( noexcept ( dataTypes::unsafeAddress < Predicate >()->operator()( * dataTypes::unsafeAddress < T > () ) ) ) -> bool REQUIRES( IsPredicateOver < Predicate COMMA T > ) {
    Size trueCount = 0;

    auto begin = this->beginPtr();
    auto end = this->endPtr();

    for ( auto it = begin; ! it->equals( * end ) && trueCount < count; it->next() )
        if ( p ( it->value() ) )
            trueCount ++;

    delete begin;
    delete end;

    return count == trueCount;
}

template < typename T >
template < typename Predicate >
auto Collection<T>::count ( Predicate const & p ) noexcept ( noexcept ( dataTypes::unsafeAddress < Predicate >()->operator()( * dataTypes::unsafeAddress < T > () ) ) ) -> Size REQUIRES( IsPredicateOver < Predicate COMMA T > ) {
    Size trueCount = 0;

    auto pBegin = this->beginPtr();
    auto pEnd = this->endPtr();

    for ( auto it = pBegin; ! it->equals( * pEnd ); it->next() )
        if ( p ( it->value() ) )
            trueCount ++;

    delete pBegin;
    delete pEnd;

    return trueCount;
}

template < typename T >
template < typename Predicate >
auto Collection<T>::count ( Predicate const & p ) const noexcept ( noexcept ( dataTypes::unsafeAddress < Predicate >()->operator()( * dataTypes::unsafeAddress < T > () ) ) ) -> Size REQUIRES( IsPredicateOver < Predicate COMMA T > ) {
    Size trueCount = 0;

    auto pBegin = this->beginPtr();
    auto pEnd = this->endPtr();

    for ( auto it = pBegin; ! it->equals( * pEnd ); it->next() )
        if ( p ( it->value() ) )
            trueCount ++;

    delete pBegin;
    delete pEnd;

    return trueCount;
}

#undef COMMA


#endif //CDS_COLLECTION_HPP
