//
// Created by loghin on 28.02.2021.
//

#ifndef CDS_JSON_HPP
#define CDS_JSON_HPP

#include <CDS/Object>
#include <CDS/Boolean>
#include <CDS/Integer>
#include <CDS/Float>
#include <CDS/Double>
#include <CDS/Long>
#include <CDS/LinkedList>
#include <CDS/Reference>
#include <CDS/Path>

class JSON : public Object {
public:
    class Array;

private:
    class Node : public Object {
    public:
        class DataException : public std::exception {
        public:
            [[nodiscard]] auto what () const noexcept -> StringLiteral override {
                return "Invalid JSON Data";
            }
        };

        class LabelException : public std::exception {
        public:
            [[nodiscard]] auto what () const noexcept -> StringLiteral override {
                return "JSON Node must be labeled";
            }
        };

    private:
        friend class JSON::Array;
        friend class JSON;

        String      _label;
        Object *    _pObject {nullptr};

        [[nodiscard]] auto stringFormattedData () const noexcept(false) -> String {
            if ( this->_pObject == nullptr ) throw DataException ();
            if ( dynamic_cast < String * > (this->_pObject) != nullptr )
                return String("\"") + this->_pObject->toString() + "\"";
            return this->_pObject->toString();
        }

    public:
        inline auto operator == ( Node const & o ) const noexcept -> bool {
            if ( this == & o ) return true;

            return this->_label == o._label && this->_pObject->equals(*o._pObject);
        }

        auto equals ( Object const & o ) const noexcept -> bool override {
            if ( this == & o ) return true;
            auto p = dynamic_cast < decltype ( this ) > (& o);
            if ( p == nullptr ) return false;
            return this->operator==(* p);
        }

        Node() noexcept = default;
        Node(Node const & o) noexcept : _label(o._label), _pObject(o._pObject->copy()) {}
        ~Node() noexcept override { delete this->_pObject; }

        auto clearData () noexcept -> Node & {
            delete this->_pObject;
            this->_pObject = nullptr;
            return * this;
        }

        auto put (Object const & obj) noexcept -> Node & {
            this->clearData();
            this->_pObject = obj.copy();
            return * this;
        }

        inline auto put (bool v)                    noexcept -> Node & { return this->put(Boolean(v)); }
        inline auto put (int v)                     noexcept -> Node & { return this->put(Integer(v)); }
        inline auto put (long long v)               noexcept -> Node & { return this->put(Long(v)); }
        inline auto put (float v)                   noexcept -> Node & { return this->put(Float(v)); }
        inline auto put (double v)                  noexcept -> Node & { return this->put(Double(v)); }
        inline auto put (StringLiteral v)           noexcept -> Node & { return this->put(String(v)); }
        auto        put (JSON::Array const &)       noexcept -> Node &;
        inline auto put (String const & v)          noexcept -> Node & { return this->put((Object &)v); }

        [[nodiscard]] auto getBoolean () const noexcept(false) -> bool {
            auto p = dynamic_cast < Boolean const * > (this->_pObject);
            if ( p == nullptr ) throw DataException();
            return p->get();
        }

        [[nodiscard]] auto getInt () const noexcept(false) -> int {
            auto p = dynamic_cast < Integer const * > (this->_pObject);
            if ( p == nullptr ) {
                auto pLong = dynamic_cast < Long const * > (this->_pObject);
                if ( pLong == nullptr )
                    throw DataException();
                return static_cast < int > (pLong->get());
            }

            return p->get();
        }

        [[nodiscard]] auto getLong () const noexcept(false) -> long long int {
            auto p = dynamic_cast < Long const * > (this->_pObject);
            if ( p == nullptr ) {
                auto pInteger = dynamic_cast < Integer const * > ( this->_pObject );
                if (pInteger == nullptr )
                    throw DataException();

                return static_cast<long long int>(pInteger->get());
            }

            return p->get();
        }

        [[nodiscard]] auto getFloat () const noexcept(false) -> float {
            auto p = dynamic_cast < Float const * > (this->_pObject);
            if ( p == nullptr ) {
                auto pDouble = dynamic_cast < Double const * > ( this->_pObject );
                if ( pDouble == nullptr )
                    throw DataException();

                return static_cast<float>(pDouble->get());
            }

            return p->get();
        }

        [[nodiscard]] auto getDouble () const noexcept(false) -> double {
            auto p = dynamic_cast < Double const * > (this->_pObject);
            if ( p == nullptr ) {
                auto pFloat = dynamic_cast < Float const * > ( this->_pObject );
                if (pFloat == nullptr )
                    throw DataException();

                return static_cast<double>(pFloat->get());
            }

            return p->get();
        }

        [[nodiscard]] inline auto getObject () const noexcept -> Object const & {
            return * this->_pObject;
        }

        [[nodiscard]] auto getJSON () const noexcept(false) -> JSON const & {
            auto p = dynamic_cast < JSON const * > ( this->_pObject );
            if ( p == nullptr ) throw DataException();
            return * p;
        }

        [[nodiscard]] auto getString () const noexcept(false) -> String const & {
            auto p = dynamic_cast < String const * > ( this->_pObject );
            if ( p == nullptr ) throw DataException();
            return * p;
        }

        [[nodiscard]] auto getArray () const noexcept(false) -> JSON::Array const &;

        inline auto getObject () noexcept -> Object & { return * this->_pObject; }

        auto getJSON () noexcept(false) -> JSON & {
            auto p = dynamic_cast < JSON * > (this->_pObject);
            if ( p == nullptr ) throw DataException();
            return * p;
        }

        auto getString () noexcept(false) -> String & {
            auto p = dynamic_cast < String * > (this->_pObject);
            if ( p == nullptr ) throw DataException();
            return * p;
        };

        auto getArray () noexcept(false) -> JSON::Array &;

        inline auto setLabel (String const & label) noexcept -> Node & { this->_label = label; return * this; }
        [[nodiscard]] inline auto getLabel () const noexcept -> String const & { return this->_label; }
        inline auto getLabel () noexcept -> String & { return this->_label; }

        [[nodiscard]] auto toString () const noexcept -> String override {
            return
                String("\"") + this->_label + "\" : " + this->stringFormattedData();
        }

        [[nodiscard]] auto dumpIndented (int indent, int count) const noexcept -> String;

        [[nodiscard]] auto copy () const noexcept -> Node * override { return new Node(*this); }
    };

    LinkedList < Node > _nodes;

public:
    class NoData : public std::exception {
        [[nodiscard]] auto what () const noexcept -> StringLiteral override {
            return "No data for Input Label";
        }
    };

    class InvalidString : public std::exception {
        [[nodiscard]] auto what () const noexcept -> StringLiteral override {
            return "Invalid Parse String";
        }
    };

    JSON() noexcept = default;
    JSON (JSON const &) noexcept = default;
    ~JSON () noexcept override = default;

    auto operator == (JSON const & o) const noexcept -> bool;

    auto equals ( Object const & o ) const noexcept -> bool override {
        if ( this == & o ) return true;
        auto p = dynamic_cast < decltype ( this ) > (& o);
        if ( p == nullptr ) return false;
        return this->operator==(* p);
    }

    [[nodiscard]] auto labels () const noexcept -> LinkedList < Reference < const String > > {
        LinkedList < Reference < const String > > labelList;

        for ( auto & e : this->_nodes )
            labelList.pushBack( e.getString() );

        return labelList;
    }

    [[nodiscard]] auto labels () noexcept -> LinkedList < Reference < String > > {
        LinkedList < Reference < String > > labelList;

        for ( auto & e : this->_nodes )
            labelList.pushBack( e.getLabel() );

        return labelList;
    }

    [[nodiscard]] inline auto keys () noexcept -> LinkedList < Reference < String > > {
        return this->labels();
    }

    [[nodiscard]] inline auto keys () const noexcept -> LinkedList < Reference < const String > > {
        return this->labels();
    }

    [[nodiscard]] auto nodes () const noexcept -> LinkedList < Reference < const Node > > {
        LinkedList < Reference < const Node > > labelList;

        for ( auto & e : this->_nodes )
            labelList.pushBack( e );

        return labelList;
    }

    [[nodiscard]] auto nodes () noexcept -> LinkedList < Reference < Node > > {
        LinkedList < Reference < Node > > labelList;

        for ( auto & e : this->_nodes )
            labelList.pushBack( e );

        return labelList;
    }

    [[nodiscard]] auto labelExists ( String const & label ) const noexcept -> bool {
        return this->labels().contains( label );
    }

    auto put ( String const &, bool ) noexcept -> JSON &;
    auto put ( String const &, int ) noexcept -> JSON &;
    auto put ( String const &, long long int ) noexcept -> JSON &;
    auto put ( String const &, float ) noexcept -> JSON &;
    auto put ( String const &, double ) noexcept -> JSON &;
    auto put ( String const &, String const & ) noexcept -> JSON &;
    auto put ( String const &, Array const & ) noexcept -> JSON &;
    auto put ( String const &, JSON const & ) noexcept -> JSON &;
    auto put ( String const &, Object const & ) noexcept -> JSON &;
    auto put ( String const &, StringLiteral ) noexcept -> JSON &;

    auto begin () noexcept -> LinkedList < JSON::Node >::Iterator { return this->_nodes.begin(); }
    auto begin () const noexcept -> LinkedList < JSON::Node >::ConstIterator { return this->_nodes.begin(); }
    auto cbegin () const noexcept -> LinkedList < JSON::Node >::ConstIterator { return this->_nodes.cbegin(); }
    auto end () noexcept -> LinkedList < JSON::Node >::Iterator { return this->_nodes.end(); }
    auto end () const noexcept -> LinkedList < JSON::Node >::ConstIterator { return this->_nodes.end(); }
    auto cend () const noexcept -> LinkedList < JSON::Node >::ConstIterator { return this->_nodes.cend(); }

    [[nodiscard]] auto getBoolean ( String const & ) const noexcept (false) -> bool;
    [[nodiscard]] auto getInt ( String const & ) const noexcept (false) -> int;
    [[nodiscard]] auto getLong ( String const & ) const noexcept (false) -> long long int;
    [[nodiscard]] auto getFloat ( String const & ) const noexcept (false) -> float;
    [[nodiscard]] auto getDouble ( String const & ) const noexcept (false) -> double;
    [[nodiscard]] auto getString ( String const & ) const noexcept (false) -> String const &;
    [[nodiscard]] auto getJSON ( String const & ) const noexcept (false) -> JSON const &;
    [[nodiscard]] auto getArray ( String const & ) const noexcept (false) -> Array const &;
    [[nodiscard]] auto getObject ( String const & ) const noexcept (false) -> Object const &;

    auto getString ( String const & ) noexcept (false) -> String &;
    auto getJSON ( String const & ) noexcept (false) -> JSON &;
    auto getArray ( String const & ) noexcept (false) -> Array &;
    auto getObject ( String const & ) noexcept (false) -> Object &;

    [[nodiscard]] auto toString () const noexcept -> String override {
        String res;

        for ( auto & e : this->_nodes )
            res += e.toString() + ", ";

        if ( res.empty() )
            return "{}";

        return String().append("{").append(res.replace(res.size() - 2, 2, "")).append("}");
    }

    static auto parse(String const &) noexcept -> JSON;
    static auto load(Path const &) noexcept -> JSON;
    [[nodiscard]] inline auto dump(int indent = 4) const noexcept -> String {
        return this->dumpIndented(indent, 0);
    }

private:
    [[nodiscard]] auto dumpIndented (int indent, int count) const noexcept -> String {
        String indentation = String(" ") * (indent * (count));
        String futureIndentation = indentation + String(" ") * indent;

        String res = "{\n";
        for ( auto & e : this->_nodes )
            res += futureIndentation + e.dumpIndented(indent, count + 1) + ",\n";

        if ( this->_nodes.empty() )
            return "{}";

        return res.replace(res.size() - 2, 2, "\n") + indentation + "}";
    }

public:

    [[nodiscard]] auto copy () const noexcept -> JSON * override {
        return new JSON(*this);
    }
};

class JSON::Array : public Object {
private:
    friend class JSON;
    LinkedList < JSON::Node > _list;

    [[nodiscard]] auto dumpIndented (int indent, int count) const noexcept -> String {
        String indentation = String(" ") * (indent * (count));
        String futureIndentation = indentation + String(" ") * indent;

        String res = "[\n";
        for ( auto & n : this->_list ) {
            auto pJSON = dynamic_cast < JSON const * > ( n._pObject );
            auto pArr = dynamic_cast < JSON::Array const * > ( n._pObject );

            if ( pJSON != nullptr )
                res += futureIndentation + pJSON->dumpIndented(indent, count + 1) + ",\n";
            else if ( pArr != nullptr )
                res += futureIndentation + pArr->dumpIndented(indent, count + 1) + ",\n";
            else
                res += futureIndentation + n.stringFormattedData() + ",\n";
        }

        return res.replace(res.size() - 2, 2, "\n") + indentation + "]";
    }
public:

    class OutOfBounds : public std::exception {
    private:
        String _message = "Data out of array bounds.";
    public:
        OutOfBounds () noexcept = default;
        explicit OutOfBounds (Index trigger, Index limit) noexcept {
            this->_message += String().append(" Accessed ").append(trigger).append(". Length : ").append(limit);
        }

        [[nodiscard]] auto what () const noexcept -> StringLiteral override {
            return this->_message.cStr();
        }
    };

    Array () noexcept = default;
    Array (Array const &) noexcept = default;
    ~Array () noexcept override = default;

    inline auto operator == (Array const & o) const noexcept -> bool {
        if ( this == & o ) return true;
        return this->_list == o._list;
    }

    auto equals (Object const & o) const noexcept -> bool override {
        if ( this == & o ) return true;
        auto p = dynamic_cast < decltype ( this ) > ( & o );
        if ( p == nullptr ) return false;

        return this->operator== (*p);
    }

    auto begin () noexcept -> LinkedList < JSON::Node >::Iterator { return this->_list.begin(); }
    auto begin () const noexcept -> LinkedList < JSON::Node >::ConstIterator { return this->_list.begin(); }
    auto cbegin () const noexcept -> LinkedList < JSON::Node >::ConstIterator { return this->_list.cbegin(); }
    auto end () noexcept -> LinkedList < JSON::Node >::Iterator { return this->_list.end(); }
    auto end () const noexcept -> LinkedList < JSON::Node >::ConstIterator { return this->_list.end(); }
    auto cend () const noexcept -> LinkedList < JSON::Node >::ConstIterator { return this->_list.cend(); }

    auto put(Index i, JSON::Node const & o) noexcept -> Array & {
        if ( i > static_cast<Index>(this->_list.size()) )
            i = this->_list.size();

        decltype(this->_list) front;

        for(Index listIndex = 0; listIndex < i; listIndex ++)
            front.pushBack ( this->_list.popFront() );

        front.pushBack( o );

        while ( ! this->_list.empty() )
            front.pushBack ( this->_list.popFront() );

        this->_list = front;
        return * this;
    }

    auto put(Index i, bool v) noexcept -> Array & {
        this->put(i, JSON::Node().put(v));
        return * this;
    }

    auto put(Index i, int v) noexcept -> Array & {
        this->put(i, JSON::Node().put(v));
        return * this;
    }

    auto put(Index i, long long int v) noexcept -> Array & {
        this->put(i, JSON::Node().put(v));
        return * this;
    }

    auto put(Index i, float v) noexcept -> Array & {
        this->put(i, JSON::Node().put(v));
        return * this;
    }

    auto put(Index i, double v) noexcept -> Array & {
        this->put(i, JSON::Node().put(v));
        return * this;
    }

    auto put(Index i, String const & s) noexcept -> Array & {
        this->put(i, JSON::Node().put(s));
        return * this;
    }

    auto put(Index i, StringLiteral s) noexcept -> Array & {
        this->put(i, JSON::Node().put(s));
        return * this;
    }

    auto put(Index i, JSON const & o) -> Array & {
        this->put(i, JSON::Node().put(o));
        return * this;
    }

    auto put(Index i, Array const & a) -> Array & {
        this->put(i, JSON::Node().put(a));
        return * this;
    }

    [[nodiscard]] inline auto length () const noexcept -> Size { return this->_list.size(); }
    [[nodiscard]] inline auto size () const noexcept -> Size { return this->_list.size(); }

    [[nodiscard]] auto get(Index i) const noexcept(false) -> JSON::Node const & {
        if ( i < 0 || i >= static_cast<Index>(this->_list.size()) ) throw OutOfBounds (i, this->_list.size());
        return this->_list.get(i);
    }

    auto get(Index i) noexcept(false) -> JSON::Node & {
        if ( i < 0 || i >= static_cast<Index>(this->_list.size()) ) throw OutOfBounds (i, this->_list.size());
        return this->_list.get(i);
    }

    auto getBoolean(Index i) noexcept(false) -> bool {
        return this->get(i).getBoolean();
    }

    auto getInt(Index i) noexcept(false) -> int{
        return this->get(i).getInt();
    }

    auto getLong(Index i) noexcept(false) -> long long int{
        return this->get(i).getLong();
    }

    auto getFloat(Index i) noexcept(false) -> float{
        return this->get(i).getFloat();
    }

    auto getDouble(Index i) noexcept(false) -> double{
        return this->get(i).getDouble();
    }

    [[nodiscard]] auto getString(Index i) const noexcept(false) -> String const &{
        return this->get(i).getString();
    }

    [[nodiscard]] auto getJSON(Index i) const noexcept(false) -> JSON const &{
        return this->get(i).getJSON();
    }

    [[nodiscard]] auto getArray(Index i) const noexcept(false) -> JSON::Array const &{
        return this->get(i).getArray();
    }

    auto getString(Index i) noexcept(false) -> String &{
        return this->get(i).getString();
    }

    auto getJSON(Index i) noexcept(false) -> JSON &{
        return this->get(i).getJSON();
    }

    auto getArray(Index i) noexcept(false) -> JSON::Array &{
        return this->get(i).getArray();
    }

    [[nodiscard]] auto toString () const noexcept -> String override {
        String res;
        for ( auto & e : this->_list ) {
            res += e.stringFormattedData() + ", ";
        }

        if (res.empty())
            return "[]";

        return String().append("[").append(res.substr(0, res.size() - 2)).append("]");
    }

    [[nodiscard]] auto copy() const noexcept -> Array * override {
        return new Array(* this);
    }

    static auto parse ( String const & data ) noexcept -> Array {
        Array result;

        auto pushBackUnknown = [& result]( String const & data ) noexcept -> Array & {
            if ( data.front() == '{' )
                result.put( result.size(), JSON::parse(data) );
            else if ( data.front() == '[' )
                result.put( result.size(), Array::parse(data) );
            else if ( data.findFirst('\"') != String::INVALID_POS )
                result.put (
                        result.size(),
                        String().append(data)
                                .replace(data.findLast('\"'), data.size(), "")
                                .replace(0, data.findFirst('\"') + 1, "")
                );
            else if ( data.findFirst('.') != String::INVALID_POS )
                result.put ( result.size(), Double::parse(data).get() );
            else if ( data.findFirst("true") != String::INVALID_POS || data.findFirst("false") != String::INVALID_POS )
                result.put ( result.size(), data == "true" );
            else
                result.put ( result.size(), Long::parse(data).get() );

            return result;
        };

        String copy = data;
        copy.replace(0, copy.findFirst('[') + 1, "");
        copy.replace(copy.findLast(']'), copy.size(), "");

        while ( ! copy.empty() ) {
            copy.ltrim(' ');

            int arrayBracketCount = 0, objectBracketCount = 0, segmentLength = 0;
            String element;

            for ( auto c : copy ) {
                if ( arrayBracketCount == 0 && objectBracketCount == 0 && c == ',' )
                    break;
                else {
                    if ( c == '{' )objectBracketCount ++;
                    else if ( c == '}' )objectBracketCount --;
                    else if ( c == '[' )arrayBracketCount ++;
                    else if ( c == ']' )arrayBracketCount --;

                    element += c;
                    segmentLength ++;
                }
            }

            copy.replace(0, segmentLength + 1, "");
            pushBackUnknown(element);
        }

        return result;
    }
};


inline auto JSON::put ( String const & label, bool v ) noexcept -> JSON & {
    this->_nodes.pushBack( JSON::Node().setLabel(label).put(v) );
    return * this;
}

inline auto JSON::put ( String const & label, int v ) noexcept -> JSON & {
    this->_nodes.pushBack( JSON::Node().setLabel(label).put(v) );
    return * this;
}

inline auto JSON::put ( String const & label, long long int v ) noexcept -> JSON & {
    this->_nodes.pushBack( JSON::Node().setLabel(label).put(v) );
    return * this;
}

inline auto JSON::put ( String const & label, float v ) noexcept -> JSON & {
    this->_nodes.pushBack( JSON::Node().setLabel(label).put(v) );
    return * this;
}

inline auto JSON::put ( String const & label, double v ) noexcept -> JSON & {
    this->_nodes.pushBack( JSON::Node().setLabel(label).put(v) );
    return * this;
}

inline auto JSON::put ( String const & label, String const & v ) noexcept -> JSON & {
    this->_nodes.pushBack( JSON::Node().setLabel(label).put(v) );
    return * this;
}

inline auto JSON::put ( String const & label, Array const & v ) noexcept -> JSON & {
    this->_nodes.pushBack( JSON::Node().setLabel(label).put(v) );
    return * this;
}

inline auto JSON::put ( String const & label, JSON const & v ) noexcept -> JSON & {
    this->_nodes.pushBack( JSON::Node().setLabel(label).put(v) );
    return * this;
}

inline auto JSON::put ( String const & label, Object const & v ) noexcept -> JSON & {
    this->_nodes.pushBack( JSON::Node().setLabel(label).put(v) );
    return * this;
}

inline auto JSON::put ( String const & label, StringLiteral v ) noexcept -> JSON & {
    this->_nodes.pushBack( JSON::Node().setLabel(label).put(v) );
    return * this;
}

inline auto JSON::getBoolean ( String const & label ) const noexcept (false) -> bool {
    for ( auto & e : this->_nodes )
        if ( e.getLabel() == label )
            return e.getBoolean ();

    throw NoData();
}

inline auto JSON::getInt ( String const & label ) const noexcept (false) -> int {
    for ( auto & e : this->_nodes )
        if ( e.getLabel() == label )
            return e.getInt ();

    throw NoData();
}

inline auto JSON::getLong ( String const & label ) const noexcept (false) -> long long int {
    for ( auto & e : this->_nodes )
        if ( e.getLabel() == label )
            return e.getLong ();

    throw NoData();
}

inline auto JSON::getFloat ( String const & label ) const noexcept (false) -> float {
    for ( auto & e : this->_nodes )
        if ( e.getLabel() == label )
            return e.getFloat ();

    throw NoData();
}

inline auto JSON::getDouble ( String const & label ) const noexcept (false) -> double {
    for ( auto & e : this->_nodes )
        if ( e.getLabel() == label )
            return e.getDouble ();

    throw NoData();
}

inline auto JSON::getString ( String const & label ) const noexcept (false) -> String const & {
    for ( auto & e : this->_nodes )
        if ( e.getLabel() == label )
            return e.getString ();

    throw NoData();
}

inline auto JSON::getJSON ( String const & label ) const noexcept (false) -> JSON const & {
    for ( auto & e : this->_nodes )
        if ( e.getLabel() == label )
            return e.getJSON ();

    throw NoData();
}

inline auto JSON::getArray ( String const & label ) const noexcept (false) -> Array const & {
    for ( auto & e : this->_nodes )
        if ( e.getLabel() == label )
            return e.getArray ();

    throw NoData();
}

inline auto JSON::getObject ( String const & label ) const noexcept (false) -> Object const & {
    for ( auto & e : this->_nodes )
        if ( e.getLabel() == label )
            return e.getObject ();

    throw NoData();
}

inline auto JSON::getString ( String const & label ) noexcept (false) -> String & {
    for ( auto & e : this->_nodes )
        if ( e.getLabel() == label )
            return e.getString ();

    throw NoData();
}

inline auto JSON::getJSON ( String const & label ) noexcept (false) -> JSON & {
    for ( auto & e : this->_nodes )
        if ( e.getLabel() == label )
            return e.getJSON ();

    throw NoData();
}

inline auto JSON::getArray ( String const & label ) noexcept (false) -> Array & {
    for ( auto & e : this->_nodes )
        if ( e.getLabel() == label )
            return e.getArray ();

    throw NoData();
}

inline auto JSON::getObject ( String const & label ) noexcept (false) -> Object & {
    for ( auto & e : this->_nodes )
        if ( e.getLabel() == label )
            return e.getObject ();

    throw NoData();
}

inline auto JSON::parse(String const & jsonString) noexcept -> JSON {
    JSON result;

    auto emplaceUnknown = [& result] ( String const & label, String const & data ) -> JSON & {
        if ( data.front() == '{' ) result.put(label, JSON::parse(data));
        else if ( data.front() == '[' ) result.put(label, JSON::Array::parse(data));
        else if ( data.findFirst('"') != String::INVALID_POS )
            result.put(
                    label,
                    String().append(data)
                            .replace(data.findLast('"'), data.length(), "")
                            .replace(0, data.findFirst('"') + 1, "")
            );
        else if ( data.findFirst('.') != String::INVALID_POS ) result.put(label, Double::parse(data));
        else if ( data.findFirst("true") != String::INVALID_POS || data.findFirst("false") != String::INVALID_POS )
            result.put(label, data == "true");
        else
            result.put(label, Long::parse(data));
        return result;
    };

    String copy = jsonString;

    copy.replace(0, copy.findFirst('{') + 1, "");
    copy.replace(copy.findLast('}'), copy.size(), "");

    while ( ! copy.empty() ) {
        String label = copy.substr(0, copy.findFirst(':'));

        label.replace(0, label.findFirst('"') + 1, "").replace(label.findLast('"'), label.size(), "");

        String data, fullData = copy.substr(copy.findFirst(':') + 1);
        int arrayBracketCount = 0, objectBracketCount = 0, segmentLength = 0;

        fullData.ltrim(' ');

        for ( auto c : fullData ) {
            if ( arrayBracketCount == 0 && objectBracketCount == 0 && c == ',' )
                break;
            else {
                if ( c == '{' ) objectBracketCount ++;
                else if ( c == '}' ) objectBracketCount --;
                else if ( c == '[' ) arrayBracketCount ++;
                else if ( c == ']' ) arrayBracketCount --;

                data += c;
                segmentLength ++;
            }
        }

        fullData.replace(0, segmentLength + 1, "");
        emplaceUnknown(label, data);
        copy = fullData;
    }

    return result;
}

inline auto JSON::Node::put ( JSON::Array const & a ) noexcept -> Node & {
    this->clearData();
    this->_pObject = a.copy();
    return * this;
}

inline auto JSON::Node::getArray () const noexcept(false) -> JSON::Array const & {
    auto p = dynamic_cast < JSON::Array * > ( this->_pObject );
    if ( p == nullptr ) throw DataException();

    return * p;
}

inline auto JSON::Node::getArray () noexcept(false) -> JSON::Array & { // NOLINT(readability-make-member-function-const)
    auto p = dynamic_cast < JSON::Array * > ( this->_pObject );
    if ( p == nullptr ) throw DataException();

    return * p;
}

#include <fstream>
#include <sstream>
inline auto JSON::load(const Path & path) noexcept -> JSON {
    std::stringstream in;
    in << std::ifstream(path.toString().cStr()).rdbuf();
    return JSON::parse(in.str());
}

inline auto JSON::Node::dumpIndented(int indent, int count) const noexcept -> String {
    String indentation = String(" ") * (indent * count);

    auto pObj = dynamic_cast < JSON const * > ( this->_pObject );
    auto pArr = dynamic_cast < JSON::Array const * > ( this->_pObject );

    if ( pObj != nullptr )
        return String("\"") + this->_label + "\" : \n" + indentation + String() * indent + pObj->dumpIndented(indent, count);
    if ( pArr != nullptr )
        return String("\"") + this->_label + "\" : \n" + indentation + String() * indent + pArr->dumpIndented(indent, count);
    return String("\"") + this->_label + "\" : " + this->stringFormattedData();
}

inline auto JSON::operator == (JSON const & o) const noexcept -> bool {
    if ( this == & o ) return true;
    return this->_nodes == o._nodes;
}

#endif //CDS_JSON_HPP
