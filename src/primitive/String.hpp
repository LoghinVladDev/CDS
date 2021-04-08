//
// Created by loghin on 22.01.2021.
//

#ifndef CDS_STRING_HPP
#define CDS_STRING_HPP

#include <CDS/String>
#include <ostream>
#include <string>

#include <CDS/Concepts>

#include "../collection/ordered/LinkedListPublic.hpp"

template < typename T >
//#if defined(__cpp_concepts)
//    requires Iterable < T >
//#endif
class View;

class String final {
public:
    typedef char ElementType;

    class StringNullAccess : public std::exception {
        [[nodiscard]] const char * what() const noexcept override {
            return "Null Access Exception : Requested Reference to Element at Index 0 for Empty String.";
        }
    };
private:
    CString _p {nullptr};
    Size _l    {0ull};
    Size _c    {0ull};

    void _alloc(Size) noexcept;

    class IteratorBase;
    class ConstIteratorBase;
public:
    class Iterator;
    class ConstIterator;
    class ReverseIterator;
    class ConstReverseIterator;

    String () noexcept = default;
    String (String const &) noexcept;
    //TODO : implement later
//    explicit String (String const &, Index, Size = UINT64_MAX) noexcept;
    String(StringLiteral) noexcept; // NOLINT(google-explicit-constructor)
//    explicit String(StringLiteral, Index, Size = UINT64_MAX) noexcept;
    String(std::string const &) noexcept; // NOLINT(google-explicit-constructor)
//    explicit String(std::string const &, Index, Size = UINT64_MAX) noexcept;
    String(Size, ElementType) noexcept;
    String(std::string::iterator const &, std::string::iterator const &) noexcept;
    String(IteratorBase const &, IteratorBase const &) noexcept;
    String(ConstIteratorBase const &, ConstIteratorBase const &) noexcept;
    String(std::initializer_list<ElementType> const &) noexcept;

    ~String() noexcept;

    [[nodiscard]] auto begin() noexcept -> Iterator;
    [[nodiscard]] auto end () noexcept -> Iterator;
    [[nodiscard]] auto begin() const noexcept -> ConstIterator;
    [[nodiscard]] auto end() const noexcept -> ConstIterator;
    [[nodiscard]] auto cbegin() const noexcept -> ConstIterator;
    [[nodiscard]] auto cend() const noexcept -> ConstIterator;

    [[nodiscard]] auto rbegin() noexcept -> ReverseIterator;
    [[nodiscard]] auto rend() noexcept -> ReverseIterator;
    [[nodiscard]] auto rbegin() const noexcept -> ConstReverseIterator;
    [[nodiscard]] auto rend() const noexcept -> ConstReverseIterator;
    [[nodiscard]] auto crbegin() const noexcept -> ConstReverseIterator;
    [[nodiscard]] auto crend() const noexcept -> ConstReverseIterator;

    [[nodiscard]] constexpr inline auto size() const noexcept -> Size { return this->_l; }
    [[nodiscard]] constexpr inline auto length() const noexcept -> Size { return this->_l; }
    [[nodiscard]] constexpr inline auto maxSize() const noexcept -> Size { return this->_c; }
    [[nodiscard]] constexpr inline auto capacity() const noexcept -> Size { return this->_c; }

    auto resize(Size) noexcept -> void; //{ this->_alloc( s ); }
    inline auto reserve(Size s) noexcept -> void { if ( s < this->_c ) return; this->resize( s ); }
    inline auto shrink(SignedSize s = -1) noexcept -> void { if ( s == -1 ) s = this->_l; if ( s > this->_c ) return; this->resize( s ); }

    auto clear() noexcept -> void;
    [[nodiscard]] constexpr inline auto empty() const noexcept -> bool { return this->_l == 0; }

    auto operator [] (Index) noexcept (false) -> ElementType &;
    [[nodiscard]] auto operator [] (Index) const noexcept -> ElementType;

    inline auto at (Index i) noexcept (false) -> ElementType & { return this->operator[](i); }
    [[nodiscard]] inline auto at (Index i) const noexcept -> ElementType { return this->operator[](i); }

    inline auto get (Index i) noexcept (false) -> ElementType & { return this->operator[](i); }
    [[nodiscard]] inline auto get (Index i) const noexcept -> ElementType { return this->operator[](i); }

    inline auto front () noexcept (false) -> ElementType & { return this->operator[](0); }
    inline auto back () noexcept (false) -> ElementType & { return this->operator[](this->_l - 1); }

    [[nodiscard]] constexpr inline auto front() const noexcept -> ElementType { return this->empty() ? '\0' : this->_p[0]; }
    [[nodiscard]] constexpr inline auto back() const noexcept -> ElementType { return this->empty() ? '\0' : this->_p[this->_l - 1]; }

    inline auto operator += (ElementType v) noexcept -> String & { return this->append( v ); }
    inline auto operator += (StringLiteral v) noexcept -> String & { return this->append( v ); }
    inline auto operator += (String const & v) noexcept -> String & { return this->append( v ); }
    inline auto operator += (std::string const & v) noexcept -> String & { return this->append( v ); }

    inline auto operator += (CDS_sint16 v) noexcept -> String & { return this->operator+=(std::to_string(v) ); }
    inline auto operator += (CDS_sint32 v) noexcept -> String & { return this->operator+=(std::to_string(v) ); }
    inline auto operator += (CDS_sint64 v) noexcept -> String & { return this->operator+=(std::to_string(v) ); }

    inline auto operator += (CDS_uint8 v) noexcept -> String & { return this->operator+=(std::to_string(v) ); }
    inline auto operator += (CDS_uint16 v) noexcept -> String & { return this->operator+=(std::to_string(v) ); }
    inline auto operator += (CDS_uint32 v) noexcept -> String & { return this->operator+=(std::to_string(v) ); }
    inline auto operator += (CDS_uint64 v) noexcept -> String & { return this->operator+=(std::to_string(v) ); }

    inline auto operator += (float v) noexcept -> String & { return this->operator+=( std::to_string(v) ); }
    inline auto operator += (double v) noexcept -> String & { return this->operator+=( std::to_string(v) ); }

    auto append (ElementType) noexcept -> String &;
    auto append (StringLiteral) noexcept -> String &;
    auto append (String const &) noexcept -> String &;
    inline auto append (std::string const & s) noexcept -> String & { return this->append(s.c_str()); }

    inline auto append (CDS_sint16 v) noexcept -> String & { return this->append(std::to_string(v) ); }
    inline auto append (CDS_sint32 v) noexcept -> String & { return this->append(std::to_string(v) ); }
    inline auto append (CDS_sint64 v) noexcept -> String & { return this->append(std::to_string(v) ); }

    inline auto append (CDS_uint8 v) noexcept -> String & { return this->append(std::to_string(v) ); }
    inline auto append (CDS_uint16 v) noexcept -> String & { return this->append(std::to_string(v) ); }
    inline auto append (CDS_uint32 v) noexcept -> String & { return this->append(std::to_string(v) ); }
    inline auto append (CDS_uint64 v) noexcept -> String & { return this->append(std::to_string(v) ); }

    inline auto append (float v) noexcept -> String & { return this->append( std::to_string(v) ); }
    inline auto append (double v) noexcept -> String & { return this->append( std::to_string(v) ); }

    inline auto prepend (ElementType e) noexcept -> String & { return this->prepend(String().append(e)); }
    inline auto prepend (StringLiteral cString) noexcept -> String & { return this->prepend(String(cString)); }
    inline auto prepend (String const & s) noexcept -> String & { return ( * this = s + * this ); }
    inline auto prepend (std::string const & s) noexcept -> String & { return this->prepend(s.c_str()); }

    inline auto prepend (CDS_sint16 v) noexcept -> String & { return this->prepend(std::to_string(v) ); }
    inline auto prepend (CDS_sint32 v) noexcept -> String & { return this->prepend(std::to_string(v) ); }
    inline auto prepend (CDS_sint64 v) noexcept -> String & { return this->prepend(std::to_string(v) ); }

    inline auto prepend (CDS_uint8 v) noexcept -> String & { return this->prepend(std::to_string(v) ); }
    inline auto prepend (CDS_uint16 v) noexcept -> String & { return this->prepend(std::to_string(v) ); }
    inline auto prepend (CDS_uint32 v) noexcept -> String & { return this->prepend(std::to_string(v) ); }
    inline auto prepend (CDS_uint64 v) noexcept -> String & { return this->prepend(std::to_string(v) ); }

    inline auto prepend (float v) noexcept -> String & { return this->prepend( std::to_string(v) ); }
    inline auto prepend (double v) noexcept -> String & { return this->prepend( std::to_string(v) ); }

    [[nodiscard]] inline auto toStdString () const noexcept -> std::string { return std::string(this->cStr()); }
    inline explicit operator std::string () const noexcept { return this->toStdString(); }

    [[nodiscard]] constexpr auto cStr () const noexcept -> StringLiteral { return this->_p == nullptr ? "" : this->_p; }
    inline explicit operator StringLiteral () const noexcept { return this->cStr(); }

    [[nodiscard]] constexpr auto data () noexcept -> CString  { return this->_p; }
    inline explicit operator CString () noexcept { return this->data(); }

    [[nodiscard]] auto find (ElementType) const noexcept -> LinkedList < Index >;
    [[nodiscard]] auto find (String const &) const noexcept -> LinkedList < Index >;
    [[nodiscard]] auto findOf (String const &) const noexcept -> LinkedList < Index >;
    [[nodiscard]] auto findNotOf (String const &) const noexcept -> LinkedList < Index >;

    [[nodiscard]] auto findFirst ( ElementType ) const noexcept -> Index;
    [[nodiscard]] auto findFirst ( String const & ) const noexcept -> Index;
    [[nodiscard]] auto findLast ( ElementType ) const noexcept -> Index;
    [[nodiscard]] auto findLast ( String const & ) const noexcept -> Index;
    [[nodiscard]] auto findFirstOf ( String const & ) const noexcept -> Index;
    [[nodiscard]] auto findFirstNotOf ( String const & ) const noexcept -> Index;
    [[nodiscard]] auto findLastOf ( String const & ) const noexcept -> Index;
    [[nodiscard]] auto findLastNotOf ( String const & ) const noexcept -> Index;

    [[nodiscard]] auto substr ( Index, Index = -1 ) const noexcept -> String;

    [[nodiscard]] auto operator == ( String const & o ) const noexcept -> bool;
    [[nodiscard]] constexpr inline auto operator == ( ElementType e ) const noexcept -> bool { return this->size() == 1 && this->_p[0] == e; }
    [[nodiscard]] auto operator == ( std::string const & ) const noexcept -> bool;
    [[nodiscard]] auto operator == ( StringLiteral ) const noexcept -> bool;

    [[nodiscard]] auto operator >= ( String const & ) const noexcept -> bool;
    [[nodiscard]] constexpr inline auto operator >= ( ElementType e ) const noexcept -> bool { return this->size() == 1 && this->_p[0] >= e; }
    [[nodiscard]] auto operator >= ( std::string const & ) const noexcept -> bool;
    [[nodiscard]] auto operator >= ( StringLiteral ) const noexcept -> bool;

    [[nodiscard]] auto operator <= ( String const & ) const noexcept -> bool;
    [[nodiscard]] constexpr inline auto operator <= ( ElementType e ) const noexcept -> bool { return this->size() == 1 && this->_p[0] <= e; }
    [[nodiscard]] auto operator <= ( std::string const & ) const noexcept -> bool;
    [[nodiscard]] auto operator <= ( StringLiteral ) const noexcept -> bool;

    [[nodiscard]] auto operator != ( String const & ) const noexcept -> bool;
    [[nodiscard]] constexpr inline auto operator != ( ElementType e ) const noexcept -> bool { return this->size() != 1 || this->_p[0] != e; }
    [[nodiscard]] auto operator != ( std::string const & ) const noexcept -> bool;
    [[nodiscard]] auto operator != ( StringLiteral ) const noexcept -> bool;

    [[nodiscard]] auto operator < ( String const & ) const noexcept -> bool;
    [[nodiscard]] constexpr inline auto operator < ( ElementType e ) const noexcept -> bool { return this->size() == 1 && this->_p[0] < e; }
    [[nodiscard]] auto operator < ( std::string const & ) const noexcept -> bool;
    [[nodiscard]] auto operator < ( StringLiteral ) const noexcept -> bool;

    [[nodiscard]] auto operator > ( String const & ) const noexcept -> bool;
    [[nodiscard]] constexpr inline auto operator > ( ElementType e ) const noexcept -> bool { return this->size() == 1 && this->_p[0] > e; }
    [[nodiscard]] auto operator > ( std::string const & ) const noexcept -> bool;
    [[nodiscard]] auto operator > ( StringLiteral ) const noexcept -> bool;

    [[nodiscard]] inline auto operator + ( String const & v ) const noexcept -> String { return String(*this).append(v); }
    [[nodiscard]] inline auto operator + ( ElementType v ) const noexcept -> String { return String(*this).append(v); }
    [[nodiscard]] inline auto operator + ( std::string const & v ) const noexcept -> String { return String(*this).append(v); }
    [[nodiscard]] inline auto operator + ( StringLiteral v ) const noexcept -> String { return String(*this).append(v); }

    [[nodiscard]] inline auto operator + (CDS_sint16 v) const noexcept -> String { return this->operator+(std::to_string(v) ); }
    [[nodiscard]] inline auto operator + (CDS_sint32 v) const noexcept -> String { return this->operator+(std::to_string(v) ); }
    [[nodiscard]] inline auto operator + (CDS_sint64 v) const noexcept -> String { return this->operator+(std::to_string(v) ); }
    [[nodiscard]] inline auto operator + (CDS_uint8 v) const noexcept -> String { return this->operator+(std::to_string(v) ); }
    [[nodiscard]] inline auto operator + (CDS_uint16 v) const noexcept -> String { return this->operator+(std::to_string(v) ); }
    [[nodiscard]] inline auto operator + (CDS_uint32 v) const noexcept -> String { return this->operator+(std::to_string(v) ); }
    [[nodiscard]] inline auto operator + (CDS_uint64 v) const noexcept -> String { return this->operator+(std::to_string(v) ); }
    [[nodiscard]] inline auto operator + (float v) const noexcept -> String { return this->operator+( std::to_string(v) ); }
    [[nodiscard]] inline auto operator + (double v) const noexcept -> String { return this->operator+( std::to_string(v) ); }

    [[nodiscard]] auto operator * (int) const noexcept -> String;

    auto ltrim ( ElementType = ' ' ) noexcept -> String &;
    auto ltrim ( String const & ) noexcept -> String &;
    auto rtrim ( ElementType = ' ' ) noexcept -> String &;
    auto rtrim ( String const & ) noexcept -> String &;
    auto inline trim ( ElementType e = ' ' ) noexcept -> String & { return this->ltrim(e).rtrim(); }
    auto inline trim ( String const & e ) noexcept -> String & { return this->ltrim(e).rtrim(); }

    auto rjust (Size, ElementType = ' ') noexcept -> String &;
    auto ljust (Size, ElementType = ' ') noexcept -> String &;

public:
    constexpr auto static inline isUpperChar(char c) noexcept -> bool { return c >= 'A' && c <= 'Z'; }
    constexpr auto static inline isLowerChar(char c) noexcept -> bool { return c >= 'a' && c <= 'z'; }
    constexpr auto static inline isDigit(char c) noexcept -> bool { return c >= '0' && c <= '9'; }
    constexpr auto static inline isLetter(char c) noexcept -> bool { return isUpperChar(c) || isLowerChar(c); }
    constexpr auto static inline isAlpha(char c) noexcept -> bool { return isLetter(c) || isDigit(c); }
    auto static inline isVowel(char c) noexcept -> bool { return String("aeiouAEIOU").contains(c); }
    auto static inline isConsonant(char c) noexcept -> bool { return isLetter(c) && ! isVowel(c); }
    constexpr auto static inline lowerChar(char c) noexcept -> char { return isUpperChar(c) ? c + 32 : c; }
    constexpr auto static inline upperChar(char c) noexcept -> char { return isLowerChar(c) ? c - 32 : c; }
    constexpr auto static inline toLowerChar(char & c) noexcept -> char & { c = lowerChar(c); return c; }
    constexpr auto static inline toUpperChar(char & c) noexcept -> char & { c = upperChar(c); return c; }

public:

#if !defined(_MSC_VER)
    auto inline toLower () noexcept -> String & { for ( Index i = 0; i < this->_l; i++ ) this->_p[i] = lowerChar(this->_p[i]); return * this; }
    auto inline toUpper () noexcept -> String & { for ( Index i = 0; i < this->_l; i++ ) this->_p[i] = upperChar(this->_p[i]); return * this; }
#else
    auto inline toLower () noexcept -> String & { for ( Size i = 0; i < this->_l; i++ ) this->_p[i] = lowerChar(this->_p[i]); return * this; }
    auto inline toUpper () noexcept -> String & { for ( Size i = 0; i < this->_l; i++ ) this->_p[i] = upperChar(this->_p[i]); return * this; }
#endif
    [[nodiscard]] auto inline lower () const noexcept -> String { return String(*this).toLower(); }
    [[nodiscard]] auto inline upper () const noexcept -> String { return String(*this).toUpper(); }

    String & operator = ( String const & ) noexcept;
    inline String & operator = ( std::string const & s ) noexcept { return this->operator=(String(s)); } // NOLINT(misc-unconventional-assign-operator)
    inline String & operator = ( ElementType e ) noexcept { return this->operator=(String().append(e)); } // NOLINT(misc-unconventional-assign-operator)
    inline String & operator = ( StringLiteral cString ) noexcept { return this->operator=(String(cString)); } // NOLINT(misc-unconventional-assign-operator)

    [[nodiscard]] auto split ( ElementType, Size = UINT32_MAX ) const noexcept -> LinkedList < String >;
    [[nodiscard]] auto split ( String const &, Size = UINT32_MAX ) const noexcept -> LinkedList < String >;

    constexpr static Index INVALID_POS = -1;

    [[nodiscard]] auto inline contains ( ElementType e ) const noexcept -> bool { return this->findFirst( e ) != INVALID_POS; }
    [[nodiscard]] auto inline contains ( String const & e ) const noexcept -> bool { return this->findFirst( e ) != INVALID_POS; }
    [[nodiscard]] auto inline contains ( StringLiteral e ) const noexcept -> bool { return this->findFirst( String(e) ) != INVALID_POS; }
    [[nodiscard]] auto inline contains ( std::string const & e ) const noexcept -> bool { return this->findFirst( String(e) ) != INVALID_POS; }

#ifndef NDEBUG
    [[nodiscard]] auto diag() const noexcept -> String;
#endif

    friend inline auto operator << ( std::ostream & out, String const & s ) noexcept -> std::ostream & {
        return ( out << (s._p == nullptr ? "null" : s._p) );
    }

    [[nodiscard]] auto hash () const noexcept -> Index {
        return this->length();
    }

    [[nodiscard]] auto copy () const noexcept -> String * {
        return new String( * this );
    }

    auto replace ( Index, Size, String const & ) noexcept -> String &;

    template < typename Action >
    auto forEach ( Action const & ) noexcept (false) -> String &;
    template < typename Action >
    auto forEach ( Action const & ) const noexcept (false) -> String const &;

    template < typename Predicate >
    auto count ( Predicate const & ) noexcept (false) -> Size;
    template < typename Predicate >
    auto count ( Predicate const & ) const noexcept (false) -> Size;

    template < typename Predicate >
    inline auto some ( Predicate const & p, Size s ) noexcept (false) -> bool { return s <= this->count ( p ); }
    template < typename Predicate >
    inline auto some ( Predicate const & p, Size s ) const noexcept(false) -> bool { return s <= this->count ( p ); }

    template < typename Predicate >
    auto any ( Predicate const & p ) noexcept (false) -> bool { return 1u <= this->count(p); }
    template < typename Predicate >
    auto any ( Predicate const & p ) const noexcept (false) -> bool { return 1u <= this->count(p); }

    template < typename Predicate >
    auto all ( Predicate const & p ) noexcept (false) -> bool { return this->size() == this->count(p); }
    template < typename Predicate >
    auto all ( Predicate const & p ) const noexcept (false) -> bool { return this->size() == this->count(p); }

    auto view () const noexcept -> View < String >;

    [[nodiscard]] auto reversed() const noexcept -> String;
};

class String::IteratorBase {
protected:
    mutable String * _s {nullptr};
    Index _pos          {0ull};

    explicit IteratorBase ( String &, Index ) noexcept;
    IteratorBase ( String::IteratorBase const & ) = default;

public:
    IteratorBase() noexcept = delete;
    virtual ~IteratorBase() noexcept = default;

    virtual auto next() -> IteratorBase & = 0;
    [[nodiscard]] constexpr inline auto equals ( const String::IteratorBase & i ) const noexcept -> bool { return this->_s == i._s && this->_pos == i._pos; }
    [[nodiscard]] inline auto value ( ) const noexcept (false) -> ElementType & { return this->_s->get(this->_pos); }

    virtual inline auto operator ++ () noexcept -> IteratorBase & { return this->next(); }
    constexpr inline auto operator == ( const IteratorBase & o ) const noexcept -> bool { return this->equals(o); }
    constexpr inline auto operator != ( const IteratorBase & o ) const noexcept -> bool { return ! this->equals(o); }
    constexpr inline auto operator - ( const IteratorBase & o ) const noexcept -> SignedSize { return this->_pos - o._pos; }
    inline auto operator * ( ) const noexcept -> ElementType & { return this->value(); }
};

class String::ConstIteratorBase {
protected:
    const String *   _s {nullptr};
    Index _pos          {0ull};

    explicit ConstIteratorBase ( String const &, Index ) noexcept;
    ConstIteratorBase ( String::ConstIteratorBase const & ) = default;

public:
    ConstIteratorBase() noexcept = delete;
    virtual ~ConstIteratorBase() noexcept = default;

    virtual auto next() -> ConstIteratorBase & = 0;
    [[nodiscard]] constexpr inline auto equals ( const String::ConstIteratorBase & i ) const noexcept -> bool { return this->_s == i._s && this->_pos == i._pos; }
    [[nodiscard]] inline auto value ( ) const noexcept -> ElementType { return this->_s->get(this->_pos); }

#if __cpp_constexpr >= 201907
    constexpr virtual inline auto operator ++ () noexcept -> ConstIteratorBase & { return this->next(); }
#else
    virtual inline auto operator ++ () noexcept -> ConstIteratorBase & { return this->next(); }
#endif
    constexpr inline auto operator == ( const ConstIteratorBase & o ) const noexcept -> bool { return this->equals(o); }
    constexpr inline auto operator != ( const ConstIteratorBase & o ) const noexcept -> bool { return ! this->equals(o); }
    constexpr inline auto operator - ( const ConstIteratorBase & o ) const noexcept -> SignedSize { return this->_pos - o._pos; }
    inline auto operator * ( ) const noexcept -> ElementType { return this->value(); }
};

class String::Iterator final : public IteratorBase {
public:
    Iterator () noexcept = delete;
    explicit Iterator ( String &, Index ) noexcept;
    Iterator ( String::Iterator const & ) noexcept = default;

    ~Iterator () noexcept final = default;

    constexpr inline auto next () noexcept -> Iterator & final { this->_pos ++; return * this; }

    constexpr inline auto operator ++ () noexcept -> Iterator & final { return this->next(); }
    inline auto operator ++ (int) noexcept -> Iterator { auto copy = * this; this->next(); return copy; }
};

class String::ConstIterator final : public ConstIteratorBase {
public:
    ConstIterator () noexcept = delete;
    explicit ConstIterator ( String const &, Index ) noexcept;
    ConstIterator ( String::ConstIterator const & ) noexcept = default;

    ~ConstIterator () noexcept final = default;

    constexpr inline auto next () noexcept -> ConstIterator & final { this->_pos ++; return * this; }

    constexpr inline auto operator ++ () noexcept -> ConstIterator & final { return this->next(); }
    inline auto operator ++ (int) noexcept -> ConstIterator { auto copy = * this; this->next(); return copy; }
};

class String::ReverseIterator final : public IteratorBase {
public:
    ReverseIterator () noexcept = delete;
    explicit ReverseIterator ( String &, Index ) noexcept;
    ReverseIterator ( String::ReverseIterator const & ) noexcept = default;

    ~ReverseIterator () noexcept final = default;

    constexpr inline auto next () noexcept -> ReverseIterator & final { this->_pos --; return * this; }

    constexpr inline auto operator ++ () noexcept -> ReverseIterator & final { return this->next(); }
    inline auto operator ++ (int) noexcept -> ReverseIterator { auto copy = * this; this->next(); return copy; }
};

class String::ConstReverseIterator final : public ConstIteratorBase {
public:
    ConstReverseIterator () noexcept = delete;
    explicit ConstReverseIterator ( String const &, Index ) noexcept;
    ConstReverseIterator ( String::ConstReverseIterator const & ) noexcept = default;

    ~ConstReverseIterator () noexcept final = default;

    constexpr inline auto next () noexcept -> ConstReverseIterator & final { this->_pos --; return * this; }

    constexpr inline auto operator ++ () noexcept -> ConstReverseIterator & final { return this->next(); }
    inline auto operator ++ (int) noexcept -> ConstReverseIterator { auto copy = * this; this->next(); return copy; }
};

template < typename Action >
auto String::forEach ( Action const & a ) noexcept (false) -> String & {
    for ( auto & e : * this )
        a ( e );

    return * this;
}

template < typename Action >
auto String::forEach ( Action const & a ) const noexcept (false) -> String const & {
    for ( auto e : * this )
        a ( e );

    return * this;
}

template < typename Predicate >
auto String::count ( Predicate const & p ) noexcept (false) -> Size {
    Index count = 0;
    for ( auto & e : * this )
        if ( p(e) ) count++;

    return count;
}

template < typename Predicate >
auto String::count ( Predicate const & p ) const noexcept (false) -> Size {
    Index count = 0;
    for ( auto e : * this )
        if ( p(e) ) count++;

    return count;
}

#endif //CDS_STRING_HPP
