//
// Created by loghin on 22.01.2021.
//

#ifndef CDS_STRING_HPP
#define CDS_STRING_HPP

#include <std-types.h>
#include <string>
#include <ostream>

#include <std-types.h>
#include <LinkedListPublic.hpp>

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
    explicit String(Size, ElementType) noexcept;
    explicit String(std::string::iterator const &, std::string::iterator const &) noexcept;
    explicit String(IteratorBase &, IteratorBase &) noexcept;
    explicit String(ConstIteratorBase &, ConstIteratorBase &) noexcept;
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

    inline auto resize(Size s) noexcept -> void { this->_alloc( s ); }
    inline auto reserve(Size s) noexcept -> void { this->_alloc( s ); }
    auto shrink(SignedSize = -1) noexcept -> void;

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

    inline auto operator += (sint16 v) noexcept -> String & { return this->operator+=( std::to_string(v) ); }
    inline auto operator += (sint32 v) noexcept -> String & { return this->operator+=( std::to_string(v) ); }
    inline auto operator += (sint64 v) noexcept -> String & { return this->operator+=( std::to_string(v) ); }

    inline auto operator += (uint8 v) noexcept -> String & { return this->operator+=( std::to_string(v) ); }
    inline auto operator += (uint16 v) noexcept -> String & { return this->operator+=( std::to_string(v) ); }
    inline auto operator += (uint32 v) noexcept -> String & { return this->operator+=( std::to_string(v) ); }
    inline auto operator += (uint64 v) noexcept -> String & { return this->operator+=( std::to_string(v) ); }

    inline auto operator += (float v) noexcept -> String & { return this->operator+=( std::to_string(v) ); }
    inline auto operator += (double v) noexcept -> String & { return this->operator+=( std::to_string(v) ); }

    auto append (ElementType) noexcept -> String &;
    auto append (StringLiteral) noexcept -> String &;
    auto append (String const &) noexcept -> String &;
    inline auto append (std::string const & s) noexcept -> String & { return this->append(s.c_str()); }

    inline auto append (sint16 v) noexcept -> String & { return this->append( std::to_string(v) ); }
    inline auto append (sint32 v) noexcept -> String & { return this->append( std::to_string(v) ); }
    inline auto append (sint64 v) noexcept -> String & { return this->append( std::to_string(v) ); }

    inline auto append (uint8 v) noexcept -> String & { return this->append( std::to_string(v) ); }
    inline auto append (uint16 v) noexcept -> String & { return this->append( std::to_string(v) ); }
    inline auto append (uint32 v) noexcept -> String & { return this->append( std::to_string(v) ); }
    inline auto append (uint64 v) noexcept -> String & { return this->append( std::to_string(v) ); }

    inline auto append (float v) noexcept -> String & { return this->append( std::to_string(v) ); }
    inline auto append (double v) noexcept -> String & { return this->append( std::to_string(v) ); }

    inline auto prepend (ElementType e) noexcept -> String & { return this->prepend(String().append(e)); }
    inline auto prepend (StringLiteral cString) noexcept -> String & { return this->prepend(String(cString)); }
    inline auto prepend (String const & s) noexcept -> String & { return ( * this = s + * this ); }
    inline auto prepend (std::string const & s) noexcept -> String & { return this->prepend(s.c_str()); }

    inline auto prepend (sint16 v) noexcept -> String & { return this->prepend( std::to_string(v) ); }
    inline auto prepend (sint32 v) noexcept -> String & { return this->prepend( std::to_string(v) ); }
    inline auto prepend (sint64 v) noexcept -> String & { return this->prepend( std::to_string(v) ); }

    inline auto prepend (uint8 v) noexcept -> String & { return this->prepend( std::to_string(v) ); }
    inline auto prepend (uint16 v) noexcept -> String & { return this->prepend( std::to_string(v) ); }
    inline auto prepend (uint32 v) noexcept -> String & { return this->prepend( std::to_string(v) ); }
    inline auto prepend (uint64 v) noexcept -> String & { return this->prepend( std::to_string(v) ); }

    inline auto prepend (float v) noexcept -> String & { return this->prepend( std::to_string(v) ); }
    inline auto prepend (double v) noexcept -> String & { return this->prepend( std::to_string(v) ); }

    [[nodiscard]] inline auto toStdString () const noexcept -> std::string { return std::string(this->cStr()); }
    inline explicit operator std::string () const noexcept { return this->toStdString(); }

    [[nodiscard]] constexpr auto cStr () const noexcept -> StringLiteral { return this->_p; }
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

    [[nodiscard]] inline auto operator + (sint16 v) const noexcept -> String { return this->operator+( std::to_string(v) ); }
    [[nodiscard]] inline auto operator + (sint32 v) const noexcept -> String { return this->operator+( std::to_string(v) ); }
    [[nodiscard]] inline auto operator + (sint64 v) const noexcept -> String { return this->operator+( std::to_string(v) ); }
    [[nodiscard]] inline auto operator + (uint8 v) const noexcept -> String { return this->operator+( std::to_string(v) ); }
    [[nodiscard]] inline auto operator + (uint16 v) const noexcept -> String { return this->operator+( std::to_string(v) ); }
    [[nodiscard]] inline auto operator + (uint32 v) const noexcept -> String { return this->operator+( std::to_string(v) ); }
    [[nodiscard]] inline auto operator + (uint64 v) const noexcept -> String { return this->operator+( std::to_string(v) ); }
    [[nodiscard]] inline auto operator + (float v) const noexcept -> String { return this->operator+( std::to_string(v) ); }
    [[nodiscard]] inline auto operator + (double v) const noexcept -> String { return this->operator+( std::to_string(v) ); }

    auto ltrim ( ElementType = ' ' ) noexcept -> String &;
    auto ltrim ( String const & ) noexcept -> String &;
    auto rtrim ( ElementType = ' ' ) noexcept -> String &;
    auto rtrim ( String const & ) noexcept -> String &;
    auto inline trim ( ElementType e = ' ' ) noexcept -> String & { return this->ltrim(e).rtrim(); }
    auto inline trim ( String const & e ) noexcept -> String & { return this->ltrim(e).rtrim(); }

    auto rjust (Size, ElementType = ' ') noexcept -> String &;
    auto ljust (Size, ElementType = ' ') noexcept -> String &;

private:
    constexpr auto static inline isUpper(char c) noexcept -> bool { return c >= 'A' && c <= 'Z'; }
    constexpr auto static inline isLower(char c) noexcept -> bool { return c >= 'a' && c <= 'z'; }
    constexpr auto static inline toLower(char c) noexcept -> char { return isUpper(c) ? c + 32 : c; }
    constexpr auto static inline toUpper(char c) noexcept -> char { return isLower(c) ? c - 32 : c; }

public:
    auto inline toLower () noexcept -> String & { for ( Index i = 0; i < this->_l; i++ ) if ( isUpper(this->_p[i]) ) this->_p[i] = toLower(this->_p[i]); return * this; }
    auto inline toUpper () noexcept -> String & { for ( Index i = 0; i < this->_l; i++ ) if ( isLower(this->_p[i]) ) this->_p[i] = toUpper(this->_p[i]); return * this; }

    [[nodiscard]] auto inline lower () const noexcept -> String { return String(*this).toLower(); }
    [[nodiscard]] auto inline upper () const noexcept -> String { return String(*this).toUpper(); }

    String & operator = ( String const & ) noexcept;
    inline String & operator = ( std::string const & s ) noexcept { return this->operator=(String(s)); } // NOLINT(misc-unconventional-assign-operator)
    inline String & operator = ( ElementType e ) noexcept { return this->operator=(String().append(e)); } // NOLINT(misc-unconventional-assign-operator)
    inline String & operator = ( StringLiteral cString ) noexcept { return this->operator=(String(cString)); } // NOLINT(misc-unconventional-assign-operator)

    [[nodiscard]] auto split ( ElementType, Size = UINT64_MAX ) const noexcept -> LinkedList < String >;
    [[nodiscard]] auto split ( String const &, Size = UINT64_MAX ) const noexcept -> LinkedList < String >;

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

    constexpr inline virtual auto next() -> IteratorBase & = 0;
    [[nodiscard]] constexpr inline auto equals ( const String::IteratorBase & i ) const noexcept -> bool { return this->_s == i._s && this->_pos == i._pos; }
    [[nodiscard]] inline auto value ( ) const noexcept (false) -> ElementType & { return this->_s->get(this->_pos); }

    virtual constexpr inline auto operator ++ () noexcept -> IteratorBase & { return this->next(); }
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

    constexpr inline virtual auto next() -> ConstIteratorBase & = 0;
    [[nodiscard]] constexpr inline auto equals ( const String::ConstIteratorBase & i ) const noexcept -> bool { return this->_s == i._s && this->_pos == i._pos; }
    [[nodiscard]] inline auto value ( ) const noexcept -> ElementType { return this->_s->get(this->_pos); }

    virtual constexpr inline auto operator ++ () noexcept -> ConstIteratorBase & { return this->next(); }
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

#include <cstring>
#define CONSTR_CLEAR() _c(0), _l(0), _p(nullptr)

void String::_alloc(Size size) noexcept {
    if ( this->_l + size + 1 < this->_c )
        return;

    auto newCap = std::max ( size + this->_l, 2 * this->_c ) + 1;
    auto newArea = new ElementType [newCap];

    if ( this->_p != nullptr )
        std::memcpy( newArea, this->_p, this->_l );

    std::memset ( newArea + this->_l, 0, newCap - this->_l );

    delete [] this->_p;

    this->_p = newArea;
    this->_c = newCap;
}

String::String(StringLiteral cString) noexcept : CONSTR_CLEAR() {
    if ( cString == nullptr )
        return;

    auto len = strlen(cString);
    if ( len == 0 )
        return;

    this->_alloc(len);

    this->_l = len;
    std::memcpy ( this->_p, cString, this->_l + 1 );
}

String::String(String const & s) noexcept : CONSTR_CLEAR() {
    if ( s.empty() )
        return;

    this->_alloc(s._l);
    this->_l = s._l;
    std::memcpy ( this->_p, s._p, this->_l + 1 );
}

String::~String() noexcept {
    delete [] this->_p;
}

auto String::append (ElementType ch) noexcept -> String & {
    this->_alloc(1);

    this->_p[this->_l++] = ch;
    return * this;
}

auto String::append (StringLiteral cString) noexcept -> String & {
    auto len = strlen(cString);
    this->_alloc(len);

    for (int i = 0; i < len; ++i)
        this->_p[this->_l++] = cString[i];

    return * this;
}

auto String::append (String const & str) noexcept -> String & {
    this->_alloc(str._l);

    for ( ElementType e : str )
        this->_p[this->_l++] = e;

    return * this;
}

String::IteratorBase::IteratorBase(String & s, Index i) noexcept : _s ( & s ), _pos ( i ) {}
String::ConstIteratorBase::ConstIteratorBase(String const & s, Index i) noexcept : _s ( & s ), _pos ( i ) {}
String::Iterator::Iterator(String & s, Index i) noexcept : IteratorBase(s, i) {}
String::ConstIterator::ConstIterator(const String & s, Index i) noexcept : ConstIteratorBase(s, i) {}
String::ReverseIterator::ReverseIterator(String & s, Index i) noexcept : IteratorBase(s, i) {}
String::ConstReverseIterator::ConstReverseIterator(const String & s, Index i) noexcept : ConstIteratorBase(s, i) {}

auto String::begin() noexcept -> Iterator { return Iterator ( * this, 0 ); }
auto String::end () noexcept -> Iterator { return Iterator ( * this, this->_l ); }
auto String::begin() const noexcept -> ConstIterator { return ConstIterator ( * this, 0 ); }
auto String::end() const noexcept -> ConstIterator { return ConstIterator ( * this, this->_l ); }
auto String::cbegin() const noexcept -> ConstIterator { return ConstIterator ( * this, 0 ); }
auto String::cend() const noexcept -> ConstIterator { return ConstIterator ( * this, this->_l ); }
auto String::rbegin() noexcept -> ReverseIterator { return ReverseIterator( * this, this->_l - 1 ); }
auto String::rend() noexcept -> ReverseIterator { return ReverseIterator( * this, -1 ); }
auto String::rbegin() const noexcept -> ConstReverseIterator { return ConstReverseIterator( * this, this->_l - 1 ); }
auto String::rend() const noexcept -> ConstReverseIterator { return ConstReverseIterator( * this, -1 ); }
auto String::crbegin() const noexcept -> ConstReverseIterator { return ConstReverseIterator( * this, this->_l - 1 ); }
auto String::crend() const noexcept -> ConstReverseIterator { return ConstReverseIterator( * this, -1 ); }

auto String::operator [] (Index i) noexcept (false) -> ElementType & {
    if ( this->empty() )
        throw String::StringNullAccess();

    if ( i < 0 )
        i += ( (-i) / this->size() + 1 ) * this->size();
    if ( i >= this->size() )
        i = i % this->size();

    return this->_p[i];
}

auto String::operator [] (Index i) const noexcept -> ElementType {
    if ( this->empty() )
        return '\0';

    if ( i < 0 )
        i += ( (-i) / this->size() + 1 ) * this->size();
    if ( i >= this->size() )
        i = i % this->size();

    return this->_p[i];
}

String::String(const std::string & s) noexcept : CONSTR_CLEAR() {
    if ( s.empty() )
        return;

    this->_alloc(s.size());

    for ( auto e : s )
        this->_p[this->_l++] = e;
}

String::String(Size count, ElementType constant) noexcept : CONSTR_CLEAR() {
    if ( count == 0 )
        return;

    this->_alloc(count);
    std::memset(this->_p, constant, count);
    this->_l = count;
}

String::String(const std::initializer_list<ElementType> & list) noexcept : CONSTR_CLEAR() {
    if ( list.size() == 0 )
        return;

    this->_alloc(list.size());
    for ( auto e : list )
        this->_p[this->_l++] = e;
}

String::String(std::string::iterator const & begin, std::string::iterator const & end) noexcept : CONSTR_CLEAR() {
    if ( end - begin <= 0 )
        return;

    this->_alloc(end - begin);

    for ( auto it = begin; it != end; it++ )
        this->_p[this->_l++] = *it;
}

String::String(IteratorBase & begin, IteratorBase & end) noexcept : CONSTR_CLEAR() {
    if ( end - begin <= 0 )
        return;
    this->_alloc(end - begin);

    for ( auto & it = begin; it != end; ++it )
        this->_p[this->_l++] = *it;
}

String::String(ConstIteratorBase & begin, ConstIteratorBase & end) noexcept : CONSTR_CLEAR() {
    if ( end - begin <= 0 )
        return;
    this->_alloc(end - begin);

    for ( auto & it = begin; it != end; ++it )
        this->_p[this->_l++] = *it;
}

auto String::shrink(SignedSize size) noexcept -> void {
    if ( this->empty() )
        return;
    if ( size == -1 )
        size = this->size();

    this->_c = size + 1;
    auto newArea = new ElementType [ this->_c ];
    std::memcpy ( newArea, this->_p, this->_c );

    delete [] this->_p;

    this->_p = newArea;
}

auto String::clear() noexcept -> void {
    if ( this->_p != nullptr )
        std::memset ( this->_p, 0, this->_l );
    this->_l = 0;
}

#include <LinkedList.hpp>
auto String::split(ElementType token, Size splitCount) const noexcept -> LinkedList < String > {
    Index splitIndex = 0;
    if ( splitCount < 1 )
        splitCount = INT64_MAX;

    LinkedList < String > segments;
    if ( this->empty() )
        return segments;

    String currentSegment;

    for ( auto c : (*this) ) {
        if ( c != token || splitIndex >= splitCount - 1 )
            currentSegment += c;
        else {
            if ( currentSegment.empty() )
                continue;

            splitIndex ++;
            segments.pushBack ( currentSegment );
            currentSegment.clear();
        }
    }

    if ( ! currentSegment.empty() )
        segments.pushBack ( currentSegment );
    return segments;
}

auto String::split(const String & delim, Size splitCount) const noexcept -> LinkedList < String > {
    Index splitIndex = 0;
    if ( splitCount < 1 )
        splitCount = INT64_MAX;

    LinkedList < String > segments;
    if ( this->empty() )
        return segments;

    String currentSegment;

    for ( auto c : (*this) ) {
        if ( ! delim.contains(c) || splitIndex >= splitCount - 1 )
            currentSegment += c;
        else {
            splitIndex ++;
            segments.pushBack ( currentSegment );
            currentSegment.clear();
        }
    }

    segments.pushBack ( currentSegment );
    return segments;
}

String & String::operator= ( String const & o ) noexcept {
    if ( this == & o )
        return * this;

    this->clear();

    if ( o.empty() )
        return * this;

    this->_alloc(o.size());
    std::memcpy ( this->_p, o._p, o._l + 1 );
    this->_l = o._l;

    return * this;
}

auto String::operator == ( String const & o ) const noexcept -> bool { return this->size() == o.size() && std::strcmp ( this->cStr(), o.cStr() ) == 0; }
auto String::operator == ( std::string const & stdString ) const noexcept -> bool { return std::strcmp ( this->cStr(), stdString.c_str() ) == 0; }
auto String::operator == ( StringLiteral cString ) const noexcept -> bool { return std::strcmp ( this->cStr(), cString ) == 0; }
auto String::operator >= ( String const & o ) const noexcept -> bool { return std::strcmp ( this->cStr(), o.cStr() ) >= 0; }
auto String::operator >= ( std::string const & stdString ) const noexcept -> bool { return std::strcmp ( this->cStr(), stdString.c_str() ) >= 0; }
auto String::operator >= ( StringLiteral cString ) const noexcept -> bool { return std::strcmp ( this->cStr(), cString ) >= 0; }
auto String::operator <= ( String const & o ) const noexcept -> bool { return std::strcmp ( this->cStr(), o.cStr() ) <= 0; }
auto String::operator <= ( std::string const & stdString ) const noexcept -> bool { return std::strcmp ( this->cStr(), stdString.c_str() ) <= 0; }
auto String::operator <= ( StringLiteral cString ) const noexcept -> bool { return std::strcmp ( this->cStr(), cString ) <= 0; }
auto String::operator != ( String const & o ) const noexcept -> bool { return this->size() != o.size() || std::strcmp ( this->cStr(), o.cStr() ) != 0; }
auto String::operator != ( std::string const & stdString ) const noexcept -> bool { return std::strcmp ( this->cStr(), stdString.c_str() ) != 0; }
auto String::operator != ( StringLiteral cString ) const noexcept -> bool { return std::strcmp ( this->cStr(), cString ) != 0; }
auto String::operator < ( String const & o ) const noexcept -> bool { return std::strcmp ( this->cStr(), o.cStr() ) < 0; }
auto String::operator < ( std::string const & stdString ) const noexcept -> bool { return std::strcmp ( this->cStr(), stdString.c_str() ) < 0; }
auto String::operator < ( StringLiteral cString ) const noexcept -> bool { return std::strcmp ( this->cStr(), cString ) < 0; }
auto String::operator > ( String const & o ) const noexcept -> bool { return std::strcmp ( this->cStr(), o.cStr() ) > 0; }
auto String::operator > ( std::string const & stdString ) const noexcept -> bool { return std::strcmp ( this->cStr(), stdString.c_str() ) > 0; }
auto String::operator > ( StringLiteral cString ) const noexcept -> bool { return std::strcmp ( this->cStr(), cString ) > 0; }

auto String::findFirst ( ElementType e ) const noexcept -> Index {
    for ( Index i = 0; auto c : (*this) )
        if ( c == e )
            return i;
        else
            i++;

    return INVALID_POS;
}

auto String::findFirst ( String const & o ) const noexcept -> Index {
    for ( Index i = 0; auto c : (*this) )
        if ( this->size() - i > o.size() && this->substr( i, i + o.size() ) == o )
            return i;
        else
            i++;
    return INVALID_POS;
}

auto String::findLast ( ElementType e ) const noexcept -> Index {
    Index i = this->size() - 1;
    for ( auto it = this->rbegin(); it != this->rend(); it++ )
        if ( it.value() == e )
            return i;
        else
            i--;
    return INVALID_POS;
}

auto String::findLast ( String const & o ) const noexcept -> Index {
    throw NotImplementedException();
    return INVALID_POS;
}

auto String::findFirstOf ( String const & o ) const noexcept -> Index {
    for ( Index i = 0; auto e : (*this) )
        if ( o.contains(e) )
            return i;
        else
            i++;
    return INVALID_POS;
}

auto String::findFirstNotOf ( String const & o ) const noexcept -> Index {
    for ( Index i = 0; auto e : (*this) )
        if ( ! o.contains(e) )
            return i;
        else
            i++;
    return INVALID_POS;
}

auto String::findLastOf ( String const & o ) const noexcept -> Index {
    Index i = 0;
    for ( auto it = this->rbegin(); it != this->rend(); it++ )
        if ( o.contains(it.value()) )
            return i;
        else
            i++;
    return INVALID_POS;
}

auto String::findLastNotOf ( String const & o ) const noexcept -> Index {
    Index i = 0;
    for ( auto it = this->rbegin(); it != this->rend(); it++ )
        if ( ! o.contains(it.value()) )
            return i;
        else
            i++;
    return INVALID_POS;
}

auto String::substr(Index from, Index to) const noexcept -> String {
    if ( to == -1 || to > this->size() )
        to = this->size();
    if ( from < 0 )
        from = 0;

    String s;
    for ( Index i = from; i < to; i++ )
        s += this->_p[i];

    return s;
}

auto String::find (ElementType e) const noexcept -> LinkedList < Index > {
    LinkedList < Index > indices;

    for ( Index i = 0; auto c : (*this) ) {
        if ( c == e )
            indices.pushBack ( i );
        i++;
    }

    return indices;
}

auto String::findOf (String const & s) const noexcept -> LinkedList < Index > {
    LinkedList < Index > indices;

    for ( Index i = 0; auto c : (*this) ) {
        if ( s.contains(c) )
            indices.pushBack ( i );
        i++;
    }

    return indices;
}

auto String::findNotOf (String const & s) const noexcept -> LinkedList < Index > {
    LinkedList < Index > indices;

    for ( Index i = 0; auto c : (*this) ) {
        if ( ! s.contains(c) )
            indices.pushBack ( i );
        i++;
    }

    return indices;
}

auto String::find (String const &) const noexcept -> LinkedList < Index > {
    throw NotImplementedException();
}

auto String::ltrim ( ElementType e ) noexcept -> String & {
    while ( this->front() == e && ! this->empty() )
        * this = this->substr( 1 );
    return * this;
}

auto String::ltrim ( String const & s ) noexcept -> String & {
    while ( s.contains( this->front() ) && ! this->empty() )
        * this = this->substr(1);
    return * this;
}

auto String::rtrim ( ElementType e ) noexcept -> String & {
    while ( this->back() == e && ! this->empty() )
        this->_p[--this->_l] = '\0';

    return * this;
}

auto String::rtrim ( String const & s ) noexcept -> String & {
    while ( s.contains(this->back()) && ! this->empty() )
        this->_p[this->_l--] = '\0';

    return * this;
}

#ifndef NDEBUG
auto String::diag() const noexcept -> String {
    return String("Debug = { data = '") + this->_p + "', length = " + this->_l + ", capacity = " + this->_c + " }";
}
#endif

auto String::rjust(Size justifySize, ElementType padChar) noexcept -> String & {
    while ( this->size() < justifySize )
        this->append(padChar);

    return * this;
}

auto String::ljust(Size justifySize, ElementType padChar) noexcept -> String & {
    while ( this->size() < justifySize )
        this->prepend(padChar);

    return * this;
}

#undef CONSTR_CLEAR

#endif //CDS_STRING_HPP
