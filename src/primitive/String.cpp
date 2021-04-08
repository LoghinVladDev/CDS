//
// Created by loghin on 24.02.2021.
//

#include <CDS/String>

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
    if ( cString == nullptr ) return * this;

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
    if ( i >= static_cast<Index>(this->size()) )
        i = i % this->size();

    return this->_p[i];
}

auto String::operator [] (Index i) const noexcept -> ElementType {
    if ( this->empty() )
        return '\0';

    if ( i < 0 )
        i += ( (-i) / this->size() + 1 ) * this->size();
    if ( i >= static_cast<Index>(this->size()) )
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

#pragma clang diagnostic push
#pragma ide diagnostic ignored "ConstantConditionsOC"
String::String(IteratorBase const & begin, IteratorBase const & end) noexcept : CONSTR_CLEAR() {
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

String::String(ConstIteratorBase const & begin, ConstIteratorBase const & end) noexcept : CONSTR_CLEAR() {
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

auto String::resize(Size size) noexcept -> void {
    if ( this->empty() )
        return;

    this->_c = size + 1;
    auto newArea = new ElementType [ this->_c ];
    std::memcpy ( newArea, this->_p, this->_c );

    delete [] this->_p;

    this->_p = newArea;
    if ( this->_l >= this->_c )
        this->_l = this->_c - 1;
}

auto String::clear() noexcept -> void {
    if ( this->_p != nullptr )
        std::memset ( this->_p, 0, this->_l );
    this->_l = 0;
}

#include <CDS/LinkedList>
auto String::split(ElementType token, Size splitCount) const noexcept -> LinkedList < String > {
    Index splitIndex = 0;
    if ( splitCount < 1 )
        splitCount = UINT32_MAX;

    LinkedList < String > segments;
    if ( this->empty() )
        return segments;

    String currentSegment;

    for ( auto c : (*this) ) {
        if ( c != token || splitIndex >= static_cast<Index>(splitCount) - 1 )
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
        if ( ! delim.contains(c) || splitIndex >= static_cast<Index>(splitCount) - 1 )
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
    Index i = 0;
    for ( auto c : (*this) )
        if ( c == e )
            return i;
        else
            i++;

    return INVALID_POS;
}

auto String::findFirst ( String const & o ) const noexcept -> Index {
    Index i = 0;
    for ( auto c : (*this) )
        if ( this->size() - i >= o.size() && this->substr( i, i + o.size() ) == o )
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
    Index i = this->size() - o.length();
    for ( i; i >= 0; i-- )
        if ( this->substr(i, i + o.length()) == o )
            return i;

    return INVALID_POS;
}

auto String::findFirstOf ( String const & o ) const noexcept -> Index {
    Index i = 0;
    for ( auto e : (*this) )
        if ( o.contains(e) )
            return i;
        else
            i++;
    return INVALID_POS;
}

auto String::findFirstNotOf ( String const & o ) const noexcept -> Index {
    Index i = 0;
    for ( auto e : (*this) )
        if ( ! o.contains(e) )
            return i;
        else
            i++;
    return INVALID_POS;
}

auto String::findLastOf ( String const & o ) const noexcept -> Index {
    Index i = this->size() - 1;
    for ( auto it = this->rbegin(); it != this->rend(); it++ )
        if ( o.contains(it.value()) )
            return i;
        else
            i--;
    return INVALID_POS;
}

auto String::findLastNotOf ( String const & o ) const noexcept -> Index {
    Index i = this->size() - 1;
    for ( auto it = this->rbegin(); it != this->rend(); it++ )
        if ( ! o.contains(it.value()) )
            return i;
        else
            i--;
    return INVALID_POS;
}

auto String::substr(Index from, Index to) const noexcept -> String {
    if ( to == -1 || to > static_cast<Index>(this->size()) )
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

    Index i = 0;
    for ( auto c : (*this) ) {
        if ( c == e )
            indices.pushBack ( i );
        i++;
    }

    return indices;
}

auto String::findOf (String const & s) const noexcept -> LinkedList < Index > {
    LinkedList < Index > indices;

    Index i = 0;
    for ( auto c : (*this) ) {
        if ( s.contains(c) )
            indices.pushBack ( i );
        i++;
    }

    return indices;
}

auto String::findNotOf (String const & s) const noexcept -> LinkedList < Index > {
    LinkedList < Index > indices;

    Index i = 0;
    for ( auto c : (*this) ) {
        if ( ! s.contains(c) )
            indices.pushBack ( i );
        i++;
    }

    return indices;
}

auto String::find (String const & o) const noexcept -> LinkedList < Index > {
#if !defined(_MSC_VER)
    Index lpsArray [o.size()];
#else
    auto lpsArray = new Index[this->size()];
#endif
    std::memset(lpsArray, 0, sizeof(Index) * o.size());

    auto computeLPSArray = [& o, &lpsArray] () {
        Index len = 0;
        lpsArray[0] = 0;

        Index i = 1;
        while ( i < static_cast<Index>(o.size()) ) {
            if ( o._p[i] == o._p[len] ) {
                len ++;
                lpsArray[i] = len;
                i ++;
            } else {
                if ( len != 0 )
                    len = lpsArray[len - 1];
                else {
                    lpsArray[i] = 0;
                    i ++;
                }
            }
        }
    };

    computeLPSArray();

    LinkedList < Index > indices;
    Index i = 0, j = 0;
    while ( i < static_cast<Index>(this->size()) ) {
        if ( o._p[j] == this->_p[i] ) {
            i ++; j ++;
        }

        if ( j == static_cast<Index>(o.size()) ) {
            indices.pushBack(i - j);
            j = lpsArray[j - 1];
        } else if ( i < static_cast<Index>(this->size()) && this->_p[i] != o._p[j] ) {
            if ( j != 0 )
                j = lpsArray[j - 1];
            else
                i ++;
        }
    }

#if !defined(_MSC_VER)
#else
    delete [] lpsArray;
#endif
    return indices;
}

auto String::ltrim ( ElementType e ) noexcept -> String & {
    while ( ! this->empty () && this->front() == e )
        * this = this->substr( 1 );
    return * this;
}

auto String::ltrim ( String const & s ) noexcept -> String & {
    while ( ! this->empty () && s.contains( this->front() ) )
        * this = this->substr(1);
    return * this;
}

auto String::rtrim ( ElementType e ) noexcept -> String & {
    while ( ! this->empty () && this->back() == e )
        this->_p[--this->_l] = '\0';

    return * this;
}

auto String::rtrim ( String const & s ) noexcept -> String & {
    while ( ! this->empty () && s.contains(this->back()) )
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

auto String::replace(Index pos, Size len, const String & newInPlace) noexcept -> String & {
    String left = this->substr(0, pos);
    String right = this->substr(pos + len);

    return ( * this = left + newInPlace + right );
}

#undef CONSTR_CLEAR

#include <CDS/View>

auto String::view() const noexcept -> View < String > {
    return View(*this);
}

auto String::reversed() const noexcept -> String {
    return {this->rbegin(), this->rend()};
}

auto String::operator * (int count) const noexcept -> String {
    String res;
    for ( int i = 0; i < count; i ++ )
        res += (*this);
    return res;
}
