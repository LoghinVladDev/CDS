//
// Created by loghin on 22.01.2021.
//

#ifndef CDS_STRING_HPP
#define CDS_STRING_HPP

//#include <CDS/String>
#include <ostream>
#include <string>

#include <CDS/Concepts>

#include "../collection/ordered/LinkedListPublic.hpp"

template < typename T >
//#if defined(__cpp_concepts)
//    requires Iterable < T >
//#endif
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

    /**
     * @test testcase not required
     */
    ~String() noexcept;


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
    inline auto operator += (CDS_sint16 v) noexcept -> String & { return this->operator+=(std::to_string(v) ); }

    /**
     * @test tested in primitive/StringTest/Append/Prepend Tests
     */
    inline auto operator += (CDS_sint32 v) noexcept -> String & { return this->operator+=(std::to_string(v) ); }

    /**
     * @test tested in primitive/StringTest/Append/Prepend Tests
     */
    inline auto operator += (CDS_sint64 v) noexcept -> String & { return this->operator+=(std::to_string(v) ); }

    /**
     * @test tested in primitive/StringTest/Append/Prepend Tests
     */
    inline auto operator += (CDS_uint8 v) noexcept -> String & { return this->operator+=(std::to_string(v) ); }

    /**
     * @test tested in primitive/StringTest/Append/Prepend Tests
     */
    inline auto operator += (CDS_uint16 v) noexcept -> String & { return this->operator+=(std::to_string(v) ); }

    /**
     * @test tested in primitive/StringTest/Append/Prepend Tests
     */
    inline auto operator += (CDS_uint32 v) noexcept -> String & { return this->operator+=(std::to_string(v) ); }

    /**
     * @test tested in primitive/StringTest/Append/Prepend Tests
     */
    inline auto operator += (CDS_uint64 v) noexcept -> String & { return this->operator+=(std::to_string(v) ); }

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
    inline auto append (CDS_sint16 v) noexcept -> String & { return this->append(std::to_string(v) ); }

    /**
     * @test tested in primitive/StringTest/Append/Prepend Tests
     */
    inline auto append (CDS_sint32 v) noexcept -> String & { return this->append(std::to_string(v) ); }

    /**
     * @test tested in primitive/StringTest/Append/Prepend Tests
     */
    inline auto append (CDS_sint64 v) noexcept -> String & { return this->append(std::to_string(v) ); }

    /**
     * @test tested in primitive/StringTest/Append/Prepend Tests
     */
    inline auto append (CDS_uint8 v) noexcept -> String & { return this->append(std::to_string(v) ); }

    /**
     * @test tested in primitive/StringTest/Append/Prepend Tests
     */
    inline auto append (CDS_uint16 v) noexcept -> String & { return this->append(std::to_string(v) ); }

    /**
     * @test tested in primitive/StringTest/Append/Prepend Tests
     */
    inline auto append (CDS_uint32 v) noexcept -> String & { return this->append(std::to_string(v) ); }

    /**
     * @test tested in primitive/StringTest/Append/Prepend Tests
     */
    inline auto append (CDS_uint64 v) noexcept -> String & { return this->append(std::to_string(v) ); }

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
    inline auto prepend (CDS_sint16 v) noexcept -> String & { return this->prepend(std::to_string(v) ); }

    /**
     * @test tested in primitive/StringTest/Append/Prepend Tests
     */
    inline auto prepend (CDS_sint32 v) noexcept -> String & { return this->prepend(std::to_string(v) ); }

    /**
     * @test tested in primitive/StringTest/Append/Prepend Tests
     */
    inline auto prepend (CDS_sint64 v) noexcept -> String & { return this->prepend(std::to_string(v) ); }

    /**
     * @test tested in primitive/StringTest/Append/Prepend Tests
     */
    inline auto prepend (CDS_uint8 v) noexcept -> String & { return this->prepend(std::to_string(v) ); }

    /**
     * @test tested in primitive/StringTest/Append/Prepend Tests
     */
    inline auto prepend (CDS_uint16 v) noexcept -> String & { return this->prepend(std::to_string(v) ); }

    /**
     * @test tested in primitive/StringTest/Append/Prepend Tests
     */
    inline auto prepend (CDS_uint32 v) noexcept -> String & { return this->prepend(std::to_string(v) ); }

    /**
     * @test tested in primitive/StringTest/Append/Prepend Tests
     */
    inline auto prepend (CDS_uint64 v) noexcept -> String & { return this->prepend(std::to_string(v) ); }

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
    [[nodiscard]] inline auto operator + (CDS_sint16 v) const noexcept -> String { return this->operator+(std::to_string(v) ); }

    /**
     * @test tested in primitive/StringTest/Append/Prepend Tests
     */
    [[nodiscard]] inline auto operator + (CDS_sint32 v) const noexcept -> String { return this->operator+(std::to_string(v) ); }

    /**
     * @test tested in primitive/StringTest/Append/Prepend Tests
     */
    [[nodiscard]] inline auto operator + (CDS_sint64 v) const noexcept -> String { return this->operator+(std::to_string(v) ); }

    /**
     * @test tested in primitive/StringTest/Append/Prepend Tests
     */
    [[nodiscard]] inline auto operator + (CDS_uint8 v) const noexcept -> String { return this->operator+(std::to_string(v) ); }

    /**
     * @test tested in primitive/StringTest/Append/Prepend Tests
     */
    [[nodiscard]] inline auto operator + (CDS_uint16 v) const noexcept -> String { return this->operator+(std::to_string(v) ); }

    /**
     * @test tested in primitive/StringTest/Append/Prepend Tests
     */
    [[nodiscard]] inline auto operator + (CDS_uint32 v) const noexcept -> String { return this->operator+(std::to_string(v) ); }

    /**
     * @test tested in primitive/StringTest/Append/Prepend Tests
     */
    [[nodiscard]] inline auto operator + (CDS_uint64 v) const noexcept -> String { return this->operator+(std::to_string(v) ); }

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

#endif //CDS_STRING_HPP
