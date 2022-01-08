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
#include <CDS/Memory>

namespace cds {

    class JSON : public Object {
    public:
        class Array; // NOLINT(cppcoreguidelines-virtual-class-destructor)

    private:
        class Node : public Object {
        private:
            friend class JSON::Array;
            friend class JSON;

            String      _label;
            Object *    _pObject {nullptr};

            __CDS_NoDiscard auto stringFormattedData () const noexcept(false) -> String {
                if ( this->_pObject == nullptr ) {
                    throw NullPointerException();
                }

                if ( dynamic_cast < String * > (this->_pObject) != nullptr ) {
                    return String("\"") + this->_pObject->toString() + "\"";
                }

                return this->_pObject->toString();
            }

        public:
            __CDS_OptimalInline auto operator == ( Node const & node ) const noexcept -> bool {
                if ( this == & node ) {
                    return true;
                }

                return this->_label == node._label && this->_pObject->equals(*node._pObject);
            }

            __CDS_NoDiscard auto equals ( Object const & object ) const noexcept -> bool override {
                if ( this == & object ) {
                    return true;
                }

                auto pObject = dynamic_cast < JSON::Node const * > (& object);

                if (pObject == nullptr ) {
                    return false;
                }

                return this->operator==(* pObject);
            }

            Node() noexcept = default;
            Node(Node const & node) noexcept :
                    _label(node._label),
                    _pObject(node._pObject->copy()) {

            }

            ~Node() noexcept override {
                Memory :: instance().destroy ( this->_pObject );
            }

            auto clearData () noexcept -> Node & {
                Memory :: instance().destroy ( this->_pObject );
                this->_pObject = nullptr;
                return * this;
            }

            auto put (Object const & obj) noexcept -> Node & {
                (void) this->clearData();
                this->_pObject = obj.copy();
                return * this;
            }

            __CDS_OptimalInline auto put (bool value)                    noexcept -> Node & { return this->put(Boolean(value)); }
            __CDS_OptimalInline auto put (int value)                     noexcept -> Node & { return this->put(Integer(value)); }
            __CDS_OptimalInline auto put (long long value)               noexcept -> Node & { return this->put(Long(value)); }
            __CDS_OptimalInline auto put (float value)                   noexcept -> Node & { return this->put(Float(value)); }
            __CDS_OptimalInline auto put (double value)                  noexcept -> Node & { return this->put(Double(value)); }
            __CDS_OptimalInline auto put (StringLiteral value)           noexcept -> Node & { return this->put(String(value)); }
                                auto put (JSON::Array const &)           noexcept -> Node &;
            __CDS_OptimalInline auto put (String const & value)          noexcept -> Node & { return this->put(reinterpret_cast < Object const & > ( value ) ); }

            __CDS_NoDiscard auto getBoolean () const noexcept(false) -> bool {
                auto pObject = dynamic_cast < Boolean const * > (this->_pObject);
                if (pObject == nullptr ) {
                    throw TypeException(Boolean());
                }

                return pObject->get();
            }

            __CDS_NoDiscard auto getInt () const noexcept(false) -> int {
                auto pObject = dynamic_cast < Integer const * > (this->_pObject);
                if (pObject == nullptr ) {
                    auto pLong = dynamic_cast < Long const * > (this->_pObject);
                    if ( pLong == nullptr ) {
                        throw TypeException(Int());
                    }

                    return static_cast < int > (pLong->get());
                }

                return pObject->get();
            }

            __CDS_NoDiscard auto getLong () const noexcept(false) -> long long int {
                auto pObject = dynamic_cast < Long const * > (this->_pObject);
                if (pObject == nullptr ) {
                    auto pInteger = dynamic_cast < Integer const * > ( this->_pObject );
                    if (pInteger == nullptr ) {
                        throw TypeException(Long());
                    }

                    return static_cast<long long int>(pInteger->get());
                }

                return pObject->get();
            }

            __CDS_NoDiscard auto getFloat () const noexcept(false) -> float {
                auto pObject = dynamic_cast < Float const * > (this->_pObject);
                if (pObject == nullptr ) {
                    auto pDouble = dynamic_cast < Double const * > ( this->_pObject );
                    if ( pDouble == nullptr ) {
                        throw TypeException(Float());
                    }

                    return static_cast<float>(pDouble->get());
                }

                return pObject->get();
            }

            __CDS_NoDiscard auto getDouble () const noexcept(false) -> double {
                auto pObject = dynamic_cast < Double const * > (this->_pObject);
                if (pObject == nullptr ) {
                    auto pFloat = dynamic_cast < Float const * > ( this->_pObject );
                    if (pFloat == nullptr ) {
                        throw TypeException(Double());
                    }

                    return static_cast<double>(pFloat->get());
                }

                return pObject->get();
            }

            __CDS_NoDiscard __CDS_OptimalInline auto getObject () const noexcept -> Object const & {
                return * this->_pObject;
            }

            __CDS_NoDiscard auto getJSON () const noexcept(false) -> JSON const & {
                auto pObject = dynamic_cast < JSON const * > ( this->_pObject );
                if (pObject == nullptr ) {
                    throw TypeException(JSON());
                }

                return * pObject;
            }

            __CDS_NoDiscard auto getString () const noexcept(false) -> String const & {
                auto pObject = dynamic_cast < String const * > ( this->_pObject );
                if (pObject == nullptr ) {
                    throw TypeException(String());
                }

                return * pObject;
            }

            __CDS_NoDiscard auto getArray () const noexcept(false) -> JSON::Array const &;

            __CDS_OptimalInline auto getObject () noexcept -> Object & {
                return * this->_pObject;
            }

            auto getJSON () noexcept(false) -> JSON & {
                auto pObject = dynamic_cast < JSON * > (this->_pObject);
                if (pObject == nullptr ) {
                    throw TypeException(JSON());
                }

                return * pObject;
            }

            auto getString () noexcept(false) -> String & {
                auto pObject = dynamic_cast < String * > (this->_pObject);
                if (pObject == nullptr ) {
                    throw TypeException(String());
                }

                return * pObject;
            };

            auto getArray () noexcept(false) -> JSON::Array &;

            __CDS_OptimalInline auto setLabel (String const & label) noexcept -> Node & {
                this->_label = label;
                return * this;
            }

            __CDS_NoDiscard __CDS_MaybeUnused constexpr auto getLabel () const noexcept -> String const & {
                return this->_label;
            }

            __CDS_cpplang_NonConstConstexprMemberFunction auto getLabel () noexcept -> String & {
                return this->_label;
            }

            __CDS_NoDiscard auto toString () const noexcept -> String override {
                return
                        String("\"") + this->_label + "\" : " + this->stringFormattedData();
            }

            __CDS_NoDiscard auto dumpIndented (int indent, int count) const noexcept -> String;

            __CDS_NoDiscard auto copy () const noexcept -> Node * override {
                return Memory::instance().create < Node > (*this);
            }
        };

        LinkedList < Node > _nodes;

    public:
        JSON() noexcept = default;
        JSON (JSON const &) noexcept = default;
        JSON (JSON &&) noexcept;
        ~JSON () noexcept override = default;

        __CDS_OptimalInline auto operator = ( JSON const & json ) noexcept -> JSON & {
            if ( this == & json ) {
                return * this;
            }

            this->_nodes = json._nodes;

            return * this;
        }

        __CDS_OptimalInline auto operator = ( JSON && json ) noexcept -> JSON & {
            if ( this == & json ) {
                return * this;
            }

            this->_nodes = std :: move ( json._nodes );

            return * this;
        }

        auto operator == (JSON const & object) const noexcept -> bool;

        __CDS_NoDiscard auto equals ( Object const & object ) const noexcept -> bool override {
            if ( this == & object ) {
                return true;
            }
            auto pObject = dynamic_cast < decltype ( this ) > (& object);
            if (pObject == nullptr ) {
                return false;
            }

            return this->operator==(* pObject);
        }

        __CDS_NoDiscard auto labels () const noexcept -> LinkedList < Reference < const String > > {
            LinkedList < Reference < const String > > labelList;

            for ( auto & element : this->_nodes ) {
                (void) labelList.pushBack(element.getLabel());
            }

            return labelList;
        }

        __CDS_NoDiscard auto labels () noexcept -> LinkedList < Reference < String > > {
            LinkedList < Reference < String > > labelList;

            for ( auto & node : this->_nodes ) {
                (void)labelList.pushBack(node.getLabel());
            }

            return labelList;
        }

        __CDS_NoDiscard __CDS_MaybeUnused __CDS_OptimalInline auto keys () noexcept -> LinkedList < Reference < String > > {
            return this->labels();
        }

        __CDS_NoDiscard __CDS_MaybeUnused __CDS_OptimalInline auto keys () const noexcept -> LinkedList < Reference < const String > > {
            return this->labels();
        }

        __CDS_NoDiscard __CDS_MaybeUnused auto nodes () const noexcept -> LinkedList < Reference < const Node > > {
            LinkedList < Reference < const Node > > labelList;

            for ( auto & node : this->_nodes ) {
                (void) labelList.pushBack(node);
            }

            return labelList;
        }

        __CDS_NoDiscard __CDS_MaybeUnused auto nodes () noexcept -> LinkedList < Reference < Node > > {
            LinkedList < Reference < Node > > labelList;

            for ( auto & node : this->_nodes ) {
                (void) labelList.pushBack(node);
            }

            return labelList;
        }

        __CDS_NoDiscard __CDS_MaybeUnused auto labelExists ( String const & label ) const noexcept -> bool {
            return this->labels().contains( label );
        }

        auto put ( String const &, bool ) noexcept -> JSON &;
        auto put ( String const &, int ) noexcept -> JSON &;
        auto put ( String const &, long long int ) noexcept -> JSON &;
        auto put ( String const &, float ) noexcept -> JSON &;
        auto put ( String const &, double ) noexcept -> JSON &;
        auto put ( String const &, String const & ) noexcept -> JSON &;
        auto put ( String const &, JSON::Array const & ) noexcept -> JSON &;
        auto put ( String const &, JSON const & ) noexcept -> JSON &;
        auto put ( String const &, Object const & ) noexcept -> JSON &;
        auto put ( String const &, StringLiteral ) noexcept -> JSON &;

        __CDS_NoDiscard __CDS_MaybeUnused auto begin () noexcept -> LinkedList < JSON::Node >::Iterator {
            return this->_nodes.begin();
        }

        __CDS_NoDiscard __CDS_MaybeUnused auto begin () const noexcept -> LinkedList < JSON::Node >::ConstIterator {
            return this->_nodes.begin();
        }

        __CDS_NoDiscard __CDS_MaybeUnused auto cbegin () const noexcept -> LinkedList < JSON::Node >::ConstIterator {
            return this->_nodes.cbegin();
        }

        __CDS_NoDiscard __CDS_MaybeUnused auto end () noexcept -> LinkedList < JSON::Node >::Iterator {
            return this->_nodes.end();
        }

        __CDS_NoDiscard __CDS_MaybeUnused auto end () const noexcept -> LinkedList < JSON::Node >::ConstIterator {
            return this->_nodes.end();
        }

        __CDS_NoDiscard __CDS_MaybeUnused auto cend () const noexcept -> LinkedList < JSON::Node >::ConstIterator {
            return this->_nodes.cend();
        }

        __CDS_NoDiscard __CDS_MaybeUnused auto getBoolean ( String const & ) const noexcept (false) -> bool;
        __CDS_NoDiscard __CDS_MaybeUnused auto getInt ( String const & ) const noexcept (false) -> int;
        __CDS_NoDiscard __CDS_MaybeUnused auto getLong ( String const & ) const noexcept (false) -> long long int;
        __CDS_NoDiscard __CDS_MaybeUnused auto getFloat ( String const & ) const noexcept (false) -> float;
        __CDS_NoDiscard __CDS_MaybeUnused auto getDouble ( String const & ) const noexcept (false) -> double;
        __CDS_NoDiscard __CDS_MaybeUnused auto getString ( String const & ) const noexcept (false) -> String const &;
        __CDS_NoDiscard __CDS_MaybeUnused auto getJSON ( String const & ) const noexcept (false) -> JSON const &;
        __CDS_NoDiscard __CDS_MaybeUnused auto getArray ( String const & ) const noexcept (false) -> Array const &;
        __CDS_NoDiscard __CDS_MaybeUnused auto getObject ( String const & ) const noexcept (false) -> Object const &;

        auto getString ( String const & ) noexcept (false) -> String &;
        auto getJSON ( String const & ) noexcept (false) -> JSON &;
        auto getArray ( String const & ) noexcept (false) -> Array &;
        __CDS_MaybeUnused auto getObject ( String const & ) noexcept (false) -> Object &;

        __CDS_NoDiscard auto toString () const noexcept -> String override {
            String res;

            for ( auto & node : this->_nodes ) {
                res += node.toString() + ", ";
            }

            if ( res.empty() ) {
                return "{}";
            }

            return String().append("{").append(res.replace(static_cast < Index > (res.size()) - 2, 2u, "")).append("}");
        }

        static auto parse(String const &) noexcept -> JSON;
        static auto load(Path const &) noexcept -> JSON;
        __CDS_NoDiscard __CDS_OptimalInline auto dump(int indent = 4) const noexcept -> String {
            return this->dumpIndented(indent, 0);
        }

    private:
        __CDS_NoDiscard auto dumpIndented (int indent, int count) const noexcept -> String { // NOLINT(misc-no-recursion)
            String indentation = String(" ") * (indent * (count));
            String futureIndentation = indentation + String(" ") * indent;

            String res = "{\n";
            for ( auto & node : this->_nodes ) {
                res += futureIndentation + node.dumpIndented(indent, count + 1) + ",\n";
            }

            if ( this->_nodes.empty() ) {
                return "{}";
            }

            return res.replace(static_cast < Index > (res.size()) - 2, 2u, "\n") + indentation + "}";
        }

    public:

        __CDS_NoDiscard auto copy () const noexcept -> JSON * override {
            return Memory :: instance().create < JSON > (*this);
        }
    };

}

namespace cds {

    class JSON::Array : public Object {
    private:
        friend class JSON;
        LinkedList < JSON::Node > _list;

        __CDS_NoDiscard auto dumpIndented (int indent, int count) const noexcept -> String { // NOLINT(misc-no-recursion)
            if ( this->_list.empty() ) {
                return "[]";
            }

            String indentation = String(" ") * (indent * (count));
            String futureIndentation = indentation + String(" ") * indent;

            String res = "[\n";
            for ( auto & node : this->_list ) {
                auto pJSON = dynamic_cast < JSON const * > ( node._pObject );
                auto pArr = dynamic_cast < JSON::Array const * > ( node._pObject );

                if ( pJSON != nullptr ) {
                    res += futureIndentation + pJSON->dumpIndented(indent, count + 1) + ",\n";
                } else if ( pArr != nullptr ) {
                    res += futureIndentation + pArr->dumpIndented(indent, count + 1) + ",\n";
                } else {
                    res += futureIndentation + node.stringFormattedData() + ",\n";
                }
            }

            return res.replace(static_cast < Index > ( res.size() ) - 2, 2u, "\n") + indentation + "]";
        }

    public:
        Array () noexcept = default;
        Array (Array const &) noexcept = default;
        ~Array () noexcept override = default;

        __CDS_OptimalInline Array ( Array && array ) noexcept :
                _list ( std :: forward < LinkedList < Node > > ( array._list ) ) {

        }

        __CDS_OptimalInline auto operator = ( Array const & array ) noexcept -> Array & {
            if ( this == & array ) {
                return * this;
            }

            this->_list = array._list;

            return * this;
        }

        __CDS_OptimalInline auto operator = ( Array && array ) noexcept -> Array & {
            if ( this == & array ) {
                return * this;
            }

            this->_list = std :: move ( array._list );

            return * this;
        }

        __CDS_OptimalInline auto operator == (Array const & array) const noexcept -> bool {
            if ( this == & array ) {
                return true;
            }

            return this->_list == array._list;
        }

        __CDS_NoDiscard auto equals (Object const & object) const noexcept -> bool override {
            if ( this == & object ) {
                return true;
            }

            auto pObject = dynamic_cast < JSON::Array const * > ( & object );
            if (pObject == nullptr ) {
                return false;
            }

            return this->operator== (*pObject);
        }

        __CDS_NoDiscard auto begin () noexcept -> LinkedList < JSON::Node >::Iterator {
            return this->_list.begin();
        }

        __CDS_NoDiscard auto begin () const noexcept -> LinkedList < JSON::Node >::ConstIterator {
            return this->_list.begin();
        }

        __CDS_NoDiscard auto cbegin () const noexcept -> LinkedList < JSON::Node >::ConstIterator {
            return this->_list.cbegin();
        }

        __CDS_NoDiscard auto end () noexcept -> LinkedList < JSON::Node >::Iterator {
            return this->_list.end();
        }

        __CDS_NoDiscard auto end () const noexcept -> LinkedList < JSON::Node >::ConstIterator {
            return this->_list.end();
        }

        __CDS_NoDiscard auto cend () const noexcept -> LinkedList < JSON::Node >::ConstIterator {
            return this->_list.cend();
        }

        auto put(Index index, JSON::Node const & value) noexcept -> Array & {
            if (index > static_cast<Index>(this->_list.size()) ) {
                index = static_cast<Index> (this->_list.size());
            }

            decltype(this->_list) front;

            for(Index listIndex = 0; listIndex < index; listIndex ++) {
                (void) front.pushBack(this->_list.popFront());
            }

            (void) front.pushBack(value );

            while ( ! this->_list.empty() ) {
                (void) front.pushBack(this->_list.popFront());
            }

            this->_list = front;
            return * this;
        }

        auto put(Index index, bool value) noexcept -> Array & {
            return this->put(index, JSON::Node().put(value));
        }

        auto put(Index index, int value) noexcept -> Array & {
            return this->put(index, JSON::Node().put(value));
        }

        auto put(Index index, long long int value) noexcept -> Array & {
            return this->put(index, JSON::Node().put(value));
        }

        auto put(Index index, float value) noexcept -> Array & {
            return this->put(index, JSON::Node().put(value));
        }

        auto put(Index index, double value) noexcept -> Array & {
            return this->put(index, JSON::Node().put(value));
        }

        auto put(Index index, String const & value) noexcept -> Array & {
            return this->put(index, JSON::Node().put(value));
        }

        auto put(Index index, StringLiteral value) noexcept -> Array & {
            return this->put(index, JSON::Node().put(value));
        }

        auto put(Index index, JSON const & value) -> Array & {
            return this->put(index, JSON::Node().put(value));
        }

        auto put(Index index, Array const & value) -> Array & {
            return this->put(index, JSON::Node().put(value));
        }

        __CDS_NoDiscard __CDS_MaybeUnused __CDS_OptimalInline auto length () const noexcept -> Size {
            return this->_list.size();
        }

        __CDS_NoDiscard __CDS_MaybeUnused __CDS_OptimalInline auto size () const noexcept -> Size {
            return this->_list.size();
        }

        __CDS_NoDiscard __CDS_MaybeUnused auto get(Index index) const noexcept(false) -> JSON::Node const & {
            if (index < 0 || index >= static_cast<Index>(this->_list.size()) ) {
                throw OutOfBoundsException(index, static_cast < Index > (this->_list.size())); // NOLINT(clion-misra-cpp2008-0-1-7)
            }

            return this->_list.get(index);
        }

        __CDS_NoDiscard __CDS_MaybeUnused auto get(Index index) noexcept(false) -> JSON::Node & {
            if (index < 0 || index >= static_cast<Index>(this->_list.size()) ) {
                throw OutOfBoundsException(index, static_cast < Index > (this->_list.size())); // NOLINT(clion-misra-cpp2008-0-1-7)
            }

            return this->_list.get(index);
        }

        __CDS_NoDiscard __CDS_MaybeUnused auto getBoolean(Index index) noexcept(false) -> bool {
            return this->get(index).getBoolean();
        }

        __CDS_NoDiscard __CDS_MaybeUnused auto getInt(Index index) noexcept(false) -> int{
            return this->get(index).getInt();
        }

        __CDS_NoDiscard __CDS_MaybeUnused auto getLong(Index index) noexcept(false) -> long long int{
            return this->get(index).getLong();
        }

        __CDS_NoDiscard __CDS_MaybeUnused auto getFloat(Index index) noexcept(false) -> float{
            return this->get(index).getFloat();
        }

        __CDS_NoDiscard __CDS_MaybeUnused auto getDouble(Index index) noexcept(false) -> double{
            return this->get(index).getDouble();
        }

        __CDS_NoDiscard __CDS_MaybeUnused auto getString(Index index) const noexcept(false) -> String const &{
            return this->get(index).getString();
        }

        __CDS_NoDiscard __CDS_MaybeUnused auto getJSON(Index index) const noexcept(false) -> JSON const &{
            return this->get(index).getJSON();
        }

        __CDS_NoDiscard __CDS_MaybeUnused auto getArray(Index index) const noexcept(false) -> JSON::Array const &{
            return this->get(index).getArray();
        }

        __CDS_NoDiscard __CDS_MaybeUnused auto getString(Index index) noexcept(false) -> String &{
            return this->get(index).getString();
        }

        __CDS_NoDiscard __CDS_MaybeUnused auto getJSON(Index index) noexcept(false) -> JSON &{
            return this->get(index).getJSON();
        }

        __CDS_NoDiscard __CDS_MaybeUnused auto getArray(Index index) noexcept(false) -> JSON::Array &{
            return this->get(index).getArray();
        }

        __CDS_NoDiscard auto toString () const noexcept -> String override {
            String res;
            for ( auto & node : this->_list ) {
                res += node.stringFormattedData() + ", ";
            }

            if (res.empty()) {
                return "[]";
            }

            return String().append("[").append(res.substr(0, static_cast < Index > (res.size()) - 2)).append("]");
        }

        __CDS_NoDiscard auto copy() const noexcept -> Array * override {
            return Memory :: instance().create < Array >(* this);
        }

        static auto parse ( String const & data ) noexcept -> Array { // NOLINT(misc-no-recursion)
            constexpr char const * whitespace = " \t\f\r\n";
            Array result;

            auto pushBackUnknown = [& result]( String const & data ) noexcept -> Array & { // NOLINT(misc-no-recursion)
                if ( data.front() == '{' ) {
                    (void) result.put(static_cast < Index > ( result.size()), JSON::parse(data));
                } else if ( data.front() == '[' ) {
                    (void) result.put(static_cast < Index > ( result.size()), Array::parse(data));
                } else if ( data.findFirst('\"') != String::INVALID_POS ) {
                    (void) result.put (
                            static_cast < Index > ( result.size() ),
                            String().append(data)
                                    .replace(data.findLast('\"'), data.size(), "")
                                    .replace(0, static_cast < Size > ( data.findFirst('\"') + 1 ), "")
                    );
                } else if ( data.findFirst('.') != String::INVALID_POS ) {
                    (void) result.put ( static_cast < Index > ( result.size() ), Double::parse(data).get() );
                } else if ( data.findFirst("true") != String::INVALID_POS || data.findFirst("false") != String::INVALID_POS ) {
                    (void) result.put ( static_cast < Index > ( result.size() ), data == "true" );
                } else {
                    (void) result.put ( static_cast < Index > ( result.size() ), Long::parse(data).get() );
                }

                return result;
            };

            String copy = data;
            (void) copy.replace(0, static_cast < Size > ( copy.findFirst('[') + 1 ), "");
            (void) copy.replace(copy.findLast(']'), copy.size(), "");
            copy = copy.trim(whitespace);

            while ( ! copy.empty() ) {
                (void) copy.ltrim(" \n\r\t\f");

                int arrayBracketCount = 0;
                int objectBracketCount = 0;
                int segmentLength = 0;
                String element;

                for ( auto character : copy ) {
                    if ( arrayBracketCount == 0 && objectBracketCount == 0 && character == ',' ) {
                        break;
                    } else {
                        if (character == '{' ) {
                            ++ objectBracketCount;
                        } else if (character == '}' ) {
                            -- objectBracketCount;
                        } else if (character == '[' ) {
                            ++ arrayBracketCount;
                        } else if (character == ']' ) {
                            -- arrayBracketCount;
                        } else {
                            /// do nothing
                        }

                        element += character;
                        segmentLength ++;
                    }
                }

                (void) copy.replace(0, static_cast < Size > ( static_cast < Index > ( segmentLength ) + 1 ), "");
                pushBackUnknown(element);
            }

            return result;
        }
    };

}

namespace cds {

    inline auto JSON::put ( String const & label, bool value ) noexcept -> JSON & {
        (void) this->_nodes.pushBack( JSON::Node().setLabel(label).put(value) );
        return * this;
    }

    inline auto JSON::put ( String const & label, int value ) noexcept -> JSON & {
        (void) this->_nodes.pushBack( JSON::Node().setLabel(label).put(value) );
        return * this;
    }

    inline auto JSON::put ( String const & label, long long int value ) noexcept -> JSON & {
        (void) this->_nodes.pushBack( JSON::Node().setLabel(label).put(value) );
        return * this;
    }

    inline auto JSON::put ( String const & label, float value ) noexcept -> JSON & {
        (void) this->_nodes.pushBack( JSON::Node().setLabel(label).put(value) );
        return * this;
    }

    inline auto JSON::put ( String const & label, double value ) noexcept -> JSON & {
        (void) this->_nodes.pushBack( JSON::Node().setLabel(label).put(value) );
        return * this;
    }

    inline auto JSON::put ( String const & label, String const & value ) noexcept -> JSON & {
        (void) this->_nodes.pushBack( JSON::Node().setLabel(label).put(value) );
        return * this;
    }

    inline auto JSON::put ( String const & label, Array const & value ) noexcept -> JSON & {
        (void) this->_nodes.pushBack( JSON::Node().setLabel(label).put(value) );
        return * this;
    }

    inline auto JSON::put ( String const & label, JSON const & value ) noexcept -> JSON & {
        (void) this->_nodes.pushBack( JSON::Node().setLabel(label).put(value) );
        return * this;
    }

    inline auto JSON::put ( String const & label, Object const & value ) noexcept -> JSON & {
        (void) this->_nodes.pushBack( JSON::Node().setLabel(label).put(value) );
        return * this;
    }

    inline auto JSON::put ( String const & label, StringLiteral value ) noexcept -> JSON & {
        (void) this->_nodes.pushBack( JSON::Node().setLabel(label).put(value) );
        return * this;
    }

    inline auto JSON::getBoolean ( String const & label ) const noexcept (false) -> bool {
        for ( auto & node : this->_nodes ) {
            if (node.getLabel() == label) {
                return node.getBoolean();
            }
        }

        throw KeyException(label);
    }

    inline auto JSON::getInt ( String const & label ) const noexcept (false) -> int {
        for ( auto & node : this->_nodes ) {
            if (node.getLabel() == label) {
                return node.getInt();
            }
        }

        throw KeyException(label);
    }

    __CDS_MaybeUnused inline auto JSON::getLong ( String const & label ) const noexcept (false) -> long long int {
        for ( auto & node : this->_nodes ) {
            if (node.getLabel() == label) {
                return node.getLong();
            }
        }

        throw KeyException(label);
    }

    __CDS_MaybeUnused inline auto JSON::getFloat ( String const & label ) const noexcept (false) -> float {
        for ( auto & node : this->_nodes ) {
            if (node.getLabel() == label) {
                return node.getFloat();
            }
        }

        throw KeyException(label);
    }

    __CDS_MaybeUnused inline auto JSON::getDouble ( String const & label ) const noexcept (false) -> double {
        for ( auto & node : this->_nodes ) {
            if (node.getLabel() == label) {
                return node.getDouble();
            }
        }

        throw KeyException(label);
    }

    inline auto JSON::getString ( String const & label ) const noexcept (false) -> String const & {
        for ( auto & node : this->_nodes ) {
            if (node.getLabel() == label) {
                return node.getString();
            }
        }

        throw KeyException(label);
    }

    inline auto JSON::getJSON ( String const & label ) const noexcept (false) -> JSON const & {
        for ( auto & node : this->_nodes ) {
            if (node.getLabel() == label) {
                return node.getJSON();
            }
        }

        throw KeyException(label);
    }

    inline auto JSON::getArray ( String const & label ) const noexcept (false) -> Array const & {
        for ( auto & node : this->_nodes ) {
            if (node.getLabel() == label) {
                return node.getArray();
            }
        }

        throw KeyException(label);
    }

    inline auto JSON::getObject ( String const & label ) const noexcept (false) -> Object const & {
        for ( auto & node : this->_nodes ) {
            if (node.getLabel() == label) {
                return node.getObject();
            }
        }

        throw KeyException(label);
    }

    inline auto JSON::getString ( String const & label ) noexcept (false) -> String & {
        for ( auto & node : this->_nodes ) {
            if (node.getLabel() == label) {
                return node.getString();
            }
        }

        throw KeyException(label);
    }

    inline auto JSON::getJSON ( String const & label ) noexcept (false) -> JSON & {
        for ( auto & node : this->_nodes ) {
            if (node.getLabel() == label) {
                return node.getJSON();
            }
        }

        throw KeyException(label);
    }

    inline auto JSON::getArray ( String const & label ) noexcept (false) -> Array & {
        for ( auto & node : this->_nodes ) {
            if (node.getLabel() == label) {
                return node.getArray();
            }
        }

        throw KeyException(label);
    }

    inline auto JSON::getObject ( String const & label ) noexcept (false) -> Object & {
        for ( auto & node : this->_nodes ) {
            if (node.getLabel() == label) {
                return node.getObject();
            }
        }

        throw KeyException(label);
    }

    inline auto JSON::parse(String const & jsonString) noexcept -> JSON { // NOLINT(misc-no-recursion)
        constexpr char const * whitespace = " \r\n\t\f";

        JSON result;

        auto emplaceUnknown = [& result] ( String const & label, String const & data ) -> JSON & { // NOLINT(misc-no-recursion)
            if ( data.front() == '{' ) {
                (void) result.put(label, JSON::parse(data));
            } else if ( data.front() == '[' ) {
                (void) result.put(label, JSON::Array::parse(data));
            } else if ( data.findFirst('"') != String::INVALID_POS ) {
                (void) result.put(
                        label,
                        String().append(data)
                                .replace(data.findLast('"'), data.length(), "")
                                .replace(0, static_cast < Size > ( data.findFirst('"') + 1 ), "")
                );
            } else if ( data.findFirst('.') != String::INVALID_POS ) {
                (void) result.put(label, Double::parse(data));
            } else if ( data.findFirst("true") != String::INVALID_POS || data.findFirst("false") != String::INVALID_POS ) {
                (void) result.put(label, data == "true");
            } else {
                (void) result.put(label, Long::parse(data));
            }

            return result;
        };

        String copy = jsonString;

        (void) copy.replace(0, static_cast < Size > ( copy.findFirst('{') + 1 ), "");
        (void) copy.replace(copy.findLast('}'), copy.size(), "");

        while ( ! copy.empty() ) {
            String label = copy.substr(0, copy.findFirst(':'));

            (void) label.replace(0, static_cast < Size > ( label.findFirst('"') + 1 ), "");
            (void) label.replace(label.findLast('"'), label.size(), "");

            String data;
            String fullData = copy.substr(copy.findFirst(':') + 1);
            int arrayBracketCount = 0;
            int objectBracketCount = 0;
            int segmentLength = 0;

            fullData = fullData.trim(whitespace);

            for ( auto character : fullData ) {
                if ( arrayBracketCount == 0 && objectBracketCount == 0 && character == ',' ) {
                    break;
                } else {
                    if (character == '{' ) {
                        ++ objectBracketCount;
                    } else if (character == '}' ) {
                        -- objectBracketCount;
                    } else if (character == '[' ) {
                        ++ arrayBracketCount;
                    } else if (character == ']' ) {
                        -- arrayBracketCount;
                    } else {
                        /// do nothing
                    }

                    data += character;
                    segmentLength ++;
                }
            }

            (void) fullData.replace(0, static_cast < Size > ( static_cast < Index > ( segmentLength ) + 1 ), "");
            emplaceUnknown(label, data);
            copy = fullData;
        }

        return result;
    }

    inline auto JSON::Node::put ( JSON::Array const & value ) noexcept -> Node & {
        (void) this->clearData();
        this->_pObject = value.copy();
        return * this;
    }

    inline auto JSON::Node::getArray () const noexcept(false) -> JSON::Array const & {
        auto pValue = dynamic_cast < JSON::Array * > ( this->_pObject );
        if (pValue == nullptr ) {
            throw TypeException(Array());
        }

        return * pValue;
    }

    inline auto JSON::Node::getArray () noexcept(false) -> JSON::Array & { // NOLINT(readability-make-member-function-const)
        auto pValue = dynamic_cast < JSON::Array * > ( this->_pObject );
        if (pValue == nullptr ) {
            throw TypeException(Array());
        }

        return * pValue;
    }

}

#include <fstream>
#include <sstream>

namespace cds {

    inline auto JSON::load(const Path & path) noexcept -> JSON {
        std::stringstream input;
        input << std::ifstream(path.toString().cStr()).rdbuf();
        return JSON::parse(input.str());
    }

    inline auto JSON::Node::dumpIndented(int indent, int count) const noexcept -> String { // NOLINT(misc-no-recursion)
        String indentation = String(" ") * (indent * count);

        auto pObj = dynamic_cast < JSON const * > ( this->_pObject );
        auto pArr = dynamic_cast < JSON::Array const * > ( this->_pObject );

        if ( pObj != nullptr ) {
            return String("\"") + this->_label + "\" : \n" + indentation + String() * indent + pObj->dumpIndented(indent, count);
        }

        if ( pArr != nullptr ) {
            return String("\"") + this->_label + "\" : \n" + indentation + String() * indent + pArr->dumpIndented(indent, count);
        }

        return String("\"") + this->_label + "\" : " + this->stringFormattedData();
    }

    inline auto JSON::operator == (JSON const & object) const noexcept -> bool {
        if ( this == & object ) {
            return true;
        }

        return this->_nodes == object._nodes;
    }

    inline JSON::JSON(JSON && json) noexcept {
        this->_nodes = std :: move ( json._nodes );
    }

}

__CDS_RegisterParseType(JSON) // NOLINT(clion-misra-cpp2008-8-0-1)
__CDS_RegisterParseType(JSON::Array) // NOLINT(clion-misra-cpp2008-8-0-1)
__CDS_RegisterParseType(JSON::Node) // NOLINT(clion-misra-cpp2008-8-0-1)

#endif //CDS_JSON_HPP
