//
// Created by loghin on 22.01.2021.
//

#ifndef CDS_STRING_HPP
#define CDS_STRING_HPP

#include <ostream>
#include <string>

#include <CDS/Concepts>

#include "../collection/ordered/LinkedListPublic.hpp"

#if defined(CDS_QT)
#include <QString>
#endif

#include <CDS/Object>

/**
 * @class String, represents a String object, ascii encoded
 */
class String final : public Object {
public:
    /**
     * @brief Represents an element in the string, char by default, done for future feature compatibility ( widechar support )
     */
    typedef char ElementType;

    /**
     * @class Exception thrown when accessing any index of a null String Object
     */
    class StringNullAccess : public std::exception {

        /**
         * @brief Function used to obtain the Exception's message
         *
         * @exceptsafe
         *
         * @return StringLiteral = Message as C String Literal
         */
        __CDS_NoDiscard auto what() const noexcept -> StringLiteral override {
            return "Null Access Exception : Requested Reference to Element at Index 0 for Empty String.";
        }
    };
private:

    /**
     * @brief Address to the data containing the Object's characters
     */
    CString _p {nullptr};

    /**
     * @brief Amount of characters until the String's terminating character ( until '\0' )
     */
    Size _l    {0ull};

    /**
     * @brief Allocated size at Address _p, in bytes
     */
    Size _c    {0ull};

    /**
     * @brief Private Function used to allocate more bytes to the String Object, keeping its' original contents
     *
     * @exceptsafe
     *
     * @test Does not require testing
     */
    void _alloc(Size) noexcept;

    /**
     * @class String::IteratorBase, Base of String Iterators, containing common functions
     */
    class IteratorBase;

    /**
     * @class String::ConstIteratorBase, Base of String ConstIterators, containing common functions
     */
    class ConstIteratorBase;
public:

    /**
     * @class String::Iterator, forward iterator over a mutable String object
     */
    class Iterator;

    /**
     * @class String::ConstIterator, forward iterator over an immutable String object
     */
    class ConstIterator;

    /**
     * @class String::Iterator, backwards iterator over a mutable String object
     */
    class ReverseIterator;

    /**
     * @class String::Iterator, backwards iterator over an immutable String object
     */
    class ConstReverseIterator;

    /**
     * @brief Default Constructor
     *
     * @exceptsafe
     *
     * @test tested in primitive/StringTest/Constructor Tests
     */
    String () noexcept = default;

    /**
     * @brief Copy Constructor
     *
     * @param s : String cref = Constant Reference to the String to copy from
     *
     * @exceptsafe
     *
     * @test tested in primitive/StringTest/Constructor Tests
     */
    String (String const &) noexcept;
    //TODO : implement later
//    explicit String (String const &, Index, Size = UINT64_MAX) noexcept;

    /**
     * @brief Constructor with given String Literal
     *
     * @param cString : StringLiteral = pointer to copy data from
     *
     * @exceptsafe
     *
     * @test tested in primitive/StringTest/Constructor Tests
     */
    String(StringLiteral) noexcept; // NOLINT(google-explicit-constructor)

    /**
     * @brief Constructor with given C String value ( char * )
     *
     * @param cString : CString = pointer to copy data from
     *
     * @exceptsafe
     *
     * @test tested in primitive/StringTest/Constructor Tests
     */
    String(CString) noexcept; // NOLINT(google-explicit-constructor)
//    explicit String(StringLiteral, Index, Size = UINT64_MAX) noexcept;

    /**
     * @brief Constructor with given std::string
     *
     * @param s : std::string cref = Constant Reference to the std::string to copy from
     *
     * @exceptsafe
     *
     * @test tested in primitive/StringTest/Constructor Tests
     */
    String(std::string const &) noexcept; // NOLINT(google-explicit-constructor)
//    explicit String(std::string const &, Index, Size = UINT64_MAX) noexcept;

    /**
     * @brief Constructor which initializes string with a number of given characters
     *
     * @param count : Size = number of characters to initialize with [constant]
     * @param constant : ElementType = character to initialize [count] positions with
     *
     * @exceptsafe
     *
     * @test tested in primitive/StringTest/Constructor Tests
     */
    String(Size, ElementType) noexcept;

    /**
     * @brief Constructor which initializes String from characters between the two given iterators
     *
     * @param begin : std::string::iterator cref = Constant Reference to the iterator to begin from
     * @param end : std::string::iterator cref = Constant REference to the iterator to end at
     *
     * @exceptsafe
     *
     * @test tested in primitive/StringTest/Constructor Tests
     */
    String(std::string::iterator const &, std::string::iterator const &) noexcept;

    /**
     * @brief Constructor which initializes String from characters between two given String iterator bases
     *
     * @param begin : String::IteratorBase cref = Constant Reference to the iterator to begin from
     * @param end : String::IteratorBase cref = Constant Reference to the iterator to end at
     *
     * @exceptsafe
     *
     * @test tested in primitive/StringTest/Constructor Tests
     */
    String(IteratorBase const &, IteratorBase const &) noexcept;

    /**
     * @brief Constructor which initializes String from characters between two given String const iterator bases
     *
     * @param begin : String::ConstIteratorBase cref = Constant Reference to the const iterator to begin from
     * @param end : String::ConstIteratorBase cref = Constant Reference to the const iterator to end at
     *
     * @exceptsafe
     *
     * @test tested in primitive/StringTest/Constructor Tests
     */
    String(ConstIteratorBase const &, ConstIteratorBase const &) noexcept;

    /**
     * @brief Constructor which initializes String from characters in a given std::initializer_list
     *
     * @param list : std::initializer_list < ElementType > cref = Constant Reference to the initializer_list containing the characters to add
     *
     * @exceptsafe
     *
     * @test tested in primitive/StringTest/Constructor Tests
     */
    String(std::initializer_list<ElementType> const &) noexcept;

#if defined(CDS_QT)

    /**
     * @brief Constructor which initializes String from a QString
     *
     * @param o : QString cref = Constant Reference to the QString to construct from
     *
     * @exceptsafe
     *
     * @test tested in MSK
     */
    String(QString const & o) noexcept : String(o.toStdString()) {}
#endif

    /**
     * @brief Constructor which initializes String from a CDS/Object's String representation
     *
     * @param o : Object cref = Constant Reference to a CDS/Object
     *
     * @exceptsafe
     *
     * @test tested in primitive/StringTest/Constructor Tests
     */
    String (Object const & o) noexcept : String(o.toString()) { } // NOLINT(google-explicit-constructor)

    /**
     * @brief Constructor which initializes String from a raw uint8 value
     *
     * @param v : uint8 = Value to represent in the String
     *
     * @exceptsafe
     *
     * @test tested in primitive/StringTest/Constructor Tests
     */
    String (uint8 v) noexcept : String(String().append(v)) { } // NOLINT(google-explicit-constructor)

    /**
     * @brief Constructor which initializes String from a raw uint16 value
     *
     * @param v : uint16 = Value to represent in the String
     *
     * @exceptsafe
     *
     * @test tested in primitive/StringTest/Constructor Tests
     */
    String (uint16 v) noexcept : String(String().append(v)) { } // NOLINT(google-explicit-constructor)

    /**
     * @brief Constructor which initializes String from a raw uint32 value
     *
     * @param v : uint32 = Value to represent in the String
     *
     * @exceptsafe
     *
     * @test tested in primitive/StringTest/Constructor Tests
     */
    String (uint32 v) noexcept : String(String().append(v)) { } // NOLINT(google-explicit-constructor)

    /**
     * @brief Constructor which initializes String from a raw uint64 value
     *
     * @param v : uint64 = Value to represent in the String
     *
     * @exceptsafe
     *
     * @test tested in primitive/StringTest/Constructor Tests
     */
    String (uint64 v) noexcept : String(String().append(v)) { } // NOLINT(google-explicit-constructor)

    /**
     * @brief Constructor which initializes String from a raw sint8 value
     *
     * @param v : sint8 = Value to represent in the String
     *
     * @exceptsafe
     *
     * @test tested in primitive/StringTest/Constructor Tests
     */
    String (sint8 v) noexcept : String(String().append(v)) { } // NOLINT(google-explicit-constructor)

    /**
     * @brief Constructor which initializes String from a raw sint16 value
     *
     * @param v : sint16 = Value to represent in the String
     *
     * @exceptsafe
     *
     * @test tested in primitive/StringTest/Constructor Tests
     */
    String (sint16 v) noexcept : String(String().append(v)) { } // NOLINT(google-explicit-constructor)

    /**
     * @brief Constructor which initializes String from a raw sint32 value
     *
     * @param v : sint32 = Value to represent in the String
     *
     * @exceptsafe
     *
     * @test tested in primitive/StringTest/Constructor Tests
     */
    String (sint32 v) noexcept : String(String().append(v)) { } // NOLINT(google-explicit-constructor)

    /**
     * @brief Constructor which initializes String from a raw sint64 value
     *
     * @param v : sint64 = Value to represent in the String
     *
     * @exceptsafe
     *
     * @test tested in primitive/StringTest/Constructor Tests
     */
    String (sint64 v) noexcept : String(String().append(v)) { } // NOLINT(google-explicit-constructor)

    /**
     * @brief Constructor which initializes String from a raw float value
     *
     * @param v : float = Value to represent in the String
     *
     * @exceptsafe
     *
     * @test tested in primitive/StringTest/Constructor Tests
     */
    String (float v) noexcept : String(String().append(v)) { } // NOLINT(google-explicit-constructor)

    /**
     * @brief Constructor which initializes String from a raw double value
     *
     * @param v : double = Value to represent in the String
     *
     * @exceptsafe
     *
     * @test tested in primitive/StringTest/Constructor Tests
     */
    String (double v) noexcept : String(String().append(v)) { } // NOLINT(google-explicit-constructor)

#if defined(__linux)

    /**
     * @brief Constructor which initializes String from a raw std::size_t value
     *
     * @param v : std::size_t = Value to represent in the String
     *
     * @exceptsafe
     *
     * @test tested in primitive/StringTest/Constructor Tests
     */
    String(std::size_t v) noexcept : String((uint64)v) {} // NOLINT(google-explicit-constructor)

#endif

    /**
     * @brief Constructor which initializes String from a raw pointer value
     *
     * @tparam T = type of object at the given address
     * @param v : T ptr = Value to represent in the String
     *
     * @exceptsafe
     *
     * @test tested in primitive/StringTest/Constructor Tests
     */
    template < typename T >
    String (T * v) noexcept : String((std::size_t)v) { } // NOLINT(google-explicit-constructor)

    /**
     * @brief Constructor which initializes String from a raw constant pointer value
     *
     * @tparam T = type of object at the given address
     * @param v : T cptr = Value to represent in the String
     *
     * @exceptsafe
     *
     * @test tested in primitive/StringTest/Constructor Tests
     */
    template < typename T >
    String (T const * v) noexcept : String((std::size_t)v) { } // NOLINT(google-explicit-constructor)

//    String (std::size_t v) noexcept : String((uint64)v) {}

#if defined(CDS_GLM)

    /**
     * @brief Constructor which initializes String from a glm::vec object
     *
     * @tparam l : glm::length_t = size of the vector
     * @tparam T = type of the elements in the vector
     * @tparam q : glm::qualifier = operation speed qualifier for the vector
     *
     * @param v : glm::vec < l, T, q > cref = Constant Reference to the vector to construct the String from
     *
     * @exceptsafe
     *
     * @test tested in LoghinVladDev/c-eng
     */
    template < glm::length_t l, typename T, glm::qualifier q >
    String ( glm::vec < l, T, q > const & v ) noexcept {
        * this = String ("glm::vec") + static_cast < uint32 > (l) + " { ";

        if constexpr ( l == 1 ) { this->append("x = ").append(v.x); }
        if constexpr ( l == 2 ) { this->append(", y = ").append(v.y); }
        if constexpr ( l == 3 ) { this->append(", z = ").append(v.z); }
        if constexpr ( l == 4 ) { this->append(", w = ").append(v.w); }

        * this += " }";
    }

#endif

    /**
     * @brief Destructor
     *
     * @exceptsafe
     *
     * @test testcase not required
     */
    ~String() noexcept override;


    /**
     * @brief Function used to obtain an Iterator to the first element in the String
     *
     * @exceptsafe
     *
     * @returns Iterator
     *
     * @test tested in primitive/StringTest/Iterator Tests
     */
    __CDS_NoDiscard auto begin() noexcept -> Iterator;

    /**
     * @brief Function used to obtain an Iterator to the position past the last element in the String
     *
     * @exceptsafe
     *
     * @returns Iterator
     *
     * @test tested in primitive/StringTest/Iterator Tests
     */
    __CDS_NoDiscard auto end () noexcept -> Iterator;

    /**
     * @brief Function used to obtain a ConstIterator to the first element in the String
     *
     * @exceptsafe
     *
     * @returns ConstIterator
     *
     * @test tested in primitive/StringTest/Iterator Tests
     */
    __CDS_NoDiscard auto begin() const noexcept -> ConstIterator;

    /**
     * @brief Function used to obtain an ConstIterator to the position past the last element in the String
     *
     * @exceptsafe
     *
     * @returns ConstIterator
     *
     * @test tested in primitive/StringTest/Iterator Tests
     */
    __CDS_NoDiscard auto end() const noexcept -> ConstIterator;

    /**
     * @brief Function used to obtain a ConstIterator to the first element in the String
     *
     * @exceptsafe
     *
     * @returns ConstIterator
     *
     * @test tested in primitive/StringTest/Iterator Tests
     */
    __CDS_NoDiscard auto cbegin() const noexcept -> ConstIterator;

    /**
     * @brief Function used to obtain an ConstIterator to the position past the last element in the String
     *
     * @exceptsafe
     *
     * @returns ConstIterator
     *
     * @test tested in primitive/StringTest/Iterator Tests
     */
    __CDS_NoDiscard auto cend() const noexcept -> ConstIterator;


    /**
     * @brief Function used to obtain a ReverseIterator to the position past the last element in the String
     *
     * @exceptsafe
     *
     * @returns ReverseIterator
     *
     * @test tested in primitive/StringTest/Iterator Tests
     */
    __CDS_NoDiscard auto rbegin() noexcept -> ReverseIterator;

    /**
     * @brief Function used to obtain a ReverseIterator to the first element in the String
     *
     * @exceptsafe
     *
     * @returns ReverseIterator
     *
     * @test tested in primitive/StringTest/Iterator Tests
     */
    __CDS_NoDiscard auto rend() noexcept -> ReverseIterator;

    /**
     * @brief Function used to obtain a ConstReverseIterator to the position past the last element in the String
     *
     * @exceptsafe
     *
     * @returns ConstReverseIterator
     *
     * @test tested in primitive/StringTest/Iterator Tests
     */
    __CDS_NoDiscard auto rbegin() const noexcept -> ConstReverseIterator;

    /**
     * @brief Function used to obtain a ConstReverseIterator to the first element in the String
     *
     * @exceptsafe
     *
     * @returns ConstReverseIterator
     *
     * @test tested in primitive/StringTest/Iterator Tests
     */
    __CDS_NoDiscard auto rend() const noexcept -> ConstReverseIterator;

    /**
     * @brief Function used to obtain a ConstReverseIterator to the position past the last element in the String
     *
     * @exceptsafe
     *
     * @returns ConstReverseIterator
     *
     * @test tested in primitive/StringTest/Iterator Tests
     */
    __CDS_NoDiscard auto crbegin() const noexcept -> ConstReverseIterator;

    /**
     * @brief Function used to obtain a ConstReverseIterator to the first element in the String
     *
     * @exceptsafe
     *
     * @returns ConstReverseIterator
     *
     * @test tested in primitive/StringTest/Iterator Tests
     */
    __CDS_NoDiscard auto crend() const noexcept -> ConstReverseIterator;


    /**
     * @brief Function used to obtain the number of characters in the String
     *
     * @exceptsafe
     *
     * @returns Size = size of the String
     *
     * @test tested in primitive/StringTest/Property Tests
     */
    __CDS_NoDiscard constexpr inline auto size() const noexcept -> Size { return this->_l; }

    /**
     * @brief Function used to obtain the number of characters in the String
     *
     * @exceptsafe
     *
     * @returns Size = size of the String
     *
     * @test tested in primitive/StringTest/Property Tests
     */
    __CDS_NoDiscard constexpr inline auto length() const noexcept -> Size { return this->_l; }

    /**
     * @brief Function used to obtain the allocated memory size in bytes
     *
     * @exceptsafe
     *
     * @returns Size = size of the buffer
     *
     * @test tested in primitive/StringTest/Property Tests
     */
    __CDS_NoDiscard __CDS_MaybeUnused constexpr inline auto maxSize() const noexcept -> Size { return this->_c; }

    /**
     * @brief Function used to obtain the allocated memory size in bytes
     *
     * @exceptsafe
     *
     * @returns Size = size of the buffer
     *
     * @test tested in primitive/StringTest/Property Tests
     */
    __CDS_NoDiscard constexpr inline auto capacity() const noexcept -> Size { return this->_c; }


    /**
     * @brief Function used to resize the String to a given size
     *
     * @param size : Size = size to resize the String to
     *
     * @exceptsafe
     *
     * @test tested in primitive/StringTest/Memory Tests
     */
    auto resize(Size) noexcept -> void; //{ this->_alloc( s ); }

    /**
     * @brief Function used to enlarge the String's capacity to a required size, but not capable of shrinking it, if it is bigger
     *
     * @param s : Size = target size for the String
     *
     * @exceptsafe
     *
     * @test tested in primitive/StringTest/Memory Tests
     */
    inline auto reserve(Size s) noexcept -> void { if ( s < this->_c ) return; this->resize( s ); }

    /**
     * @brief Function used to shrink the String's capacity, but not capable of enlarging it, if given size is greater than capacity
     * If no parameters are given, it shrinks to the least possible capacity, its' length
     *
     * @param s : SignedSize = target size to shrink at. If left default (-1), it will shrink to length
     *
     * @exceptsafe
     *
     * @test tested in primitive/StringTest/Memory Tests
     */
    inline auto shrink(SignedSize s = -1) noexcept -> void { if ( s == -1 ) s = static_cast < SignedSize > ( this->_l ); if ( s > this->_c ) return; this->resize( s ); }

    /**
     * @brief Function used to clear the contents of the String
     *
     * @exceptsafe
     *
     * @test tested in primitive/StringTest/Content Functions Tests
     */
    auto clear() noexcept -> void;

    /**
     * Function returns true if the String's contents are empty, false otherwise
     *
     * @exceptsafe
     *
     * @returns bool = true if empty, false otherwise
     *
     * @test tested in primitive/StringTest/Content Functions Tests
     */
    __CDS_NoDiscard constexpr inline auto empty() const noexcept -> bool { return this->_l == 0; }


    /**
     * Get Operator used to acquire element at given index, behaves circularly ( if given index > length, it loops around, from the start )
     *
     * @param i : Index = index to acquire element from
     *
     * @throws String::StringNullAccess() if used on an empty String
     *
     * @returns ElementType ref = Reference to the element at given index
     *
     * @test tested in primitive/StringTest/Content Functions Tests
     */
    auto operator [] (Index) noexcept (false) -> ElementType &;

    /**
     * @brief Get Operator used to acquire element value at given index, behaves circularly
     *
     * @param i : Index = index to acquire value from
     *
     * @exceptsafe
     *
     * @returns ElementType = Value of the element at given index
     *
     * @test tested in primitive/StringTest/Content Functions Tests
     */
    __CDS_NoDiscard auto operator [] (Index) const noexcept -> ElementType;

    /**
     * @brief Explicit Get Function used to acquire element at given index, behaves circularly, calls operator []
     *
     * @param i : Index = index to acquire element from
     *
     * @throws String::StringNullAccess() if used on an empty String
     *
     * @returns ElementType ref = Reference to the element at given index
     *
     * @test If operator [] has a test, function is tested
     */
    __CDS_MaybeUnused inline auto at (Index i) noexcept (false) -> ElementType & { return this->operator[](i); }

    /**
     * @brief Get Operator used to acquire element value at given index, behaves circularly, calls operator []
     *
     * @param i : Index = index to acquire value from
     *
     * @exceptsafe
     *
     * @returns ElementType = Value of the element at given index
     *
     * @test tested in primitive/StringTest/Content Functions Tests
     */
    __CDS_NoDiscard __CDS_MaybeUnused inline auto at (Index i) const noexcept -> ElementType { return this->operator[](i); }

    /**
     * @brief Explicit Get Function used to acquire element at given index, behaves circularly, calls operator []
     *
     * @param i : Index = index to acquire element from
     *
     * @throws String::StringNullAccess() if used on an empty String
     *
     * @returns ElementType ref = Reference to the element at given index
     *
     * @test If operator [] has a test, function is tested
     */
    inline auto get (Index i) noexcept (false) -> ElementType & { return this->operator[](i); }

    /**
     * @brief Get Operator used to acquire element value at given index, behaves circularly, calls operator []
     *
     * @param i : Index = index to acquire value from
     *
     * @exceptsafe
     *
     * @returns ElementType = Value of the element at given index
     *
     * @test tested in primitive/StringTest/Content Functions Tests
     */
    __CDS_NoDiscard inline auto get (Index i) const noexcept -> ElementType { return this->operator[](i); }

    /**
     * @brief Function used to acquire element at the front of the String
     *
     * @throws String::StringNullAccess() if used on an empty String
     *
     * @returns ElementType ref = Reference to the first element in the String
     *
     * @test If operator [] has a test, function is tested
     */
    inline auto front () noexcept (false) -> ElementType & { return this->operator[](0); }

    /**
     * @brief Function used to acquire the last element in the String
     *
     * @throws String::StringNullAccess() if used on an empty String
     *
     * @returns ElementType ref = Reference to the last element in the String
     *
     * @test If operator [] has a test, function is tested
     */
    inline auto back () noexcept (false) -> ElementType & { return this->operator[](static_cast < Index > (this->_l) - 1); }

    /**
     * @brief Function used to acquire the value of the first element in the String, if any. Returns '\0' if empty
     *
     * @exceptsafe
     *
     * @returns ElementType = Value of the first element, or '\0' if empty
     *
     * @test If operator [] has a test, function is tested
     */
    __CDS_NoDiscard constexpr inline auto front() const noexcept -> ElementType { return this->empty() ? '\0' : this->_p[0]; }

    /**
     * @brief Function used to acquire the value of the last element in the String, if any. Returns '\0' if empty
     *
     * @exceptsafe
     *
     * @returns ElementType = Value of the first element, or '\0' if empty
     *
     * @test If operator [] has a test, function is tested
     */
    __CDS_NoDiscard constexpr inline auto back() const noexcept -> ElementType { return this->empty() ? '\0' : this->_p[this->_l - 1]; }

    /**
     * @brief Accumulate operator used to append an ElementType to the String
     *
     * @param v : ElementType = Value to add to the end of the String
     *
     * @exceptsafe
     *
     * @returns String ref = Reference to the modified String
     *
     * @test tested in primitive/StringTest/Append/Prepend Tests
     */
    inline auto operator += (ElementType v) noexcept -> String & { return this->append( v ); }

    /**
     * @brief Accumulate operator used to append a StringLiteral to the String
     *
     * @param v : StringLiteral = Address to a StringLiteral to add to the end of the String
     *
     * @exceptsafe
     *
     * @returns String ref = Reference to the modified String
     *
     * @test tested in primitive/StringTest/Append/Prepend Tests
     */
    inline auto operator += (StringLiteral v) noexcept -> String & { return this->append( v ); }

    /**
     * @brief Accumulate operator used to append a CString to the String
     *
     * @param v : CString = Address to a CString to add to the end of the String
     *
     * @exceptsafe
     *
     * @returns String ref = Reference to the modified String
     *
     * @test tested in primitive/StringTest/Append/Prepend Tests
     */
    inline auto operator += (CString v) noexcept -> String & { return this->append( v ); }

    /**
     * @brief Accumulate operator used to append a String to the String
     *
     * @param v : String cref = Constant Reference to the String to add at the end of the String
     *
     * @exceptsafe
     *
     * @returns String ref = Reference to the modified String
     *
     * @test tested in primitive/StringTest/Append/Prepend Tests
     */
    inline auto operator += (String const & v) noexcept -> String & { return this->append( v ); }

    /**
     * @brief Accumulate operator used to append a std::string to the String
     *
     * @param v : std::string cref = Constant Reference to the std::string to add at the end of the String
     *
     * @exceptsafe
     *
     * @returns String ref = Reference to the modified String
     *
     * @test tested in primitive/StringTest/Append/Prepend Tests
     */
    inline auto operator += (std::string const & v) noexcept -> String & { return this->append( v ); }

    /**
     * @brief Accumulate operator used to append a sint16 to the String
     *
     * @param v : sint16 = value to add at the end of the String
     *
     * @exceptsafe
     *
     * @returns String ref = Reference to the modified String
     *
     * @test tested in primitive/StringTest/Append/Prepend Tests
     */
    inline auto operator += (sint16 v) noexcept -> String & { return this->operator+=(std::to_string(v) ); }

    /**
     * @brief Accumulate operator used to append a sint32 to the String
     *
     * @param v : sint32 = value to add at the end of the String
     *
     * @exceptsafe
     *
     * @returns String ref = Reference to the modified String
     *
     * @test tested in primitive/StringTest/Append/Prepend Tests
     */
    inline auto operator += (sint32 v) noexcept -> String & { return this->operator+=(std::to_string(v) ); }

    /**
     * @brief Accumulate operator used to append a sint64 to the String
     *
     * @param v : sint64 = value to add at the end of the String
     *
     * @exceptsafe
     *
     * @returns String ref = Reference to the modified String
     *
     * @test tested in primitive/StringTest/Append/Prepend Tests
     */
    inline auto operator += (sint64 v) noexcept -> String & { return this->operator+=(std::to_string(v) ); }

    /**
     * @brief Accumulate operator used to append a uint8 to the String
     *
     * @param v : uint8 = value to add at the end of the String
     *
     * @exceptsafe
     *
     * @returns String ref = Reference to the modified String
     *
     * @test tested in primitive/StringTest/Append/Prepend Tests
     */
    inline auto operator += (uint8 v) noexcept -> String & { return this->operator+=(std::to_string(v) ); }

    /**
     * @brief Accumulate operator used to append a uint16 to the String
     *
     * @param v : uint16 = value to add at the end of the String
     *
     * @exceptsafe
     *
     * @returns String ref = Reference to the modified String
     *
     * @test tested in primitive/StringTest/Append/Prepend Tests
     */
    inline auto operator += (uint16 v) noexcept -> String & { return this->operator+=(std::to_string(v) ); }

    /**
     * @brief Accumulate operator used to append a uint32 to the String
     *
     * @param v : uint32 = value to add at the end of the String
     *
     * @exceptsafe
     *
     * @returns String ref = Reference to the modified String
     *
     * @test tested in primitive/StringTest/Append/Prepend Tests
     */
    inline auto operator += (uint32 v) noexcept -> String & { return this->operator+=(std::to_string(v) ); }

    /**
     * @brief Accumulate operator used to append a uint64 to the String
     *
     * @param v : uint64 = value to add at the end of the String
     *
     * @exceptsafe
     *
     * @returns String ref = Reference to the modified String
     *
     * @test tested in primitive/StringTest/Append/Prepend Tests
     */
    inline auto operator += (uint64 v) noexcept -> String & { return this->operator+=(std::to_string(v) ); }

    /**
     * @brief Accumulate operator used to append a float to the String
     *
     * @param v : float = value to add at the end of the String
     *
     * @exceptsafe
     *
     * @returns String ref = Reference to the modified String
     *
     * @test tested in primitive/StringTest/Append/Prepend Tests
     */
    inline auto operator += (float v) noexcept -> String & { return this->operator+=( std::to_string(v) ); }

    /**
     * @brief Accumulate operator used to append a double to the String
     *
     * @param v : double = value to add at the end of the String
     *
     * @exceptsafe
     *
     * @returns String ref = Reference to the modified String
     *
     * @test tested in primitive/StringTest/Append/Prepend Tests
     */
    inline auto operator += (double v) noexcept -> String & { return this->operator+=( std::to_string(v) ); }

#if defined(CDS_QT)

    /**
     * @brief Accumulate operator used to append a QString to the String
     *
     * @param v : QString cref = Constant Reference to a QString to append at the end of this String
     *
     * @exceptsafe
     *
     * @returns String ref = Reference to the modified String
     *
     * @test tested in MSK
     */
    inline auto operator += (QString const & v) noexcept -> String & { return this->operator += (String(v)); }
#endif

    /**
     * @brief Append Function used to append an ElementType to the String
     *
     * @param v : ElementType = Value to add to the end of the String
     *
     * @exceptsafe
     *
     * @returns String ref = Reference to the modified String
     *
     * @test tested in primitive/StringTest/Append/Prepend Tests
     */
    auto append (ElementType) noexcept -> String &;

    /**
     * @brief Append Function used to append a StringLiteral to the String
     *
     * @param v : StringLiteral = Address to a StringLiteral to add to the end of the String
     *
     * @exceptsafe
     *
     * @returns String ref = Reference to the modified String
     *
     * @test tested in primitive/StringTest/Append/Prepend Tests
     */
    auto append (StringLiteral) noexcept -> String &;

    /**
     * @brief Append Function used to append a CString to the String
     *
     * @param v : CString = Address to a CString to add to the end of the String
     *
     * @exceptsafe
     *
     * @returns String ref = Reference to the modified String
     *
     * @test tested in primitive/StringTest/Append/Prepend Tests
     */
    auto append (CString) noexcept -> String &;

    /**
     * @brief Append Function used to append a String to the String
     *
     * @param v : String cref = Constant Reference to the String to add at the end of the String
     *
     * @exceptsafe
     *
     * @returns String ref = Reference to the modified String
     *
     * @test tested in primitive/StringTest/Append/Prepend Tests
     */
    auto append (String const &) noexcept -> String &;

    /**
     * @brief Append Function used to append a std::string to the String
     *
     * @param v : std::string cref = Constant Reference to the std::string to add at the end of the String
     *
     * @exceptsafe
     *
     * @returns String ref = Reference to the modified String
     *
     * @test tested in primitive/StringTest/Append/Prepend Tests
     */
    inline auto append (std::string const & s) noexcept -> String & { return this->append(s.c_str()); }

    /**
     * @brief Append Function used to append a sint16 to the String
     *
     * @param v : sint16 = value to add at the end of the String
     *
     * @exceptsafe
     *
     * @returns String ref = Reference to the modified String
     *
     * @test tested in primitive/StringTest/Append/Prepend Tests
     */
    inline auto append (sint16 v) noexcept -> String & { return this->append(std::to_string(v) ); }

    /**
     * @brief Append Function used to append a sint32 to the String
     *
     * @param v : sint32 = value to add at the end of the String
     *
     * @exceptsafe
     *
     * @returns String ref = Reference to the modified String
     *
     * @test tested in primitive/StringTest/Append/Prepend Tests
     */
    inline auto append (sint32 v) noexcept -> String & { return this->append(std::to_string(v) ); }

    /**
     * @brief Append Function used to append a sint64 to the String
     *
     * @param v : sint64 = value to add at the end of the String
     *
     * @exceptsafe
     *
     * @returns String ref = Reference to the modified String
     *
     * @test tested in primitive/StringTest/Append/Prepend Tests
     */
    inline auto append (sint64 v) noexcept -> String & { return this->append(std::to_string(v) ); }

    /**
     * @brief Append Function used to append a uint8 to the String
     *
     * @param v : uint8 = value to add at the end of the String
     *
     * @exceptsafe
     *
     * @returns String ref = Reference to the modified String
     *
     * @test tested in primitive/StringTest/Append/Prepend Tests
     */
    inline auto append (uint8 v) noexcept -> String & { return this->append(std::to_string(v) ); }

    /**
     * @brief Append Function used to append a uint16 to the String
     *
     * @param v : uint16 = value to add at the end of the String
     *
     * @exceptsafe
     *
     * @returns String ref = Reference to the modified String
     *
     * @test tested in primitive/StringTest/Append/Prepend Tests
     */
    inline auto append (uint16 v) noexcept -> String & { return this->append(std::to_string(v) ); }

    /**
     * @brief Append Function used to append a uint32 to the String
     *
     * @param v : uint32 = value to add at the end of the String
     *
     * @exceptsafe
     *
     * @returns String ref = Reference to the modified String
     *
     * @test tested in primitive/StringTest/Append/Prepend Tests
     */
    inline auto append (uint32 v) noexcept -> String & { return this->append(std::to_string(v) ); }

    /**
     * @brief Append Function used to append a uint64 to the String
     *
     * @param v : uint64 = value to add at the end of the String
     *
     * @exceptsafe
     *
     * @returns String ref = Reference to the modified String
     *
     * @test tested in primitive/StringTest/Append/Prepend Tests
     */
    inline auto append (uint64 v) noexcept -> String & { return this->append(std::to_string(v) ); }

    /**
     * @brief Append Function used to append a float to the String
     *
     * @param v : float = value to add at the end of the String
     *
     * @exceptsafe
     *
     * @returns String ref = Reference to the modified String
     *
     * @test tested in primitive/StringTest/Append/Prepend Tests
     */
    inline auto append (float v) noexcept -> String & { return this->append( std::to_string(v) ); }

    /**
     * @brief Append Function used to append a double to the String
     *
     * @param v : double = value to add at the end of the String
     *
     * @exceptsafe
     *
     * @returns String ref = Reference to the modified String
     *
     * @test tested in primitive/StringTest/Append/Prepend Tests
     */
    inline auto append (double v) noexcept -> String & { return this->append( std::to_string(v) ); }

#if defined(CDS_QT)

    /**
     * @brief Append Function used to append a QString to the String
     *
     * @param v : QString cref = Constant Reference to a QString to append at the end of this String
     *
     * @exceptsafe
     *
     * @returns String ref = Reference to the modified String
     *
     * @test tested in MSK
     */
    inline auto append (QString const & v) noexcept -> String & { return this->append(String(v)); }
#endif


    /**
     * @brief Prepent Function used to prepend an ElementType to the String
     *
     * @param v : ElementType = Value to add at the beginning of the String
     *
     * @exceptsafe
     *
     * @returns String ref = Reference to the modified String
     *
     * @test tested in primitive/StringTest/Append/Prepend Tests
     */
    inline auto prepend (ElementType e) noexcept -> String & { return this->prepend(String().append(e)); }

    /**
     * @brief Prepend Function used to prepend a StringLiteral to the String
     *
     * @param v : StringLiteral = Address to a StringLiteral at the beginning of the String
     *
     * @exceptsafe
     *
     * @returns String ref = Reference to the modified String
     *
     * @test tested in primitive/StringTest/Append/Prepend Tests
     */
    inline auto prepend (StringLiteral cString) noexcept -> String & { return this->prepend(String(cString)); }

    /**
     * @brief Prepend Function used to prepend a CString to the String
     *
     * @param v : CString = Address to a CString to add at the beginning of the String
     *
     * @exceptsafe
     *
     * @returns String ref = Reference to the modified String
     *
     * @test tested in primitive/StringTest/Append/Prepend Tests
     */
    inline auto prepend (CString cString) noexcept -> String & { return this->prepend(String(cString)); }

    /**
     * @brief Prepend Function used to prepend a String to the String
     *
     * @param v : String cref = Constant Reference to the String to add at the beginning of the String
     *
     * @exceptsafe
     *
     * @returns String ref = Reference to the modified String
     *
     * @test tested in primitive/StringTest/Append/Prepend Tests
     */
    inline auto prepend (String const & s) noexcept -> String & { return ( * this = s + * this ); }

    /**
     * @brief Prepend Function used to prepend a std::string to the String
     *
     * @param v : std::string cref = Constant Reference to the std::string to add at the beginning of the String
     *
     * @exceptsafe
     *
     * @returns String ref = Reference to the modified String
     *
     * @test tested in primitive/StringTest/Append/Prepend Tests
     */
    inline auto prepend (std::string const & s) noexcept -> String & { return this->prepend(s.c_str()); }

    /**
     * @brief Prepend Function used to prepend a sint16 to the String
     *
     * @param v : sint16 = value to add at the beginning of the String
     *
     * @exceptsafe
     *
     * @returns String ref = Reference to the modified String
     *
     * @test tested in primitive/StringTest/Append/Prepend Tests
     */
    inline auto prepend (sint16 v) noexcept -> String & { return this->prepend(std::to_string(v) ); }

    /**
     * @brief Prepend Function used to prepend a sint32 to the String
     *
     * @param v : sint32 = value to add at the beginning of the String
     *
     * @exceptsafe
     *
     * @returns String ref = Reference to the modified String
     *
     * @test tested in primitive/StringTest/Append/Prepend Tests
     */
    inline auto prepend (sint32 v) noexcept -> String & { return this->prepend(std::to_string(v) ); }

    /**
     * @brief Prepend Function used to prepend a sint64 to the String
     *
     * @param v : sint64 = value to add at the beginning of the String
     *
     * @exceptsafe
     *
     * @returns String ref = Reference to the modified String
     *
     * @test tested in primitive/StringTest/Append/Prepend Tests
     */
    inline auto prepend (sint64 v) noexcept -> String & { return this->prepend(std::to_string(v) ); }

    /**
     * @brief Prepend Function used to prepend a uint8 to the String
     *
     * @param v : uint8 = value to add at the beginning of the String
     *
     * @exceptsafe
     *
     * @returns String ref = Reference to the modified String
     *
     * @test tested in primitive/StringTest/Append/Prepend Tests
     */
    inline auto prepend (uint8 v) noexcept -> String & { return this->prepend(std::to_string(v) ); }

    /**
     * @brief Prepend Function used to prepend a uint16 to the String
     *
     * @param v : uint16 = value to add at the beginning of the String
     *
     * @exceptsafe
     *
     * @returns String ref = Reference to the modified String
     *
     * @test tested in primitive/StringTest/Append/Prepend Tests
     */
    inline auto prepend (uint16 v) noexcept -> String & { return this->prepend(std::to_string(v) ); }

    /**
     * @brief Prepend Function used to prepend a uint32 to the String
     *
     * @param v : uint32 = value to add at the beginning of the String
     *
     * @exceptsafe
     *
     * @returns String ref = Reference to the modified String
     *
     * @test tested in primitive/StringTest/Append/Prepend Tests
     */
    inline auto prepend (uint32 v) noexcept -> String & { return this->prepend(std::to_string(v) ); }

    /**
     * @brief Prepend Function used to prepend a uint64 to the String
     *
     * @param v : uint64 = value to add at the beginning of the String
     *
     * @exceptsafe
     *
     * @returns String ref = Reference to the modified String
     *
     * @test tested in primitive/StringTest/Append/Prepend Tests
     */
    inline auto prepend (uint64 v) noexcept -> String & { return this->prepend(std::to_string(v) ); }

    /**
     * @brief Prepend Function used to prepend a float to the String
     *
     * @param v : float = value to add at the prepend of the String
     *
     * @exceptsafe
     *
     * @returns String ref = Reference to the modified String
     *
     * @test tested in primitive/StringTest/Append/Prepend Tests
     */
    inline auto prepend (float v) noexcept -> String & { return this->prepend( std::to_string(v) ); }

    /**
     * @brief Prepend Function used to prepend a double to the String
     *
     * @param v : double = value to add at the beginning of the String
     *
     * @exceptsafe
     *
     * @returns String ref = Reference to the modified String
     *
     * @test tested in primitive/StringTest/Append/Prepend Tests
     */
    inline auto prepend (double v) noexcept -> String & { return this->prepend( std::to_string(v) ); }

#if defined(CDS_QT)

    /**
     * @brief Prepend Function used to prepend a QString to the String
     *
     * @param v : QString cref = Constant Reference to a QString to append at the beginning of this String
     *
     * @exceptsafe
     *
     * @returns String ref = Reference to the modified String
     *
     * @test tested in MSK
     */

    inline auto prepend (QString const & v) noexcept -> String & { return this->prepend(String(v)); }
#endif

    /**
     * @brief Function used to obtain a std::string from this String
     *
     * @exceptsafe
     *
     * @returns std::string = std::string containing the data from this String
     *
     * @test tested in primitive/StringTest
     */
    __CDS_NoDiscard inline auto toStdString () const noexcept -> std::string { return this->cStr(); }

    /**
     * @brief Cast Specification used to obtain a std::string from this string
     *
     * @exceptsafe
     *
     * @returns std::string = std::string containing the data from this String
     *
     * @test tested in primitive/StringTest
     */
    inline operator std::string () const noexcept { return this->toStdString(); } // NOLINT(google-explicit-constructor)

#if defined(CDS_QT)

    /**
     * @brief Function used to obtain a QString from this String
     *
     * @exceptsafe
     *
     * @returns QString = QString containing the data from this String
     *
     * @test tested in MSK
     */
    __CDS_NoDiscard inline auto toQString () const noexcept -> QString { return QString(this->cStr()); }

    /**
     * @brief Cast Specification used to obtain a QString from this string
     *
     * @exceptsafe
     *
     * @returns QString = QString containing the data from this String
     *
     * @test tested in MSK
     */
    inline operator QString () const noexcept { return this->toQString(); }
#endif


    /**
     * @brief Function used to obtain the immutable C String buffer of this String object
     *
     * @exceptsafe
     *
     * @returns StringLiteral = buffer containing the String Data
     *
     * @test tested in primitive/StringTest
     */
    __CDS_NoDiscard constexpr auto cStr () const noexcept -> StringLiteral { return this->_p == nullptr ? "" : this->_p; }

    /**
     * @brief Cast Specification used to obtain the immutable C String buffer of this String object
     *
     * @exceptsafe
     *
     * @returns StringLiteral = buffer containing the String Data
     *
     * @test tested in primitive/StringTest/Append/
     */
    inline explicit operator StringLiteral () const noexcept { return this->cStr(); }

    /**
     * @brief Function used to obtain the mutable C String buffer of this String object
     *
     * @exceptsafe
     *
     * @returns CString = buffer containing the String Data
     *
     * @test tested in primitive/StringTest/Append/
     */
    __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto data () noexcept -> CString  { return this->_p; }

    /**
     * @brief Cast Specification used to obtain the mutable C String buffer of this String object
     *
     * @exceptsafe
     *
     * @returns CString = buffer containing the String Data
     *
     * @test tested in primitive/StringTest/Append/
     */
    inline explicit operator CString () noexcept { return this->data(); }

    /**
     * @brief Function used to obtain the indices of the given element in the String
     *
     * @param e : ElementType = element to find in the String
     *
     * @exceptsafe
     *
     * @returns LinkedList < Index > = List containing the indices where the element is in the String
     *
     * @test tested in primitive/StringTest/Find Tests
     */
    __CDS_NoDiscard auto find (ElementType) const noexcept -> LinkedList < Index >;

    /**
     * @brief Function used to obtain the indices of the given String in the String
     *
     * @param s : String cref = Constant Reference to the String to find in the String
     *
     * @exceptsafe
     *
     * @returns LinkedList < Index > = List containing the indices where the String occurs in the String
     *
     * @test tested in primitive/StringTest/Find Tests
     */
    __CDS_NoDiscard auto find (String const &) const noexcept -> LinkedList < Index >;

    /**
     * @brief Function used to obtain the indices of the elements in the given String, in the String
     *
     * @param s : String cref = Constant Reference to the String containing the elements to find in the String
     *
     * @exceptsafe
     *
     * @returns LinkedList < Index > = List containing the indices where the elements from the given String is in the String
     *
     * @test tested in primitive/StringTest/Find Tests
     */
    __CDS_NoDiscard auto findOf (String const &) const noexcept -> LinkedList < Index >;

    /**
     * @brief Function used to obtain the indices of the elements not in the given String, in the String
     *
     * @param s : String cref = Constant Reference to the String not containing the elements to find in the String
     *
     * @exceptsafe
     *
     * @returns LinkedList < Index > = List containing the indices where the elements from the given String is in the String
     *
     * @test tested in primitive/StringTest/Find Tests
     */
    __CDS_NoDiscard auto findNotOf (String const &) const noexcept -> LinkedList < Index >;

    /**
     * @brief Function used to obtain the index of the first element in the String
     *
     * @param e : ElementType = element to find in the String
     *
     * @exceptsafe
     *
     * @returns Index = index of the first occurrence
     *
     * @test tested in primitive/StringTest/Find Tests
     */
    __CDS_NoDiscard auto findFirst ( ElementType ) const noexcept -> Index;

    /**
     * @brief Function used to obtain the index of the first String in the String
     *
     * @param s : String cref = Constant Reference to the String to find in the String
     *
     * @exceptsafe
     *
     * @returns Index = index of the first occurrence
     *
     * @test tested in primitive/StringTest/Find Tests
     */
    __CDS_NoDiscard auto findFirst ( String const & ) const noexcept -> Index;

    /**
     * @brief Function used to obtain the index of the last element in the String
     *
     * @param e : ElementType = element to find in the String
     *
     * @exceptsafe
     *
     * @returns Index = index of the last occurrence
     *
     * @test tested in primitive/StringTest/Find Tests
     */
    __CDS_NoDiscard auto findLast ( ElementType ) const noexcept -> Index;

    /**
     * @brief Function used to obtain the index of the last String in the String
     *
     * @param s : String cref = Constant Reference to the String to find in the String
     *
     * @exceptsafe
     *
     * @returns Index = index of the last occurrence
     *
     * @test tested in primitive/StringTest/Find Tests
     */
    __CDS_NoDiscard auto findLast ( String const & ) const noexcept -> Index;

    /**
     * @brief Function used to obtain the index of the first element from the given String, in the String
     *
     * @param s : String cref = Constant Reference to the String containing the elements to find in the String
     *
     * @exceptsafe
     *
     * @returns Index = index of the first occurrence
     *
     * @test tested in primitive/StringTest/Find Tests
     */
    __CDS_NoDiscard auto findFirstOf ( String const & ) const noexcept -> Index;

    /**
     * @brief Function used to obtain the index of the first element not in the given String, in the String
     *
     * @param s : String cref = Constant Reference to the String not containing the elements to find in the String
     *
     * @exceptsafe
     *
     * @returns Index = index of the first occurrence
     *
     * @test tested in primitive/StringTest/Find Tests
     */
    __CDS_NoDiscard auto findFirstNotOf ( String const & ) const noexcept -> Index;

    /**
     * @brief Function used to obtain the index of the last element from the given String, in the String
     *
     * @param s : String cref = Constant Reference to the String containing the elements to find in the String
     *
     * @exceptsafe
     *
     * @returns Index = index of the last occurrence
     *
     * @test tested in primitive/StringTest/Find Tests
     */
    __CDS_NoDiscard auto findLastOf ( String const & ) const noexcept -> Index;

    /**
     * @brief Function used to obtain the index of the last element not in the given String, in the String
     *
     * @param s : String cref = Constant Reference to the String not containing the elements to find in the String
     *
     * @exceptsafe
     *
     * @returns Index = index of the last occurrence
     *
     * @test tested in primitive/StringTest/Find Tests
     */
    __CDS_NoDiscard auto findLastNotOf ( String const & ) const noexcept -> Index;

    /**
     * @brief Function used to obtain a substring from given index and until given index
     *
     * @param from : Index = starting index
     * @param to : Index = ending index. If not given, it will default to end of string
     *
     * @exceptsafe
     *
     * @returns String = String containing the data from starting index to ending index provided
     *
     * @test tested in primitive/StringTest/Substring Tests
     */
    __CDS_NoDiscard auto substr ( Index, Index = -1 ) const noexcept -> String;

    /**
     * @brief Comparison operator
     *
     * @param o : String cref = Constant Reference to a String to compare this Object to
     *
     * @exceptsafe
     *
     * @returns bool = true if Strings are equal, false otherwise
     *
     * @test tested in primitive/StringTest/Comparison Tests
     */
    __CDS_NoDiscard auto operator == ( String const & o ) const noexcept -> bool;

    /**
     * @brief Comparison Function
     *
     * @param o : Object cref = Constant Reference to a CDS/Object to compare this Object to
     *
     * @exceptsafe
     *
     * @returns bool = true if Strings are equal, false otherwise
     *
     * @test tested in primitive/StringTest/Comparison Tests
     */
    __CDS_NoDiscard inline auto equals ( Object const & o) const noexcept -> bool final {
        if ( this == & o ) return true;
        auto p = dynamic_cast < decltype ( this ) > ( & o );
        if ( p == nullptr ) return false;
        return this->operator==(* p);
    }

    /**
     * @brief Comparison Operator
     *
     * @param e : ElementType = Character to compare String to
     *
     * @overload
     * @exceptsafe
     *
     * @returns bool = true if String is of one character and equal with given character, false otherwise
     *
     * @test tested in primitive/StringTest/Comparison Tests
     */
    __CDS_NoDiscard constexpr inline auto operator == ( ElementType e ) const noexcept -> bool { return this->size() == 1 && this->_p[0] == e; }

    /**
     * Comparison Operator
     *
     * @param stdString : std::string cref = Constant Reference to a std::string to compare contents of this String to
     *
     * @overload
     * @exceptsafe
     *
     * @returns bool = true if Strings have same content, false otherwise
     *
     * @test tested in primitive/StringTest/Comparison Tests
     */
    __CDS_NoDiscard auto operator == ( std::string const & ) const noexcept -> bool;

    /**
     * Comparison Operator
     *
     * @param cString : StringLiteral = Address to a C String to compare contents of this String to
     *
     * @overload
     * @exceptsafe
     *
     * @returns bool = true if Strings have same content, false otherwise
     *
     * @test tested in primitive/StringTest/Comparison Tests
     */
    __CDS_NoDiscard auto operator == ( StringLiteral ) const noexcept -> bool;

#if defined(CDS_QT)

    /**
     * Comparison Operator
     *
     * @param v : QString cref = Constant Reference to a QString to compare contents of this String to
     *
     * @overload
     * @exceptsafe
     *
     * @returns bool = true if Strings have same content, false otherwise
     *
     * @test tested in primitive/StringTest/Comparison Tests
     */
    inline auto operator == (QString const & v) const noexcept -> bool { return * this == String(v); }
#endif


    /**
     * Comparison Operator, Greater or Equals
     *
     * @param o : String cref = Constant Reference to a String to compare contents of this String to
     *
     * @exceptsafe
     *
     * @returns bool = true if leftmost has the first difference greater or equals than the given right String, false otherwise
     *
     * @test tested in primitive/StringTest/Comparison Tests
     */
    __CDS_NoDiscard auto operator >= ( String const & ) const noexcept -> bool;

    /**
     * @brief Comparison Operator, Greater or Equals
     *
     * @param e : ElementType = Character to compare String to
     *
     * @overload
     * @exceptsafe
     *
     * @returns bool = true if String is of one character and greater or equal than given character, false otherwise
     *
     * @test tested in primitive/StringTest/Comparison Tests
     */
    __CDS_NoDiscard constexpr inline auto operator >= ( ElementType e ) const noexcept -> bool { return this->size() == 1 && this->_p[0] >= e; }

    /**
     * Comparison Operator, Greater or Equals
     *
     * @param stdString : std::string cref = Constant Reference to a std::string to compare contents of this String to
     *
     * @overload
     * @exceptsafe
     *
     * @returns bool = true if leftmost has the first difference greater or equals than the given right String, false otherwise
     *
     * @test tested in primitive/StringTest/Comparison Tests
     */
    __CDS_NoDiscard auto operator >= ( std::string const & ) const noexcept -> bool;

#if defined(CDS_QT)

    /**
     * Comparison Operator, Greater or Equals
     *
     * @param v : QString cref = Constant Reference to a QString to compare contents of this String to
     *
     * @overload
     * @exceptsafe
     *
     * @returns bool = true if leftmost has the first difference greater or equals than the given right String, false otherwise
     *
     * @test tested in MSK
     */
    inline auto operator >= (QString const & v) const noexcept -> bool { return * this >= String(v); }
#endif

    /**
     * Comparison Operator, Greater or Equals
     *
     * @param cString : StringLiteral = Address to a C String to compare contents of this String to
     *
     * @overload
     * @exceptsafe
     *
     * @returns bool = true if leftmost has the first difference greater or equals than the given right String, false otherwise
     *
     * @test tested in primitive/StringTest/Comparison Tests
     */
    __CDS_NoDiscard auto operator >= ( StringLiteral ) const noexcept -> bool;


    /**
     * Comparison Operator, Less or Equals
     *
     * @param o : String cref = Constant Reference to a String to compare contents of this String to
     *
     * @exceptsafe
     *
     * @returns bool = true if leftmost has the first difference less or equals than the given right String, false otherwise
     *
     * @test tested in primitive/StringTest/Comparison Tests
     */
    __CDS_NoDiscard auto operator <= ( String const & ) const noexcept -> bool;

#if defined(CDS_QT)

    /**
     * Comparison Operator, Less or Equals
     *
     * @param v : QString cref = Constant Reference to a QString to compare contents of this String to
     *
     * @overload
     * @exceptsafe
     *
     * @returns bool = true if leftmost has the first difference less or equals than the given right String, false otherwise
     *
     * @test tested in primitive/StringTest/Comparison Tests
     */
    inline auto operator <= (QString const & v) const noexcept -> bool { return * this <= String(v); }
#endif


    /**
     * @brief Comparison Operator, Less or Equals
     *
     * @param e : ElementType = Character to compare String to
     *
     * @overload
     * @exceptsafe
     *
     * @returns bool = true if String is of one character and less or equal than given character, false otherwise
     *
     * @test tested in primitive/StringTest/Comparison Tests
     */
    __CDS_NoDiscard constexpr inline auto operator <= ( ElementType e ) const noexcept -> bool { return this->size() == 1 && this->_p[0] <= e; }

    /**
     * Comparison Operator, Less or Equals
     *
     * @param stdString : std::string cref = Constant Reference to a std::string to compare contents of this String to
     *
     * @overload
     * @exceptsafe
     *
     * @returns bool = true if leftmost has the first difference less or equal than the given right String, false otherwise
     *
     * @test tested in primitive/StringTest/Comparison Tests
     */
    __CDS_NoDiscard auto operator <= ( std::string const & ) const noexcept -> bool;

    /**
     * Comparison Operator, Less or Equals
     *
     * @param cString : StringLiteral = Address to a C String to compare contents of this String to
     *
     * @overload
     * @exceptsafe
     *
     * @returns bool = true if leftmost has the first difference less or equals than the given right String, false otherwise
     *
     * @test tested in primitive/StringTest/Comparison Tests
     */
    __CDS_NoDiscard auto operator <= ( StringLiteral ) const noexcept -> bool;


    /**
     * @brief Comparison operator, Not Equal
     *
     * @param o : String cref = Constant Reference to a String to compare this Object to
     *
     * @exceptsafe
     *
     * @returns bool = true if Strings are not equal, false otherwise
     *
     * @test tested in primitive/StringTest/Comparison Tests
     */
    __CDS_NoDiscard auto operator != ( String const & ) const noexcept -> bool;

    /**
     * @brief Comparison Operator, Not Equal
     *
     * @param e : ElementType = Character to compare String to
     *
     * @overload
     * @exceptsafe
     *
     * @returns bool = true if String is of one character and not equal with given character, false otherwise
     *
     * @test tested in primitive/StringTest/Comparison Tests
     */
    __CDS_NoDiscard constexpr inline auto operator != ( ElementType e ) const noexcept -> bool { return this->size() != 1 || this->_p[0] != e; }

    /**
     * Comparison Operator, Not Equal
     *
     * @param stdString : std::string cref = Constant Reference to a std::string to compare contents of this String to
     *
     * @overload
     * @exceptsafe
     *
     * @returns bool = true if Strings do not have same content, false otherwise
     *
     * @test tested in primitive/StringTest/Comparison Tests
     */
    __CDS_NoDiscard auto operator != ( std::string const & ) const noexcept -> bool;

    /**
     * Comparison Operator, Not Equal
     *
     * @param cString : StringLiteral = Address to a C String to compare contents of this String to
     *
     * @overload
     * @exceptsafe
     *
     * @returns bool = true if Strings do not have same content, false otherwise
     *
     * @test tested in primitive/StringTest/Comparison Tests
     */
    __CDS_NoDiscard auto operator != ( StringLiteral ) const noexcept -> bool;

#if defined(CDS_QT)

    /**
     * Comparison Operator, Not Equal
     *
     * @param v : QString cref = Constant Reference to a QString to compare contents of this String to
     *
     * @overload
     * @exceptsafe
     *
     * @returns bool = true if Strings do not have same content, false otherwise
     *
     * @test tested in primitive/StringTest/Comparison Tests
     */
    inline auto operator != (QString const & v) const noexcept -> bool { return * this != String(v); }
#endif


    /**
     * Comparison Operator, Less
     *
     * @param o : String cref = Constant Reference to a String to compare contents of this String to
     *
     * @exceptsafe
     *
     * @returns bool = true if leftmost has the first difference less than the given right String, false otherwise
     *
     * @test tested in primitive/StringTest/Comparison Tests
     */
    __CDS_NoDiscard auto operator < ( String const & ) const noexcept -> bool;

    /**
     * @brief Comparison Operator, Less
     *
     * @param e : ElementType = Character to compare String to
     *
     * @overload
     * @exceptsafe
     *
     * @returns bool = true if String is of one character and less than given character, false otherwise
     *
     * @test tested in primitive/StringTest/Comparison Tests
     */
    __CDS_NoDiscard constexpr inline auto operator < ( ElementType e ) const noexcept -> bool { return this->size() == 1 && this->_p[0] < e; }

    /**
     * Comparison Operator, Less
     *
     * @param stdString : std::string cref = Constant Reference to a std::string to compare contents of this String to
     *
     * @overload
     * @exceptsafe
     *
     * @returns bool = true if leftmost has the first difference less than the given right String, false otherwise
     *
     * @test tested in primitive/StringTest/Comparison Tests
     */
    __CDS_NoDiscard auto operator < ( std::string const & ) const noexcept -> bool;

    /**
     * @test tested in primitive/StringTest/Comparison Tests
     */
    __CDS_NoDiscard auto operator < ( StringLiteral ) const noexcept -> bool;

#if defined(CDS_QT)

    /**
     * Comparison Operator, Less
     *
     * @param v : QString cref = Constant Reference to a QString to compare contents of this String to
     *
     * @overload
     * @exceptsafe
     *
     * @returns bool = true if leftmost has the first difference less than the given right String, false otherwise
     *
     * @test tested in MSK
     */
    inline auto operator < (QString const & v) const noexcept -> bool { return * this < String(v); }
#endif


    /**
     * Comparison Operator, Greater
     *
     * @param o : String cref = Constant Reference to a String to compare contents of this String to
     *
     * @exceptsafe
     *
     * @returns bool = true if leftmost has the first difference greater than the given right String, false otherwise
     *
     * @test tested in primitive/StringTest/Comparison Tests
     */
    __CDS_NoDiscard auto operator > ( String const & ) const noexcept -> bool;

    /**
     * @brief Comparison Operator, Greater
     *
     * @param e : ElementType = Character to compare String to
     *
     * @overload
     * @exceptsafe
     *
     * @returns bool = true if String is of one character and greater than given character, false otherwise
     *
     * @test tested in primitive/StringTest/Comparison Tests
     */
    __CDS_NoDiscard constexpr inline auto operator > ( ElementType e ) const noexcept -> bool { return this->size() == 1 && this->_p[0] > e; }

    /**
     * Comparison Operator, Greater
     *
     * @param stdString : std::string cref = Constant Reference to a std::string to compare contents of this String to
     *
     * @overload
     * @exceptsafe
     *
     * @returns bool = true if leftmost has the first difference greater than the given right String, false otherwise
     *
     * @test tested in primitive/StringTest/Comparison Tests
     */
    __CDS_NoDiscard auto operator > ( std::string const & ) const noexcept -> bool;

    /**
     * Comparison Operator, Greater
     *
     * @param cString : StringLiteral = Address to a C String to compare contents of this String to
     *
     * @overload
     * @exceptsafe
     *
     * @returns bool = true if leftmost has the first difference greater than the given right String, false otherwise
     *
     * @test tested in primitive/StringTest/Comparison Tests
     */
    __CDS_NoDiscard auto operator > ( StringLiteral ) const noexcept -> bool;

#if defined(CDS_QT)

    /**
     * Comparison Operator, Greater
     *
     * @param v : QString cref = Constant Reference to a QString to compare contents of this String to
     *
     * @overload
     * @exceptsafe
     *
     * @returns bool = true if leftmost has the first difference greater than the given right String, false otherwise
     *
     * @test tested in MSK
     */
    inline auto operator > (QString const & v) const noexcept -> bool { return * this > String(v); }
#endif


    /**
     * @brief Append Function used to append a String to the String
     *
     * @param v : String cref = Constant Reference to the String to add at the end of the String
     *
     * @exceptsafe
     *
     * @returns String ref = Reference to the modified String
     *
     * @test tested in primitive/StringTest/Append/Prepend Tests
     */
    __CDS_NoDiscard inline auto operator + ( String const & v ) const noexcept -> String { return String(*this).append(v); }

    /**
     * @brief Append Function used to append an ElementType to the String
     *
     * @param v : ElementType = Value to add to the end of the String
     *
     * @exceptsafe
     *
     * @returns String ref = Reference to the modified String
     *
     * @test tested in primitive/StringTest/Append/Prepend Tests
     */
    __CDS_NoDiscard inline auto operator + ( ElementType v ) const noexcept -> String { return String(*this).append(v); }

    /**
     * @brief Append Function used to append a std::string to the String
     *
     * @param v : std::string cref = Constant Reference to the std::string to add at the end of the String
     *
     * @exceptsafe
     *
     * @returns String ref = Reference to the modified String
     *
     * @test tested in primitive/StringTest/Append/Prepend Tests
     */
    __CDS_NoDiscard inline auto operator + ( std::string const & v ) const noexcept -> String { return String(*this).append(v); }

    /**
     * @brief Append Function used to append a StringLiteral to the String
     *
     * @param v : StringLiteral = Address to a StringLiteral to add to the end of the String
     *
     * @exceptsafe
     *
     * @returns String ref = Reference to the modified String
     *
     * @test tested in primitive/StringTest/Append/Prepend Tests
     */
    __CDS_NoDiscard inline auto operator + ( StringLiteral v ) const noexcept -> String { return String(*this).append(v); }

    /**
     * @brief Append Function used to append a CString to the String
     *
     * @param v : CString = Address to a CString to add to the end of the String
     *
     * @exceptsafe
     *
     * @returns String ref = Reference to the modified String
     *
     * @test tested in primitive/StringTest/Append/Prepend Tests
     */
    __CDS_NoDiscard inline auto operator + ( CString v ) const noexcept -> String { return String(*this).append(v); }

    /**
     * @brief Append Function used to append a sint16 to the String
     *
     * @param v : sint16 = value to add at the end of the String
     *
     * @exceptsafe
     *
     * @returns String ref = Reference to the modified String
     *
     * @test tested in primitive/StringTest/Append/Prepend Tests
     */
    __CDS_NoDiscard inline auto operator + (sint16 v) const noexcept -> String { return this->operator+(std::to_string(v) ); }

    /**
     * @brief Append Function used to append a sint32 to the String
     *
     * @param v : sint32 = value to add at the end of the String
     *
     * @exceptsafe
     *
     * @returns String ref = Reference to the modified String
     *
     * @test tested in primitive/StringTest/Append/Prepend Tests
     */
    __CDS_NoDiscard inline auto operator + (sint32 v) const noexcept -> String { return this->operator+(std::to_string(v) ); }

    /**
     * @brief Append Function used to append a sint64 to the String
     *
     * @param v : sint64 = value to add at the end of the String
     *
     * @exceptsafe
     *
     * @returns String ref = Reference to the modified String
     *
     * @test tested in primitive/StringTest/Append/Prepend Tests
     */
    __CDS_NoDiscard inline auto operator + (sint64 v) const noexcept -> String { return this->operator+(std::to_string(v) ); }

    /**
     * @brief Append Function used to append a uint8 to the String
     *
     * @param v : uint8 = value to add at the end of the String
     *
     * @exceptsafe
     *
     * @returns String ref = Reference to the modified String
     *
     * @test tested in primitive/StringTest/Append/Prepend Tests
     */
    __CDS_NoDiscard inline auto operator + (uint8 v) const noexcept -> String { return this->operator+(std::to_string(v) ); }

    /**
     * @brief Append Function used to append a uint16 to the String
     *
     * @param v : uint16 = value to add at the end of the String
     *
     * @exceptsafe
     *
     * @returns String ref = Reference to the modified String
     *
     * @test tested in primitive/StringTest/Append/Prepend Tests
     */
    __CDS_NoDiscard inline auto operator + (uint16 v) const noexcept -> String { return this->operator+(std::to_string(v) ); }

    /**
     * @brief Append Function used to append a uint32 to the String
     *
     * @param v : uint32 = value to add at the end of the String
     *
     * @exceptsafe
     *
     * @returns String ref = Reference to the modified String
     *
     * @test tested in primitive/StringTest/Append/Prepend Tests
     */
    __CDS_NoDiscard inline auto operator + (uint32 v) const noexcept -> String { return this->operator+(std::to_string(v) ); }

    /**
     * @brief Append Function used to append a uint64 to the String
     *
     * @param v : uint64 = value to add at the end of the String
     *
     * @exceptsafe
     *
     * @returns String ref = Reference to the modified String
     *
     * @test tested in primitive/StringTest/Append/Prepend Tests
     */
    __CDS_NoDiscard inline auto operator + (uint64 v) const noexcept -> String { return this->operator+(std::to_string(v) ); }

    /**
     * @brief Append Function used to append a float to the String
     *
     * @param v : float = value to add at the end of the String
     *
     * @exceptsafe
     *
     * @returns String ref = Reference to the modified String
     *
     * @test tested in primitive/StringTest/Append/Prepend Tests
     */
    __CDS_NoDiscard inline auto operator + (float v) const noexcept -> String { return this->operator+( std::to_string(v) ); }

    /**
     * @brief Append Function used to append a double to the String
     *
     * @param v : double = value to add at the end of the String
     *
     * @exceptsafe
     *
     * @returns String ref = Reference to the modified String
     *
     * @test tested in primitive/StringTest/Append/Prepend Tests
     */
    __CDS_NoDiscard inline auto operator + (double v) const noexcept -> String { return this->operator+( std::to_string(v) ); }

#if defined(CDS_QT)

    /**
     * @brief Append Function used to append a QString to the String
     *
     * @param v : QString cref = Constant Reference to a QString to append at the end of this String
     *
     * @exceptsafe
     *
     * @returns String ref = Reference to the modified String
     *
     * @test tested in MSK
     */
    inline auto operator + (QString const & v) const noexcept -> String { return * this + String(v); }
#endif

    /**
     * @brief Function used to multiply given String by [count] times
     *
     * @param count : int = number of times to repeat the String in the final result
     *
     * @exceptsafe
     *
     * @returns String = String containing the repeated String
     *
     * @test tested in primitive/StringTest/Utility Functions, String Formatting
     */
    __CDS_NoDiscard auto operator * (int) const noexcept -> String;


    /**
     * @brief Function used to trim the occurrences of given element [e] from the left of the String
     *
     * @param e : ElementType = element to trim from the left
     *
     * @exceptsafe
     *
     * @returns String ref = Reference to the modified String
     *
     * @test tested in primitive/StringTest/Utility Functions, String Formatting
     */
    auto ltrim ( ElementType = ' ' ) noexcept -> String &;

    /**
     * @brief Function used to trim the occurrences of given String [s] from the left of the String
     *
     * @param s : String cref = Constant Reference to the String occurrences to remove from the left
     *
     * @exceptsafe
     *
     * @returns String ref = Reference to the modified String
     *
     * @test tested in primitive/StringTest/Utility Functions, String Formatting
     */
    auto ltrim ( String const & ) noexcept -> String &;

    /**
     * @brief Function used to trim the occurrences of given element [e] from the left of the String into a new String
     *
     * @param e : ElementType = element to trim from the left
     *
     * @exceptsafe
     *
     * @returns String ref = Reference to a new, modified String
     *
     * @test tested in primitive/StringTest/Utility Functions, String Formatting
     */
    __CDS_NoDiscard __CDS_MaybeUnused inline auto ltrim ( ElementType e = ' ' ) const noexcept -> String {
        return String(*this).ltrim(e);
    }

    /**
     * @brief Function used to trim the occurrences of given String [s] from the left of the String into a new String
     *
     * @param s : String cref = Constant Reference to the String occurrences to remove from the left
     *
     * @exceptsafe
     *
     * @returns String ref = Reference to a new, modified String
     *
     * @test tested in primitive/StringTest/Utility Functions, String Formatting
     */
    __CDS_NoDiscard __CDS_MaybeUnused inline auto ltrim ( String const & e ) const noexcept -> String {
        return String(*this).ltrim(e);
    }

    /**
     * @brief Function used to trim the occurrences of given element [e] from the right of the String
     *
     * @param e : ElementType = element to trim from the right
     *
     * @exceptsafe
     *
     * @returns String ref = Reference to the modified String
     *
     * @test tested in primitive/StringTest/Utility Functions, String Formatting
     */
    auto rtrim ( ElementType = ' ' ) noexcept -> String &;

    /**
     * @brief Function used to trim the occurrences of given String [s] from the right of the String
     *
     * @param s : String cref = Constant Reference to the String occurrences to remove
     *
     * @exceptsafe
     *
     * @returns String ref = Reference to the modified String
     *
     * @test tested in primitive/StringTest/Utility Functions, String Formatting
     */
    auto rtrim ( String const & ) noexcept -> String &;

    /**
     * @brief Function used to trim the occurrences of given element [e] from the right of the String into a new String
     *
     * @param e : ElementType = element to trim from the right
     *
     * @exceptsafe
     *
     * @returns String ref = Reference to a new, modified String
     *
     * @test tested in primitive/StringTest/Utility Functions, String Formatting
     */
    __CDS_NoDiscard __CDS_MaybeUnused inline auto rtrim ( ElementType e = ' ' ) const noexcept -> String {
        return String(*this).rtrim(e);
    }

    /**
     * @brief Function used to trim the occurrences of given String [s] from the right of the String into a new String
     *
     * @param s : String cref = Constant Reference to the String occurrences to remove from the right
     *
     * @exceptsafe
     *
     * @returns String ref = Reference to a new, modified String
     *
     * @test tested in primitive/StringTest/Utility Functions, String Formatting
     */
    __CDS_NoDiscard __CDS_MaybeUnused inline auto rtrim ( String const & e ) const noexcept -> String {
        return String(*this).rtrim(e);
    }

    /**
     * @brief Function used to trim the occurrences of given element [e] from the left and right of the String
     *
     * @param e : ElementType = element to trim from the left and right
     *
     * @exceptsafe
     *
     * @returns String ref = Reference to the modified String
     *
     * @test tested in primitive/StringTest/Utility Functions, String Formatting
     */
    auto inline trim ( ElementType e = ' ' ) noexcept -> String & { return this->ltrim(e).rtrim(e); }

    /**
     * @brief Function used to trim the occurrences of given String [s] from the left and right of the String
     *
     * @param s : String cref = Constant Reference to the String occurrences to remove from the left and right
     *
     * @exceptsafe
     *
     * @returns String ref = Reference to the modified String
     *
     * @test tested in primitive/StringTest/Utility Functions, String Formatting
     */
    auto inline trim ( String const & e ) noexcept -> String & { return this->ltrim(e).rtrim(e); }

    /**
     * @brief Function used to trim the occurrences of given element [e] from the left and right of the String into a new String
     *
     * @param e : ElementType = element to trim from the left and right
     *
     * @exceptsafe
     *
     * @returns String ref = Reference to a new, modified String
     *
     * @test tested in primitive/StringTest/Utility Functions, String Formatting
     */
    __CDS_NoDiscard __CDS_MaybeUnused inline auto trim ( ElementType e = ' ' ) const noexcept -> String {
        return String(*this).trim(e);
    }

    /**
     * @brief Function used to trim the occurrences of given String [s] from the left and right of the String into a new String
     *
     * @param s : String cref = Constant Reference to the String occurrences to remove from the left and right
     *
     * @exceptsafe
     *
     * @returns String ref = Reference to a new, modified String
     *
     * @test tested in primitive/StringTest/Utility Functions, String Formatting
     */

    __CDS_NoDiscard __CDS_MaybeUnused inline auto trim ( String const & e ) const noexcept -> String {
        return String(*this).trim(e);
    }

    /**
     * @brief Function used to justify the right side of the string with given elements or spaces, if no param given, spaces are used
     *
     * Characters added are done until the size is obtained
     * If size given < length, then none are added
     *
     * @param justifySize : Size = number of [padChar] characters to add at the right
     * @param padChar : Size = character to pad string with
     *
     * @exceptsafe
     *
     * @returns String ref = Reference to the modified String
     *
     * @test tested in primitive/StringTest/Utility Functions, String Formatting
     */
    auto rjust (Size, ElementType = ' ') noexcept -> String &;

    /**
     * @brief Function used to justify the right side of the string with given elements or spaces, if no param given, spaces are used
     *
     * Characters added are done until the size is obtained
     * If size given < length, then none are added
     *
     * @param justifySize : Size = number of [padChar] characters to add at the right
     * @param padChar : Size = character to pad string with
     *
     * @exceptsafe
     *
     * @returns String = the new string with modifications
     *
     * @test tested in primitive/StringTest/Utility Functions, String Formatting
     */
    __CDS_NoDiscard __CDS_MaybeUnused inline auto rjust (Size s, ElementType e = ' ') const noexcept -> String {
        return String(*this).rjust(s, e);
    }

    /**
     * @brief Function used to justify the left side of the string with given elements or spaces, if no param given, spaces are used
     *
     * Characters added are done until the size is obtained
     * If size given < length, then none are added
     *
     * @param justifySize : Size = number of [padChar] characters to add at the left
     * @param padChar : Size = character to pad string with
     *
     * @exceptsafe
     *
     * @returns String ref = Reference to the modified String
     *
     * @test tested in primitive/StringTest/Utility Functions, String Formatting
     */
    auto ljust (Size, ElementType = ' ') noexcept -> String &;

    /**
     * @brief Function used to justify the left side of the string with given elements or spaces, if no param given, spaces are used
     *
     * Characters added are done until the size is obtained
     * If size given < length, then none are added
     *
     * @param justifySize : Size = number of [padChar] characters to add at the left
     * @param padChar : Size = character to pad string with
     *
     * @exceptsafe
     *
     * @returns String = the new string with modifications
     *
     * @test tested in primitive/StringTest/Utility Functions, String Formatting
     */
    __CDS_NoDiscard __CDS_MaybeUnused inline auto ljust (Size s, ElementType e = ' ') const noexcept -> String {
        return String(*this).ljust(s, e);
    }

public:

    /**
     * @brief Function used to check whether character is upper
     *
     * @param c : char = Character to check whether is upper
     *
     * @static
     * @exceptsafe
     *
     * @returns bool = true if character is upper, false otherwise
     *
     * @test tested in primitive/StringTest/Utility Functions, String Formatting
     */
    constexpr auto static inline isUpperChar(char c) noexcept -> bool { return c >= 'A' && c <= 'Z'; }

    /**
     * @brief Function used to check whether character is lower
     *
     * @param c : char = Character to check whether is lower
     *
     * @static
     * @exceptsafe
     *
     * @returns bool = true if character is lower, false otherwise
     *
     * @test tested in primitive/StringTest/Utility Functions, String Formatting
     */
    constexpr auto static inline isLowerChar(char c) noexcept -> bool { return c >= 'a' && c <= 'z'; }

    /**
     * @brief Function used to check whether character is a digit
     *
     * @param c : char = Character to check whether is a digit
     *
     * @static
     * @exceptsafe
     *
     * @returns bool = true if character is a digit, false otherwise
     *
     * @test tested in primitive/StringTest/Utility Functions, String Formatting
     */
    constexpr auto static inline isDigit(char c) noexcept -> bool { return c >= '0' && c <= '9'; }

    /**
     * @brief Function used to check whether character is a letter
     *
     * @param c : char = Character to check whether is a letter
     *
     * @static
     * @exceptsafe
     *
     * @returns bool = true if character is a letter, false otherwise
     *
     * @test tested in primitive/StringTest/Utility Functions, String Formatting
     */
    constexpr auto static inline isLetter(char c) noexcept -> bool { return isUpperChar(c) || isLowerChar(c); }

    /**
     * @brief Function used to check whether character is alphanumeric
     *
     * @param c : char = Character to check whether is alphanumeric
     *
     * @static
     * @exceptsafe
     *
     * @returns bool = true if character is alphanumeric, false otherwise
     *
     * @test tested in primitive/StringTest/Utility Functions, String Formatting
     */
    constexpr auto static inline isAlpha(char c) noexcept -> bool { return isLetter(c) || isDigit(c); }

    /**
     * @brief Function used to check whether character is a vowel
     *
     * @param c : char = Character to check whether is a vowel
     *
     * @static
     * @exceptsafe
     *
     * @returns bool = true if character is a vowel, false otherwise
     *
     * @test tested in primitive/StringTest/Utility Functions, String Formatting
     */
    auto static inline isVowel(char c) noexcept -> bool { return String("aeiouAEIOU").contains(c); }

    /**
     * @brief Function used to check whether character is a consonant
     *
     * @param c : char = Character to check whether is a consonant
     *
     * @static
     * @exceptsafe
     *
     * @returns bool = true if character is a consonant, false otherwise
     *
     * @test tested in primitive/StringTest/Utility Functions, String Formatting
     */
    auto static inline isConsonant(char c) noexcept -> bool { return isLetter(c) && ! isVowel(c); }

    /**
     * @brief Function used to convert character to a lower character, if possible ( if is upper )
     *
     * @param c : char = Character to convert
     *
     * @static
     * @exceptsafe
     *
     * @returns char = Modified Character Value
     *
     * @test tested in primitive/StringTest/Utility Functions, String Formatting
     */
    constexpr auto static inline lowerChar(char c) noexcept -> char { return isUpperChar(c) ? static_cast < ElementType > ( c + 32 ) : c; }

    /**
     * @brief Function used to convert character to an upper character, if possible ( if is lower )
     *
     * @param c : char = Character to convert
     *
     * @static
     * @exceptsafe
     *
     * @returns char = Modified Character Value
     *
     * @test tested in primitive/StringTest/Utility Functions, String Formatting
     */
    constexpr auto static inline upperChar(char c) noexcept -> char { return isLowerChar(c) ? static_cast < ElementType > ( c - 32 ) : c; }

    /**
     * @brief Function used to convert character to a lower character, if possible ( if is upper )
     *
     * @param c : char ref = Reference Character to convert
     *
     * @static
     * @exceptsafe
     *
     * @returns char ref = Reference to Modified Character Value
     *
     * @test tested in primitive/StringTest/Utility Functions, String Formatting
     */
    __CDS_cpplang_ConstexprConditioned auto static toLowerChar(char & c) noexcept -> char & { c = lowerChar(c); return c; }

    /**
     * @brief Function used to convert character to an upper character, if possible ( if is lower )
     *
     * @param c : char ref = Reference Character to convert
     *
     * @static
     * @exceptsafe
     *
     * @returns char ref = Reference to Modified Character Value
     *
     * @test tested in primitive/StringTest/Utility Functions, String Formatting
     */
    __CDS_cpplang_ConstexprConditioned auto static toUpperChar(char & c) noexcept -> char & { c = upperChar(c); return c; }

public:

#if !defined(_MSC_VER)

    /**
     * @brief Function used to convert characters of a String to their lower values ( if are upper )
     *
     * @exceptsafe
     *
     * @returns String ref = Reference to the modified String object
     *
     * @test tested in primitive/StringTest/Utility Functions, String Formatting
     */
    auto inline toLower () noexcept -> String & { for ( Index i = 0; i < this->_l; i++ ) this->_p[i] = lowerChar(this->_p[i]); return * this; }

    /**
     * @brief Function used to convert characters of a String to their upper values ( if are lower )
     *
     * @exceptsafe
     *
     * @returns String ref = Reference to the modified String object
     *
     * @test tested in primitive/StringTest/Utility Functions, String Formatting
     */
    auto inline toUpper () noexcept -> String & { for ( Index i = 0; i < this->_l; i++ ) this->_p[i] = upperChar(this->_p[i]); return * this; }
#else

    /**
     * @brief Function used to convert characters of a String to their lower values ( if are upper )
     *
     * @exceptsafe
     *
     * @returns String ref = Reference to the modified String object
     *
     * @test tested in primitive/StringTest/Utility Functions, String Formatting
     */
    auto inline toLower () noexcept -> String & { for ( Size i = 0; i < this->_l; i++ ) this->_p[i] = lowerChar(this->_p[i]); return * this; }

    /**
     * @brief Function used to convert characters of a String to their upper values ( if are lower )
     *
     * @exceptsafe
     *
     * @returns String ref = Reference to the modified String object
     *
     * @test tested in primitive/StringTest/Utility Functions, String Formatting
     */
    auto inline toUpper () noexcept -> String & { for ( Size i = 0; i < this->_l; i++ ) this->_p[i] = upperChar(this->_p[i]); return * this; }
#endif

    /**
     * @brief Function used to convert characters of a String to their lower values ( if are upper ) and return it
     *
     * @exceptsafe
     *
     * @returns String = new String object modified as lower
     *
     * @test tested in primitive/StringTest/Utility Functions, String Formatting
     */
    __CDS_NoDiscard auto inline lower () const noexcept -> String { return String(*this).toLower(); }

    /**
     * @brief Function used to convert characters of a String to their upper values ( if are lower ) and return it
     *
     * @exceptsafe
     *
     * @returns String = new String object modified as upper
     *
     * @test tested in primitive/StringTest/Utility Functions, String Formatting
     */
    __CDS_NoDiscard auto inline upper () const noexcept -> String { return String(*this).toUpper(); }

    /**
     * @brief Copy Operator
     *
     * @param o : String cref = Constant Reference to a String to copy data from
     *
     * @exceptsafe
     *
     * @returns String ref = Reference to the modified Object
     *
     * @test tested in primitive/StringTest/Assignment Tests
     */
    String & operator = ( String const & ) noexcept;

#if defined(CDS_QT)

    /**
     * @brief Copy Operator
     *
     * @param v : QString cref = Constant Reference to a QString to copy data from
     *
     * @exceptsafe
     *
     * @returns String ref = Reference to the modified Object
     *
     * @test tested in primitive/StringTest/Assignment Tests
     */
    inline String & operator = (QString const & v) noexcept { return ((* this) = String(v)); }
#endif

    /**
     * @brief Copy Operator
     *
     * @param s : std::string cref = Constant Reference to a std::string to copy data from
     *
     * @exceptsafe
     *
     * @returns String ref = Reference to the modified Object
     *
     * @test tested in primitive/StringTest/Assignment Tests
     */
    inline String & operator = ( std::string const & s ) noexcept { return this->operator=(String(s)); } // NOLINT(misc-unconventional-assign-operator)

    /**
     * @brief Copy Operator
     *
     * @param e : ElementType = Element to assign to the String
     *
     * @exceptsafe
     *
     * @returns String ref = Reference to the modified Object
     *
     * @test tested in primitive/StringTest/Assignment Tests
     */
    inline String & operator = ( ElementType e ) noexcept { return this->operator=(String().append(e)); } // NOLINT(misc-unconventional-assign-operator)

    /**
     * @brief Copy Operator
     *
     * @param o : StringLiteral = Address to a C String to copy data from
     *
     * @exceptsafe
     *
     * @returns String ref = Reference to the modified Object
     *
     * @test tested in primitive/StringTest/Assignment Tests
     */
    inline String & operator = ( StringLiteral cString ) noexcept { return this->operator=(String(cString)); } // NOLINT(misc-unconventional-assign-operator)


    /**
     * @brief Function used to split string by token given, in an optional given number of tokens
     *
     * @param token : ElementType = value to split the string by
     * @param limit : Size = max number of tokens to split the string in
     *
     * @exceptsafe
     *
     * @returns LinkedList < String > = list of tokens resulted after splitting the string
     *
     * @test tested in primitive/StringTest/Split Tests
     */
    __CDS_NoDiscard auto split ( ElementType, Size = UINT32_MAX ) const noexcept -> LinkedList < String >;

    /**
     * @brief Function used to split string by tokens given in a String, in an optional given number of tokens
     *
     * @param delim : String cref = Constant Reference to the String containing the values to split the string by
     * @param limit : Size = max number of tokens to split the string in
     *
     * @exceptsafe
     *
     * @returns LinkedList < String > = list of tokens resulted after splitting the string
     *
     * @test tested in primitive/StringTest/Split Tests
     */
    __CDS_NoDiscard auto split ( String const &, Size = UINT32_MAX ) const noexcept -> LinkedList < String >;

    /**
     * @brief Function used to split string by string token given, in an optional given number of tokens
     *
     * @param token : String cref = Constant Reference to the token to split by
     * @param limit : Size = max number of tokens to split the string in
     *
     * @exceptsafe
     *
     * @returns LinkedList < String > = list of tokens resulted after splitting the string
     *
     * @test tested in primitive/StringTest/Split Tests
     */
    __CDS_NoDiscard __CDS_MaybeUnused auto splitByString ( String const &, Size = UINT32_MAX ) const noexcept -> LinkedList < String >;

    /**
     * @brief Variable indicating an invalid position resulted from a find operation
     */
    constexpr static Index INVALID_POS = -1;

    /**
     * @brief Function used to check whether String contains given element
     *
     * @param e : ElementType = element to check if it exists in a String
     *
     * @exceptsafe
     *
     * @returns bool = true if element exists in String, false otherwise
     *
     * @test tested in primitive/StringTest/Content Functions Tests
     */
    __CDS_NoDiscard auto inline contains ( ElementType e ) const noexcept -> bool { return this->findFirst( e ) != INVALID_POS; }

    /**
     * @brief Function used to check whether String contains given String
     *
     * @param e : String cref = Constant Reference to a String to check if Object contains it
     *
     * @exceptsafe
     *
     * @returns bool = true if element exists in String, false otherwise
     *
     * @test tested in primitive/StringTest/Content Functions Tests
     */
    __CDS_NoDiscard auto inline contains ( String const & e ) const noexcept -> bool { return this->findFirst( e ) != INVALID_POS; }

    /**
     * @brief Function used to check whether String contains given StringLiteral
     *
     * @param e : StringLiteral = Address to a C String to check if Object contains it
     *
     * @exceptsafe
     *
     * @returns bool = true if element exists in String, false otherwise
     *
     * @test tested in primitive/StringTest/Content Functions Tests
     */
    __CDS_NoDiscard auto inline contains ( StringLiteral e ) const noexcept -> bool { return this->findFirst( String(e) ) != INVALID_POS; }

    /**
     * @brief Function used to check whether String contains given std::string
     *
     * @param e : std::string cref = Constant Reference to a std::string to check if Object contains it
     *
     * @exceptsafe
     *
     * @returns bool = true if element exists in String, false otherwise
     *
     * @test tested in primitive/StringTest/Content Functions Tests
     */
    __CDS_NoDiscard auto inline contains ( std::string const & e ) const noexcept -> bool { return this->findFirst( String(e) ) != INVALID_POS; }

#if defined(CDS_QT)

    /**
     * @brief Function used to check whether String contains given QString
     *
     * @param e : QString cref = Constant Reference to a QString to check if Object contains it
     *
     * @exceptsafe
     *
     * @returns bool = true if element exists in String, false otherwise
     *
     * @test tested in primitive/StringTest/Content Functions Tests
     */
    inline auto contains (QString const & v) const noexcept -> bool { return this->contains(String(v)); }
#endif

#ifndef NDEBUG

    /**
     * @brief Diagnostic Debug Function
     *
     * @exceptsafe
     *
     * @returns String = Diagnostic String, containing structural info
     *
     * @test Not Applicable
     */
    __CDS_NoDiscard auto diag() const noexcept -> String;
#endif

    /**
     * @brief Print Operator
     *
     * @param out : std::ostream ref = Reference to an output stream to print on
     * @param s : String cref = Constant Reference to the String to print
     *
     * @exceptsafe
     *
     * @return std::ostream ref = Reference to the modified output stream
     *
     * @test Not Applicable
     */
    friend inline auto operator << ( std::ostream & out, String const & s ) noexcept -> std::ostream & {
        return ( out << (s._p == nullptr ? "null" : s._p) );
    }

    /**
     * @brief Function used to obtain hash value
     *
     * @exceptsafe
     *
     * @returns Index = hash value of the String
     *
     * @test Not Applicable
     */
    __CDS_NoDiscard auto hash () const noexcept -> Index override {
        return static_cast < Index > ( this->length() );
    }

    /**
     * @brief Function used to obtain a copy of this object
     *
     * @exceptsafe
     *
     * @returns String ptr = Address to a new String containing this object's data
     *
     * @test Not Applicable
     */
    __CDS_NoDiscard auto copy () const noexcept -> String * override {
        return new String( * this );
    }

    /**
     * @brief Function used to obtain the String representation of this object
     *
     * @exceptsafe
     *
     * @returns String = String representation of this object
     *
     * @test Not Applicable
     */
    __CDS_NoDiscard auto toString () const noexcept -> String override {
        return * this;
    }

    /**
     * @brief Function used to replace a section of the string with a replacement
     *
     * @param pos : Index = position to start replacement from
     * @param len : Size = length of replaced section
     * @param newInPlace : String cref = Constant Reference to the replacement to be placed
     *
     * @exceptsafe
     *
     * @returns String ref = Reference to the modified String
     *
     * @test tested in primitive/StringTest/Replace Tests
     */
    auto replace ( Index, Size, String const & ) noexcept -> String &;

    /**
     * @brief Function used to apply a function over each of the elements in the String iteratively
     *
     * @tparam Action = Callable type with void return type ( preferably ) and one input parameter representing an iterable element ( ElementType or ElementType ref or ElementType cref )
     * @param a : Action cref = Constant Reference to the Callable to supply the element to
     *
     * @throws Action's exceptions
     *
     * @returns String ref = Reference to the object after the iteration
     *
     * @test Tested in
     */
    template < typename Action >
    __CDS_MaybeUnused auto forEach ( Action const & ) noexcept (false) -> String &;
    template < typename Action >
    __CDS_MaybeUnused auto forEach ( Action const & ) const noexcept (false) -> String const &;

    template < typename Predicate >
    __CDS_MaybeUnused auto count ( Predicate const & ) noexcept (false) -> Size;
    template < typename Predicate >
    __CDS_MaybeUnused auto count ( Predicate const & ) const noexcept (false) -> Size;

    template < typename Predicate >
    __CDS_MaybeUnused inline auto some ( Predicate const & p, Size s ) noexcept (false) -> bool { return s <= this->count ( p ); }
    template < typename Predicate >
    __CDS_MaybeUnused inline auto some ( Predicate const & p, Size s ) const noexcept(false) -> bool { return s <= this->count ( p ); }

    template < typename Predicate >
    __CDS_MaybeUnused auto any ( Predicate const & p ) noexcept (false) -> bool { return 1u <= this->count(p); }
    template < typename Predicate >
    __CDS_MaybeUnused auto any ( Predicate const & p ) const noexcept (false) -> bool { return 1u <= this->count(p); }

    template < typename Predicate >
    __CDS_MaybeUnused auto all ( Predicate const & p ) noexcept (false) -> bool { return this->size() == this->count(p); }
    template < typename Predicate >
    __CDS_MaybeUnused auto all ( Predicate const & p ) const noexcept (false) -> bool { return this->size() == this->count(p); }

    __CDS_NoDiscard auto reversed() const noexcept -> String;

    __CDS_NoDiscard __CDS_MaybeUnused auto startsWith (String const &) const noexcept -> bool;
    __CDS_NoDiscard __CDS_MaybeUnused auto endsWith (String const &) const noexcept -> bool;

    __CDS_NoDiscard inline auto removePrefix (String const & prefix) noexcept -> String & {
        if ( this->length() < prefix.length() ) return * this;
        if ( this->substr(0, static_cast < Index > ( prefix.length() )) == prefix ) * this = this->substr(static_cast < Index > ( prefix.length() ));
        return * this;
    }

    __CDS_NoDiscard __CDS_MaybeUnused inline auto removePrefix (String const & prefix) const noexcept -> String { return String(*this).removePrefix(prefix); }

    __CDS_NoDiscard inline auto removeSuffix (String const & suffix) noexcept -> String & {
        if ( this->length() < suffix.length() ) return * this;
        if ( this->substr( static_cast < Index > ( this->length() ) - static_cast < Index > ( suffix.length() ) ) == suffix ) * this = this->substr(0, static_cast < Index > ( this->length() ) - static_cast < Index > ( suffix.length() ));
        return * this;
    }

    __CDS_NoDiscard inline auto removeSuffix (String const & suffix) const noexcept -> String { return String(*this).removeSuffix(suffix); }
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
    __CDS_NoDiscard constexpr inline auto equals ( const String::IteratorBase & i ) const noexcept -> bool { return this->_s == i._s && this->_pos == i._pos; }
    __CDS_NoDiscard inline auto value ( ) const noexcept (false) -> ElementType & { return this->_s->get(this->_pos); }

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
    __CDS_NoDiscard constexpr inline auto equals ( const String::ConstIteratorBase & i ) const noexcept -> bool { return this->_s == i._s && this->_pos == i._pos; }
    __CDS_NoDiscard inline auto value ( ) const noexcept -> ElementType { return this->_s->get(this->_pos); }

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

    __CDS_cpplang_VirtualConstexpr auto next () noexcept -> Iterator & final { this->_pos ++; return * this; }

    __CDS_cpplang_VirtualConstexpr auto operator ++ () noexcept -> Iterator & final { return this->next(); }
    inline auto operator ++ (int) noexcept -> Iterator { auto copy = * this; this->next(); return copy; }
};

class String::ConstIterator final : public ConstIteratorBase {
public:
    ConstIterator () noexcept = delete;
    explicit ConstIterator ( String const &, Index ) noexcept;
    ConstIterator ( String::ConstIterator const & ) noexcept = default;

    ~ConstIterator () noexcept final = default;

    __CDS_cpplang_VirtualConstexpr auto next () noexcept -> ConstIterator & final { this->_pos ++; return * this; }

    __CDS_cpplang_VirtualConstexpr auto operator ++ () noexcept -> ConstIterator & final { return this->next(); }
    inline auto operator ++ (int) noexcept -> ConstIterator { auto copy = * this; this->next(); return copy; }
};

class String::ReverseIterator final : public IteratorBase {
public:
    ReverseIterator () noexcept = delete;
    explicit ReverseIterator ( String &, Index ) noexcept;
    ReverseIterator ( String::ReverseIterator const & ) noexcept = default;

    ~ReverseIterator () noexcept final = default;

    __CDS_cpplang_VirtualConstexpr auto next () noexcept -> ReverseIterator & final { this->_pos --; return * this; }

    __CDS_cpplang_VirtualConstexpr auto operator ++ () noexcept -> ReverseIterator & final { return this->next(); }
    inline auto operator ++ (int) noexcept -> ReverseIterator { auto copy = * this; this->next(); return copy; }
};

class String::ConstReverseIterator final : public ConstIteratorBase {
public:
    ConstReverseIterator () noexcept = delete;
    explicit ConstReverseIterator ( String const &, Index ) noexcept;
    ConstReverseIterator ( String::ConstReverseIterator const & ) noexcept = default;

    ~ConstReverseIterator () noexcept final = default;

    __CDS_cpplang_VirtualConstexpr auto next () noexcept -> ConstReverseIterator & final { this->_pos --; return * this; }

    __CDS_cpplang_VirtualConstexpr auto operator ++ () noexcept -> ConstReverseIterator & final { return this->next(); }
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

#include <sstream>
inline auto Object::toString() const noexcept -> String {
    std::stringstream oss;
    oss << "Object at 0x" << std::hex << reinterpret_cast < AddressValueType > (this);
    return oss.str();
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

    __CDS_WarningSuppression_ArgumentPossibleUnexpectedValue_SuppressEnable

    std::memcpy ( this->_p, cString, this->_l + 1 );

    __CDS_WarningSuppression_ArgumentPossibleUnexpectedValue_SuppressDisable
}

inline String::String(CString cString) noexcept : CONSTR_CLEAR() {
    if ( cString == nullptr )
        return;

    auto len = strlen(cString);
    if ( len == 0 )
        return;

    this->_alloc(len);

    this->_l = len;

    __CDS_WarningSuppression_ArgumentPossibleUnexpectedValue_SuppressEnable

    std::memcpy ( this->_p, cString, this->_l + 1 );

    __CDS_WarningSuppression_ArgumentPossibleUnexpectedValue_SuppressDisable
}

inline String::String(String const & s) noexcept : CONSTR_CLEAR() {
    if ( s.empty() )
        return;

    this->_alloc(s._l);
    this->_l = s._l;

    __CDS_WarningSuppression_ArgumentPossibleUnexpectedValue_SuppressEnable

    std::memcpy ( this->_p, s._p, this->_l + 1 );

    __CDS_WarningSuppression_ArgumentPossibleUnexpectedValue_SuppressDisable
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

inline auto String::append (CString cString) noexcept -> String & {
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
inline auto String::end () noexcept -> Iterator { return Iterator ( * this, static_cast < Index > ( this->_l ) ); }
inline auto String::begin() const noexcept -> ConstIterator { return ConstIterator ( * this, 0 ); }
inline auto String::end() const noexcept -> ConstIterator { return ConstIterator ( * this, static_cast < Index > ( this->_l ) ); }
inline auto String::cbegin() const noexcept -> ConstIterator { return ConstIterator ( * this, 0 ); }
inline auto String::cend() const noexcept -> ConstIterator { return ConstIterator ( * this, static_cast < Index > ( this->_l ) ); }
inline auto String::rbegin() noexcept -> ReverseIterator { return ReverseIterator( * this, static_cast < Index > ( this->_l ) - 1 ); }
inline auto String::rend() noexcept -> ReverseIterator { return ReverseIterator( * this, -1 ); }
inline auto String::rbegin() const noexcept -> ConstReverseIterator { return ConstReverseIterator( * this, static_cast < Index > ( this->_l ) - 1 ); }
inline auto String::rend() const noexcept -> ConstReverseIterator { return ConstReverseIterator( * this, -1 ); }
inline auto String::crbegin() const noexcept -> ConstReverseIterator { return ConstReverseIterator( * this, static_cast < Index > ( this->_l ) - 1 ); }
inline auto String::crend() const noexcept -> ConstReverseIterator { return ConstReverseIterator( * this, -1 ); }

inline auto String::operator [] (Index i) noexcept (false) -> ElementType & {
    if ( this->empty() )
        throw String::StringNullAccess();

    if ( i < 0 )
        i += ( (-i) / static_cast < Index > ( this->size() ) + 1 ) * static_cast < Index > ( this->size() );
    if ( i >= static_cast<Index>(this->size()) )
        i = static_cast < Index > ( i ) % static_cast < Index > ( this->size() );

    return this->_p[i];
}

inline auto String::operator [] (Index i) const noexcept -> ElementType {
    if ( this->empty() )
        return '\0';

    if ( i < 0 )
        i += ( (-i) / static_cast < Index > ( this->size() ) + 1 ) * static_cast < Index > ( this->size() );
    if ( i >= static_cast<Index>(this->size()) )
        i = i % static_cast < Index > ( this->size() );

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

    __CDS_WarningSuppression_ArgumentPossibleUnexpectedValue_SuppressEnable

    std::memset(this->_p, constant, count); 

    __CDS_WarningSuppression_ArgumentPossibleUnexpectedValue_SuppressDisable

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

#if !defined(_MSC_VER)
#pragma clang diagnostic push
#pragma ide diagnostic ignored "ConstantConditionsOC"
#endif
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
#if !defined(_MSC_VER)
#pragma clang diagnostic pop
#endif

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
    for ( auto c : * this ) {
        (void)c;

        if (this->size() - i >= o.size() && this->substr(i, i + static_cast < Index > ( o.size())) == o)
            return i;
        else
            i++;
    }
    return INVALID_POS;
}

inline auto String::findLast ( ElementType e ) const noexcept -> Index {
    auto i = static_cast < Index > ( this->size() ) - 1;
    for ( auto it = this->rbegin(); it != this->rend(); it++ )
        if ( it.value() == e )
            return i;
        else
            i--;
    return INVALID_POS;
}

inline auto String::findLast ( String const & o ) const noexcept -> Index {
    auto i = static_cast < Index > ( this->size() ) - static_cast < Index > ( o.length() );
    for ( ; i >= 0; i-- )
        if ( this->substr(i, i + static_cast < Index > ( o.length() )) == o )
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
    auto i = static_cast < Index > (this->size()) - 1;
    for ( auto it = this->rbegin(); it != this->rend(); it++ )
        if ( o.contains(it.value()) )
            return i;
        else
            i--;
    return INVALID_POS;
}

inline auto String::findLastNotOf ( String const & o ) const noexcept -> Index {
    auto i = static_cast < Index > (this->size()) - 1;
    for ( auto it = this->rbegin(); it != this->rend(); it++ )
        if ( ! o.contains(it.value()) )
            return i;
        else
            i--;
    return INVALID_POS;
}

inline auto String::substr(Index from, Index to) const noexcept -> String {
    if ( to == -1 || to > static_cast<Index>(this->size()) )
        to = static_cast < Index > (this->size());
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
    String right = this->substr(pos + static_cast < Index > ( len ));

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

__CDS_MaybeUnused inline auto String::startsWith(String const & str) const noexcept -> bool {
    if ( str.size() > this->size() ) return false;
    return this->substr(0, static_cast < Index > ( str.size() )) == str;
}

__CDS_MaybeUnused inline auto String::endsWith(String const & str) const noexcept -> bool {
    if ( str.size() > this->size() ) return false;
    return this->substr(static_cast < Index > ( this->size() ) - static_cast < Index > ( str.size() )) == str;
}

inline auto operator "" _obj (const char * pString, std::size_t length __CDS_MaybeUnused ) noexcept -> String {
    return pString;
}

inline auto operator "" _s (const char * pString, std::size_t length __CDS_MaybeUnused ) noexcept -> String {
    return pString;
}

#undef CONSTR_CLEAR

#include <CDS/Types>

namespace dataTypes {
    template<> auto hash<String>(String const &o) noexcept -> Index { return static_cast < Index > ( o.length() ); }
}

#endif //CDS_STRING_HPP
