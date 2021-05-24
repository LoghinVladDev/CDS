//
// Created by loghin on 22.01.2021.
//

#ifndef CDS_STRING_HPP
#define CDS_STRING_HPP

#include <ostream>
#include <string>

#include <CDS/Concepts>

#include "../collection/ordered/LinkedListPublic.hpp"

template < typename T >
class View;

#if defined(CDS_QT)
#include <QString>
#endif

#include <CDS/Object>

class String final : public Object {
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

    /**
     * @test tested in primitive/StringTest/Constructor Tests
     */
    String () noexcept = default;

    /**
     * @test tested in primitive/StringTest/Constructor Tests
     */
    String (String const &) noexcept;
    //TODO : implement later
//    explicit String (String const &, Index, Size = UINT64_MAX) noexcept;

    /**
     * @test tested in primitive/StringTest/Constructor Tests
     */
    String(StringLiteral) noexcept; // NOLINT(google-explicit-constructor)
//    explicit String(StringLiteral, Index, Size = UINT64_MAX) noexcept;

    /**
     * @test tested in primitive/StringTest/Constructor Tests
     */
    String(std::string const &) noexcept; // NOLINT(google-explicit-constructor)
//    explicit String(std::string const &, Index, Size = UINT64_MAX) noexcept;

    /**
     * @test tested in primitive/StringTest/Constructor Tests
     */
    String(Size, ElementType) noexcept;

    /**
     * @test tested in primitive/StringTest/Constructor Tests
     */
    String(std::string::iterator const &, std::string::iterator const &) noexcept;

    /**
     * @test tested in primitive/StringTest/Constructor Tests
     */
    String(IteratorBase const &, IteratorBase const &) noexcept;

    /**
     * @test tested in primitive/StringTest/Constructor Tests
     */
    String(ConstIteratorBase const &, ConstIteratorBase const &) noexcept;

    /**
     * @test tested in primitive/StringTest/Constructor Tests
     */
    String(std::initializer_list<ElementType> const &) noexcept;

#if defined(CDS_QT)
    String(QString const & o) noexcept : String(o.toStdString()) {}
#endif

    String (Object const & o) noexcept : String(o.toString()) { }

    String (uint8 v) noexcept : String(String().append(v)) { }
    String (uint16 v) noexcept : String(String().append(v)) { }
    String (uint32 v) noexcept : String(String().append(v)) { }
    String (uint64 v) noexcept : String(String().append(v)) { }

    String (sint8 v) noexcept : String(String().append(v)) { }
    String (sint16 v) noexcept : String(String().append(v)) { }
    String (sint32 v) noexcept : String(String().append(v)) { }
    String (sint64 v) noexcept : String(String().append(v)) { }

    String (float v) noexcept : String(String().append(v)) { }
    String (double v) noexcept : String(String().append(v)) { }

#if defined(__linux)

    String(std::size_t v) noexcept : String((uint64)v) {}

#endif

    template < typename T >
    String (T * v) noexcept : String((std::size_t)v) { }

    template < typename T >
    String (T const * v) noexcept : String((std::size_t)v) { }

//    String (std::size_t v) noexcept : String((CDS_uint64)v) {}

#if defined(CDS_GLM)

    template < glm::length_t l, typename T, glm::qualifier q >
    auto hash ( glm::vec < l, T , q > const & v ) noexcept -> Index {
        if constexpr ( l == 1 )         return hash (v.x);
        else if constexpr ( l == 2 )    return hash (v.x) * 100 + hash (v.y);
        else if constexpr ( l == 3 )    return hash (v.x) * 10000 + hash (v.y) * 100 + hash(v.z);
        else if constexpr ( l == 4 )    return hash (v.x) * 1000000 + hash (v.y) * 10000 + hash(v.z) * 100 + hash(v.w);
        else return 0;
    }

#endif

    /**
     * @test testcase not required
     */
    ~String() noexcept override;


    /**
     * @test tested in primitive/StringTest/Iterator Tests
     */
    [[nodiscard]] auto begin() noexcept -> Iterator;

    /**
     * @test tested in primitive/StringTest/Iterator Tests
     */
    [[nodiscard]] auto end () noexcept -> Iterator;

    /**
     * @test tested in primitive/StringTest/Iterator Tests
     */
    [[nodiscard]] auto begin() const noexcept -> ConstIterator;

    /**
     * @test tested in primitive/StringTest/Iterator Tests
     */
    [[nodiscard]] auto end() const noexcept -> ConstIterator;

    /**
     * @test tested in primitive/StringTest/Iterator Tests
     */
    [[nodiscard]] auto cbegin() const noexcept -> ConstIterator;

    /**
     * @test tested in primitive/StringTest/Iterator Tests
     */
    [[nodiscard]] auto cend() const noexcept -> ConstIterator;

    /**
     * @test tested in primitive/StringTest/Iterator Tests
     */


    /**
     * @test tested in primitive/StringTest/Iterator Tests
     */
    [[nodiscard]] auto rbegin() noexcept -> ReverseIterator;

    /**
     * @test tested in primitive/StringTest/Iterator Tests
     */
    [[nodiscard]] auto rend() noexcept -> ReverseIterator;

    /**
     * @test tested in primitive/StringTest/Iterator Tests
     */
    [[nodiscard]] auto rbegin() const noexcept -> ConstReverseIterator;

    /**
     * @test tested in primitive/StringTest/Iterator Tests
     */
    [[nodiscard]] auto rend() const noexcept -> ConstReverseIterator;

    /**
     * @test tested in primitive/StringTest/Iterator Tests
     */
    [[nodiscard]] auto crbegin() const noexcept -> ConstReverseIterator;

    /**
     * @test tested in primitive/StringTest/Iterator Tests
     */
    [[nodiscard]] auto crend() const noexcept -> ConstReverseIterator;


    /**
     * @test tested in primitive/StringTest/Property Tests
     */
    [[nodiscard]] constexpr inline auto size() const noexcept -> Size { return this->_l; }

    /**
     * @test tested in primitive/StringTest/Property Tests
     */
    [[nodiscard]] constexpr inline auto length() const noexcept -> Size { return this->_l; }

    /**
     * @test tested in primitive/StringTest/Property Tests
     */
    [[nodiscard]] constexpr inline auto maxSize() const noexcept -> Size { return this->_c; }

    /**
     * @test tested in primitive/StringTest/Property Tests
     */
    [[nodiscard]] constexpr inline auto capacity() const noexcept -> Size { return this->_c; }


    /**
     * @test tested in primitive/StringTest/Memory Tests
     */
    auto resize(Size) noexcept -> void; //{ this->_alloc( s ); }

    /**
     * @test tested in primitive/StringTest/Memory Tests
     */
    inline auto reserve(Size s) noexcept -> void { if ( s < this->_c ) return; this->resize( s ); }

    /**
     * @test tested in primitive/StringTest/Memory Tests
     */
    inline auto shrink(SignedSize s = -1) noexcept -> void { if ( s == -1 ) s = this->_l; if ( s > this->_c ) return; this->resize( s ); }

    /**
     * @test tested in primitive/StringTest/Content Functions Tests
     */
    auto clear() noexcept -> void;

    /**
     * @test tested in primitive/StringTest/Content Functions Tests
     */
    [[nodiscard]] constexpr inline auto empty() const noexcept -> bool { return this->_l == 0; }


    /**
     * @test tested in primitive/StringTest/Content Functions Tests
     */
    auto operator [] (Index) noexcept (false) -> ElementType &;

    /**
     * @test tested in primitive/StringTest/Content Functions Tests
     */
    [[nodiscard]] auto operator [] (Index) const noexcept -> ElementType;


    /**
     * @test If operator [] has a test, function is tested
     */
    inline auto at (Index i) noexcept (false) -> ElementType & { return this->operator[](i); }

    /**
     * @test If operator [] has a test, function is tested
     */
    [[nodiscard]] inline auto at (Index i) const noexcept -> ElementType { return this->operator[](i); }

    /**
     * @test If operator [] has a test, function is tested
     */
    inline auto get (Index i) noexcept (false) -> ElementType & { return this->operator[](i); }

    /**
     * @test If operator [] has a test, function is tested
     */
    [[nodiscard]] inline auto get (Index i) const noexcept -> ElementType { return this->operator[](i); }

    /**
     * @test If operator [] has a test, function is tested
     */
    inline auto front () noexcept (false) -> ElementType & { return this->operator[](0); }

    /**
     * @test If operator [] has a test, function is tested
     */
    inline auto back () noexcept (false) -> ElementType & { return this->operator[](this->_l - 1); }

    /**
     * @test If operator [] has a test, function is tested
     */
    [[nodiscard]] constexpr inline auto front() const noexcept -> ElementType { return this->empty() ? '\0' : this->_p[0]; }

    /**
     * @test If operator [] has a test, function is tested
     */
    [[nodiscard]] constexpr inline auto back() const noexcept -> ElementType { return this->empty() ? '\0' : this->_p[this->_l - 1]; }

    /**
     * @test tested in primitive/StringTest/Append/Prepend Tests
     */
    inline auto operator += (ElementType v) noexcept -> String & { return this->append( v ); }

    /**
     * @test tested in primitive/StringTest/Append/Prepend Tests
     */
    inline auto operator += (StringLiteral v) noexcept -> String & { return this->append( v ); }

    /**
     * @test tested in primitive/StringTest/Append/Prepend Tests
     */
    inline auto operator += (String const & v) noexcept -> String & { return this->append( v ); }

    /**
     * @test tested in primitive/StringTest/Append/Prepend Tests
     */
    inline auto operator += (std::string const & v) noexcept -> String & { return this->append( v ); }

    /**
     * @test tested in primitive/StringTest/Append/Prepend Tests
     */
    inline auto operator += (sint16 v) noexcept -> String & { return this->operator+=(std::to_string(v) ); }

    /**
     * @test tested in primitive/StringTest/Append/Prepend Tests
     */
    inline auto operator += (sint32 v) noexcept -> String & { return this->operator+=(std::to_string(v) ); }

    /**
     * @test tested in primitive/StringTest/Append/Prepend Tests
     */
    inline auto operator += (sint64 v) noexcept -> String & { return this->operator+=(std::to_string(v) ); }

    /**
     * @test tested in primitive/StringTest/Append/Prepend Tests
     */
    inline auto operator += (uint8 v) noexcept -> String & { return this->operator+=(std::to_string(v) ); }

    /**
     * @test tested in primitive/StringTest/Append/Prepend Tests
     */
    inline auto operator += (uint16 v) noexcept -> String & { return this->operator+=(std::to_string(v) ); }

    /**
     * @test tested in primitive/StringTest/Append/Prepend Tests
     */
    inline auto operator += (uint32 v) noexcept -> String & { return this->operator+=(std::to_string(v) ); }

    /**
     * @test tested in primitive/StringTest/Append/Prepend Tests
     */
    inline auto operator += (uint64 v) noexcept -> String & { return this->operator+=(std::to_string(v) ); }

    /**
     * @test tested in primitive/StringTest/Append/Prepend Tests
     */
    inline auto operator += (float v) noexcept -> String & { return this->operator+=( std::to_string(v) ); }

    /**
     * @test tested in primitive/StringTest/Append/Prepend Tests
     */
    inline auto operator += (double v) noexcept -> String & { return this->operator+=( std::to_string(v) ); }

#if defined(CDS_QT)
    inline auto operator += (QString const & v) noexcept -> String & { return this->operator += (String(v)); }
#endif

    /**
     * @test tested in primitive/StringTest/Append/Prepend Tests
     */
    auto append (ElementType) noexcept -> String &;

    /**
     * @test tested in primitive/StringTest/Append/Prepend Tests
     */
    auto append (StringLiteral) noexcept -> String &;

    /**
     * @test tested in primitive/StringTest/Append/Prepend Tests
     */
    auto append (String const &) noexcept -> String &;

    /**
     * @test tested in primitive/StringTest/Append/Prepend Tests
     */
    inline auto append (std::string const & s) noexcept -> String & { return this->append(s.c_str()); }

    /**
     * @test tested in primitive/StringTest/Append/Prepend Tests
     */
    inline auto append (sint16 v) noexcept -> String & { return this->append(std::to_string(v) ); }

    /**
     * @test tested in primitive/StringTest/Append/Prepend Tests
     */
    inline auto append (sint32 v) noexcept -> String & { return this->append(std::to_string(v) ); }

    /**
     * @test tested in primitive/StringTest/Append/Prepend Tests
     */
    inline auto append (sint64 v) noexcept -> String & { return this->append(std::to_string(v) ); }

    /**
     * @test tested in primitive/StringTest/Append/Prepend Tests
     */
    inline auto append (uint8 v) noexcept -> String & { return this->append(std::to_string(v) ); }

    /**
     * @test tested in primitive/StringTest/Append/Prepend Tests
     */
    inline auto append (uint16 v) noexcept -> String & { return this->append(std::to_string(v) ); }

    /**
     * @test tested in primitive/StringTest/Append/Prepend Tests
     */
    inline auto append (uint32 v) noexcept -> String & { return this->append(std::to_string(v) ); }

    /**
     * @test tested in primitive/StringTest/Append/Prepend Tests
     */
    inline auto append (uint64 v) noexcept -> String & { return this->append(std::to_string(v) ); }

    /**
     * @test tested in primitive/StringTest/Append/Prepend Tests
     */
    inline auto append (float v) noexcept -> String & { return this->append( std::to_string(v) ); }

    /**
     * @test tested in primitive/StringTest/Append/Prepend Tests
     */
    inline auto append (double v) noexcept -> String & { return this->append( std::to_string(v) ); }

#if defined(CDS_QT)
    inline auto append (QString const & v) noexcept -> String & { return this->append(String(v)); }
#endif


    /**
     * @test tested in primitive/StringTest/Append/Prepend Tests
     */
    inline auto prepend (ElementType e) noexcept -> String & { return this->prepend(String().append(e)); }

    /**
     * @test tested in primitive/StringTest/Append/Prepend Tests
     */
    inline auto prepend (StringLiteral cString) noexcept -> String & { return this->prepend(String(cString)); }

    /**
     * @test tested in primitive/StringTest/Append/Prepend Tests
     */
    inline auto prepend (String const & s) noexcept -> String & { return ( * this = s + * this ); }

    /**
     * @test tested in primitive/StringTest/Append/Prepend Tests
     */
    inline auto prepend (std::string const & s) noexcept -> String & { return this->prepend(s.c_str()); }

    /**
     * @test tested in primitive/StringTest/Append/Prepend Tests
     */
    inline auto prepend (sint16 v) noexcept -> String & { return this->prepend(std::to_string(v) ); }

    /**
     * @test tested in primitive/StringTest/Append/Prepend Tests
     */
    inline auto prepend (sint32 v) noexcept -> String & { return this->prepend(std::to_string(v) ); }

    /**
     * @test tested in primitive/StringTest/Append/Prepend Tests
     */
    inline auto prepend (sint64 v) noexcept -> String & { return this->prepend(std::to_string(v) ); }

    /**
     * @test tested in primitive/StringTest/Append/Prepend Tests
     */
    inline auto prepend (uint8 v) noexcept -> String & { return this->prepend(std::to_string(v) ); }

    /**
     * @test tested in primitive/StringTest/Append/Prepend Tests
     */
    inline auto prepend (uint16 v) noexcept -> String & { return this->prepend(std::to_string(v) ); }

    /**
     * @test tested in primitive/StringTest/Append/Prepend Tests
     */
    inline auto prepend (uint32 v) noexcept -> String & { return this->prepend(std::to_string(v) ); }

    /**
     * @test tested in primitive/StringTest/Append/Prepend Tests
     */
    inline auto prepend (uint64 v) noexcept -> String & { return this->prepend(std::to_string(v) ); }

    /**
     * @test tested in primitive/StringTest/Append/Prepend Tests
     */
    inline auto prepend (float v) noexcept -> String & { return this->prepend( std::to_string(v) ); }

    /**
     * @test tested in primitive/StringTest/Append/Prepend Tests
     */
    inline auto prepend (double v) noexcept -> String & { return this->prepend( std::to_string(v) ); }

#if defined(CDS_QT)
    inline auto prepend (QString const & v) noexcept -> String & { return this->prepend(String(v)); }
#endif


    /**
     * @test tested in primitive/StringTest/*
     */
    [[nodiscard]] inline auto toStdString () const noexcept -> std::string { return std::string(this->cStr()); }

    /**
     * @test tested in primitive/StringTest/Append/*
     */
    inline operator std::string () const noexcept { return this->toStdString(); }

#if defined(CDS_QT)
    [[nodiscard]] inline auto toQString () const noexcept -> QString { return QString(this->cStr()); }

    inline operator QString () const noexcept { return this->toQString(); }
#endif


    /**
     * @test tested in primitive/StringTest/*
     */
    [[nodiscard]] constexpr auto cStr () const noexcept -> StringLiteral { return this->_p == nullptr ? "" : this->_p; }

    /**
     * @test tested in primitive/StringTest/Append/*
     */
    inline explicit operator StringLiteral () const noexcept { return this->cStr(); }

    [[nodiscard]] constexpr auto data () noexcept -> CString  { return this->_p; }
    inline explicit operator CString () noexcept { return this->data(); }

    /**
     * @test tested in primitive/StringTest/Find Tests
     */
    [[nodiscard]] auto find (ElementType) const noexcept -> LinkedList < Index >;

    /**
     * @test tested in primitive/StringTest/Find Tests
     */
    [[nodiscard]] auto find (String const &) const noexcept -> LinkedList < Index >;

    /**
     * @test tested in primitive/StringTest/Find Tests
     */
    [[nodiscard]] auto findOf (String const &) const noexcept -> LinkedList < Index >;

    /**
     * @test tested in primitive/StringTest/Find Tests
     */
    [[nodiscard]] auto findNotOf (String const &) const noexcept -> LinkedList < Index >;


    /**
     * @test tested in primitive/StringTest/Find Tests
     */
    [[nodiscard]] auto findFirst ( ElementType ) const noexcept -> Index;

    /**
     * @test tested in primitive/StringTest/Find Tests
     */
    [[nodiscard]] auto findFirst ( String const & ) const noexcept -> Index;

    /**
     * @test tested in primitive/StringTest/Find Tests
     */
    [[nodiscard]] auto findLast ( ElementType ) const noexcept -> Index;

    /**
     * @test tested in primitive/StringTest/Find Tests
     */
    [[nodiscard]] auto findLast ( String const & ) const noexcept -> Index;

    /**
     * @test tested in primitive/StringTest/Find Tests
     */
    [[nodiscard]] auto findFirstOf ( String const & ) const noexcept -> Index;

    /**
     * @test tested in primitive/StringTest/Find Tests
     */
    [[nodiscard]] auto findFirstNotOf ( String const & ) const noexcept -> Index;

    /**
     * @test tested in primitive/StringTest/Find Tests
     */
    [[nodiscard]] auto findLastOf ( String const & ) const noexcept -> Index;

    /**
     * @test tested in primitive/StringTest/Find Tests
     */
    [[nodiscard]] auto findLastNotOf ( String const & ) const noexcept -> Index;


    /**
     * @test tested in primitive/StringTest/Substring Tests
     */
    [[nodiscard]] auto substr ( Index, Index = -1 ) const noexcept -> String;


    /**
     * @test tested in primitive/StringTest/Comparison Tests
     */
    [[nodiscard]] auto operator == ( String const & o ) const noexcept -> bool;

    /**
     * @test tested in primitive/StringTest/Comparison Tests
     */
    [[nodiscard]] constexpr inline auto operator == ( ElementType e ) const noexcept -> bool { return this->size() == 1 && this->_p[0] == e; }

    /**
     * @test tested in primitive/StringTest/Comparison Tests
     */
    [[nodiscard]] auto operator == ( std::string const & ) const noexcept -> bool;

    /**
     * @test tested in primitive/StringTest/Comparison Tests
     */
    [[nodiscard]] auto operator == ( StringLiteral ) const noexcept -> bool;

#if defined(CDS_QT)
    inline auto operator == (QString const & v) const noexcept -> bool { return * this == String(v); }
#endif


    /**
     * @test tested in primitive/StringTest/Comparison Tests
     */
    [[nodiscard]] auto operator >= ( String const & ) const noexcept -> bool;

    /**
     * @test tested in primitive/StringTest/Comparison Tests
     */
    [[nodiscard]] constexpr inline auto operator >= ( ElementType e ) const noexcept -> bool { return this->size() == 1 && this->_p[0] >= e; }

    /**
     * @test tested in primitive/StringTest/Comparison Tests
     */
    [[nodiscard]] auto operator >= ( std::string const & ) const noexcept -> bool;

#if defined(CDS_QT)
    inline auto operator >= (QString const & v) const noexcept -> bool { return * this >= String(v); }
#endif

    /**
     * @test tested in primitive/StringTest/Comparison Tests
     */
    [[nodiscard]] auto operator >= ( StringLiteral ) const noexcept -> bool;


    /**
     * @test tested in primitive/StringTest/Comparison Tests
     */
    [[nodiscard]] auto operator <= ( String const & ) const noexcept -> bool;

#if defined(CDS_QT)
    inline auto operator <= (QString const & v) const noexcept -> bool { return * this <= String(v); }
#endif


    /**
     * @test tested in primitive/StringTest/Comparison Tests
     */
    [[nodiscard]] constexpr inline auto operator <= ( ElementType e ) const noexcept -> bool { return this->size() == 1 && this->_p[0] <= e; }

    /**
     * @test tested in primitive/StringTest/Comparison Tests
     */
    [[nodiscard]] auto operator <= ( std::string const & ) const noexcept -> bool;

    /**
     * @test tested in primitive/StringTest/Comparison Tests
     */
    [[nodiscard]] auto operator <= ( StringLiteral ) const noexcept -> bool;


    /**
     * @test tested in primitive/StringTest/Comparison Tests
     */
    [[nodiscard]] auto operator != ( String const & ) const noexcept -> bool;

    /**
     * @test tested in primitive/StringTest/Comparison Tests
     */
    [[nodiscard]] constexpr inline auto operator != ( ElementType e ) const noexcept -> bool { return this->size() != 1 || this->_p[0] != e; }

    /**
     * @test tested in primitive/StringTest/Comparison Tests
     */
    [[nodiscard]] auto operator != ( std::string const & ) const noexcept -> bool;

    /**
     * @test tested in primitive/StringTest/Comparison Tests
     */
    [[nodiscard]] auto operator != ( StringLiteral ) const noexcept -> bool;

#if defined(CDS_QT)
    inline auto operator != (QString const & v) const noexcept -> bool { return * this != String(v); }
#endif


    /**
     * @test tested in primitive/StringTest/Comparison Tests
     */
    [[nodiscard]] auto operator < ( String const & ) const noexcept -> bool;

    /**
     * @test tested in primitive/StringTest/Comparison Tests
     */
    [[nodiscard]] constexpr inline auto operator < ( ElementType e ) const noexcept -> bool { return this->size() == 1 && this->_p[0] < e; }

    /**
     * @test tested in primitive/StringTest/Comparison Tests
     */
    [[nodiscard]] auto operator < ( std::string const & ) const noexcept -> bool;

    /**
     * @test tested in primitive/StringTest/Comparison Tests
     */
    [[nodiscard]] auto operator < ( StringLiteral ) const noexcept -> bool;

#if defined(CDS_QT)
    inline auto operator < (QString const & v) const noexcept -> bool { return * this < String(v); }
#endif


    /**
     * @test tested in primitive/StringTest/Comparison Tests
     */
    [[nodiscard]] auto operator > ( String const & ) const noexcept -> bool;

    /**
     * @test tested in primitive/StringTest/Comparison Tests
     */
    [[nodiscard]] constexpr inline auto operator > ( ElementType e ) const noexcept -> bool { return this->size() == 1 && this->_p[0] > e; }

    /**
     * @test tested in primitive/StringTest/Comparison Tests
     */
    [[nodiscard]] auto operator > ( std::string const & ) const noexcept -> bool;

    /**
     * @test tested in primitive/StringTest/Comparison Tests
     */
    [[nodiscard]] auto operator > ( StringLiteral ) const noexcept -> bool;

#if defined(CDS_QT)
    inline auto operator > (QString const & v) const noexcept -> bool { return * this > String(v); }
#endif


    /**
     * @test tested in primitive/StringTest/Append/Prepend Tests
     */
    [[nodiscard]] inline auto operator + ( String const & v ) const noexcept -> String { return String(*this).append(v); }

    /**
     * @test tested in primitive/StringTest/Append/Prepend Tests
     */
    [[nodiscard]] inline auto operator + ( ElementType v ) const noexcept -> String { return String(*this).append(v); }

    /**
     * @test tested in primitive/StringTest/Append/Prepend Tests
     */
    [[nodiscard]] inline auto operator + ( std::string const & v ) const noexcept -> String { return String(*this).append(v); }

    /**
     * @test tested in primitive/StringTest/Append/Prepend Tests
     */
    [[nodiscard]] inline auto operator + ( StringLiteral v ) const noexcept -> String { return String(*this).append(v); }

    /**
     * @test tested in primitive/StringTest/Append/Prepend Tests
     */


    /**
     * @test tested in primitive/StringTest/Append/Prepend Tests
     */
    [[nodiscard]] inline auto operator + (sint16 v) const noexcept -> String { return this->operator+(std::to_string(v) ); }

    /**
     * @test tested in primitive/StringTest/Append/Prepend Tests
     */
    [[nodiscard]] inline auto operator + (sint32 v) const noexcept -> String { return this->operator+(std::to_string(v) ); }

    /**
     * @test tested in primitive/StringTest/Append/Prepend Tests
     */
    [[nodiscard]] inline auto operator + (sint64 v) const noexcept -> String { return this->operator+(std::to_string(v) ); }

    /**
     * @test tested in primitive/StringTest/Append/Prepend Tests
     */
    [[nodiscard]] inline auto operator + (uint8 v) const noexcept -> String { return this->operator+(std::to_string(v) ); }

    /**
     * @test tested in primitive/StringTest/Append/Prepend Tests
     */
    [[nodiscard]] inline auto operator + (uint16 v) const noexcept -> String { return this->operator+(std::to_string(v) ); }

    /**
     * @test tested in primitive/StringTest/Append/Prepend Tests
     */
    [[nodiscard]] inline auto operator + (uint32 v) const noexcept -> String { return this->operator+(std::to_string(v) ); }

    /**
     * @test tested in primitive/StringTest/Append/Prepend Tests
     */
    [[nodiscard]] inline auto operator + (uint64 v) const noexcept -> String { return this->operator+(std::to_string(v) ); }

    /**
     * @test tested in primitive/StringTest/Append/Prepend Tests
     */
    [[nodiscard]] inline auto operator + (float v) const noexcept -> String { return this->operator+( std::to_string(v) ); }

    /**
     * @test tested in primitive/StringTest/Append/Prepend Tests
     */
    [[nodiscard]] inline auto operator + (double v) const noexcept -> String { return this->operator+( std::to_string(v) ); }

#if defined(CDS_QT)
    inline auto operator + (QString const & v) const noexcept -> String { return * this + String(v); }
#endif

    /**
     * @test tested in primitive/StringTest/Utility Functions, String Formatting
     */
    [[nodiscard]] auto operator * (int) const noexcept -> String;


    /**
     * @test tested in primitive/StringTest/Utility Functions, String Formatting
     */
    auto ltrim ( ElementType = ' ' ) noexcept -> String &;

    /**
     * @test tested in primitive/StringTest/Utility Functions, String Formatting
     */
    auto ltrim ( String const & ) noexcept -> String &;

    /**
     * @test tested in primitive/StringTest/Utility Functions, String Formatting
     */
    auto rtrim ( ElementType = ' ' ) noexcept -> String &;

    /**
     * @test tested in primitive/StringTest/Utility Functions, String Formatting
     */
    auto rtrim ( String const & ) noexcept -> String &;

    /**
     * @test tested in primitive/StringTest/Utility Functions, String Formatting
     */
    auto inline trim ( ElementType e = ' ' ) noexcept -> String & { return this->ltrim(e).rtrim(e); }

    /**
     * @test tested in primitive/StringTest/Utility Functions, String Formatting
     */
    auto inline trim ( String const & e ) noexcept -> String & { return this->ltrim(e).rtrim(e); }

    /**
     * @test tested in primitive/StringTest/Utility Functions, String Formatting
     */


    /**
     * @test tested in primitive/StringTest/Utility Functions, String Formatting
     */
    auto rjust (Size, ElementType = ' ') noexcept -> String &;

    /**
     * @test tested in primitive/StringTest/Utility Functions, String Formatting
     */
    auto ljust (Size, ElementType = ' ') noexcept -> String &;

public:

    /**
     * @test tested in primitive/StringTest/Utility Functions, String Formatting
     */
    constexpr auto static inline isUpperChar(char c) noexcept -> bool { return c >= 'A' && c <= 'Z'; }

    /**
     * @test tested in primitive/StringTest/Utility Functions, String Formatting
     */
    constexpr auto static inline isLowerChar(char c) noexcept -> bool { return c >= 'a' && c <= 'z'; }

    /**
     * @test tested in primitive/StringTest/Utility Functions, String Formatting
     */
    constexpr auto static inline isDigit(char c) noexcept -> bool { return c >= '0' && c <= '9'; }

    /**
     * @test tested in primitive/StringTest/Utility Functions, String Formatting
     */
    constexpr auto static inline isLetter(char c) noexcept -> bool { return isUpperChar(c) || isLowerChar(c); }

    /**
     * @test tested in primitive/StringTest/Utility Functions, String Formatting
     */
    constexpr auto static inline isAlpha(char c) noexcept -> bool { return isLetter(c) || isDigit(c); }

    /**
     * @test tested in primitive/StringTest/Utility Functions, String Formatting
     */
    auto static inline isVowel(char c) noexcept -> bool { return String("aeiouAEIOU").contains(c); }

    /**
     * @test tested in primitive/StringTest/Utility Functions, String Formatting
     */
    auto static inline isConsonant(char c) noexcept -> bool { return isLetter(c) && ! isVowel(c); }

    /**
     * @test tested in primitive/StringTest/Utility Functions, String Formatting
     */
    constexpr auto static inline lowerChar(char c) noexcept -> char { return isUpperChar(c) ? c + 32 : c; }

    /**
     * @test tested in primitive/StringTest/Utility Functions, String Formatting
     */
    constexpr auto static inline upperChar(char c) noexcept -> char { return isLowerChar(c) ? c - 32 : c; }

    /**
     * @test tested in primitive/StringTest/Utility Functions, String Formatting
     */
    constexpr auto static inline toLowerChar(char & c) noexcept -> char & { c = lowerChar(c); return c; }

    /**
     * @test tested in primitive/StringTest/Utility Functions, String Formatting
     */
    constexpr auto static inline toUpperChar(char & c) noexcept -> char & { c = upperChar(c); return c; }

public:

#if !defined(_MSC_VER)

    /**
     * @test tested in primitive/StringTest/Utility Functions, String Formatting
     */
    auto inline toLower () noexcept -> String & { for ( Index i = 0; i < this->_l; i++ ) this->_p[i] = lowerChar(this->_p[i]); return * this; }

    /**
     * @test tested in primitive/StringTest/Utility Functions, String Formatting
     */
    auto inline toUpper () noexcept -> String & { for ( Index i = 0; i < this->_l; i++ ) this->_p[i] = upperChar(this->_p[i]); return * this; }
#else

    /**
     * @test tested in primitive/StringTest/Utility Functions, String Formatting
     */
    auto inline toLower () noexcept -> String & { for ( Size i = 0; i < this->_l; i++ ) this->_p[i] = lowerChar(this->_p[i]); return * this; }

    /**
     * @test tested in primitive/StringTest/Utility Functions, String Formatting
     */
    auto inline toUpper () noexcept -> String & { for ( Size i = 0; i < this->_l; i++ ) this->_p[i] = upperChar(this->_p[i]); return * this; }
#endif

    /**
     * @test tested in primitive/StringTest/Utility Functions, String Formatting
     */
    [[nodiscard]] auto inline lower () const noexcept -> String { return String(*this).toLower(); }

    /**
     * @test tested in primitive/StringTest/Utility Functions, String Formatting
     */
    [[nodiscard]] auto inline upper () const noexcept -> String { return String(*this).toUpper(); }

    /**
     * @test tested in primitive/StringTest/Assignment Tests
     */
    String & operator = ( String const & ) noexcept;

#if defined(CDS_QT)
    inline String & operator = (QString const & v) noexcept { return ((* this) = String(v)); }
#endif

    /**
     * @test tested in primitive/StringTest/Assignment Tests
     */
    inline String & operator = ( std::string const & s ) noexcept { return this->operator=(String(s)); } // NOLINT(misc-unconventional-assign-operator)

    /**
     * @test tested in primitive/StringTest/Assignment Tests
     */
    inline String & operator = ( ElementType e ) noexcept { return this->operator=(String().append(e)); } // NOLINT(misc-unconventional-assign-operator)

    /**
     * @test tested in primitive/StringTest/Assignment Tests
     */
    inline String & operator = ( StringLiteral cString ) noexcept { return this->operator=(String(cString)); } // NOLINT(misc-unconventional-assign-operator)


    /**
     * @test tested in primitive/StringTest/Split Tests
     */
    [[nodiscard]] auto split ( ElementType, Size = UINT32_MAX ) const noexcept -> LinkedList < String >;

    /**
     * @test tested in primitive/StringTest/Split Tests
     */
    [[nodiscard]] auto split ( String const &, Size = UINT32_MAX ) const noexcept -> LinkedList < String >;

    constexpr static Index INVALID_POS = -1;

    /**
     * @test tested in primitive/StringTest/Content Functions Tests
     */
    [[nodiscard]] auto inline contains ( ElementType e ) const noexcept -> bool { return this->findFirst( e ) != INVALID_POS; }

    /**
     * @test tested in primitive/StringTest/Content Functions Tests
     */
    [[nodiscard]] auto inline contains ( String const & e ) const noexcept -> bool { return this->findFirst( e ) != INVALID_POS; }

    /**
     * @test tested in primitive/StringTest/Content Functions Tests
     */
    [[nodiscard]] auto inline contains ( StringLiteral e ) const noexcept -> bool { return this->findFirst( String(e) ) != INVALID_POS; }

    /**
     * @test tested in primitive/StringTest/Content Functions Tests
     */
    [[nodiscard]] auto inline contains ( std::string const & e ) const noexcept -> bool { return this->findFirst( String(e) ) != INVALID_POS; }

#if defined(CDS_QT)
    inline auto contains (QString const & v) const noexcept -> bool { return this->contains(String(v)); }
#endif

#ifndef NDEBUG

    /**
     * @test N/A
     */
    [[nodiscard]] auto diag() const noexcept -> String;
#endif

    /**
     * @test N/A
     */
    friend inline auto operator << ( std::ostream & out, String const & s ) noexcept -> std::ostream & {
        return ( out << (s._p == nullptr ? "null" : s._p) );
    }

    /**
     * @test N/A
     */
    [[nodiscard]] auto hash () const noexcept -> Index override {
        return this->length();
    }

    /**
     * @test N/A
     */
    [[nodiscard]] auto copy () const noexcept -> String * override {
        return new String( * this );
    }

    [[nodiscard]] auto toString () const noexcept -> String override {
        return * this;
    }

    /**
     * @test tested in primitive/StringTest/Replace Tests
     */
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

// weird stuff here
inline Object::operator String () const noexcept {
    return this->toString();
}

inline auto operator << (std::ostream & out, Object const & o) noexcept -> std::ostream & {
    return (out << o.toString());
}
// end of weird stuff


#include <cstring>
#define CONSTR_CLEAR() _c(0), _l(0), _p(nullptr)

inline void String::_alloc(Size size) noexcept {
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

inline String::String(StringLiteral cString) noexcept : CONSTR_CLEAR() {
    if ( cString == nullptr )
        return;

    auto len = strlen(cString);
    if ( len == 0 )
        return;

    this->_alloc(len);

    this->_l = len;
    std::memcpy ( this->_p, cString, this->_l + 1 );
}

inline String::String(String const & s) noexcept : CONSTR_CLEAR() {
    if ( s.empty() )
        return;

    this->_alloc(s._l);
    this->_l = s._l;
    std::memcpy ( this->_p, s._p, this->_l + 1 );
}

inline String::~String() noexcept {
    delete [] this->_p;
}

inline auto String::append (ElementType ch) noexcept -> String & {
    this->_alloc(1);

    this->_p[this->_l++] = ch;
    return * this;
}

inline auto String::append (StringLiteral cString) noexcept -> String & {
    if ( cString == nullptr ) return * this;

    auto len = strlen(cString);
    this->_alloc(len);

    for (int i = 0; i < len; ++i)
        this->_p[this->_l++] = cString[i];

    return * this;
}

inline auto String::append (String const & str) noexcept -> String & {
    this->_alloc(str._l);

    for ( ElementType e : str )
        this->_p[this->_l++] = e;

    return * this;
}

inline String::IteratorBase::IteratorBase(String & s, Index i) noexcept : _s ( & s ), _pos ( i ) {}
inline String::ConstIteratorBase::ConstIteratorBase(String const & s, Index i) noexcept : _s ( & s ), _pos ( i ) {}
inline String::Iterator::Iterator(String & s, Index i) noexcept : IteratorBase(s, i) {}
inline String::ConstIterator::ConstIterator(const String & s, Index i) noexcept : ConstIteratorBase(s, i) {}
inline String::ReverseIterator::ReverseIterator(String & s, Index i) noexcept : IteratorBase(s, i) {}
inline String::ConstReverseIterator::ConstReverseIterator(const String & s, Index i) noexcept : ConstIteratorBase(s, i) {}

inline auto String::begin() noexcept -> Iterator { return Iterator ( * this, 0 ); }
inline auto String::end () noexcept -> Iterator { return Iterator ( * this, this->_l ); }
inline auto String::begin() const noexcept -> ConstIterator { return ConstIterator ( * this, 0 ); }
inline auto String::end() const noexcept -> ConstIterator { return ConstIterator ( * this, this->_l ); }
inline auto String::cbegin() const noexcept -> ConstIterator { return ConstIterator ( * this, 0 ); }
inline auto String::cend() const noexcept -> ConstIterator { return ConstIterator ( * this, this->_l ); }
inline auto String::rbegin() noexcept -> ReverseIterator { return ReverseIterator( * this, this->_l - 1 ); }
inline auto String::rend() noexcept -> ReverseIterator { return ReverseIterator( * this, -1 ); }
inline auto String::rbegin() const noexcept -> ConstReverseIterator { return ConstReverseIterator( * this, this->_l - 1 ); }
inline auto String::rend() const noexcept -> ConstReverseIterator { return ConstReverseIterator( * this, -1 ); }
inline auto String::crbegin() const noexcept -> ConstReverseIterator { return ConstReverseIterator( * this, this->_l - 1 ); }
inline auto String::crend() const noexcept -> ConstReverseIterator { return ConstReverseIterator( * this, -1 ); }

inline auto String::operator [] (Index i) noexcept (false) -> ElementType & {
    if ( this->empty() )
        throw String::StringNullAccess();

    if ( i < 0 )
        i += ( (-i) / this->size() + 1 ) * this->size();
    if ( i >= static_cast<Index>(this->size()) )
        i = i % this->size();

    return this->_p[i];
}

inline auto String::operator [] (Index i) const noexcept -> ElementType {
    if ( this->empty() )
        return '\0';

    if ( i < 0 )
        i += ( (-i) / this->size() + 1 ) * this->size();
    if ( i >= static_cast<Index>(this->size()) )
        i = i % this->size();

    return this->_p[i];
}

inline String::String(const std::string & s) noexcept : CONSTR_CLEAR() {
    if ( s.empty() )
        return;

    this->_alloc(s.size());

    for ( auto e : s )
        this->_p[this->_l++] = e;
}

inline String::String(Size count, ElementType constant) noexcept : CONSTR_CLEAR() {
    if ( count == 0 )
        return;

    this->_alloc(count);
    std::memset(this->_p, constant, count);
    this->_l = count;
}

inline String::String(const std::initializer_list<ElementType> & list) noexcept : CONSTR_CLEAR() {
    if ( list.size() == 0 )
        return;

    this->_alloc(list.size());
    for ( auto e : list )
        this->_p[this->_l++] = e;
}

inline String::String(std::string::iterator const & begin, std::string::iterator const & end) noexcept : CONSTR_CLEAR() {
    if ( end - begin <= 0 )
        return;

    this->_alloc(end - begin);

    for ( auto it = begin; it != end; it++ )
        this->_p[this->_l++] = *it;
}

#pragma clang diagnostic push
#pragma ide diagnostic ignored "ConstantConditionsOC"
inline String::String(IteratorBase const & begin, IteratorBase const & end) noexcept : CONSTR_CLEAR() {
    bool reversed = dynamic_cast < Iterator const * > ( & begin ) == nullptr;
    if ( ! reversed && end - begin <= 0 || reversed && begin - end <= 0)
        return;
    this->_alloc(! reversed ? end - begin : begin - end);

    if ( ! reversed )
        for ( auto it = dynamic_cast < Iterator const & > ( begin ); it != end; it.next() )
            this->_p[this->_l++] = *it;
    else
        for ( auto it = dynamic_cast < ReverseIterator const & > ( begin ); it != end; it.next() )
            this->_p[this->_l++] = *it;
}
#pragma clang diagnostic pop

inline String::String(ConstIteratorBase const & begin, ConstIteratorBase const & end) noexcept : CONSTR_CLEAR() {
    bool reversed = dynamic_cast < ConstIterator const * > ( & begin ) == nullptr;
    if ( ! reversed && end - begin <= 0 || reversed && begin - end <= 0)
        return;
    this->_alloc(! reversed ? end - begin : begin - end);

    if ( ! reversed )
        for ( auto it = dynamic_cast < ConstIterator const & > ( begin ); it != end; it.next() )
            this->_p[this->_l++] = *it;
    else
        for ( auto it = dynamic_cast < ConstReverseIterator const & > ( begin ); it != end; it.next() )
            this->_p[this->_l++] = *it;
}

inline auto String::resize(Size size) noexcept -> void {
//    if ( this->empty() )
//        return;

    this->_c = size + 1;
    auto newArea = new ElementType [ this->_c ];

    if ( ! this->empty() ) {
        std::memcpy(newArea, this->_p, this->_c);
        delete[] this->_p;
    }

    this->_p = newArea;
    if ( this->_l >= this->_c )
        this->_l = this->_c - 1;
}

inline auto String::clear() noexcept -> void {
    if ( this->_p != nullptr )
        std::memset ( this->_p, 0, this->_l );
    this->_l = 0;
}

//#include <CDS/LinkedList>

inline String & String::operator= ( String const & o ) noexcept {
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

inline auto String::operator == ( String const & o ) const noexcept -> bool { return this->size() == o.size() && std::strcmp ( this->cStr(), o.cStr() ) == 0; }
inline auto String::operator == ( std::string const & stdString ) const noexcept -> bool { return std::strcmp ( this->cStr(), stdString.c_str() ) == 0; }
inline auto String::operator == ( StringLiteral cString ) const noexcept -> bool { return std::strcmp ( this->cStr(), cString ) == 0; }
inline auto String::operator >= ( String const & o ) const noexcept -> bool { return std::strcmp ( this->cStr(), o.cStr() ) >= 0; }
inline auto String::operator >= ( std::string const & stdString ) const noexcept -> bool { return std::strcmp ( this->cStr(), stdString.c_str() ) >= 0; }
inline auto String::operator >= ( StringLiteral cString ) const noexcept -> bool { return std::strcmp ( this->cStr(), cString ) >= 0; }
inline auto String::operator <= ( String const & o ) const noexcept -> bool { return std::strcmp ( this->cStr(), o.cStr() ) <= 0; }
inline auto String::operator <= ( std::string const & stdString ) const noexcept -> bool { return std::strcmp ( this->cStr(), stdString.c_str() ) <= 0; }
inline auto String::operator <= ( StringLiteral cString ) const noexcept -> bool { return std::strcmp ( this->cStr(), cString ) <= 0; }
inline auto String::operator != ( String const & o ) const noexcept -> bool { return this->size() != o.size() || std::strcmp ( this->cStr(), o.cStr() ) != 0; }
inline auto String::operator != ( std::string const & stdString ) const noexcept -> bool { return std::strcmp ( this->cStr(), stdString.c_str() ) != 0; }
inline auto String::operator != ( StringLiteral cString ) const noexcept -> bool { return std::strcmp ( this->cStr(), cString ) != 0; }
inline auto String::operator < ( String const & o ) const noexcept -> bool { return std::strcmp ( this->cStr(), o.cStr() ) < 0; }
inline auto String::operator < ( std::string const & stdString ) const noexcept -> bool { return std::strcmp ( this->cStr(), stdString.c_str() ) < 0; }
inline auto String::operator < ( StringLiteral cString ) const noexcept -> bool { return std::strcmp ( this->cStr(), cString ) < 0; }
inline auto String::operator > ( String const & o ) const noexcept -> bool { return std::strcmp ( this->cStr(), o.cStr() ) > 0; }
inline auto String::operator > ( std::string const & stdString ) const noexcept -> bool { return std::strcmp ( this->cStr(), stdString.c_str() ) > 0; }
inline auto String::operator > ( StringLiteral cString ) const noexcept -> bool { return std::strcmp ( this->cStr(), cString ) > 0; }

inline auto String::findFirst ( ElementType e ) const noexcept -> Index {
    Index i = 0;
    for ( auto c : (*this) )
        if ( c == e )
            return i;
        else
            i++;

    return INVALID_POS;
}

inline auto String::findFirst ( String const & o ) const noexcept -> Index {
    Index i = 0;
    for ( auto c : (*this) )
        if ( this->size() - i >= o.size() && this->substr( i, i + o.size() ) == o )
            return i;
        else
            i++;
    return INVALID_POS;
}

inline auto String::findLast ( ElementType e ) const noexcept -> Index {
    Index i = this->size() - 1;
    for ( auto it = this->rbegin(); it != this->rend(); it++ )
        if ( it.value() == e )
            return i;
        else
            i--;
    return INVALID_POS;
}

inline auto String::findLast ( String const & o ) const noexcept -> Index {
    Index i = this->size() - o.length();
    for ( i; i >= 0; i-- )
        if ( this->substr(i, i + o.length()) == o )
            return i;

    return INVALID_POS;
}

inline auto String::findFirstOf ( String const & o ) const noexcept -> Index {
    Index i = 0;
    for ( auto e : (*this) )
        if ( o.contains(e) )
            return i;
        else
            i++;
    return INVALID_POS;
}

inline auto String::findFirstNotOf ( String const & o ) const noexcept -> Index {
    Index i = 0;
    for ( auto e : (*this) )
        if ( ! o.contains(e) )
            return i;
        else
            i++;
    return INVALID_POS;
}

inline auto String::findLastOf ( String const & o ) const noexcept -> Index {
    Index i = this->size() - 1;
    for ( auto it = this->rbegin(); it != this->rend(); it++ )
        if ( o.contains(it.value()) )
            return i;
        else
            i--;
    return INVALID_POS;
}

inline auto String::findLastNotOf ( String const & o ) const noexcept -> Index {
    Index i = this->size() - 1;
    for ( auto it = this->rbegin(); it != this->rend(); it++ )
        if ( ! o.contains(it.value()) )
            return i;
        else
            i--;
    return INVALID_POS;
}

inline auto String::substr(Index from, Index to) const noexcept -> String {
    if ( to == -1 || to > static_cast<Index>(this->size()) )
        to = this->size();
    if ( from < 0 )
        from = 0;

    String s;
    for ( Index i = from; i < to; i++ )
        s += this->_p[i];

    return s;
}


inline auto String::ltrim ( ElementType e ) noexcept -> String & {
    while ( ! this->empty () && this->front() == e )
        * this = this->substr( 1 );
    return * this;
}

inline auto String::ltrim ( String const & s ) noexcept -> String & {
    while ( ! this->empty () && s.contains( this->front() ) )
        * this = this->substr(1);
    return * this;
}

inline auto String::rtrim ( ElementType e ) noexcept -> String & {
    while ( ! this->empty () && this->back() == e )
        this->_p[--this->_l] = '\0';

    return * this;
}

inline auto String::rtrim ( String const & s ) noexcept -> String & {
    while ( ! this->empty () && s.contains(this->back()) )
        this->_p[--this->_l] = '\0';

    return * this;
}

#ifndef NDEBUG
inline auto String::diag() const noexcept -> String {
    return String("Debug = { data = '") + this->_p + "', length = " + this->_l + ", capacity = " + this->_c + " }";
}
#endif

inline auto String::rjust(Size justifySize, ElementType padChar) noexcept -> String & {
    while ( this->size() < justifySize )
        this->append(padChar);

    return * this;
}

inline auto String::ljust(Size justifySize, ElementType padChar) noexcept -> String & {
    while ( this->size() < justifySize )
        this->prepend(padChar);

    return * this;
}

inline auto String::replace(Index pos, Size len, const String & newInPlace) noexcept -> String & {
    String left = this->substr(0, pos);
    String right = this->substr(pos + len);

    return ( * this = left + newInPlace + right );
}

inline auto String::reversed() const noexcept -> String {
    return {this->rbegin(), this->rend()};
}

inline auto String::operator * (int count) const noexcept -> String {
    String res;
    for ( int i = 0; i < count; i ++ )
        res += (*this);
    return res;
}

#undef CONSTR_CLEAR

#include <CDS/Types>

namespace dataTypes {
    template<> auto hash<String>(String const &o) noexcept -> Index { return o.length(); }
}

#endif //CDS_STRING_HPP
