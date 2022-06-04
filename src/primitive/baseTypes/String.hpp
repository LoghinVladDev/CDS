//
// Created by loghin on 22.01.2021.
//

#ifndef CDS_STRING_HPP
#define CDS_STRING_HPP

#include <CDS/Concepts>
#include <CDS/Options>
#include <CDS/Limits>


namespace cds {

    template < typename T >
    class DoubleLinkedList;
    
    template < typename C >
    class Sequence;

    template < typename C >
    class Collection;

}

#include <CDS/Object>
#include <CDS/Traits>
#include <CDS/Conversion>
#include <CDS/Memory>

#if defined(CDS_QT)
#include <QString>
#endif

#include <cstring>

#include <ostream>
#include <string>

#include <cstdarg>

namespace cds {

    /**
     * @class String, represents a String object, ascii encoded
     */
    class String : public Object {
    public:
        /**
         * @brief Represents an element in the string, char by default, done for future feature compatibility ( widechar support )
         */
        using ElementType = char;

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
            __CDS_NoDiscard __CDS_cpplang_VirtualConstexpr auto what() const noexcept -> StringLiteral override {
                return "Null Access Exception : Requested Reference to Element at Index 0 for Empty String.";
            }
        };

        class FormatException : public std::exception {

            /**
             * @brief Function used to obtain the Exception's message
             *
             * @exceptsafe
             *
             * @return StringLiteral = Message as C String Literal
             */
            __CDS_NoDiscard __CDS_cpplang_VirtualConstexpr auto what() const noexcept -> StringLiteral override {
                return "Format Exception";
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

    #if defined(_MSC_VER)

    #pragma push_macro("min")
    #pragma push_macro("max")
    #undef min
    #undef max

    #endif

        /**
         * @brief Private Function used to allocate more bytes to the String Object, keeping its' original contents
         *
         * @exceptsafe
         *
         * @test Does not require testing
         */
        __CDS_cpplang_ConstexprDynamicAllocation void _alloc(Size size) noexcept {
            if (this->_l + size + 1u < this->_c) {
                return;
            }

            auto newCap = std::max(size + this->_l, 2u * this->_c) + 1u;
            auto newArea = Memory :: instance().createArray < ElementType > (newCap);

            if (this->_p != nullptr) {
                (void) std :: memcpy(newArea, this->_p, this->_l);
            }

            (void) std :: memset(newArea + this->_l, 0, newCap - this->_l);

            Memory :: instance().destroyArray ( this->_p );

            this->_p = newArea;
            this->_c = newCap;
        }

    #if defined(_MSC_VER)

    #pragma pop_macro("max")
    #pragma pop_macro("min")

    #endif

        /**
         * @class String::IteratorBase, Base of String Iterators, containing common functions
         */
        class IteratorBase {
        protected:

            /**
             * @brief Address to the String, mutable as to allow const functions with modifications over address location
             */
            String mutable * _s {nullptr}; // NOLINT(clion-misra-cpp2008-11-0-1)

            /**
             * @brief Position in the String
             */
            Index _pos          {0}; // NOLINT(clion-misra-cpp2008-11-0-1)

            /**
             * @brief Base Constructor, from a given String and Index in String
             *
             * @param string : String ref = Reference to a String object
             * @param index : Index = index to a String's position
             *
             * @exceptsafe
             *
             * @test Tested in primitive/StringTest/Iterable Tests
             */
            constexpr IteratorBase (String & string, Index index ) noexcept :
                    _s (& string ),
                    _pos (index ) {

            }

            /**
             * @brief Copy Constructor
             *
             * @param s : String :: IteratorBase cref = Constant Reference to a String IteratorBase derived object
             *
             * @exceptsafe
             *
             * @test Tested in primitive/StringTest/Iterable Tests
             */
            constexpr IteratorBase ( String::IteratorBase const & ) = default;

        public:

            /**
             * @brief Default Constructor, deleted as it needs to be created over Iterator
             *
             * @exceptsafe
             *
             * @test Tested in primitive/StringTest/Iterable Tests
             */
            constexpr IteratorBase() noexcept = delete;

            /**
             * @brief Destructor
             *
             * @exceptsafe
             *
             * @test Tested in primitive/StringTest/Iterable Tests
             */
            __CDS_cpplang_ConstexprDestructor virtual ~IteratorBase() noexcept = default;

            /**
             * @brief Function used to shift the iterator to next element
             *
             * @exceptsafe
             *
             * @returns IteratorBase ref = Reference to the modified Object
             *
             * @test Tested in primitive/StringTest/Iterable Tests
             */
            __CDS_cpplang_ConstexprPureAbstract virtual auto next() -> IteratorBase & = 0;

            /**
             * @brief Function used to compare Iterator values
             *
             * @param iterator : String::IteratorBase cref = Constant Reference to a String IteratorBase derived object
             *
             * @exceptsafe
             *
             * @returns bool = true if Iterators are equal, false otherwise
             *
             * @test Tested in primitive/StringTest/Iterable Tests
             */
            __CDS_NoDiscard constexpr auto equals ( const String::IteratorBase & iterator ) const noexcept -> bool {
                return this->_s == iterator._s && this->_pos == iterator._pos;
            }

            /**
             * @brief Function used to obtain value at Iterator Position
             *
             * @exceptsafe
             *
             * @returns ElementType ref = Reference to the element at Iterator Position
             *
             * @test Tested in primitive/StringTest/Iterable Tests
             */
            __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto value ( ) const noexcept (false) -> ElementType & {
                return this->_s->get(this->_pos);
            }

            /**
             * @brief Function used to shift the iterator to next element
             *
             * @exceptsafe
             *
             * @returns IteratorBase ref = Reference to the modified Object
             *
             * @test Tested in primitive/StringTest/Iterable Tests
             */
            __CDS_cpplang_VirtualConstexpr virtual auto operator ++ () noexcept -> IteratorBase & {
                return this->next();
            }

            /**
             * @brief Function used to compare Iterator values
             *
             * @param iterator : String::IteratorBase cref = Constant Reference to a String IteratorBase derived object
             *
             * @exceptsafe
             *
             * @returns bool = true if Iterators are equal, false otherwise
             *
             * @test Tested in primitive/StringTest/Iterable Tests
             */
            constexpr auto operator == ( IteratorBase const & iterator ) const noexcept -> bool {
                return this->equals(iterator);
            }

            /**
             * @brief Function used to compare Iterator values
             *
             * @param i : String::IteratorBase cref = Constant Reference to a String IteratorBase derived object
             *
             * @exceptsafe
             *
             * @returns bool = true if Iterators are not equal, false otherwise
             *
             * @test Tested in primitive/StringTest/Iterable Tests
             */
            constexpr auto operator != ( IteratorBase const & iterator ) const noexcept -> bool {
                return ! this->equals(iterator);
            }

            /**
             * @brief Function used to obtain difference size between two iterator positions
             *
             * @param i : String::IteratorBase cref = Constant Reference to a String IteratorBase derived object
             *
             * @exceptsafe
             *
             * @returns SignedSize = difference between the left and right Iterators, in positions
             *
             * @test Tested in primitive/StringTest/Iterable Tests
             */
            constexpr auto operator - ( IteratorBase const & iteratorBase ) const noexcept -> SignedSize {
                return this->_pos - iteratorBase._pos;
            }

            /**
             * @brief Function used to obtain value at Iterator Position
             *
             * @exceptsafe
             *
             * @returns ElementType ref = Reference to the element at Iterator Position
             *
             * @test Tested in primitive/StringTest/Iterable Tests
             */
            __CDS_cpplang_ConstexprConditioned auto operator * ( ) const noexcept -> ElementType & {
                return this->value();
            }
        };

        /**
         * @class String::ConstIteratorBase, Base of String ConstIterators, containing common functions
         */
        class ConstIteratorBase {
        protected:

            /**
             * @brief Address to the String
             */
            const String *   _s {nullptr}; // NOLINT(clion-misra-cpp2008-11-0-1)

            /**
             * @brief Position in the String
             */
            Index _pos          {0}; // NOLINT(clion-misra-cpp2008-11-0-1)

            /**
             * @brief Base Constructor, from a given String and Index in String
             *
             * @param string : String cref = Constant Reference to a String object
             * @param index : Index = index to a String's position
             *
             * @exceptsafe
             *
             * @test Tested in primitive/StringTest/Iterable Tests
             */
            constexpr ConstIteratorBase (String const & string, Index index ) noexcept :
                    _s(& string),
                    _pos(index) {

            }

            /**
             * @brief Copy Constructor
             *
             * @param s : String :: ConstIteratorBase cref = Constant Reference to a String ConstIteratorBase derived object
             *
             * @exceptsafe
             *
             * @test Tested in primitive/StringTest/Iterable Tests
             */
            constexpr ConstIteratorBase ( String :: ConstIteratorBase const & ) = default;

        public:

            /**
             * @brief Default Constructor, deleted as it needs to be created over Iterator
             *
             * @exceptsafe
             *
             * @test Tested in primitive/StringTest/Iterable Tests
             */
            constexpr ConstIteratorBase() noexcept = delete;

            /**
             * @brief Destructor
             *
             * @exceptsafe
             *
             * @test Tested in primitive/StringTest/Iterable Tests
             */
            __CDS_cpplang_ConstexprDestructor virtual ~ConstIteratorBase() noexcept = default;

            /**
             * @brief Function used to shift the iterator to next element
             *
             * @exceptsafe
             *
             * @returns ConstIteratorBase ref = Reference to the modified Object
             *
             * @test Tested in primitive/StringTest/Iterable Tests
             */
            __CDS_cpplang_ConstexprPureAbstract virtual auto next() -> ConstIteratorBase & = 0;

            /**
             * @brief Function used to compare Iterator values
             *
             * @param iterator : String::ConstIteratorBase cref = Constant Reference to a String ConstIteratorBase derived object
             *
             * @exceptsafe
             *
             * @returns bool = true if Iterators are equal, false otherwise
             *
             * @test Tested in primitive/StringTest/Iterable Tests
             */
            __CDS_NoDiscard constexpr auto equals ( String :: ConstIteratorBase const & iterator ) const noexcept -> bool {
                return this->_s == iterator._s && this->_pos == iterator._pos;
            }

            /**
             * @brief Function used to obtain value at Iterator Position
             *
             * @exceptsafe
             *
             * @returns ElementType = Copy of the element at Iterator Position
             *
             * @test Tested in primitive/StringTest/Iterable Tests
             */
            __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto value ( ) const noexcept -> ElementType {
                return this->_s->get(this->_pos);
            }

            /**
             * @brief Function used to shift the iterator to next element
             *
             * @exceptsafe
             *
             * @returns ConstIteratorBase ref = Reference to the modified Object
             *
             * @test Tested in primitive/StringTest/Iterable Tests
             */
            __CDS_cpplang_VirtualConstexpr virtual auto operator ++ () noexcept -> ConstIteratorBase & {
                return this->next();
            }

            /**
             * @brief Function used to compare Iterator values
             *
             * @param iterator : String::ConstIteratorBase cref = Constant Reference to a String ConstIteratorBase derived object
             *
             * @exceptsafe
             *
             * @returns bool = true if Iterators are equal, false otherwise
             *
             * @test Tested in primitive/StringTest/Iterable Tests
             */
            constexpr auto operator == ( ConstIteratorBase const & iterator ) const noexcept -> bool {
                return this->equals(iterator);
            }

            /**
             * @brief Function used to compare Iterator values
             *
             * @param i : String::ConstIteratorBase cref = Constant Reference to a String ConstIteratorBase derived object
             *
             * @exceptsafe
             *
             * @returns bool = true if Iterators are not equal, false otherwise
             *
             * @test Tested in primitive/StringTest/Iterable Tests
             */
            constexpr auto operator != ( ConstIteratorBase const & iterator ) const noexcept -> bool {
                return ! this->equals(iterator);
            }

            /**
             * @brief Function used to obtain difference size between two iterator positions
             *
             * @param i : String::ConstIteratorBase cref = Constant Reference to a String ConstIteratorBase derived object
             *
             * @exceptsafe
             *
             * @returns SignedSize = difference between the left and right Iterators, in positions
             *
             * @test Tested in primitive/StringTest/Iterable Tests
             */
            constexpr auto operator - ( ConstIteratorBase const & iterator ) const noexcept -> SignedSize {
                return this->_pos - iterator._pos;
            }

            /**
             * @brief Function used to obtain value at Iterator Position
             *
             * @exceptsafe
             *
             * @returns ElementType = Copy of the element at Iterator Position
             *
             * @test Tested in primitive/StringTest/Iterable Tests
             */
            __CDS_cpplang_ConstexprConditioned auto operator * ( ) const noexcept -> ElementType {
                return this->value();
            }
        };
    public:

        /**
         * @class String::Iterator, forward iterator over a mutable String object
         */
        class Iterator : public String::IteratorBase {
        public:

            /**
             * @brief Default constructor, deleted
             */
            constexpr Iterator () noexcept = delete;

            /**
             * @brief Base Constructor, from a given String and Index in String
             *
             * @param string : String ref = Reference to a String object
             * @param index : Index = index to a String's position
             *
             * @exceptsafe
             *
             * @test Tested in primitive/StringTest/Iterable Tests
             */
            constexpr Iterator (String & string, Index index ) noexcept :
                    IteratorBase(string, index) {

            }

            /**
             * @brief Copy Constructor
             *
             * @param s : String :: Iterator cref = Constant Reference to a String Iterator derived object
             *
             * @exceptsafe
             *
             * @test Tested in primitive/StringTest/Iterable Tests
             */
            constexpr Iterator ( String::Iterator const & ) noexcept = default;

            /**
             * @brief Destructor
             *
             * @exceptsafe
             *
             * @test Tested in primitive/StringTest/Iterable Tests
             */
            __CDS_cpplang_ConstexprDestructor ~Iterator () noexcept override = default;

            /**
             * @brief Function used to shift the iterator to next element
             *
             * @exceptsafe
             *
             * @returns Iterator ref = Reference to the modified Object
             *
             * @test Tested in primitive/StringTest/Iterable Tests
             */
            __CDS_cpplang_VirtualConstexpr auto next () noexcept -> Iterator & final {
                this->_pos ++; return * this;
            }

            /**
             * @brief Function used to shift the iterator to next element
             *
             * @exceptsafe
             *
             * @returns Iterator ref = Reference to the modified Object
             *
             * @test Tested in primitive/StringTest/Iterable Tests
             */
            __CDS_cpplang_VirtualConstexpr auto operator ++ () noexcept -> Iterator & final {
                return this->next();
            }

            /**
             * @brief Function used to shift the iterator to next element into a new Iterator element
             *
             * @exceptsafe
             *
             * @returns Iterator ref = New Iterator shifted based to original
             *
             * @test Tested in primitive/StringTest/Iterable Tests
             */
            __CDS_cpplang_ConstexprDestructor auto operator ++ (int) noexcept -> Iterator {
                auto copy = * this;
                (void) this->next();
                return copy;
            }
        };

        /**
         * @class String::ConstIterator, forward iterator over an immutable String object
         */
        class ConstIterator : public ConstIteratorBase {
        public:

            /**
             * @brief Default constructor, deleted
             */
            constexpr ConstIterator () noexcept = delete;

            /**
             * @brief Base Constructor, from a given String and Index in String
             *
             * @param string : String ref = Reference to a String object
             * @param index : Index = index to a String's position
             *
             * @exceptsafe
             *
             * @test Tested in primitive/StringTest/Iterable Tests
             */
            constexpr ConstIterator (String const & string, Index index ) noexcept :
                    ConstIteratorBase(string, index) {

            }

            /**
             * @brief Copy Constructor
             *
             * @param s : String :: Iterator cref = Constant Reference to a String Iterator derived object
             *
             * @exceptsafe
             *
             * @test Tested in primitive/StringTest/Iterable Tests
             */
            constexpr ConstIterator ( String::ConstIterator const & ) noexcept = default;

            /**
             * @brief Destructor
             *
             * @exceptsafe
             *
             * @test Tested in primitive/StringTest/Iterable Tests
             */
            __CDS_cpplang_ConstexprDestructor ~ConstIterator () noexcept override = default;

            /**
             * @brief Function used to shift the iterator to next element
             *
             * @exceptsafe
             *
             * @returns Iterator ref = Reference to the modified Object
             *
             * @test Tested in primitive/StringTest/Iterable Tests
             */
            __CDS_cpplang_VirtualConstexpr auto next () noexcept -> ConstIterator & final {
                this->_pos ++; return * this;
            }

            /**
             * @brief Function used to shift the iterator to next element
             *
             * @exceptsafe
             *
             * @returns Iterator ref = Reference to the modified Object
             *
             * @test Tested in primitive/StringTest/Iterable Tests
             */
            __CDS_cpplang_VirtualConstexpr auto operator ++ () noexcept -> ConstIterator & final {
                return this->next();
            }

            /**
             * @brief Function used to shift the iterator to next element into a new Iterator element
             *
             * @exceptsafe
             *
             * @returns Iterator ref = New Iterator shifted based to original
             *
             * @test Tested in primitive/StringTest/Iterable Tests
             */
            __CDS_cpplang_ConstexprDestructor auto operator ++ (int) noexcept -> ConstIterator {
                auto copy = * this;
                (void) this->next();
                return copy;
            }
        };

        /**
         * @class String::Iterator, backwards iterator over a mutable String object
         */
        class ReverseIterator : public IteratorBase {
        public:

            /**
             * @brief Default constructor, deleted
             */
            constexpr ReverseIterator () noexcept = delete;

            /**
             * @brief Base Constructor, from a given String and Index in String
             *
             * @param string : String ref = Reference to a String object
             * @param index : Index = index to a String's position
             *
             * @exceptsafe
             *
             * @test Tested in primitive/StringTest/Iterable Tests
             */
            constexpr ReverseIterator (String & string, Index index ) noexcept :
                    IteratorBase(string, index) {

            }

            /**
             * @brief Copy Constructor
             *
             * @param s : String :: Iterator cref = Constant Reference to a String Iterator derived object
             *
             * @exceptsafe
             *
             * @test Tested in primitive/StringTest/Iterable Tests
             */
            constexpr ReverseIterator ( String::ReverseIterator const & ) noexcept = default;

            /**
             * @brief Destructor
             *
             * @exceptsafe
             *
             * @test Tested in primitive/StringTest/Iterable Tests
             */
            __CDS_cpplang_ConstexprDestructor ~ReverseIterator () noexcept override = default;

            /**
             * @brief Function used to shift the iterator to next element
             *
             * @exceptsafe
             *
             * @returns Iterator ref = Reference to the modified Object
             *
             * @test Tested in primitive/StringTest/Iterable Tests
             */
            __CDS_cpplang_VirtualConstexpr auto next () noexcept -> ReverseIterator & final {
                this->_pos --;
                return * this;
            }

            /**
             * @brief Function used to shift the iterator to next element
             *
             * @exceptsafe
             *
             * @returns Iterator ref = Reference to the modified Object
             *
             * @test Tested in primitive/StringTest/Iterable Tests
             */
            __CDS_cpplang_VirtualConstexpr auto operator ++ () noexcept -> ReverseIterator & final {
                return this->next();
            }

            /**
             * @brief Function used to shift the iterator to next element into a new Iterator element
             *
             * @exceptsafe
             *
             * @returns Iterator ref = New Iterator shifted based to original
             *
             * @test Tested in primitive/StringTest/Iterable Tests
             */
            __CDS_cpplang_ConstexprDestructor auto operator ++ (int) noexcept -> ReverseIterator {
                auto copy = * this;
                (void) this->next();
                return copy;
            }
        };

        /**
         * @class String::Iterator, backwards iterator over an immutable String object
         */
        class ConstReverseIterator : public ConstIteratorBase {
        public:

            /**
             * @brief Default constructor, deleted
             */
            constexpr ConstReverseIterator () noexcept = delete;

            /**
             * @brief Base Constructor, from a given String and Index in String
             *
             * @param string : String ref = Reference to a String object
             * @param index : Index = index to a String's position
             *
             * @exceptsafe
             *
             * @test Tested in primitive/StringTest/Iterable Tests
             */
            constexpr ConstReverseIterator (String const & string, Index index ) noexcept :
                    ConstIteratorBase(string, index) {

            }

            /**
             * @brief Copy Constructor
             *
             * @param s : String :: Iterator cref = Constant Reference to a String Iterator derived object
             *
             * @exceptsafe
             *
             * @test Tested in primitive/StringTest/Iterable Tests
             */
            constexpr ConstReverseIterator ( String::ConstReverseIterator const & ) noexcept = default;

            /**
             * @brief Destructor
             *
             * @exceptsafe
             *
             * @test Tested in primitive/StringTest/Iterable Tests
             */
            __CDS_cpplang_ConstexprDestructor ~ConstReverseIterator () noexcept override = default;

            /**
             * @brief Function used to shift the iterator to next element
             *
             * @exceptsafe
             *
             * @returns Iterator ref = Reference to the modified Object
             *
             * @test Tested in primitive/StringTest/Iterable Tests
             */
            __CDS_cpplang_VirtualConstexpr auto next () noexcept -> ConstReverseIterator & final {
                this->_pos --;
                return * this;
            }

            /**
             * @brief Function used to shift the iterator to next element
             *
             * @exceptsafe
             *
             * @returns Iterator ref = Reference to the modified Object
             *
             * @test Tested in primitive/StringTest/Iterable Tests
             */
            __CDS_cpplang_VirtualConstexpr auto operator ++ () noexcept -> ConstReverseIterator & final {
                return this->next();
            }

            /**
             * @brief Function used to shift the iterator to next element into a new Iterator element
             *
             * @exceptsafe
             *
             * @returns Iterator ref = New Iterator shifted based to original
             *
             * @test Tested in primitive/StringTest/Iterable Tests
             */
            __CDS_cpplang_ConstexprDestructor auto operator ++ (int) noexcept -> ConstReverseIterator {
                auto copy = * this;
                (void) this->next();
                return copy;
            }
        };

        /**
         * @brief Default Constructor
         *
         * @exceptsafe
         *
         * @test tested in primitive/StringTest/Constructor Tests
         */
        constexpr String () noexcept = default;

        /**
         * @brief Copy Constructor
         *
         * @param string : String cref = Constant Reference to the String to copy from
         *
         * @exceptsafe
         *
         * @test tested in primitive/StringTest/Constructor Tests
         */
        __CDS_cpplang_ConstexprConditioned String (String const & string) noexcept {

            if ( string.empty() ) {
                return;
            }

            this->_alloc(string._l);
            this->_l = string._l;

            __CDS_WarningSuppression_ArgumentPossibleUnexpectedValue_SuppressEnable

            (void) std::memcpy (this->_p, string._p, this->_l + 1llu );

            __CDS_WarningSuppression_ArgumentPossibleUnexpectedValue_SuppressDisable
        }

        __CDS_cpplang_ConstexprConditioned String (String && string) noexcept :
                _p(exchange(string._p, nullptr)),
                _l(exchange(string._l, 0)),
                _c(exchange(string._c, 0)){

        }

    #if defined(_MSC_VER)

    #pragma push_macro("min")
    #pragma push_macro("max")
    #undef min
    #undef max

    #endif

        /**
         * @brief Constructor with given String Literal
         *
         * @param cString : StringLiteral = pointer to copy data from
         *
         * @exceptsafe
         *
         * @test tested in primitive/StringTest/Constructor Tests
         */
        __CDS_cpplang_ConstexprConditioned String(StringLiteral cString, Size length = UINT64_MAX ) noexcept { // NOLINT(google-explicit-constructor)

            if ( cString == nullptr ) {
                return;
            }

            auto len = std::min(static_cast < Size > (strlen(cString)), length);
            if ( len == 0u ) {
                return;
            }

            this->_alloc(len);

            this->_l = len;

            __CDS_WarningSuppression_ArgumentPossibleUnexpectedValue_SuppressEnable

            this->_p[this->_l] = '\0';
            (void) std::memcpy ( this->_p, cString, this->_l );

            __CDS_WarningSuppression_ArgumentPossibleUnexpectedValue_SuppressDisable
        }

        /**
         * @brief Constructor with given C String value ( char * )
         *
         * @param cString : CString = pointer to copy data from
         *
         * @exceptsafe
         *
         * @test tested in primitive/StringTest/Constructor Tests
         */
        __CDS_cpplang_ConstexprConditioned String(CString cString, Size length = UINT64_MAX) noexcept { // NOLINT(google-explicit-constructor)
            if ( cString == nullptr ) {
                return;
            }

            auto len = std::min(static_cast < Size > (strlen(cString)), length);
            if ( len == 0u ) {
                return;
            }

            this->_alloc(len);

            this->_l = len;

            __CDS_WarningSuppression_ArgumentPossibleUnexpectedValue_SuppressEnable

            this->_p[this->_l] = '\0';
            (void) std::memcpy ( this->_p, cString, this->_l );

            __CDS_WarningSuppression_ArgumentPossibleUnexpectedValue_SuppressDisable
        }

    #if defined(_MSC_VER)

    #pragma pop_macro("max")
    #pragma pop_macro("min")

    #endif

        /**
         * @brief Constructor with given std::string
         *
         * @param string : std::string cref = Constant Reference to the std::string to copy from
         *
         * @exceptsafe
         *
         * @test tested in primitive/StringTest/Constructor Tests
         */
        __CDS_OptionalInline String(std::string const & string) noexcept { // NOLINT(google-explicit-constructor)

            if ( string.empty() ) {
                return;
            }

            this->_alloc(string.size());

            this->_l = string.size();
            (void) std::memcpy(this->_p, string.c_str(), string.size());
        }

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
        __CDS_cpplang_ConstexprConditioned String(Size count, ElementType constant) noexcept {

            if ( count == 0u ) {
                return;
            }

            this->_alloc(count);

            __CDS_WarningSuppression_ArgumentPossibleUnexpectedValue_SuppressEnable

            (void) std::memset(this->_p, constant, count);

            __CDS_WarningSuppression_ArgumentPossibleUnexpectedValue_SuppressDisable

            this->_l = count;
        }

        /**
         * @brief Constructor which initializes String from characters between the two given iterators
         *
         * @param begin : std::string::iterator cref = Constant Reference to the iterator to begin from
         * @param end : std::string::iterator cref = Constant Reference to the iterator to end at
         *
         * @exceptsafe
         *
         * @test tested in primitive/StringTest/Constructor Tests
         */
        __CDS_cpplang_ConstexprSTLIteratorOp String(std::string::iterator const & begin, std::string::iterator const & end) noexcept {

            if ( end - begin <= 0 ) {
                return;
            }

            this->_alloc(end - begin); // NOLINT(clion-misra-cpp2008-5-0-4)

            for ( auto it = begin; it != end; it++ ) { // NOLINT(clion-misra-cpp2008-6-5-1)
                this->_p[this->_l++] = *it;
            }
        }

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
        __CDS_cpplang_ConstexprDestructor String(IteratorBase const & begin, IteratorBase const & end) noexcept {

            bool reversed = dynamic_cast < Iterator const * > ( & begin ) == nullptr;
            if ( ! reversed && end - begin <= 0 || reversed && begin - end <= 0) {
                return;
            }

            this->_alloc(! reversed ? end - begin : begin - end); // NOLINT(clion-misra-cpp2008-5-0-4)

            if ( ! reversed ) {
                for ( auto it = dynamic_cast < Iterator const & > ( begin ); it != end; it.next() ) { // NOLINT(clion-misra-cpp2008-6-5-1)
                    this->_p[this->_l++] = *it;
                }
            } else {
                for ( auto it = dynamic_cast < ReverseIterator const & > ( begin ); it != end; it.next() ) { // NOLINT(clion-misra-cpp2008-6-5-1)
                    this->_p[this->_l++] = *it;
                }
            }
        }

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
        __CDS_cpplang_ConstexprDestructor String(ConstIteratorBase const & begin, ConstIteratorBase const & end) noexcept {

            bool reversed = dynamic_cast < ConstIterator const * > ( & begin ) == nullptr;
            if ( ! reversed && end - begin <= 0 || reversed && begin - end <= 0) {
                return;
            }

            this->_alloc(! reversed ? end - begin : begin - end); // NOLINT(clion-misra-cpp2008-5-0-4)

            if ( ! reversed ) {
                for ( auto it = dynamic_cast < ConstIterator const & > ( begin ); it != end; it.next() ) { // NOLINT(clion-misra-cpp2008-6-5-1)
                    this->_p[this->_l++] = *it;
                }
            } else {
                for ( auto it = dynamic_cast < ConstReverseIterator const & > ( begin ); it != end; it.next() ) { // NOLINT(clion-misra-cpp2008-6-5-1)
                    this->_p[this->_l++] = *it;
                }
            }
        }

        /**
         * @brief Constructor which initializes String from characters in a given std::initializer_list
         *
         * @param list : std::initializer_list < ElementType > cref = Constant Reference to the initializer_list containing the characters to add
         *
         * @exceptsafe
         *
         * @test tested in primitive/StringTest/Constructor Tests
         */
        __CDS_cpplang_ConstexprConditioned String(std::initializer_list<ElementType> const & list) noexcept {

            if ( list.size() == 0u ) {
                return;
            }

            this->_alloc(list.size());

            for ( auto element : list ) { // NOLINT(clion-misra-cpp2008-5-0-11)
                this->_p[this->_l++] = element;
            }
        }

    #if defined(CDS_QT)

        /**
         * @brief Constructor which initializes String from a QString
         *
         * @param qString : QString cref = Constant Reference to the QString to construct from
         *
         * @exceptsafe
         *
         * @test tested in MSK
         */
        String(QString const & qString) noexcept : // NOLINT(google-explicit-constructor)
                String(qString.toStdString()) {

        }

    #endif

        __CDS_WarningSuppression_DelegateCtorSuppressUninitializedMembers_SuppressEnable

        /**
         * @brief Constructor which initializes String from a CDS/Object's String representation
         *
         * @param object : Object cref = Constant Reference to a CDS/Object
         *
         * @exceptsafe
         *
         * @test tested in primitive/StringTest/Constructor Tests
         */
        __CDS_OptimalInline String (Object const & object) noexcept : // NOLINT(google-explicit-constructor)
                String(object.toString()) {

        }

        /**
         * @brief Constructor which initializes String from a raw uint8 value
         *
         * @param value : uint8 = Value to represent in the String
         *
         * @exceptsafe
         *
         * @test tested in primitive/StringTest/Constructor Tests
         */
        __CDS_OptimalInline String (uint8 value) noexcept : // NOLINT(google-explicit-constructor,clion-misra-cpp2008-12-1-3)
                String(String().append(value)) {

        }

        /**
         * @brief Constructor which initializes String from a raw uint16 value
         *
         * @param value : uint16 = Value to represent in the String
         *
         * @exceptsafe
         *
         * @test tested in primitive/StringTest/Constructor Tests
         */
        __CDS_OptimalInline String (uint16 value) noexcept : // NOLINT(google-explicit-constructor,clion-misra-cpp2008-12-1-3)
                String(String().append(value)) {

        }

        /**
         * @brief Constructor which initializes String from a raw uint32 value
         *
         * @param value : uint32 = Value to represent in the String
         *
         * @exceptsafe
         *
         * @test tested in primitive/StringTest/Constructor Tests
         */
        __CDS_OptimalInline String (uint32 value) noexcept : // NOLINT(google-explicit-constructor,clion-misra-cpp2008-12-1-3)
                String(String().append(value)) {

        }

        /**
         * @brief Constructor which initializes String from a raw uint64 value
         *
         * @param value : uint64 = Value to represent in the String
         *
         * @exceptsafe
         *
         * @test tested in primitive/StringTest/Constructor Tests
         */
        __CDS_OptimalInline String (uint64 value) noexcept : // NOLINT(google-explicit-constructor,clion-misra-cpp2008-12-1-3)
                String(String().append(value)) {

        }

        /**
         * @brief Constructor which initializes String from a raw sint8 value
         *
         * @param value : sint8 = Value to represent in the String
         *
         * @exceptsafe
         *
         * @test tested in primitive/StringTest/Constructor Tests
         */
        __CDS_OptimalInline String (sint8 value) noexcept : // NOLINT(google-explicit-constructor,clion-misra-cpp2008-12-1-3)
                String(String().append(value)) {

        }

        /**
         * @brief Constructor which initializes String from a raw sint16 value
         *
         * @param value : sint16 = Value to represent in the String
         *
         * @exceptsafe
         *
         * @test tested in primitive/StringTest/Constructor Tests
         */
        __CDS_OptimalInline String (sint16 value) noexcept : // NOLINT(google-explicit-constructor,clion-misra-cpp2008-12-1-3)
                String(String().append(value)) {

        }

        /**
         * @brief Constructor which initializes String from a raw sint32 value
         *
         * @param value : sint32 = Value to represent in the String
         *
         * @exceptsafe
         *
         * @test tested in primitive/StringTest/Constructor Tests
         */
        __CDS_OptimalInline String (sint32 value) noexcept : // NOLINT(google-explicit-constructor,clion-misra-cpp2008-12-1-3)
                String(String().append(value)) {

        }

        /**
         * @brief Constructor which initializes String from a raw sint64 value
         *
         * @param value : sint64 = Value to represent in the String
         *
         * @exceptsafe
         *
         * @test tested in primitive/StringTest/Constructor Tests
         */
        __CDS_OptimalInline String (sint64 value) noexcept : // NOLINT(google-explicit-constructor,clion-misra-cpp2008-12-1-3)
                String(String().append(value)) {

        }

        /**
         * @brief Constructor which initializes String from a raw float value
         *
         * @param value : float = Value to represent in the String
         *
         * @exceptsafe
         *
         * @test tested in primitive/StringTest/Constructor Tests
         */
        __CDS_OptimalInline String (float value) noexcept : // NOLINT(google-explicit-constructor,clion-misra-cpp2008-12-1-3)
                String(String().append(value)) {

        }

        /**
         * @brief Constructor which initializes String from a raw double value
         *
         * @param value : double = Value to represent in the String
         *
         * @exceptsafe
         *
         * @test tested in primitive/StringTest/Constructor Tests
         */
        __CDS_OptimalInline String (double value) noexcept : // NOLINT(google-explicit-constructor,clion-misra-cpp2008-12-1-3)
                String(String().append(value)) {

        }

    #if defined(__linux)

        /**
         * @brief Constructor which initializes String from a raw std::size_t value
         *
         * @param value : std::size_t = Value to represent in the String
         *
         * @exceptsafe
         *
         * @test tested in primitive/StringTest/Constructor Tests
         */
        __CDS_OptimalInline String(std::size_t value) noexcept : // NOLINT(google-explicit-constructor,clion-misra-cpp2008-12-1-3)
                String(static_cast < uint64 > (value) ) {

        }

    #endif

        /**
         * @brief Constructor which initializes String from a raw pointer value
         *
         * @tparam T = type of object at the given address
         * @param address : T ptr = Value to represent in the String
         *
         * @exceptsafe
         *
         * @test tested in primitive/StringTest/Constructor Tests
         */
        template < typename T >
        __CDS_cpplang_ConstexprConditioned String (T * address) noexcept : // NOLINT(google-explicit-constructor)
                String( reinterpret_cast < std::size_t > ( address ) ) {

        }

        /**
         * @brief Constructor which initializes String from a raw constant pointer value
         *
         * @tparam T = type of object at the given address
         * @param address : T cptr = Value to represent in the String
         *
         * @exceptsafe
         *
         * @test tested in primitive/StringTest/Constructor Tests
         */
        template < typename T >
        __CDS_cpplang_ConstexprConditioned String (T const * address) noexcept : // NOLINT(google-explicit-constructor)
                String( reinterpret_cast < std :: size_t const > (address) ) {

        }

        __CDS_WarningSuppression_DelegateCtorSuppressUninitializedMembers_SuppressDisable

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
        __CDS_OptionalInline String ( glm::vec < l, T, q > const & v ) noexcept {
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
        __CDS_OptimalInline ~String() noexcept override {
            Memory :: instance().destroyArray ( this->_p );
        }


        /**
         * @brief Function used to obtain an Iterator to the first element in the String
         *
         * @exceptsafe
         *
         * @returns Iterator
         *
         * @test tested in primitive/StringTest/Iterator Tests
         */
        __CDS_NoDiscard __CDS_cpplang_ConstexprDestructor auto begin() noexcept -> Iterator {
            return {* this, 0 };
        }

        /**
         * @brief Function used to obtain an Iterator to the position past the last element in the String
         *
         * @exceptsafe
         *
         * @returns Iterator
         *
         * @test tested in primitive/StringTest/Iterator Tests
         */
        __CDS_NoDiscard __CDS_cpplang_ConstexprDestructor auto end () noexcept -> Iterator {
            return { * this, static_cast < Index > ( this->_l ) };
        }

        /**
         * @brief Function used to obtain a ConstIterator to the first element in the String
         *
         * @exceptsafe
         *
         * @returns ConstIterator
         *
         * @test tested in primitive/StringTest/Iterator Tests
         */
        __CDS_NoDiscard __CDS_cpplang_ConstexprDestructor auto begin() const noexcept -> ConstIterator {
            return { * this, 0 };
        }

        /**
         * @brief Function used to obtain an ConstIterator to the position past the last element in the String
         *
         * @exceptsafe
         *
         * @returns ConstIterator
         *
         * @test tested in primitive/StringTest/Iterator Tests
         */
        __CDS_NoDiscard __CDS_cpplang_ConstexprDestructor auto end() const noexcept -> ConstIterator {
            return { * this, static_cast < Index > ( this->_l ) };
        }

        /**
         * @brief Function used to obtain a ConstIterator to the first element in the String
         *
         * @exceptsafe
         *
         * @returns ConstIterator
         *
         * @test tested in primitive/StringTest/Iterator Tests
         */
        __CDS_NoDiscard __CDS_cpplang_ConstexprDestructor auto cbegin() const noexcept -> ConstIterator {
            return { * this, 0 };
        }

        /**
         * @brief Function used to obtain an ConstIterator to the position past the last element in the String
         *
         * @exceptsafe
         *
         * @returns ConstIterator
         *
         * @test tested in primitive/StringTest/Iterator Tests
         */
        __CDS_NoDiscard __CDS_cpplang_ConstexprDestructor auto cend() const noexcept -> ConstIterator {
            return { * this, static_cast < Index > ( this->_l ) };
        }


        /**
         * @brief Function used to obtain a ReverseIterator to the position past the last element in the String
         *
         * @exceptsafe
         *
         * @returns ReverseIterator
         *
         * @test tested in primitive/StringTest/Iterator Tests
         */
        __CDS_NoDiscard __CDS_cpplang_ConstexprDestructor auto rbegin() noexcept -> ReverseIterator {
            return { * this, static_cast < Index > ( this->_l ) - 1 };
        }

        /**
         * @brief Function used to obtain a ReverseIterator to the first element in the String
         *
         * @exceptsafe
         *
         * @returns ReverseIterator
         *
         * @test tested in primitive/StringTest/Iterator Tests
         */
        __CDS_NoDiscard __CDS_cpplang_ConstexprDestructor auto rend() noexcept -> ReverseIterator {
            return { * this, -1 };
        }

        /**
         * @brief Function used to obtain a ConstReverseIterator to the position past the last element in the String
         *
         * @exceptsafe
         *
         * @returns ConstReverseIterator
         *
         * @test tested in primitive/StringTest/Iterator Tests
         */
        __CDS_NoDiscard __CDS_cpplang_ConstexprDestructor auto rbegin() const noexcept -> ConstReverseIterator {
            return { * this, static_cast < Index > ( this->_l ) - 1 };
        }

        /**
         * @brief Function used to obtain a ConstReverseIterator to the first element in the String
         *
         * @exceptsafe
         *
         * @returns ConstReverseIterator
         *
         * @test tested in primitive/StringTest/Iterator Tests
         */
        __CDS_NoDiscard __CDS_cpplang_ConstexprDestructor auto rend() const noexcept -> ConstReverseIterator {
            return { * this, -1 };
        }

        /**
         * @brief Function used to obtain a ConstReverseIterator to the position past the last element in the String
         *
         * @exceptsafe
         *
         * @returns ConstReverseIterator
         *
         * @test tested in primitive/StringTest/Iterator Tests
         */
        __CDS_NoDiscard __CDS_MaybeUnused __CDS_cpplang_ConstexprDestructor auto crbegin() const noexcept -> ConstReverseIterator {
            return { * this, static_cast < Index > ( this->_l ) - 1 };
        }

        /**
         * @brief Function used to obtain a ConstReverseIterator to the first element in the String
         *
         * @exceptsafe
         *
         * @returns ConstReverseIterator
         *
         * @test tested in primitive/StringTest/Iterator Tests
         */
        __CDS_NoDiscard __CDS_cpplang_ConstexprDestructor auto crend() const noexcept -> ConstReverseIterator {
            return { * this, -1 };
        }


        /**
         * @brief Function used to obtain the number of characters in the String
         *
         * @exceptsafe
         *
         * @returns Size = size of the String
         *
         * @test tested in primitive/StringTest/Property Tests
         */
        __CDS_NoDiscard constexpr auto size() const noexcept -> Size {
            return this->_l;
        }

        /**
         * @brief Function used to obtain the number of characters in the String
         *
         * @exceptsafe
         *
         * @returns Size = size of the String
         *
         * @test tested in primitive/StringTest/Property Tests
         */
        __CDS_NoDiscard constexpr auto length() const noexcept -> Size {
            return this->_l;
        }

        /**
         * @brief Function used to obtain the allocated memory size in bytes
         *
         * @exceptsafe
         *
         * @returns Size = size of the buffer
         *
         * @test tested in primitive/StringTest/Property Tests
         */
        __CDS_NoDiscard __CDS_MaybeUnused constexpr auto maxSize() const noexcept -> Size {
            return this->_c;
        }

        /**
         * @brief Function used to obtain the allocated memory size in bytes
         *
         * @exceptsafe
         *
         * @returns Size = size of the buffer
         *
         * @test tested in primitive/StringTest/Property Tests
         */
        __CDS_NoDiscard constexpr auto capacity() const noexcept -> Size {
            return this->_c;
        }

    #if defined(_MSC_VER)

    #pragma push_macro("min")
    #pragma push_macro("max")
    #undef min
    #undef max

    #endif

        /**
         * @brief Function used to resize the String to a given size
         *
         * @param size : Size = size to resize the String to
         *
         * @exceptsafe
         *
         * @test tested in primitive/StringTest/Memory Tests
         */
        __CDS_OptimalInline auto resize(Size size) noexcept -> void {
            auto toCopy = std :: min ( this->_c, size + 1u );
            this->_c = size + 1u;
            auto newArea = Memory :: instance().createArray < ElementType > ( this->_c );

            if ( ! this->empty() ) {
                (void) std::memcpy(newArea, this->_p, toCopy);
                Memory :: instance().destroyArray ( this->_p );
            }

            this->_p = newArea;
            if ( this->_l >= this->_c ) {
                this->_l = this->_c - 1u;
            }
        }

    #if defined(_MSC_VER)

    #pragma pop_macro("max")
    #pragma pop_macro("min")

    #endif

        /**
         * @brief Function used to enlarge the String's capacity to a required size, but not capable of shrinking it, if it is bigger
         *
         * @param size : Size = target size for the String
         *
         * @exceptsafe
         *
         * @test tested in primitive/StringTest/Memory Tests
         */
        __CDS_MaybeUnused __CDS_cpplang_ConstexprDynamicAllocation auto reserve(Size size) noexcept -> void {
            if (size < this->_c ) {
                return;
            }

            this->resize(size );
        }

        /**
         * @brief Function used to shrink the String's capacity, but not capable of enlarging it, if given size is greater than capacity
         * If no parameters are given, it shrinks to the least possible capacity, its' length
         *
         * @param size : SignedSize = target size to shrink at. If left default (-1), it will shrink to length
         *
         * @exceptsafe
         *
         * @test tested in primitive/StringTest/Memory Tests
         */
        __CDS_MaybeUnused __CDS_cpplang_ConstexprDynamicAllocation auto shrink(SignedSize size = -1) noexcept -> void {
            if ( size == -1 ) {
                size = static_cast < SignedSize > ( this->_l );
            }

            if ( static_cast < Size > ( size ) > this->_c ) {
                return;
            }

            this->resize( static_cast < Size > ( size ) );
        }

        /**
         * @brief Function used to clear the contents of the String
         *
         * @exceptsafe
         *
         * @test tested in primitive/StringTest/Content Functions Tests
         */
        __CDS_cpplang_ConstexprConditioned auto clear() noexcept -> void {
            if ( this->_p != nullptr ) {

                __CDS_WarningSuppression_StringOperationOverflow_SuppressEnable

                (void) std::memset(this->_p, 0, this->_l);

                __CDS_WarningSuppression_StringOperationOverflow_SuppressDisable

            }
            this->_l = 0u;
        }

        /**
         * Function returns true if the String's contents are empty, false otherwise
         *
         * @exceptsafe
         *
         * @returns bool = true if empty, false otherwise
         *
         * @test tested in primitive/StringTest/Content Functions Tests
         */
        __CDS_NoDiscard constexpr auto empty() const noexcept -> bool {
            return this->_l == 0u;
        }


        /**
         * Get Operator used to acquire element at given index, behaves circularly ( if given index > length, it loops around, from the start )
         *
         * @param index : Index = index to acquire element from
         *
         * @throws String::StringNullAccess() if used on an empty String
         *
         * @returns ElementType ref = Reference to the element at given index
         *
         * @test tested in primitive/StringTest/Content Functions Tests
         */
        __CDS_cpplang_ConstexprConditioned auto operator [] (Index index) noexcept (false) -> ElementType & {
            if ( this->empty() ) {
                throw String::StringNullAccess();
            }

            if (index < 0 ) {
                index += ((-index) / static_cast < Index > ( this->size()) + 1) * static_cast < Index > ( this->size());
            }

            if (index >= static_cast<Index>(this->size()) ) {
                index = index % static_cast < Index > ( this->size());
            }

            return this->_p[index];
        }

        /**
         * @brief Get Operator used to acquire element value at given index, behaves circularly
         *
         * @param index : Index = index to acquire value from
         *
         * @exceptsafe
         *
         * @returns ElementType = Value of the element at given index
         *
         * @test tested in primitive/StringTest/Content Functions Tests
         */
        __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator [] (Index index) const noexcept -> ElementType {
            if ( this->empty() ) {
                return '\0';
            }

            if (index < 0 ) {
                index += ((-index) / static_cast < Index > ( this->size()) + 1) * static_cast < Index > ( this->size());
            }

            if (index >= static_cast<Index>(this->size()) ) {
                index = index % static_cast < Index > ( this->size());
            }

            return this->_p[index];
        }

        /**
         * @brief Explicit Get Function used to acquire element at given index, behaves circularly, calls operator []
         *
         * @param index : Index = index to acquire element from
         *
         * @throws String::StringNullAccess() if used on an empty String
         *
         * @returns ElementType ref = Reference to the element at given index
         *
         * @test If operator [] has a test, function is tested
         */
        __CDS_MaybeUnused __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto at (Index index) noexcept (false) -> ElementType & {
            return this->operator[](index);
        }

        /**
         * @brief Get Operator used to acquire element value at given index, behaves circularly, calls operator []
         *
         * @param index : Index = index to acquire value from
         *
         * @exceptsafe
         *
         * @returns ElementType = Value of the element at given index
         *
         * @test tested in primitive/StringTest/Content Functions Tests
         */
        __CDS_NoDiscard __CDS_MaybeUnused __CDS_cpplang_ConstexprConditioned auto at (Index index) const noexcept -> ElementType {
            return this->operator[](index);
        }

        /**
         * @brief Explicit Get Function used to acquire element at given index, behaves circularly, calls operator []
         *
         * @param index : Index = index to acquire element from
         *
         * @throws String::StringNullAccess() if used on an empty String
         *
         * @returns ElementType ref = Reference to the element at given index
         *
         * @test If operator [] has a test, function is tested
         */
        __CDS_NoDiscard __CDS_MaybeUnused __CDS_cpplang_ConstexprConditioned auto get (Index index) noexcept (false) -> ElementType & {
            return this->operator[](index);
        }

        /**
         * @brief Get Operator used to acquire element value at given index, behaves circularly, calls operator []
         *
         * @param index : Index = index to acquire value from
         *
         * @exceptsafe
         *
         * @returns ElementType = Value of the element at given index
         *
         * @test tested in primitive/StringTest/Content Functions Tests
         */
        __CDS_NoDiscard __CDS_MaybeUnused __CDS_cpplang_ConstexprConditioned auto get (Index index) const noexcept -> ElementType {
            return this->operator[](index);
        }

        /**
         * @brief Function used to acquire element at the front of the String
         *
         * @throws String::StringNullAccess() if used on an empty String
         *
         * @returns ElementType ref = Reference to the first element in the String
         *
         * @test If operator [] has a test, function is tested
         */
        __CDS_NoDiscard __CDS_MaybeUnused __CDS_cpplang_ConstexprConditioned auto front () noexcept (false) -> ElementType & {
            return this->operator[](0);
        }

        /**
         * @brief Function used to acquire the last element in the String
         *
         * @throws String::StringNullAccess() if used on an empty String
         *
         * @returns ElementType ref = Reference to the last element in the String
         *
         * @test If operator [] has a test, function is tested
         */
        __CDS_NoDiscard __CDS_MaybeUnused __CDS_cpplang_ConstexprConditioned auto back () noexcept (false) -> ElementType & {
            return this->operator[](static_cast < Index > (this->_l) - 1);
        }

        /**
         * @brief Function used to acquire the value of the first element in the String, if any. Returns '\0' if empty
         *
         * @exceptsafe
         *
         * @returns ElementType = Value of the first element, or '\0' if empty
         *
         * @test If operator [] has a test, function is tested
         */
        __CDS_NoDiscard __CDS_MaybeUnused __CDS_cpplang_ConstexprConditioned auto front() const noexcept -> ElementType {
            return this->empty() ? '\0' : this->_p[0];
        }

        /**
         * @brief Function used to acquire the value of the last element in the String, if any. Returns '\0' if empty
         *
         * @exceptsafe
         *
         * @returns ElementType = Value of the first element, or '\0' if empty
         *
         * @test If operator [] has a test, function is tested
         */
        __CDS_NoDiscard __CDS_MaybeUnused __CDS_cpplang_ConstexprConditioned auto back() const noexcept -> ElementType {
            return this->empty() ? '\0' : this->_p[this->_l - 1u];
        }

        /**
         * @brief Accumulate operator used to append an ElementType to the String
         *
         * @param value : ElementType = Value to add to the end of the String
         *
         * @exceptsafe
         *
         * @returns String ref = Reference to the modified String
         *
         * @test tested in primitive/StringTest/Append/Prepend Tests
         */
        __CDS_cpplang_ConstexprDynamicAllocation auto operator += (ElementType value) noexcept -> String & {
            return this->append(value );
        }

        /**
         * @brief Accumulate operator used to append a StringLiteral to the String
         *
         * @param stringLiteral : StringLiteral = Address to a StringLiteral to add to the end of the String
         *
         * @exceptsafe
         *
         * @returns String ref = Reference to the modified String
         *
         * @test tested in primitive/StringTest/Append/Prepend Tests
         */
        __CDS_cpplang_ConstexprDynamicAllocation auto operator += (StringLiteral stringLiteral) noexcept -> String & {
            return this->append(stringLiteral );
        }

        /**
         * @brief Accumulate operator used to append a CString to the String
         *
         * @param string : CString = Address to a CString to add to the end of the String
         *
         * @exceptsafe
         *
         * @returns String ref = Reference to the modified String
         *
         * @test tested in primitive/StringTest/Append/Prepend Tests
         */
        __CDS_cpplang_ConstexprDynamicAllocation auto operator += (CString string) noexcept -> String & {
            return this->append(string );
        }

        /**
         * @brief Accumulate operator used to append a String to the String
         *
         * @param string : String cref = Constant Reference to the String to add at the end of the String
         *
         * @exceptsafe
         *
         * @returns String ref = Reference to the modified String
         *
         * @test tested in primitive/StringTest/Append/Prepend Tests
         */
        __CDS_cpplang_ConstexprDynamicAllocation auto operator += (String const & string) noexcept -> String & {
            return this->append(string );
        }

        /**
         * @brief Accumulate operator used to append a std::string to the String
         *
         * @param string : std::string cref = Constant Reference to the std::string to add at the end of the String
         *
         * @exceptsafe
         *
         * @returns String ref = Reference to the modified String
         *
         * @test tested in primitive/StringTest/Append/Prepend Tests
         */
        __CDS_OptimalInline auto operator += (std::string const & string) noexcept -> String & {
            return this->append(string );
        }

        /**
         * @brief Accumulate operator used to append a sint16 to the String
         *
         * @param value : sint16 = value to add at the end of the String
         *
         * @exceptsafe
         *
         * @returns String ref = Reference to the modified String
         *
         * @test tested in primitive/StringTest/Append/Prepend Tests
         */
        __CDS_cpplang_ConstexprDynamicAllocation auto operator += (sint16 value) noexcept -> String & {
            return this->append(value);
        }

        /**
         * @brief Accumulate operator used to append a sint32 to the String
         *
         * @param value : sint32 = value to add at the end of the String
         *
         * @exceptsafe
         *
         * @returns String ref = Reference to the modified String
         *
         * @test tested in primitive/StringTest/Append/Prepend Tests
         */
        __CDS_cpplang_ConstexprDynamicAllocation auto operator += (sint32 value) noexcept -> String & {
            return this->append(value);
        }

        /**
         * @brief Accumulate operator used to append a sint64 to the String
         *
         * @param value : sint64 = value to add at the end of the String
         *
         * @exceptsafe
         *
         * @returns String ref = Reference to the modified String
         *
         * @test tested in primitive/StringTest/Append/Prepend Tests
         */
        __CDS_cpplang_ConstexprDynamicAllocation auto operator += (sint64 value) noexcept -> String & {
            return this->append(value);
        }

        /**
         * @brief Accumulate operator used to append a uint8 to the String
         *
         * @param value : uint8 = value to add at the end of the String
         *
         * @exceptsafe
         *
         * @returns String ref = Reference to the modified String
         *
         * @test tested in primitive/StringTest/Append/Prepend Tests
         */
        __CDS_cpplang_ConstexprDynamicAllocation auto operator += (uint8 value) noexcept -> String & {
            return this->append(value);
        }

        /**
         * @brief Accumulate operator used to append a uint16 to the String
         *
         * @param value : uint16 = value to add at the end of the String
         *
         * @exceptsafe
         *
         * @returns String ref = Reference to the modified String
         *
         * @test tested in primitive/StringTest/Append/Prepend Tests
         */
        __CDS_cpplang_ConstexprDynamicAllocation auto operator += (uint16 value) noexcept -> String & {
            return this->append(value);
        }

        /**
         * @brief Accumulate operator used to append a uint32 to the String
         *
         * @param value : uint32 = value to add at the end of the String
         *
         * @exceptsafe
         *
         * @returns String ref = Reference to the modified String
         *
         * @test tested in primitive/StringTest/Append/Prepend Tests
         */
        __CDS_cpplang_ConstexprDynamicAllocation auto operator += (uint32 value) noexcept -> String & {
            return this->append(value);
        }

        /**
         * @brief Accumulate operator used to append a uint64 to the String
         *
         * @param value : uint64 = value to add at the end of the String
         *
         * @exceptsafe
         *
         * @returns String ref = Reference to the modified String
         *
         * @test tested in primitive/StringTest/Append/Prepend Tests
         */
        __CDS_cpplang_ConstexprDynamicAllocation auto operator += (uint64 value) noexcept -> String & {
            return this->append(value);
        }

        /**
         * @brief Accumulate operator used to append a float to the String
         *
         * @param value : float = value to add at the end of the String
         *
         * @exceptsafe
         *
         * @returns String ref = Reference to the modified String
         *
         * @test tested in primitive/StringTest/Append/Prepend Tests
         */
        __CDS_OptimalInline auto operator += (float value) noexcept -> String & {
            return this->operator+=( std::to_string(value) );
        }

        /**
         * @brief Accumulate operator used to append a double to the String
         *
         * @param value : double = value to add at the end of the String
         *
         * @exceptsafe
         *
         * @returns String ref = Reference to the modified String
         *
         * @test tested in primitive/StringTest/Append/Prepend Tests
         */
        __CDS_OptimalInline auto operator += (double value) noexcept -> String & {
            return this->operator+=( std::to_string(value) );
        }

    #if defined(CDS_QT)

        /**
         * @brief Accumulate operator used to append a QString to the String
         *
         * @param string : QString cref = Constant Reference to a QString to append at the end of this String
         *
         * @exceptsafe
         *
         * @returns String ref = Reference to the modified String
         *
         * @test tested in MSK
         */
        __CDS_OptimalInline auto operator += (QString const & string) noexcept -> String & {
            return this->operator += (String(string));
        }

    #endif

        /**
         * @brief Append Function used to append an ElementType to the String
         *
         * @param value : ElementType = Value to add to the end of the String
         *
         * @exceptsafe
         *
         * @returns String ref = Reference to the modified String
         *
         * @test tested in primitive/StringTest/Append/Prepend Tests
         */
        __CDS_cpplang_ConstexprDynamicAllocation auto append (ElementType value) noexcept -> String & {
            this->_alloc(1u);

            this->_p[this->_l++] = value;
            return * this;
        }

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
        __CDS_cpplang_ConstexprDynamicAllocation auto append (StringLiteral cString) noexcept -> String & {
            if ( cString == nullptr ) {
                return * this;
            }

            auto len = std::char_traits<char>::length( cString );
            this->_alloc(len);

            (void) std::memcpy ( this->_p + this->_l, cString, len );
            this->_l += len;

            return * this;
        }

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
        __CDS_cpplang_ConstexprDynamicAllocation auto append (CString cString) noexcept -> String & {
            if ( cString == nullptr ) {
                return * this;
            }

            auto len = std::char_traits<char>::length(cString);
            this->_alloc(len);

            (void) std::memcpy ( this->_p + this->_l, cString, len );
            this->_l += len;

            return * this;
        }

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
        __CDS_cpplang_ConstexprDynamicAllocation auto append (String const & str) noexcept -> String & {
            if ( str.empty() ) {
                return * this;
            }

            this->_alloc(str._l);

            (void) std::memcpy ( this->_p + this->_l, str._p, str._l );
            this->_l += str._l;

            return * this;
        }

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
        __CDS_OptimalInline auto append (std::string const & string) noexcept -> String & {
            if ( string.empty() ) {
                return * this;
            }

            this->_alloc(string.size());

            (void) std::memcpy ( this->_p + this->_l, string.c_str(), string.size() );
            this->_l += string.size();

            return * this;
        }

        /**
         * @brief Append Function used to append a sint16 to the String
         *
         * @param value : sint16 = value to add at the end of the String
         *
         * @exceptsafe
         *
         * @returns String ref = Reference to the modified String
         *
         * @test tested in primitive/StringTest/Append/Prepend Tests
         */
        __CDS_cpplang_ConstexprDynamicAllocation auto append (sint16 value) noexcept -> String & {
            bool const negative = value < 0;
            uint16 const uValue = negative ? static_cast < uint16 > (~ value) + 1u : static_cast < uint16 > ( value ); // NOLINT(clion-misra-cpp2008-5-0-6)
            auto const length = utility :: conversion :: toCharBase10Length( uValue );

            this->_alloc(static_cast < Size > ( length ) + static_cast < uint8 > (negative));

            if(negative) {
                this->_p[this->_l] = '-';
            }

            utility :: conversion::toCharBase10( this->_p + this->_l + static_cast < uint8 > (negative), length, uValue ); // NOLINT(clion-misra-cpp2008-5-0-4)
            this->_l += static_cast < Size > ( length ) + static_cast < uint8 > (negative);

            return * this;
        }

        /**
         * @brief Append Function used to append a sint32 to the String
         *
         * @param value : sint32 = value to add at the end of the String
         *
         * @exceptsafe
         *
         * @returns String ref = Reference to the modified String
         *
         * @test tested in primitive/StringTest/Append/Prepend Tests
         */
        __CDS_cpplang_ConstexprDynamicAllocation auto append (sint32 value) noexcept -> String & {
            bool const negative = value < 0;
            uint32 const uValue = negative ? static_cast < uint32 > (~ value) + 1u : static_cast < uint32 > ( value );
            auto const length = utility :: conversion :: toCharBase10Length( uValue );

            this->_alloc(static_cast < Size > ( length ) + static_cast < uint8 > (negative));

            if(negative) {
                this->_p[this->_l] = '-';
            }

            utility :: conversion::toCharBase10( this->_p + this->_l + static_cast < uint8 > (negative), length, uValue ); // NOLINT(clion-misra-cpp2008-5-0-4)
            this->_l += static_cast < Size > ( length ) + static_cast < uint8 > (negative);

            return * this;
        }

        /**
         * @brief Append Function used to append a sint64 to the String
         *
         * @param value : sint64 = value to add at the end of the String
         *
         * @exceptsafe
         *
         * @returns String ref = Reference to the modified String
         *
         * @test tested in primitive/StringTest/Append/Prepend Tests
         */
        __CDS_cpplang_ConstexprDynamicAllocation auto append (sint64 value) noexcept -> String & {
            bool const negative = value < 0;
            uint64 const uValue = negative ? static_cast < uint64 > (~ value) + 1u : static_cast < uint64 > (value);
            auto const length = utility :: conversion :: toCharBase10Length( uValue );

            this->_alloc(static_cast < Size > ( length ) + static_cast < uint8 > (negative));

            if(negative) {
                this->_p[this->_l] = '-';
            }

            utility :: conversion::toCharBase10( this->_p + this->_l + static_cast < uint8 > (negative), length, uValue ); // NOLINT(clion-misra-cpp2008-5-0-4)
            this->_l += static_cast < Size > (length) + static_cast < uint8 > (negative);

            return * this;
        }

        /**
         * @brief Append Function used to append a uint8 to the String
         *
         * @param value : uint8 = value to add at the end of the String
         *
         * @exceptsafe
         *
         * @returns String ref = Reference to the modified String
         *
         * @test tested in primitive/StringTest/Append/Prepend Tests
         */
        __CDS_cpplang_ConstexprDynamicAllocation auto append (uint8 value) noexcept -> String & {
            uint32 const length = utility :: conversion::toCharBase10Length(value);
            this->_alloc(length);

            utility :: conversion::toCharBase10(this->_p + this->_l, length, value);
            this->_l += length;
            return * this;
        }

        /**
         * @brief Append Function used to append a uint16 to the String
         *
         * @param value : uint16 = value to add at the end of the String
         *
         * @exceptsafe
         *
         * @returns String ref = Reference to the modified String
         *
         * @test tested in primitive/StringTest/Append/Prepend Tests
         */
        __CDS_cpplang_ConstexprDynamicAllocation auto append (uint16 value) noexcept -> String & {
            uint32 const length = utility :: conversion::toCharBase10Length(value);
            this->_alloc(length);

            utility :: conversion::toCharBase10(this->_p + this->_l, length, value);
            this->_l += length;
            return * this;
        }

        /**
         * @brief Append Function used to append a uint32 to the String
         *
         * @param value : uint32 = value to add at the end of the String
         *
         * @exceptsafe
         *
         * @returns String ref = Reference to the modified String
         *
         * @test tested in primitive/StringTest/Append/Prepend Tests
         */
        __CDS_cpplang_ConstexprDynamicAllocation auto append (uint32 value) noexcept -> String & {
            uint32 const length = utility :: conversion::toCharBase10Length(value);
            this->_alloc(length);

            utility :: conversion::toCharBase10(this->_p + this->_l, length, value);
            this->_l += length;
            return * this;
        }

        /**
         * @brief Append Function used to append a uint64 to the String
         *
         * @param value : uint64 = value to add at the end of the String
         *
         * @exceptsafe
         *
         * @returns String ref = Reference to the modified String
         *
         * @test tested in primitive/StringTest/Append/Prepend Tests
         */
        __CDS_cpplang_ConstexprDynamicAllocation auto append (uint64 value) noexcept -> String & {
            uint32 const length = utility :: conversion::toCharBase10Length(value);
            this->_alloc(length);

            utility :: conversion::toCharBase10(this->_p + this->_l, length, value);
            this->_l += length;
            return * this;
        }

        /**
         * @brief Append Function used to append a float to the String
         *
         * @param value : float = value to add at the end of the String
         *
         * @exceptsafe
         *
         * @returns String ref = Reference to the modified String
         *
         * @test tested in primitive/StringTest/Append/Prepend Tests
         */
        __CDS_OptimalInline auto append (float value) noexcept -> String & {
            return this->append( std::to_string(value) );
        }

        /**
         * @brief Append Function used to append a double to the String
         *
         * @param value : double = value to add at the end of the String
         *
         * @exceptsafe
         *
         * @returns String ref = Reference to the modified String
         *
         * @test tested in primitive/StringTest/Append/Prepend Tests
         */
        __CDS_OptimalInline auto append (double value) noexcept -> String & {
            return this->append(std::to_string(value) );
        }

    #if defined(CDS_QT)

        /**
         * @brief Append Function used to append a QString to the String
         *
         * @param string : QString cref = Constant Reference to a QString to append at the end of this String
         *
         * @exceptsafe
         *
         * @returns String ref = Reference to the modified String
         *
         * @test tested in MSK
         */
        __CDS_OptimalInline auto append (QString const & string) noexcept -> String & {
            return this->append(String(string));
        }

    #endif


        /**
         * @brief Prepend Function used to prepend an ElementType to the String
         *
         * @param v : ElementType = Value to add at the beginning of the String
         *
         * @exceptsafe
         *
         * @returns String ref = Reference to the modified String
         *
         * @test tested in primitive/StringTest/Append/Prepend Tests
         */
        __CDS_OptimalInline auto prepend (ElementType element) noexcept -> String & {
            return this->prepend(String().append(element));
        }

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
        __CDS_OptimalInline auto prepend (StringLiteral cString) noexcept -> String & {
            return this->prepend(String(cString));
        }

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
        __CDS_OptimalInline auto prepend (CString cString) noexcept -> String & {
            return this->prepend(String(cString));
        }

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
        __CDS_OptimalInline auto prepend (String const & string) noexcept -> String & {
            return * this = (String( string )).append(* this);
        }

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
        __CDS_OptimalInline auto prepend (std::string const & string) noexcept -> String & {
            return this->prepend(string.c_str());
        }

        /**
         * @brief Prepend Function used to prepend a sint16 to the String
         *
         * @param value : sint16 = value to add at the beginning of the String
         *
         * @exceptsafe
         *
         * @returns String ref = Reference to the modified String
         *
         * @test tested in primitive/StringTest/Append/Prepend Tests
         */
        __CDS_OptimalInline auto prepend (sint16 value) noexcept -> String & {
            return this->prepend(String(value));
        }

        /**
         * @brief Prepend Function used to prepend a sint32 to the String
         *
         * @param value : sint32 = value to add at the beginning of the String
         *
         * @exceptsafe
         *
         * @returns String ref = Reference to the modified String
         *
         * @test tested in primitive/StringTest/Append/Prepend Tests
         */
        __CDS_OptimalInline auto prepend (sint32 value) noexcept -> String & {
            return this->prepend(String(value));
        }

        /**
         * @brief Prepend Function used to prepend a sint64 to the String
         *
         * @param value : sint64 = value to add at the beginning of the String
         *
         * @exceptsafe
         *
         * @returns String ref = Reference to the modified String
         *
         * @test tested in primitive/StringTest/Append/Prepend Tests
         */
        __CDS_OptimalInline auto prepend (sint64 value) noexcept -> String & {
            return this->prepend(String(value));
        }

        /**
         * @brief Prepend Function used to prepend a uint8 to the String
         *
         * @param value : uint8 = value to add at the beginning of the String
         *
         * @exceptsafe
         *
         * @returns String ref = Reference to the modified String
         *
         * @test tested in primitive/StringTest/Append/Prepend Tests
         */
        __CDS_OptimalInline auto prepend (uint8 value) noexcept -> String & {
            return this->prepend(String(value));
        }

        /**
         * @brief Prepend Function used to prepend a uint16 to the String
         *
         * @param value : uint16 = value to add at the beginning of the String
         *
         * @exceptsafe
         *
         * @returns String ref = Reference to the modified String
         *
         * @test tested in primitive/StringTest/Append/Prepend Tests
         */
        __CDS_OptimalInline auto prepend (uint16 value) noexcept -> String & {
            return this->prepend(String(value));
        }

        /**
         * @brief Prepend Function used to prepend a uint32 to the String
         *
         * @param value : uint32 = value to add at the beginning of the String
         *
         * @exceptsafe
         *
         * @returns String ref = Reference to the modified String
         *
         * @test tested in primitive/StringTest/Append/Prepend Tests
         */
        __CDS_OptimalInline auto prepend (uint32 value) noexcept -> String & {
            return this->prepend(String(value));
        }

        /**
         * @brief Prepend Function used to prepend a uint64 to the String
         *
         * @param value : uint64 = value to add at the beginning of the String
         *
         * @exceptsafe
         *
         * @returns String ref = Reference to the modified String
         *
         * @test tested in primitive/StringTest/Append/Prepend Tests
         */
        __CDS_OptimalInline auto prepend (uint64 value) noexcept -> String & {
            return this->prepend(String(value));
        }

        /**
         * @brief Prepend Function used to prepend a float to the String
         *
         * @param value : float = value to add at the prepend of the String
         *
         * @exceptsafe
         *
         * @returns String ref = Reference to the modified String
         *
         * @test tested in primitive/StringTest/Append/Prepend Tests
         */
        __CDS_OptimalInline auto prepend (float value) noexcept -> String & {
            return this->prepend( std::to_string(value) );
        }

        /**
         * @brief Prepend Function used to prepend a double to the String
         *
         * @param value : double = value to add at the beginning of the String
         *
         * @exceptsafe
         *
         * @returns String ref = Reference to the modified String
         *
         * @test tested in primitive/StringTest/Append/Prepend Tests
         */
        __CDS_OptimalInline auto prepend (double value) noexcept -> String & {
            return this->prepend( std::to_string(value) );
        }

    #if defined(CDS_QT)

        /**
         * @brief Prepend Function used to prepend a QString to the String
         *
         * @param string : QString cref = Constant Reference to a QString to append at the beginning of this String
         *
         * @exceptsafe
         *
         * @returns String ref = Reference to the modified String
         *
         * @test tested in MSK
         */
    
        __CDS_OptimalInline auto prepend (QString const & string) noexcept -> String & {
            return this->prepend(String(string));
        }

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
        __CDS_NoDiscard __CDS_OptimalInline auto toStdString () const noexcept -> std::string {
            return this->cStr();
        }

        /**
         * @brief Cast Specification used to obtain a std::string from this string
         *
         * @exceptsafe
         *
         * @returns std::string = std::string containing the data from this String
         *
         * @test tested in primitive/StringTest
         */
        __CDS_OptimalInline operator std::string () const noexcept { // NOLINT(google-explicit-constructor)
            return this->toStdString();
        }

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
        __CDS_NoDiscard __CDS_OptimalInline auto toQString () const noexcept -> QString {
            return {this->cStr() };
        }
    
        /**
         * @brief Cast Specification used to obtain a QString from this string
         *
         * @exceptsafe
         *
         * @returns QString = QString containing the data from this String
         *
         * @test tested in MSK
         */
        __CDS_OptimalInline operator QString () const noexcept {  // NOLINT(google-explicit-constructor)
            return this->toQString();
        }

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
        __CDS_NoDiscard constexpr auto cStr () const noexcept -> StringLiteral {
            return this->_p == nullptr ? "" : this->_p;
        }

        /**
         * @brief Cast Specification used to obtain the immutable C String buffer of this String object
         *
         * @exceptsafe
         *
         * @returns StringLiteral = buffer containing the String Data
         *
         * @test tested in primitive/StringTest/Append/
         */
        constexpr explicit operator StringLiteral () const noexcept {
            return this->cStr();
        }

        /**
         * @brief Function used to obtain the mutable C String buffer of this String object
         *
         * @exceptsafe
         *
         * @returns CString = buffer containing the String Data
         *
         * @test tested in primitive/StringTest/Append/
         */
        __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto data () noexcept -> CString  {
            return this->_p;
        }

        /**
         * @brief Cast Specification used to obtain the mutable C String buffer of this String object
         *
         * @exceptsafe
         *
         * @returns CString = buffer containing the String Data
         *
         * @test tested in primitive/StringTest/Append/
         */
        __CDS_cpplang_NonConstConstexprMemberFunction explicit operator CString () noexcept {
            return this->data();
        }

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
        __CDS_NoDiscard auto find (ElementType) const noexcept -> DoubleLinkedList < Index >;

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
        __CDS_NoDiscard auto find (String const &) const noexcept -> DoubleLinkedList < Index >;

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
        __CDS_NoDiscard __CDS_MaybeUnused auto findOf (String const &) const noexcept -> DoubleLinkedList < Index >;

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
        __CDS_NoDiscard __CDS_MaybeUnused auto findNotOf (String const &) const noexcept -> DoubleLinkedList < Index >;

        /**
         * @brief Function used to obtain the index of the first element in the String
         *
         * @param element : ElementType = element to find in the String
         *
         * @exceptsafe
         *
         * @returns Index = index of the first occurrence
         *
         * @test tested in primitive/StringTest/Find Tests
         */
        __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto findFirst ( ElementType element ) const noexcept -> Index {
            for ( Index i = 0; static_cast < Size > ( i ) < this->_l; ++ i ) {
                if (this->_p[i] == element) {
                    return i;
                }
            }

            return INVALID_POS;
        }

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
        __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto findFirst ( String const & string ) const noexcept -> Index {
            for ( Index i = 0; static_cast < Size > ( i ) < this->_l; ++ i ) {
                if (this->size() - static_cast < Size > ( i ) >= string.size() && this->substr(i, i + static_cast < Index > ( string.size())) == string) {
                    return i;
                }
            }

            return INVALID_POS;
        }

        /**
         * @brief Function used to obtain the index of the last element in the String
         *
         * @param element : ElementType = element to find in the String
         *
         * @exceptsafe
         *
         * @returns Index = index of the last occurrence
         *
         * @test tested in primitive/StringTest/Find Tests
         */
        __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto findLast ( ElementType element ) const noexcept -> Index {
            for ( auto i = static_cast < Index > ( this->_l ) - 1; i >= 0; -- i ) {
                if (this->_p[i] == element) {
                    return i;
                }
            }

            return INVALID_POS;
        }

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
        __CDS_NoDiscard __CDS_MaybeUnused __CDS_cpplang_ConstexprDynamicAllocation auto findLast ( String const & string ) const noexcept -> Index {
            auto index = static_cast < Index > ( this->size() ) - static_cast < Index > ( string.length() );
            for ( ; index >= 0; index-- ) {
                if (this->substr(index, index + static_cast < Index > ( string.length() )) == string ) {
                    return index;
                }
            }

            return INVALID_POS;
        }

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
        __CDS_NoDiscard __CDS_MaybeUnused __CDS_cpplang_ConstexprConditioned auto findFirstOf ( String const & string ) const noexcept -> Index {
            for ( Index i = 0; static_cast < Size > ( i ) < this->_l; ++ i ) {
                if (string.contains(this->_p[i])) {
                    return i;
                }
            }

            return INVALID_POS;
        }

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
        __CDS_NoDiscard __CDS_MaybeUnused __CDS_cpplang_ConstexprConditioned auto findFirstNotOf ( String const & string ) const noexcept -> Index {
            for ( Index i = 0; static_cast < Size > ( i ) < this->_l; ++ i ) {
                if (!string.contains(this->_p[i])) {
                    return i;
                }
            }

            return INVALID_POS;
        }

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
        __CDS_NoDiscard __CDS_MaybeUnused __CDS_cpplang_ConstexprConditioned auto findLastOf ( String const & string ) const noexcept -> Index {
            for ( auto i = static_cast < Index > ( this->_l ) - 1; i >= 0; -- i ) {
                if (string.contains(this->_p[i])) {
                    return i;
                }
            }

            return INVALID_POS;
        }

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
        __CDS_NoDiscard __CDS_MaybeUnused __CDS_cpplang_ConstexprConditioned auto findLastNotOf ( String const & string ) const noexcept -> Index {
            for ( auto i = static_cast < Index > ( this->_l ) - 1; i >= 0; -- i ) {
                if (!string.contains(this->_p[i])) {
                    return i;
                }
            }

            return INVALID_POS;
        }

        /**
         * @brief Function used to obtain a substring from given index and until given index
         *
         * @param from : Index = starting index
         * @param until : Index = ending index. If not given, it will default to end of string
         *
         * @exceptsafe
         *
         * @returns String = String containing the data from starting index to ending index provided
         *
         * @test tested in primitive/StringTest/Substring Tests
         */
        __CDS_NoDiscard __CDS_OptimalInline auto substr ( Index from, Index until = -1 ) const noexcept -> String {
            if (until == -1 || until > static_cast<Index>(this->size()) ) {
                until = static_cast < Index > (this->size());
            }

            if ( from < 0 ) {
                from = 0;
            }

            if (until < from ) {
                return {};
            }

            return { this->_p + from, static_cast < Size > ( until - from ) };
        }

        /**
         * @brief Comparison operator
         *
         * @param string : String cref = Constant Reference to a String to compare this Object to
         *
         * @exceptsafe
         *
         * @returns bool = true if Strings are equal, false otherwise
         *
         * @test tested in primitive/StringTest/Comparison Tests
         */
        __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator == ( String const & string ) const noexcept -> bool {
            return this->size() == string.size() && std :: char_traits < ElementType > :: compare (this->cStr(), string.cStr(), this->_l ) == 0;
        }

        /**
         * @brief Comparison Function
         *
         * @param object : Object cref = Constant Reference to a CDS/Object to compare this Object to
         *
         * @exceptsafe
         *
         * @returns bool = true if Strings are equal, false otherwise
         *
         * @test tested in primitive/StringTest/Comparison Tests
         */
        __CDS_NoDiscard __CDS_cpplang_VirtualConstexpr auto equals ( Object const & object) const noexcept -> bool final {
            if ( this == & object ) {
                return true;
            }

            auto pString = dynamic_cast < decltype ( this ) > ( & object );
            if (pString == nullptr ) {
                return false;
            }

            return this->operator==(* pString);
        }

        /**
         * @brief Comparison Operator
         *
         * @param element : ElementType = Character to compare String to
         *
         * @overload
         * @exceptsafe
         *
         * @returns bool = true if String is of one character and equal with given character, false otherwise
         *
         * @test tested in primitive/StringTest/Comparison Tests
         */
        __CDS_NoDiscard constexpr auto operator == ( ElementType element ) const noexcept -> bool {
            return this->size() == 1u && this->_p[0] == element;
        }

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
        __CDS_NoDiscard __CDS_cpplang_IfConstexpr auto operator == ( StringLiteral cString ) const noexcept -> bool {
            if ( this->_l == 0u ) {
                return std :: char_traits < ElementType > :: length ( cString ) == 0u;
            }

            return std :: char_traits < ElementType > :: compare ( this->cStr(), cString, this->_l ) == 0;
        }

    #if defined(CDS_QT)

        /**
         * Comparison Operator
         *
         * @param string : QString cref = Constant Reference to a QString to compare contents of this String to
         *
         * @overload
         * @exceptsafe
         *
         * @returns bool = true if Strings have same content, false otherwise
         *
         * @test tested in primitive/StringTest/Comparison Tests
         */
        __CDS_OptimalInline auto operator == (QString const & string) const noexcept -> bool {
            return * this == String(string);
        }

    #endif


        /**
         * Comparison Operator, Greater or Equals
         *
         * @param string : String cref = Constant Reference to a String to compare contents of this String to
         *
         * @exceptsafe
         *
         * @returns bool = true if leftmost has the first difference greater or equals than the given right String, false otherwise
         *
         * @test tested in primitive/StringTest/Comparison Tests
         */
        __CDS_NoDiscard __CDS_cpplang_IfConstexpr auto operator >= ( String const & string ) const noexcept -> bool {
            auto compareResult = std :: char_traits < ElementType > :: compare (this->cStr(), string.cStr(), this->_l );
            if ( compareResult > 0 ) {
                return true;
            }

            if ( compareResult < 0 ) {
                return false;
            }

            return this->_l > string._l;
        }

        /**
         * @brief Comparison Operator, Greater or Equals
         *
         * @param element : ElementType = Character to compare String to
         *
         * @overload
         * @exceptsafe
         *
         * @returns bool = true if String is of one character and greater or equal than given character, false otherwise
         *
         * @test tested in primitive/StringTest/Comparison Tests
         */
        __CDS_NoDiscard constexpr auto operator >= ( ElementType element ) const noexcept -> bool {
            return this->size() == 1u && this->_p[0] >= element;
        }

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
         * @param string : QString cref = Constant Reference to a QString to compare contents of this String to
         *
         * @overload
         * @exceptsafe
         *
         * @returns bool = true if leftmost has the first difference greater or equals than the given right String, false otherwise
         *
         * @test tested in MSK
         */
        __CDS_OptimalInline auto operator >= (QString const & string) const noexcept -> bool {
            return * this >= String(string);
        }
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
        __CDS_NoDiscard __CDS_cpplang_IfConstexpr auto operator >= ( StringLiteral cString ) const noexcept -> bool {
            auto length = std :: char_traits < ElementType > :: length ( cString );
            auto compareResult = std :: char_traits < ElementType > :: compare ( this->cStr(), cString, this->_l );
            if ( compareResult > 0 ) {
                return true;
            }

            if ( compareResult < 0 ) {
                return false;
            }

            return this->_l > length;
        }

        /**
         * Comparison Operator, Less or Equals
         *
         * @param string : String cref = Constant Reference to a String to compare contents of this String to
         *
         * @exceptsafe
         *
         * @returns bool = true if leftmost has the first difference less or equals than the given right String, false otherwise
         *
         * @test tested in primitive/StringTest/Comparison Tests
         */
        __CDS_NoDiscard __CDS_cpplang_IfConstexpr auto operator <= ( String const & string ) const noexcept -> bool {
            auto compareResult = std :: char_traits < ElementType > :: compare (this->cStr(), string.cStr(), this->_l );
            if ( compareResult < 0 ) {
                return true;
            }

            if ( compareResult > 0 ) {
                return false;
            }

            return this->_l < string._l;
        }

    #if defined(CDS_QT)

        /**
         * Comparison Operator, Less or Equals
         *
         * @param string : QString cref = Constant Reference to a QString to compare contents of this String to
         *
         * @overload
         * @exceptsafe
         *
         * @returns bool = true if leftmost has the first difference less or equals than the given right String, false otherwise
         *
         * @test tested in primitive/StringTest/Comparison Tests
         */
        __CDS_OptimalInline auto operator <= (QString const & string) const noexcept -> bool {
            return * this <= String(string);
        }

    #endif


        /**
         * @brief Comparison Operator, Less or Equals
         *
         * @param element : ElementType = Character to compare String to
         *
         * @overload
         * @exceptsafe
         *
         * @returns bool = true if String is of one character and less or equal than given character, false otherwise
         *
         * @test tested in primitive/StringTest/Comparison Tests
         */
        __CDS_NoDiscard constexpr auto operator <= ( ElementType element ) const noexcept -> bool {
            return this->size() == 1u && this->_p[0] <= element;
        }

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
        __CDS_NoDiscard __CDS_cpplang_IfConstexpr auto operator <= ( StringLiteral cString ) const noexcept -> bool {
            auto length = std :: char_traits < ElementType > :: length ( cString );
            auto compareResult = std :: char_traits < ElementType > :: compare ( this->cStr(), cString, this->_l );
            if ( compareResult < 0 ) {
                return true;
            }

            if ( compareResult > 0 ) {
                return false;
            }

            return this->_l < length;
        }

        /**
         * @brief Comparison operator, Not Equal
         *
         * @param string : String cref = Constant Reference to a String to compare this Object to
         *
         * @exceptsafe
         *
         * @returns bool = true if Strings are not equal, false otherwise
         *
         * @test tested in primitive/StringTest/Comparison Tests
         */
        __CDS_NoDiscard __CDS_cpplang_IfConstexpr auto operator != ( String const & string ) const noexcept -> bool {
            return ! (* this == string );
        }

        /**
         * @brief Comparison Operator, Not Equal
         *
         * @param element : ElementType = Character to compare String to
         *
         * @overload
         * @exceptsafe
         *
         * @returns bool = true if String is of one character and not equal with given character, false otherwise
         *
         * @test tested in primitive/StringTest/Comparison Tests
         */
        __CDS_NoDiscard constexpr auto operator != ( ElementType element ) const noexcept -> bool {
            return this->size() != 1u || this->_p[0] != element;
        }

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
        __CDS_NoDiscard __CDS_cpplang_IfConstexpr auto operator != ( StringLiteral cString ) const noexcept -> bool {
            return ! ( * this == cString );
        }

    #if defined(CDS_QT)

        /**
         * Comparison Operator, Not Equal
         *
         * @param string : QString cref = Constant Reference to a QString to compare contents of this String to
         *
         * @overload
         * @exceptsafe
         *
         * @returns bool = true if Strings do not have same content, false otherwise
         *
         * @test tested in primitive/StringTest/Comparison Tests
         */
        __CDS_OptimalInline auto operator != (QString const & string) const noexcept -> bool {
            return * this != String(string);
        }

    #endif


        /**
         * Comparison Operator, Less
         *
         * @param string : String cref = Constant Reference to a String to compare contents of this String to
         *
         * @exceptsafe
         *
         * @returns bool = true if leftmost has the first difference less than the given right String, false otherwise
         *
         * @test tested in primitive/StringTest/Comparison Tests
         */
        __CDS_NoDiscard __CDS_cpplang_IfConstexpr auto operator < ( String const & string ) const noexcept -> bool {
            return ! (* this >= string );
        }

        /**
         * @brief Comparison Operator, Less
         *
         * @param element : ElementType = Character to compare String to
         *
         * @overload
         * @exceptsafe
         *
         * @returns bool = true if String is of one character and less than given character, false otherwise
         *
         * @test tested in primitive/StringTest/Comparison Tests
         */
        __CDS_NoDiscard constexpr auto operator < ( ElementType element ) const noexcept -> bool {
            return this->size() == 1u && this->_p[0] < element;
        }

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
        __CDS_NoDiscard __CDS_cpplang_IfConstexpr auto operator < ( StringLiteral cString ) const noexcept -> bool {
            return ! ( * this >= cString );
        }

    #if defined(CDS_QT)

        /**
         * Comparison Operator, Less
         *
         * @param string : QString cref = Constant Reference to a QString to compare contents of this String to
         *
         * @overload
         * @exceptsafe
         *
         * @returns bool = true if leftmost has the first difference less than the given right String, false otherwise
         *
         * @test tested in MSK
         */
        __CDS_OptimalInline auto operator < (QString const & string) const noexcept -> bool {
            return * this < String(string);
        }

    #endif


        /**
         * Comparison Operator, Greater
         *
         * @param string : String cref = Constant Reference to a String to compare contents of this String to
         *
         * @exceptsafe
         *
         * @returns bool = true if leftmost has the first difference greater than the given right String, false otherwise
         *
         * @test tested in primitive/StringTest/Comparison Tests
         */
        __CDS_NoDiscard auto operator > ( String const & string ) const noexcept -> bool {
            return ! (* this <= string );
        }

        /**
         * @brief Comparison Operator, Greater
         *
         * @param element : ElementType = Character to compare String to
         *
         * @overload
         * @exceptsafe
         *
         * @returns bool = true if String is of one character and greater than given character, false otherwise
         *
         * @test tested in primitive/StringTest/Comparison Tests
         */
        __CDS_NoDiscard constexpr auto operator > ( ElementType element ) const noexcept -> bool {
            return this->size() == 1u && this->_p[0] > element;
        }

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
        __CDS_NoDiscard auto operator > ( StringLiteral cString ) const noexcept -> bool {
            return ! ( * this <= cString );
        }

    #if defined(CDS_QT)

        /**
         * Comparison Operator, Greater
         *
         * @param string : QString cref = Constant Reference to a QString to compare contents of this String to
         *
         * @overload
         * @exceptsafe
         *
         * @returns bool = true if leftmost has the first difference greater than the given right String, false otherwise
         *
         * @test tested in MSK
         */
        __CDS_OptimalInline auto operator > (QString const & string) const noexcept -> bool {
            return * this > String(string);
        }

    #endif


        /**
         * @brief Append Function used to append a String to the String
         *
         * @param string : String cref = Constant Reference to the String to add at the end of the String
         *
         * @exceptsafe
         *
         * @returns String ref = Reference to the modified String
         *
         * @test tested in primitive/StringTest/Append/Prepend Tests
         */
        __CDS_NoDiscard __CDS_OptimalInline auto operator + ( String const & string ) const noexcept -> String {
            return String(*this).append(string);
        }

        /**
         * @brief Append Function used to append an ElementType to the String
         *
         * @param element : ElementType = Value to add to the end of the String
         *
         * @exceptsafe
         *
         * @returns String ref = Reference to the modified String
         *
         * @test tested in primitive/StringTest/Append/Prepend Tests
         */
        __CDS_NoDiscard __CDS_OptimalInline auto operator + ( ElementType element ) const noexcept -> String {
            return String(*this).append(element);
        }

        __CDS_NoDiscard __CDS_MaybeUnused __CDS_OptimalInline friend auto operator + ( ElementType element, String const & string ) noexcept -> String {
            return String(element).append(string);
        }

        /**
         * @brief Append Function used to append a std::string to the String
         *
         * @param string : std::string cref = Constant Reference to the std::string to add at the end of the String
         *
         * @exceptsafe
         *
         * @returns String ref = Reference to the modified String
         *
         * @test tested in primitive/StringTest/Append/Prepend Tests
         */
        __CDS_NoDiscard __CDS_OptimalInline auto operator + ( std::string const & string ) const noexcept -> String {
            return String(*this).append(string);
        }

        __CDS_NoDiscard __CDS_MaybeUnused __CDS_OptimalInline friend auto operator + ( std :: string const & element, String const & string ) noexcept -> String {
            return String(element).append(string);
        }

        /**
         * @brief Append Function used to append a StringLiteral to the String
         *
         * @param stringLiteral : StringLiteral = Address to a StringLiteral to add to the end of the String
         *
         * @exceptsafe
         *
         * @returns String ref = Reference to the modified String
         *
         * @test tested in primitive/StringTest/Append/Prepend Tests
         */
        __CDS_NoDiscard __CDS_OptimalInline auto operator + ( StringLiteral stringLiteral ) const noexcept -> String {
            return String(*this).append(stringLiteral);
        }

        __CDS_NoDiscard __CDS_MaybeUnused __CDS_OptimalInline friend auto operator + ( StringLiteral element, String const & string ) noexcept -> String {
            return String(element).append(string);
        }

        /**
         * @brief Append Function used to append a CString to the String
         *
         * @param string : CString = Address to a CString to add to the end of the String
         *
         * @exceptsafe
         *
         * @returns String ref = Reference to the modified String
         *
         * @test tested in primitive/StringTest/Append/Prepend Tests
         */
        __CDS_NoDiscard __CDS_OptimalInline auto operator + ( CString string ) const noexcept -> String {
            return String(*this).append(string);
        }

        __CDS_NoDiscard __CDS_MaybeUnused __CDS_OptimalInline friend auto operator + ( CString element, String const & string ) noexcept -> String {
            return String(element).append(string);
        }

        /**
         * @brief Append Function used to append a sint16 to the String
         *
         * @param value : sint16 = value to add at the end of the String
         *
         * @exceptsafe
         *
         * @returns String ref = Reference to the modified String
         *
         * @test tested in primitive/StringTest/Append/Prepend Tests
         */
        __CDS_NoDiscard __CDS_OptimalInline auto operator + (sint16 value) const noexcept -> String {
            return String(*this).append(value);
        }

        __CDS_NoDiscard __CDS_MaybeUnused __CDS_OptimalInline friend auto operator + ( sint16 element, String const & string ) noexcept -> String {
            return String(element).append(string);
        }

        /**
         * @brief Append Function used to append a sint32 to the String
         *
         * @param value : sint32 = value to add at the end of the String
         *
         * @exceptsafe
         *
         * @returns String ref = Reference to the modified String
         *
         * @test tested in primitive/StringTest/Append/Prepend Tests
         */
        __CDS_NoDiscard __CDS_OptimalInline auto operator + (sint32 value) const noexcept -> String {
            return String(*this).append(value);
        }

        __CDS_NoDiscard __CDS_MaybeUnused __CDS_OptimalInline friend auto operator + ( sint32 element, String const & string ) noexcept -> String {
            return String(element).append(string);
        }

        /**
         * @brief Append Function used to append a sint64 to the String
         *
         * @param value : sint64 = value to add at the end of the String
         *
         * @exceptsafe
         *
         * @returns String ref = Reference to the modified String
         *
         * @test tested in primitive/StringTest/Append/Prepend Tests
         */
        __CDS_NoDiscard __CDS_OptimalInline auto operator + (sint64 value) const noexcept -> String {
            return String(*this).append(value);
        }

        __CDS_NoDiscard __CDS_MaybeUnused __CDS_OptimalInline friend auto operator + ( sint64 element, String const & string ) noexcept -> String {
            return String(element).append(string);
        }

        /**
         * @brief Append Function used to append a uint8 to the String
         *
         * @param value : uint8 = value to add at the end of the String
         *
         * @exceptsafe
         *
         * @returns String ref = Reference to the modified String
         *
         * @test tested in primitive/StringTest/Append/Prepend Tests
         */
        __CDS_NoDiscard __CDS_OptimalInline auto operator + (uint8 value) const noexcept -> String {
            return String(*this).append(value);
        }

        __CDS_NoDiscard __CDS_MaybeUnused __CDS_OptimalInline friend auto operator + ( uint8 element, String const & string ) noexcept -> String {
            return String(element).append(string);
        }

        /**
         * @brief Append Function used to append a uint16 to the String
         *
         * @param value : uint16 = value to add at the end of the String
         *
         * @exceptsafe
         *
         * @returns String ref = Reference to the modified String
         *
         * @test tested in primitive/StringTest/Append/Prepend Tests
         */
        __CDS_NoDiscard __CDS_OptimalInline auto operator + (uint16 value) const noexcept -> String {
            return String(*this).append(value);
        }

        __CDS_NoDiscard __CDS_MaybeUnused __CDS_OptimalInline friend auto operator + ( uint16 element, String const & string ) noexcept -> String {
            return String(element).append(string);
        }

        /**
         * @brief Append Function used to append a uint32 to the String
         *
         * @param value : uint32 = value to add at the end of the String
         *
         * @exceptsafe
         *
         * @returns String ref = Reference to the modified String
         *
         * @test tested in primitive/StringTest/Append/Prepend Tests
         */
        __CDS_NoDiscard __CDS_OptimalInline auto operator + (uint32 value) const noexcept -> String {
            return String(*this).append(value);
        }

        __CDS_NoDiscard __CDS_MaybeUnused __CDS_OptimalInline friend auto operator + ( uint32 element, String const & string ) noexcept -> String {
            return String(element).append(string);
        }

        /**
         * @brief Append Function used to append a uint64 to the String
         *
         * @param value : uint64 = value to add at the end of the String
         *
         * @exceptsafe
         *
         * @returns String ref = Reference to the modified String
         *
         * @test tested in primitive/StringTest/Append/Prepend Tests
         */
        __CDS_NoDiscard __CDS_OptimalInline auto operator + (uint64 value) const noexcept -> String {
            return String(*this).append(value);
        }

        /**
         * @brief Append Function used to append a float to the String
         *
         * @param value : float = value to add at the end of the String
         *
         * @exceptsafe
         *
         * @returns String ref = Reference to the modified String
         *
         * @test tested in primitive/StringTest/Append/Prepend Tests
         */
        __CDS_NoDiscard __CDS_OptimalInline auto operator + (float value) const noexcept -> String {
            return this->operator+(std::to_string(value) );
        }

        __CDS_NoDiscard __CDS_MaybeUnused __CDS_OptimalInline friend auto operator + ( float element, String const & string ) noexcept -> String {
            return String(element).append(string);
        }

        /**
         * @brief Append Function used to append a double to the String
         *
         * @param value : double = value to add at the end of the String
         *
         * @exceptsafe
         *
         * @returns String ref = Reference to the modified String
         *
         * @test tested in primitive/StringTest/Append/Prepend Tests
         */
        __CDS_NoDiscard __CDS_OptimalInline auto operator + (double value) const noexcept -> String {
            return this->operator+(std::to_string(value) );
        }

        __CDS_NoDiscard __CDS_MaybeUnused __CDS_OptimalInline friend auto operator + ( double element, String const & string ) noexcept -> String {
            return String(element).append(string);
        }

    #if defined(CDS_QT)

        /**
         * @brief Append Function used to append a QString to the String
         *
         * @param string : QString cref = Constant Reference to a QString to append at the end of this String
         *
         * @exceptsafe
         *
         * @returns String ref = Reference to the modified String
         *
         * @test tested in MSK
         */
        __CDS_OptimalInline auto operator + (QString const & string) const noexcept -> String {
            return * this + String(string);
        }

        __CDS_NoDiscard __CDS_MaybeUnused __CDS_OptimalInline friend auto operator + ( QString const & element, String const & string ) noexcept -> String {
            return String(element).append(string);
        }

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
        __CDS_NoDiscard __CDS_OptimalInline auto operator * (int count) const noexcept -> String {
            String res;
            for ( int i = 0; i < count; i ++ ) {
                res += (*this);
            }

            return res;
        }


        /**
         * @brief Function used to trim the occurrences of given element [e] from the left of the String
         *
         * @param element : ElementType = element to trim from the left
         *
         * @exceptsafe
         *
         * @returns String ref = Reference to the modified String
         *
         * @test tested in primitive/StringTest/Utility Functions, String Formatting
         */
        __CDS_cpplang_ConstexprDynamicAllocation auto ltrim ( ElementType element = ' ' ) noexcept -> String & {
            while ( ! this->empty () && this->front() == element ) {
                * this = this->substr(1);
            }

            return * this;
        }

        /**
         * @brief Function used to trim the occurrences of given String [s] from the left of the String
         *
         * @param string : String cref = Constant Reference to the String occurrences to remove from the left
         *
         * @exceptsafe
         *
         * @returns String ref = Reference to the modified String
         *
         * @test tested in primitive/StringTest/Utility Functions, String Formatting
         */
        __CDS_cpplang_ConstexprDynamicAllocation auto ltrim ( String const & string ) noexcept -> String & {
            while (! this->empty () && string.contains(this->front() ) ) {
                * this = this->substr(1);
            }

            return * this;
        }

        /**
         * @brief Function used to trim the occurrences of given element [e] from the left of the String into a new String
         *
         * @param element : ElementType = element to trim from the left
         *
         * @exceptsafe
         *
         * @returns String ref = Reference to a new, modified String
         *
         * @test tested in primitive/StringTest/Utility Functions, String Formatting
         */
        __CDS_NoDiscard __CDS_MaybeUnused __CDS_OptimalInline auto ltrim ( ElementType element = ' ' ) const noexcept -> String {
            return String(*this).ltrim(element);
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
        __CDS_NoDiscard __CDS_MaybeUnused __CDS_OptimalInline auto ltrim ( String const & string ) const noexcept -> String {
            return String(*this).ltrim(string);
        }

        /**
         * @brief Function used to trim the occurrences of given element [e] from the right of the String
         *
         * @param element : ElementType = element to trim from the right
         *
         * @exceptsafe
         *
         * @returns String ref = Reference to the modified String
         *
         * @test tested in primitive/StringTest/Utility Functions, String Formatting
         */
        __CDS_cpplang_ConstexprConditioned auto rtrim ( ElementType element = ' ' ) noexcept -> String & {
            while ( ! this->empty () && this->back() == element ) {
                this->_p[--this->_l] = '\0';
            }

            return * this;
        }

        /**
         * @brief Function used to trim the occurrences of given String [s] from the right of the String
         *
         * @param string : String cref = Constant Reference to the String occurrences to remove
         *
         * @exceptsafe
         *
         * @returns String ref = Reference to the modified String
         *
         * @test tested in primitive/StringTest/Utility Functions, String Formatting
         */
        __CDS_cpplang_ConstexprConditioned auto rtrim ( String const & string ) noexcept -> String & {
            while (! this->empty () && string.contains(this->back()) ) {
                this->_p[--this->_l] = '\0';
            }

            return * this;
        }

        /**
         * @brief Function used to trim the occurrences of given element [e] from the right of the String into a new String
         *
         * @param element : ElementType = element to trim from the right
         *
         * @exceptsafe
         *
         * @returns String ref = Reference to a new, modified String
         *
         * @test tested in primitive/StringTest/Utility Functions, String Formatting
         */
        __CDS_NoDiscard __CDS_MaybeUnused __CDS_OptimalInline auto rtrim ( ElementType element = ' ' ) const noexcept -> String {
            return String(*this).rtrim(element);
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
        __CDS_NoDiscard __CDS_MaybeUnused __CDS_OptimalInline auto rtrim ( String const & string ) const noexcept -> String {
            return String(*this).rtrim(string);
        }

        /**
         * @brief Function used to trim the occurrences of given element [e] from the left and right of the String
         *
         * @param element : ElementType = element to trim from the left and right
         *
         * @exceptsafe
         *
         * @returns String ref = Reference to the modified String
         *
         * @test tested in primitive/StringTest/Utility Functions, String Formatting
         */
        __CDS_cpplang_ConstexprDynamicAllocation auto trim ( ElementType element = ' ' ) noexcept -> String & {
            return this->ltrim(element).rtrim(element);
        }

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
        __CDS_cpplang_ConstexprDynamicAllocation auto trim ( String const & string ) noexcept -> String & {
            return this->ltrim(string).rtrim(string);
        }

        /**
         * @brief Function used to trim the occurrences of given element [e] from the left and right of the String into a new String
         *
         * @param element : ElementType = element to trim from the left and right
         *
         * @exceptsafe
         *
         * @returns String ref = Reference to a new, modified String
         *
         * @test tested in primitive/StringTest/Utility Functions, String Formatting
         */
        __CDS_NoDiscard __CDS_MaybeUnused __CDS_OptimalInline auto trim ( ElementType element = ' ' ) const noexcept -> String {
            return String(*this).trim(element);
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

        __CDS_NoDiscard __CDS_MaybeUnused __CDS_OptimalInline auto trim ( String const & string ) const noexcept -> String {
            return String(*this).trim(string);
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
        __CDS_cpplang_ConstexprDynamicAllocation auto rjust (Size justifySize, ElementType padChar = ' ') noexcept -> String & { // NOLINT(bugprone-easily-swappable-parameters)
            while ( this->size() < justifySize ) {
                (void) this->append(padChar);
            }

            return * this;
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
         * @returns String = the new string with modifications
         *
         * @test tested in primitive/StringTest/Utility Functions, String Formatting
         */
        __CDS_NoDiscard __CDS_MaybeUnused __CDS_OptimalInline auto rjust (Size size, ElementType element = ' ') const noexcept -> String {
            return String(*this).rjust(size, element);
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
        __CDS_cpplang_ConstexprDynamicAllocation auto ljust (Size justifySize, ElementType padChar = ' ') noexcept -> String & { // NOLINT(bugprone-easily-swappable-parameters)
            while ( this->size() < justifySize ) {
                (void) this->prepend(padChar);
            }

            return * this;
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
         * @returns String = the new string with modifications
         *
         * @test tested in primitive/StringTest/Utility Functions, String Formatting
         */
        __CDS_NoDiscard __CDS_MaybeUnused __CDS_OptimalInline auto ljust (Size size, ElementType element = ' ') const noexcept -> String {
            return String(*this).ljust(size, element);
        }

    public:

        /**
         * @brief Function used to check whether character is upper
         *
         * @param character : char = Character to check whether is upper
         *
         * @static
         * @exceptsafe
         *
         * @returns bool = true if character is upper, false otherwise
         *
         * @test tested in primitive/StringTest/Utility Functions, String Formatting
         */
        constexpr auto static isUpperChar(char character) noexcept -> bool {
            return character >= 'A' && character <= 'Z';
        }

        /**
         * @brief Function used to check whether character is lower
         *
         * @param character : char = Character to check whether is lower
         *
         * @static
         * @exceptsafe
         *
         * @returns bool = true if character is lower, false otherwise
         *
         * @test tested in primitive/StringTest/Utility Functions, String Formatting
         */
        constexpr auto static isLowerChar(char character) noexcept -> bool {
            return character >= 'a' && character <= 'z';
        }

        /**
         * @brief Function used to check whether character is a digit
         *
         * @param character : char = Character to check whether is a digit
         *
         * @static
         * @exceptsafe
         *
         * @returns bool = true if character is a digit, false otherwise
         *
         * @test tested in primitive/StringTest/Utility Functions, String Formatting
         */
        constexpr auto static isDigit(char character) noexcept -> bool {
            return character >= '0' && character <= '9';
        }

        /**
         * @brief Function used to check whether character is a letter
         *
         * @param character : char = Character to check whether is a letter
         *
         * @static
         * @exceptsafe
         *
         * @returns bool = true if character is a letter, false otherwise
         *
         * @test tested in primitive/StringTest/Utility Functions, String Formatting
         */
        constexpr auto static isLetter(char character) noexcept -> bool {
            return isUpperChar(character) || isLowerChar(character);
        }

        /**
         * @brief Function used to check whether character is alphanumeric
         *
         * @param character : char = Character to check whether is alphanumeric
         *
         * @static
         * @exceptsafe
         *
         * @returns bool = true if character is alphanumeric, false otherwise
         *
         * @test tested in primitive/StringTest/Utility Functions, String Formatting
         */
        constexpr auto static isAlpha(char character) noexcept -> bool {
            return isLetter(character) || isDigit(character);
        }

        /**
         * @brief Function used to check whether character is a vowel
         *
         * @param character : char = Character to check whether is a vowel
         *
         * @static
         * @exceptsafe
         *
         * @returns bool = true if character is a vowel, false otherwise
         *
         * @test tested in primitive/StringTest/Utility Functions, String Formatting
         */
        __CDS_OptimalInline auto static isVowel(char character) noexcept -> bool {
            return String("aeiouAEIOU").contains(character);
        }

        /**
         * @brief Function used to check whether character is a consonant
         *
         * @param character : char = Character to check whether is a consonant
         *
         * @static
         * @exceptsafe
         *
         * @returns bool = true if character is a consonant, false otherwise
         *
         * @test tested in primitive/StringTest/Utility Functions, String Formatting
         */
        __CDS_MaybeUnused __CDS_cpplang_ConstexprConditioned auto static isConsonant(char character) noexcept -> bool {
            return isLetter(character) && ! isVowel(character);
        }

        /**
         * @brief Function used to convert character to a lower character, if possible ( if is upper )
         *
         * @param character : char = Character to convert
         *
         * @static
         * @exceptsafe
         *
         * @returns char = Modified Character Value
         *
         * @test tested in primitive/StringTest/Utility Functions, String Formatting
         */
        constexpr auto static lowerChar(char character) noexcept -> char {
            return isUpperChar(character) ? static_cast < ElementType > ( character + 32 ) : character;
        }

        /**
         * @brief Function used to convert character to an upper character, if possible ( if is lower )
         *
         * @param character : char = Character to convert
         *
         * @static
         * @exceptsafe
         *
         * @returns char = Modified Character Value
         *
         * @test tested in primitive/StringTest/Utility Functions, String Formatting
         */
        constexpr auto static upperChar(char character) noexcept -> char {
            return isLowerChar(character) ? static_cast < ElementType > ( character - 32 ) : character;
        }

        /**
         * @brief Function used to convert character to a lower character, if possible ( if is upper )
         *
         * @param character : char ref = Reference Character to convert
         *
         * @static
         * @exceptsafe
         *
         * @returns char ref = Reference to Modified Character Value
         *
         * @test tested in primitive/StringTest/Utility Functions, String Formatting
         */
        __CDS_MaybeUnused __CDS_cpplang_ConstexprConditioned auto static toLowerChar(char & character) noexcept -> char & {
            character = lowerChar(character); return character;
        }

        /**
         * @brief Function used to convert character to an upper character, if possible ( if is lower )
         *
         * @param character : char ref = Reference Character to convert
         *
         * @static
         * @exceptsafe
         *
         * @returns char ref = Reference to Modified Character Value
         *
         * @test tested in primitive/StringTest/Utility Functions, String Formatting
         */
        __CDS_MaybeUnused __CDS_cpplang_ConstexprConditioned auto static toUpperChar(char & character) noexcept -> char & {
            character = upperChar(character); return character;
        }

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
        __CDS_cpplang_ConstexprConditioned auto toLower () noexcept -> String & {
            for ( Index i = 0; static_cast < Size > ( i ) < this->_l; i++ ) {
                this->_p[i] = lowerChar(this->_p[i]);
            }

            return * this;
        }

        /**
         * @brief Function used to convert characters of a String to their upper values ( if are lower )
         *
         * @exceptsafe
         *
         * @returns String ref = Reference to the modified String object
         *
         * @test tested in primitive/StringTest/Utility Functions, String Formatting
         */
        __CDS_cpplang_ConstexprConditioned auto toUpper () noexcept -> String & {
            for ( Index i = 0; static_cast < Size > ( i ) < this->_l; i++ ) {
                this->_p[i] = upperChar(this->_p[i]);
            }

            return * this;
        }
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
        __CDS_cpplang_ConstexprConditioned auto toLower () noexcept -> String & { for ( Size i = 0; i < this->_l; i++ ) this->_p[i] = lowerChar(this->_p[i]); return * this; }
    
        /**
         * @brief Function used to convert characters of a String to their upper values ( if are lower )
         *
         * @exceptsafe
         *
         * @returns String ref = Reference to the modified String object
         *
         * @test tested in primitive/StringTest/Utility Functions, String Formatting
         */
        __CDS_cpplang_ConstexprConditioned auto toUpper () noexcept -> String & { for ( Size i = 0; i < this->_l; i++ ) this->_p[i] = upperChar(this->_p[i]); return * this; }

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
        __CDS_NoDiscard __CDS_OptimalInline auto lower () const noexcept -> String {
            return String(*this).toLower();
        }

        /**
         * @brief Function used to convert characters of a String to their upper values ( if are lower ) and return it
         *
         * @exceptsafe
         *
         * @returns String = new String object modified as upper
         *
         * @test tested in primitive/StringTest/Utility Functions, String Formatting
         */
        __CDS_NoDiscard __CDS_OptimalInline auto upper () const noexcept -> String {
            return String(*this).toUpper();
        }

        /**
         * @brief Copy Operator
         *
         * @param string : String cref = Constant Reference to a String to copy data from
         *
         * @exceptsafe
         *
         * @returns String ref = Reference to the modified Object
         *
         * @test tested in primitive/StringTest/Assignment Tests
         */
        __CDS_cpplang_ConstexprDynamicAllocation auto operator = ( String const & string ) noexcept -> String & {
            if ( this == & string ) {
                return * this;
            }

            this->clear();

            if ( string.empty() ) {
                return * this;
            }

            this->_alloc(string.size());
            (void) std::memcpy (this->_p, string._p, string._l + 1llu );
            this->_l = string._l;

            return * this;
        }

        /**
         * @brief Move Operator
         *
         * @param string : String mref = Move Reference to a String to copy data from
         *
         * @exceptsafe
         *
         * @returns String ref = Reference to the modified Object
         *
         * @test tested in primitive/StringTest/Assignment Tests
         */
        __CDS_cpplang_ConstexprDynamicAllocation auto operator = ( String && string ) noexcept -> String & {
            if ( this == & string ) {
                return * this;
            }

            Memory :: instance().destroyArray ( this->_p );

            this->_p = exchange(string._p, nullptr );
            this->_l = exchange(string._l, 0u );
            this->_c = exchange(string._c, 0u );

            return * this;
        }

    #if defined(CDS_QT)

        /**
         * @brief Copy Operator
         *
         * @param string : QString cref = Constant Reference to a QString to copy data from
         *
         * @exceptsafe
         *
         * @returns String ref = Reference to the modified Object
         *
         * @test tested in primitive/StringTest/Assignment Tests
         */
        __CDS_OptimalInline String & operator = (QString const & string) noexcept {
            return ((* this) = String(string));
        }

    #endif

        /**
         * @brief Copy Operator
         *
         * @param string : std::string cref = Constant Reference to a std::string to copy data from
         *
         * @exceptsafe
         *
         * @returns String ref = Reference to the modified Object
         *
         * @test tested in primitive/StringTest/Assignment Tests
         */
        __CDS_OptimalInline auto operator = ( std::string const & string ) noexcept -> String & {
            return this->operator=(String(string)); // NOLINT(misc-unconventional-assign-operator)
        }

        /**
         * @brief Copy Operator
         *
         * @param element : ElementType = Element to assign to the String
         *
         * @exceptsafe
         *
         * @returns String ref = Reference to the modified Object
         *
         * @test tested in primitive/StringTest/Assignment Tests
         */
        __CDS_OptimalInline auto operator = ( ElementType element ) noexcept -> String & {
            return this->operator=(String().append(element));  // NOLINT(misc-unconventional-assign-operator)
        }

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
        __CDS_OptimalInline auto operator = ( StringLiteral cString ) noexcept -> String & {
            return this->operator=(String(cString)); // NOLINT(misc-unconventional-assign-operator)
        }


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
        __CDS_NoDiscard auto split ( ElementType, Size = UINT32_MAX ) const noexcept -> DoubleLinkedList < String >;

        __CDS_NoDiscard __CDS_MaybeUnused auto lines () const noexcept -> DoubleLinkedList < String >;

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
        __CDS_NoDiscard auto split ( String const &, Size = UINT32_MAX ) const noexcept -> DoubleLinkedList < String >;

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
        __CDS_NoDiscard __CDS_MaybeUnused auto splitByString ( String const &, Size = UINT32_MAX ) const noexcept -> DoubleLinkedList < String >;

        /**
         * @brief Variable indicating an invalid position resulted from a find operation
         */
        constexpr static Index INVALID_POS = -1;

        /**
         * @brief Function used to check whether String contains given element
         *
         * @param element : ElementType = element to check if it exists in a String
         *
         * @exceptsafe
         *
         * @returns bool = true if element exists in String, false otherwise
         *
         * @test tested in primitive/StringTest/Content Functions Tests
         */
        __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto contains ( ElementType element ) const noexcept -> bool {
            return this->findFirst(element ) != INVALID_POS;
        }

        /**
         * @brief Function used to check whether String contains given String
         *
         * @param string : String cref = Constant Reference to a String to check if Object contains it
         *
         * @exceptsafe
         *
         * @returns bool = true if element exists in String, false otherwise
         *
         * @test tested in primitive/StringTest/Content Functions Tests
         */
        __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto contains ( String const & string ) const noexcept -> bool {
            return this->findFirst(string ) != INVALID_POS;
        }

        /**
         * @brief Function used to check whether String contains given StringLiteral
         *
         * @param stringLiteral : StringLiteral = Address to a C String to check if Object contains it
         *
         * @exceptsafe
         *
         * @returns bool = true if element exists in String, false otherwise
         *
         * @test tested in primitive/StringTest/Content Functions Tests
         */
        __CDS_NoDiscard __CDS_OptimalInline auto contains ( StringLiteral stringLiteral ) const noexcept -> bool {
            return this->findFirst( String(stringLiteral) ) != INVALID_POS;
        }

        /**
         * @brief Function used to check whether String contains given std::string
         *
         * @param string : std::string cref = Constant Reference to a std::string to check if Object contains it
         *
         * @exceptsafe
         *
         * @returns bool = true if element exists in String, false otherwise
         *
         * @test tested in primitive/StringTest/Content Functions Tests
         */
        __CDS_NoDiscard __CDS_OptimalInline auto contains ( std::string const & string ) const noexcept -> bool {
            return this->findFirst(String(string) ) != INVALID_POS;
        }

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
        __CDS_NoDiscard __CDS_OptimalInline auto contains (QString const & string) const noexcept -> bool {
            return this->contains(String(string));
        }

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
        __CDS_NoDiscard __CDS_OptimalInline auto diag() const noexcept -> String {
            return String("Debug = { data = '") + this->_p + "', length = " + this->_l + ", capacity = " + this->_c + " }";
        }

    #else

        __CDS_NoDiscard __CDS_OptimalInline auto diag() const noexcept -> String { return ""; }

    #endif

        /**
         * @brief Print Operator
         *
         * @param out : std::ostream ref = Reference to an output stream to print on
         * @param string : String cref = Constant Reference to the String to print
         *
         * @exceptsafe
         *
         * @return std::ostream ref = Reference to the modified output stream
         *
         * @test Not Applicable
         */
        friend __CDS_OptionalInline auto operator << ( std::ostream & out, String const & string ) noexcept -> std::ostream & {
            return ( out << (string._p == nullptr ? "" : string._p) );
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
        __CDS_NoDiscard __CDS_cpplang_VirtualConstexpr auto hash () const noexcept -> Index override {
            return static_cast < Index > ( this->length() );
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
        __CDS_NoDiscard __CDS_OptimalInline auto toString () const noexcept -> String override {
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
        __CDS_OptimalInline auto replace ( Index pos, Size len, String const & newInPlace ) noexcept -> String & {
            String left = this->substr(0, pos);
            String right = this->substr(pos + static_cast < Index > ( len ));

            return ( * this = left + newInPlace + right );
        }

        /**
         * @brief Function used to apply a function over each of the elements in the String iteratively. Requires mutable String, enables modification of elements
         *
         * @tparam Action = Callable type with void return type ( preferably ) and one input parameter representing an iterable element ( ElementType or ElementType ref or ElementType cref )
         * @param action : Action cref = Constant Reference to the Callable to supply the element to
         *
         * @throws Action's exceptions, if any. If none, is exception safe
         *
         * @returns String ref = Reference to the object after the iteration
         *
         * @test Tested in primitive/StringTest/ForEach Tests
         */
        template < typename Action >
        __CDS_MaybeUnused __CDS_cpplang_ConstexprConditioned auto forEach ( Action const & action ) noexcept ( noexcept ( ( * Type < Action > :: unsafeAddress () ) (Type < char > :: unsafeReference() ) ) ) -> String & {
            for ( Index i = 0; static_cast < Size > ( i ) < this->_l; ++ i ) {
                action(this->_p[i]);
            }

            return * this;
        }

        /**
         * @brief Function used to apply a function over each of the elements in the String iteratively. Is const, requiring Action over immutable element ( no char & )
         *
         * @tparam Action = Callable type with void return type ( preferably ) and one input parameter representing an iterable element ( ElementType or ElementType ref or ElementType cref )
         * @param action : Action cref = Constant Reference to the Callable to supply the element to
         *
         * @throws Action's exceptions, if any. If none, is exception safe
         *
         * @returns String ref = Reference to the object after the iteration
         *
         * @test Tested in primitive/StringTest/ForEach Tests
         */
        template < typename Action >
        __CDS_MaybeUnused __CDS_cpplang_ConstexprConditioned auto forEach ( Action const & action ) const noexcept ( noexcept ( ( * Type < Action > :: unsafeAddress () ) (Type < const char > :: unsafeReference() ) ) ) -> String const & {
            for ( Index i = 0; static_cast < Size > ( i ) < this->_l; ++ i ) {
                action(this->_p[i]);
            }

            return * this;
        }

        /**
         * @brief Function used to count number of elements that validate a certain Predicate. Requires mutable String, as Predicate given can change elements in String
         *
         * @tparam Predicate = boolean return Callable with one parameter of ElementType, used to validate a property of an element
         *
         * @param predicate : Predicate cref = Constant Reference to a Predicate - static function, Lambda, Function or any callable type object
         *
         * @throws Predicate's exception, if any. If none, is exception safe
         *
         * @return Size = number of elements validating given predicate
         *
         * @test Tested in primitive/StringTest/ForEach tests
         */
        template < typename Predicate, typename P = Predicate, typename std :: enable_if < Type < P > :: isCallable, int > :: type = 0 >
        __CDS_MaybeUnused __CDS_cpplang_ConstexprConditioned auto count ( Predicate const & predicate ) noexcept ( noexcept ( ( * Type < Predicate > :: unsafeAddress () ) (Type < char > :: unsafeReference() ) ) ) -> Size {
            Size count = 0u;
            for ( Index i = 0; static_cast < Size > ( i ) < this->_l; ++ i ) {
                if (predicate(this->_p[i])) {
                    count++;
                }
            }

            return count;
        }

        /**
         * @brief Function used to count number of elements that validate a certain Predicate. Requires Predicate that does not modify elements ( char & ), due to it being applied over immutable String
         *
         * @tparam Predicate = boolean return Callable with one parameter of ElementType, used to validate a property of an element
         *
         * @param predicate : Predicate cref = Constant Reference to a Predicate - static function, Lambda, Function or any callable type object
         *
         * @throws Predicate's exception, if any. If none, is exception safe
         *
         * @return Size = number of elements validating given predicate
         *
         * @test Tested in primitive/StringTest/ForEach tests
         */
        template < typename Predicate, typename P = Predicate, typename std :: enable_if < Type < P > :: isCallable, int > :: type = 0  >
        __CDS_MaybeUnused __CDS_cpplang_ConstexprConditioned auto count ( Predicate const & predicate ) const noexcept ( noexcept ( ( * Type < Predicate > :: unsafeAddress () ) (Type < const char > :: unsafeReference() ) ) ) -> Size {
            Size count = 0u;
            for ( Index i = 0; static_cast < Size > ( i ) < this->_l; ++ i ) {
                if (predicate(this->_p[i])) {
                    count++;
                }
            }

            return count;
        }

        __CDS_MaybeUnused __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto count ( ElementType element ) const noexcept -> Size {
            Size count = 0u;
            for ( Index i = 0; static_cast < Size > ( i ) < this->_l; ++ i ) {
                if (this->_p[i] == element) {
                    ++ count;
                }
            }

            return count;
        }

        /**
         * @brief Function used to verify if a given number of elements validate a certain Predicate. Requires mutable String, as Predicate given can change elements in String
         *
         * @tparam Predicate = boolean return Callable with one parameter of ElementType, used to validate a property of an element
         *
         * @param predicate : Predicate cref = Constant Reference to a Predicate - static function, Lambda, Function or any callable type object
         *
         * @throws Predicate's exception, if any. If none, is exception safe
         *
         * @return bool = true if required count to validate <= count that validate, false otherwise
         *
         * @test Tested in primitive/StringTest/ForEach tests
         */
        template < typename Predicate >
        __CDS_MaybeUnused __CDS_cpplang_ConstexprConditioned auto some (Predicate const & predicate, Size count ) noexcept ( noexcept ( ( * Type < Predicate > :: unsafeAddress () ) (Type < char > :: unsafeReference() ) ) ) -> bool {
            return count <= this->count (predicate );
        }

        /**
         * @brief Function used to verify if a given number of elements validate a certain Predicate. Requires Predicate that does not modify elements ( char & ), due to it being applied over immutable String
         *
         * @tparam Predicate = boolean return Callable with one parameter of ElementType, used to validate a property of an element
         *
         * @param predicate : Predicate cref = Constant Reference to a Predicate - static function, Lambda, Function or any callable type object
         *
         * @throws Predicate's exception, if any. If none, is exception safe
         *
         * @return bool = true if required count to validate <= count that validate, false otherwise
         *
         * @test Tested in primitive/StringTest/ForEach tests
         */
         template < typename Predicate >
        __CDS_MaybeUnused __CDS_cpplang_ConstexprConditioned auto some (Predicate const & predicate, Size count ) const noexcept( noexcept ( ( * Type < Predicate > :: unsafeAddress () ) (Type < const char > :: unsafeReference() ) ) ) -> bool {
            return count <= this->count (predicate );
        }

        /**
         * @brief Function used to verify if any element validates a certain Predicate. Requires mutable String, as Predicate given can change elements in String
         *
         * @tparam Predicate = boolean return Callable with one parameter of ElementType, used to validate a property of an element
         *
         * @param predicate : Predicate cref = Constant Reference to a Predicate - static function, Lambda, Function or any callable type object
         *
         * @throws Predicate's exception, if any. If none, is exception safe
         *
         * @return bool = true if at least one element validates given Predicate, false otherwise
         *
         * @test Tested in primitive/StringTest/ForEach tests
         */
        template < typename Predicate >
        __CDS_MaybeUnused __CDS_cpplang_ConstexprConditioned auto any ( Predicate const & predicate ) noexcept ( noexcept ( ( * Type < Predicate > :: unsafeAddress () ) (Type < char > :: unsafeReference() ) ) ) -> bool {
            return 1u <= this->count(predicate);
        }

        /**
         * @brief Function used to verify if any element validates a certain Predicate. Requires Predicate that does not modify elements ( char & ), due to it being applied over immutable String
         *
         * @tparam Predicate = boolean return Callable with one parameter of ElementType, used to validate a property of an element
         *
         * @param predicate : Predicate cref = Constant Reference to a Predicate - static function, Lambda, Function or any callable type object
         *
         * @throws Predicate's exception, if any. If none, is exception safe
         *
         * @return bool = true if at least one element validates given Predicate, false otherwise
         *
         * @test Tested in primitive/StringTest/ForEach tests
         */
        template < typename Predicate >
        __CDS_MaybeUnused __CDS_cpplang_ConstexprConditioned auto any ( Predicate const & predicate ) const noexcept ( noexcept ( ( * Type < Predicate > :: unsafeAddress () ) (Type < const char > :: unsafeReference() ) ) ) -> bool {
            return 1u <= this->count(predicate);
        }

        /**
         * @brief Function used to verify if all the elements validate a certain Predicate. Requires mutable String, as Predicate given can change elements in String
         *
         * @tparam Predicate = boolean return Callable with one parameter of ElementType, used to validate a property of an element
         *
         * @param predicate : Predicate cref = Constant Reference to a Predicate - static function, Lambda, Function or any callable type object
         *
         * @throws Predicate's exception, if any. If none, is exception safe
         *
         * @return bool = true if all elements validate given Predicate, false otherwise
         *
         * @test Tested in primitive/StringTest/ForEach tests
         */
        template < typename Predicate >
        __CDS_MaybeUnused __CDS_cpplang_ConstexprConditioned auto all ( Predicate const & predicate ) noexcept ( noexcept ( ( * Type < Predicate > :: unsafeAddress () ) (Type < char > :: unsafeReference() ) ) ) -> bool {
            return this->size() == this->count(predicate);
        }

        /**
         * @brief Function used to verify if all the elements validate a certain Predicate. Requires Predicate that does not modify elements ( char & ), due to it being applied over immutable String
         *
         * @tparam Predicate = boolean return Callable with one parameter of ElementType, used to validate a property of an element
         *
         * @param predicate : Predicate cref = Constant Reference to a Predicate - static function, Lambda, Function or any callable type object
         *
         * @throws Predicate's exception, if any. If none, is exception safe
         *
         * @return bool = true if all elements validate given Predicate, false otherwise
         *
         * @test Tested in primitive/StringTest/ForEach tests
         */
        template < typename Predicate >
        __CDS_MaybeUnused __CDS_cpplang_ConstexprConditioned auto all ( Predicate const & predicate ) const noexcept ( noexcept ( ( * Type < Predicate > :: unsafeAddress () ) (Type < const char > :: unsafeReference() ) ) ) -> bool {
            return this->size() == this->count(predicate);
        }

        /**
         * @brief Function obtains a String that contains the contents of the caller in reverse order
         *
         * @exceptsafe
         *
         * @return String = new String with reversed contents
         *
         * @test Tested in primitive/StringTest/Constructor Tests
         */
        __CDS_NoDiscard __CDS_OptimalInline auto reversed() const noexcept -> String {
            String reversed;
            reversed._alloc(this->_l);
            for (Index i = static_cast < Index > (this->_l) - 1; i >= 0; -- i) {
                reversed._p[reversed._l++] = this->_p[i];
            }

            return reversed;
        }

        __CDS_NoDiscard __CDS_MaybeUnused static auto join ( Collection < String > const &, String const & = "" ) noexcept -> String;

        /**
         * @brief Function checks whether a String starts with a given String
         *
         * @param str : String cref = Constant Reference to a String to check if it is at the beginning of the caller String
         *
         * @exceptsafe
         *
         * @return bool = true if String starts with given parameter, false otherwise
         *
         * @test Tested in primitive/StringTest/Utility Tests
         */
        __CDS_NoDiscard __CDS_MaybeUnused __CDS_cpplang_ConstexprDynamicAllocation auto startsWith (String const & str) const noexcept -> bool {
            if ( str.size() > this->size() ) {
                return false;
            }

            return this->substr(0, static_cast < Index > ( str.size() )) == str;
        }

        /**
         * @brief Function checks whether a String ends with a given String
         *
         * @param str : String cref = Constant Reference to a String to check if it is at the end of the caller String
         *
         * @exceptsafe
         *
         * @return bool = true if String ends with given parameter, false otherwise
         *
         * @test Tested in primitive/StringTest/Utility Tests
         */
        __CDS_NoDiscard __CDS_MaybeUnused __CDS_cpplang_ConstexprDynamicAllocation auto endsWith (String const & str) const noexcept -> bool {
            if ( str.size() > this->size() ) {
                return false;
            }

            return this->substr(static_cast < Index > ( this->size() ) - static_cast < Index > ( str.size() )) == str;
        }

        /**
         * @brief Function used to remove a String's prefix. Used over mutable Strings, removing it from the caller String
         *
         * @param prefix : String cref = Constant Reference to the String containing the prefix to remove
         *
         * @exceptsafe
         *
         * @return String ref = Reference to the modified String
         *
         * @test Tested in primitive/StringTest/Utility Functions
         */
        __CDS_cpplang_ConstexprDynamicAllocation auto removePrefix (String const & prefix) noexcept -> String & {
            if ( this->length() < prefix.length() ) {
                return * this;
            }

            if ( this->substr(0, static_cast < Index > ( prefix.length() )) == prefix ) {
                * this = this->substr(static_cast < Index > ( prefix.length()));
            }

            return * this;
        }

        /**
         * @brief Function used to obtain a String without the requested prefix
         *
         * @param prefix : String cref = Constant Reference to the String containing the prefix to remove
         *
         * @return String = New String without the requested prefix
         *
         * @test Tested in primitive/StringTest/Utility Functions
         */
        __CDS_NoDiscard __CDS_MaybeUnused __CDS_OptimalInline auto removePrefix (String const & prefix) const noexcept -> String {
            return String(*this).removePrefix(prefix);
        }

        /**
         * @brief Function used to remove a String's suffix. Used over mutable Strings, removing it from the caller String
         *
         * @param suffix : String cref = Constant Reference to the String containing the suffix to remove
         *
         * @exceptsafe
         *
         * @return String ref = Reference to the modified String
         *
         * @test Tested in primitive/StringTest/Utility Functions
         */
        __CDS_cpplang_ConstexprDynamicAllocation auto removeSuffix (String const & suffix) noexcept -> String & {
            if ( this->length() < suffix.length() ) {
                return * this;
            }

            if ( this->substr( static_cast < Index > ( this->length() ) - static_cast < Index > ( suffix.length() ) ) == suffix ) {
                * this = this->substr(0, static_cast < Index > ( this->length()) - static_cast < Index > ( suffix.length()));
            }

            return * this;
        }

        /**
         * @brief Function used to obtain a String without the requested suffix
         *
         * @param prefix : String cref = Constant Reference to the String containing the suffix to remove
         *
         * @return String = New String without the requested suffix
         *
         * @test Tested in primitive/StringTest/Utility Functions
         */
        __CDS_NoDiscard __CDS_OptimalInline auto removeSuffix (String const & suffix) const noexcept -> String {
            return String(*this).removeSuffix(suffix);
        }

        __CDS_NoDiscard __CDS_OptionalInline auto static format (StringLiteral format, ...) noexcept (false) -> String { // NOLINT(clion-misra-cpp2008-8-4-1)
            va_list args;
            va_start (args, format); // NOLINT(clion-misra-cpp2008-5-2-12)

            Size currentSize = __CDS_StringFormat_StartSize;

            while(currentSize <= __CDS_StringFormat_MaxSize) {
                char * buffer = Memory :: instance ().createArray < char > (currentSize);

                int returnValue = std::vsnprintf ( buffer, currentSize, format, args ); // NOLINT(clion-misra-cpp2008-5-2-12)
                if ( returnValue >= 0 && static_cast < Size > (returnValue) < currentSize ) {
                    String string(buffer, static_cast < Size > ( returnValue ) );
                    Memory :: instance().destroyArray ( buffer );
                    va_end (args); // NOLINT(clion-misra-cpp2008-5-2-12)

                    return string;
                }

                va_end(args); // NOLINT(clion-misra-cpp2008-5-2-12)
                va_start(args, format); // NOLINT(clion-misra-cpp2008-5-2-12)
                Memory :: instance ().destroyArray ( buffer );
                currentSize *= __CDS_StringFormat_SizeMultiplier;
            }

            va_end (args); // NOLINT(clion-misra-cpp2008-5-2-12)
            throw FormatException();
        }

        __CDS_NoDiscard __CDS_OptionalInline auto static f ( StringLiteral format, ... ) noexcept (false) -> String { // NOLINT(clion-misra-cpp2008-8-4-1)
            va_list args;
            va_start (args, format); // NOLINT(clion-misra-cpp2008-5-2-12)

            Size currentSize = __CDS_StringFormat_StartSize;

            while(currentSize <= __CDS_StringFormat_MaxSize) {
                char * buffer = Memory :: instance().createArray < char > (currentSize);

                int returnValue = std::vsnprintf ( buffer, currentSize, format, args ); // NOLINT(clion-misra-cpp2008-5-2-12)
                if ( returnValue >= 0 && static_cast < Size > ( returnValue ) < currentSize ) {
                    String string(buffer, static_cast < Size > ( returnValue ) );
                    Memory :: instance().destroyArray ( buffer );
                    va_end (args); // NOLINT(clion-misra-cpp2008-5-2-12)

                    return string;
                }

                va_end(args); // NOLINT(clion-misra-cpp2008-5-2-12)
                va_start(args, format); // NOLINT(clion-misra-cpp2008-5-2-12)
                Memory :: instance().destroyArray( buffer );
                currentSize *= __CDS_StringFormat_SizeMultiplier;
            }

            va_end (args); // NOLINT(clion-misra-cpp2008-5-2-12)
            throw FormatException();
        }

        __CDS_NoDiscard auto sequence () const & noexcept -> Sequence < const String >;
        __CDS_NoDiscard auto sequence () & noexcept -> Sequence < String >;
        __CDS_NoDiscard auto sequence () const && noexcept -> Sequence < const String >;
        __CDS_NoDiscard auto sequence () && noexcept -> Sequence < String >;

        friend class Socket;
    };

    inline Object::operator String () const noexcept {
        return this->toString();
    }

    inline auto operator << (std::ostream & out, Object const & object) noexcept -> std::ostream & {
        return (out << object.toString());
    }

}

#include <sstream>

namespace cds {

    inline auto Object::toString() const noexcept -> String {
        std::stringstream oss;
        oss << "Object at 0x" << std::hex << reinterpret_cast < AddressValueType const > (this);
        return oss.str();
    }

    inline auto String::operator == ( std::string const & stdString ) const noexcept -> bool {
        return std::strcmp ( this->cStr(), stdString.c_str() ) == 0;
    }

    inline auto String::operator >= ( std::string const & stdString ) const noexcept -> bool {
        return std::strcmp ( this->cStr(), stdString.c_str() ) >= 0;
    }

    inline auto String::operator <= ( std::string const & stdString ) const noexcept -> bool {
        return std::strcmp ( this->cStr(), stdString.c_str() ) <= 0;
    }

    inline auto String::operator != ( std::string const & stdString ) const noexcept -> bool {
        return std::strcmp ( this->cStr(), stdString.c_str() ) != 0;
    }

    inline auto String::operator < ( std::string const & stdString ) const noexcept -> bool {
        return std::strcmp ( this->cStr(), stdString.c_str() ) < 0;
    }

    inline auto String::operator > ( std::string const & stdString ) const noexcept -> bool {
        return std::strcmp ( this->cStr(), stdString.c_str() ) > 0;
    }

}

#if defined(CDS_STRING_POSTFIX)

inline auto operator "" _obj (const char * pString, std::size_t length __CDS_MaybeUnused ) noexcept -> cds :: String {
    return pString;
}

inline auto operator "" _s (const char * pString, std::size_t length __CDS_MaybeUnused ) noexcept -> cds :: String {
    return pString;
}

#endif

#include <CDS/Types>

namespace cds {
    template<> auto hash<String>(String const &object) noexcept -> Index { return static_cast < Index > ( object.length() ); }
}

__CDS_RegisterParseType(String) // NOLINT(clion-misra-cpp2008-8-0-1)
__CDS_RegisterParseType(Object) // NOLINT(clion-misra-cpp2008-8-0-1)

#endif //CDS_STRING_HPP
