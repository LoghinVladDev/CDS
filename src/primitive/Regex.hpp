//
// Created by loghin on 15.07.2021.
//

#ifndef CDS_REGEX_HPP
#define CDS_REGEX_HPP

#include <CDS/Object>
#include <CDS/HashMap>
#include <CDS/Pointer>

class Regex : public Object {
public:
    enum class Format {
        PYTHON_RE
    };

    enum FlagBit : uint8 {
        NONE        = 0x00u,

        DOT_ALL     = 0x01u,
        MULTILINE   = 0x02u,
        IGNORE_CASE = 0x04u,
        DEBUG       = 0x08u,

        A           = DOT_ALL,
        ML          = MULTILINE,
        I           = IGNORE_CASE,
        D           = DEBUG
    };

    using Flags = uint8;

    constexpr auto static _flagMask =
            FlagBit::DOT_ALL    |
            FlagBit::MULTILINE  |
            FlagBit::IGNORE_CASE;

    using Pattern = String;

private:
    enum SpecialCharacter {
        ANY,
        START,
        END,

        COUNT_NONE_OR_MORE,
        COUNT_ONE_OR_MORE,
        COUNT_ONE_MAXIMUM,

        RANGE_START,
        RANGE_END,

        CHAR_SET_START,
        CHAR_SET_END,
        CHAR_SET_INTERVAL,

        OR,

        GROUP_START,
        GROUP_END,

        /// end of single char

        ESCAPE,

        ONLY_AT_START,
        BLANK_START_OR_END,
        BLANK_NOT_START_AND_NOT_END,

        DECIMAL,
        NON_DECIMAL,

        WHITESPACE,
        NON_WHITESPACE,

        WORD,
        NON_WORD,

        ONLY_AT_END
    };

    [[nodiscard]] constexpr static auto pythonReFormat (SpecialCharacter character) noexcept -> StringLiteral {
        switch (character) {
            case SpecialCharacter::ANY:                            return ".";
            case SpecialCharacter::START:                          return "^";
            case SpecialCharacter::END:                            return "$";
            case SpecialCharacter::COUNT_NONE_OR_MORE:             return "*";
            case SpecialCharacter::COUNT_ONE_OR_MORE:              return "+";
            case SpecialCharacter::COUNT_ONE_MAXIMUM:              return "?";
            case SpecialCharacter::RANGE_START:                    return "{";
            case SpecialCharacter::RANGE_END:                      return "}";
            case SpecialCharacter::CHAR_SET_START:                 return "[";
            case SpecialCharacter::CHAR_SET_END:                   return "]";
            case SpecialCharacter::CHAR_SET_INTERVAL:              return "-";
            case SpecialCharacter::OR:                             return "|";
            case SpecialCharacter::GROUP_START:                    return "(";
            case SpecialCharacter::GROUP_END:                      return ")";
            case SpecialCharacter::ESCAPE:                         return "\\";

            case SpecialCharacter::ONLY_AT_START:                  return "\\A";
            case SpecialCharacter::BLANK_START_OR_END:             return "\\b";
            case SpecialCharacter::BLANK_NOT_START_AND_NOT_END:    return "\\B";
            case SpecialCharacter::DECIMAL:                        return "\\d";
            case SpecialCharacter::NON_DECIMAL:                    return "\\D";
            case SpecialCharacter::WHITESPACE:                     return "\\s";
            case SpecialCharacter::NON_WHITESPACE:                 return "\\S";
            case SpecialCharacter::WORD:                           return "\\w";
            case SpecialCharacter::NON_WORD:                       return "\\W";
            case SpecialCharacter::ONLY_AT_END:                    return "\\Z";
        }

        return nullptr;
    }

    [[nodiscard]] constexpr static auto character (SpecialCharacter character, Format format) noexcept -> StringLiteral {
        switch (format) {
            case Format::PYTHON_RE: return pythonReFormat (character);
        }

        return nullptr;
    }

public:
    class Match : public Object {

    };

private:
    inline static Format _globalFormat { Format::PYTHON_RE };
    inline static Flags  _globalFlags  { FlagBit::NONE };

    inline static class Cache : public Object {
    public:
        constexpr static const bool DEFAULT_CACHE_STATUS = false;
        constexpr static const Size DEFAULT_CACHE_SIZE = 0x10u;
        constexpr static const Size DEFAULT_CACHE_LIFETIME = 0xFFu;

    private:
        HashMap < Pattern, Regex * >_cachedRegexObjects;
        HashMap < Regex *, Size >   _cachedObjectsLife;

        bool                        _enabled    { DEFAULT_CACHE_STATUS };
        Size                        _size       { DEFAULT_CACHE_SIZE };

    public:
        Cache () noexcept : _enabled(DEFAULT_CACHE_STATUS) {}
        ~Cache() noexcept override {
            this->purge();
        }

        [[nodiscard]] constexpr auto size () const noexcept -> Size { return this->_size; }
        [[nodiscard]] constexpr auto size () noexcept -> Size & { return this->_size; }

        constexpr auto enable () noexcept -> Cache & { this->_enabled = true; return * this; }
        constexpr auto disable () noexcept -> Cache & { this->_enabled = false; return * this; }

        [[nodiscard]] constexpr auto enabled () const noexcept -> bool { return this->_enabled; }
        [[nodiscard]] constexpr auto enabled () noexcept -> bool & { return this->_enabled; }

        [[nodiscard]] inline auto get (Pattern const & regex) const noexcept -> Regex const * { return this->_cachedRegexObjects[regex]; }
        [[nodiscard]] inline auto get (Pattern const & regex) noexcept -> Regex * & { return this->_cachedRegexObjects[regex]; }

        [[nodiscard]] inline auto operator [] (Pattern const & regex) const noexcept -> Regex const * { return this->get(regex); }
        [[nodiscard]] inline auto operator [] (Pattern const & regex) noexcept -> Regex * & { return this->get(regex); }

        inline auto purge () noexcept -> Cache & {
            this->_cachedRegexObjects.forEach([](auto & p){delete p.getSecond();});
            this->_cachedRegexObjects.clear();
            this->_cachedObjectsLife.clear();

            return * this;
        }
    } _cache;

private:
    class CharacterSet : public Object {
    private:
        uint8 _chars[16];

    public:
        CharacterSet() noexcept = default; // NOLINT(cppcoreguidelines-pro-type-member-init)

        CharacterSet(CharacterSet const & o) noexcept { // NOLINT(cppcoreguidelines-pro-type-member-init)
            std::memcpy ( this->_chars, o._chars, 16 );
        }

        auto operator = ( CharacterSet const & obj ) noexcept -> CharacterSet & {
            if ( this == & obj ) return * this;

            std::memcpy (this->_chars, obj._chars, 16);

            return * this;
        }

        explicit CharacterSet(String const & str) noexcept { // NOLINT(cppcoreguidelines-pro-type-member-init)
            this->clear();
            char left; uint8 rangeState = 0;

            for(auto c : str) {
                if (String::isAlpha(c)) {
                    if ( rangeState == 1 ) {
                        this->add(left);
                    } else if ( rangeState == 2 ) {
                        this->add(left, c);
                        rangeState = 0;
                        continue;
                    }

                    rangeState = 1;
                    left = c;
                } else if ( c == Regex::character(SpecialCharacter::CHAR_SET_INTERVAL, Regex::globalFormat())[0] && rangeState == 1 ) rangeState = 2;
                else this->add(c);
            }

            if ( rangeState == 1 ) this->add(left);
        }

        constexpr auto clear () noexcept -> void {
            std::memset(this->_chars, 0, 16);
        }

        [[nodiscard]] constexpr auto contains (char c) const noexcept -> bool {
            return this->_chars[c >> 3] & (1 << (c % 8));
        }

        static auto compile (String const & s) noexcept -> CharacterSet { return CharacterSet(s); }

        constexpr auto add (char c) noexcept -> void {
            this->_chars[c >> 3] |= (1 << (c % 8));
        }

        constexpr auto add (char l, char u) noexcept -> void {
            for ( char i = l; i <= u; i++ )
                this->add(i);
        }

        [[nodiscard]] inline auto toString () const noexcept -> String override {
            return Range(1, 128).sequence()
                .filter([this](Index i){ return this->contains((char)i); })
                .fold(""_s, [this](String const & s, Index i){
                    if ( this->contains((char)i - 1) )
                        if ( s[(Index)s.length() - 2] == Regex::character(SpecialCharacter::CHAR_SET_INTERVAL, Regex::globalFormat())[0] )
                            return s.removeSuffix(""_s + (char)(i-1)).append((char)i);
                        else
                            return s + Regex::character(SpecialCharacter::CHAR_SET_INTERVAL, Regex::globalFormat())[0] + (char)i;
                    else
                        return s + String().append((char)i);
                });
        }

        [[nodiscard]] inline auto copy () const noexcept -> CharacterSet * override {
            return new CharacterSet(*this);
        }
    };

private:

    class CompiledPattern : public Object {
    private:
        class Node : public Object {
        private:
            LinkedList < Pair < CharacterSet *, Node * > > _nextStates;
            bool _isEndState {false};

            Size _minRepCount {1};
            Size _maxRepCount {1};

            Index _debugStateIndex {-1};

        public:

            inline auto clear () noexcept -> Node & {
                this->_isEndState = false;
                this->_minRepCount = 1;
                this->_maxRepCount = 1;
                this->_debugStateIndex = -1;

                this->_nextStates.forEach([](auto & e){delete e.getFirst(); delete e.getSecond();});
                this->_nextStates.clear();

                return * this;
            }

            ~Node () noexcept override {
                this->clear();
            }

            Node (Node const & pattern) noexcept :
                    Object(pattern),
                    _isEndState(pattern._isEndState),
                    _minRepCount(pattern._minRepCount),
                    _maxRepCount(pattern._maxRepCount),
                    _debugStateIndex(pattern._debugStateIndex),
                    _nextStates(
                        pattern._nextStates.sequence()
                            .map([](Pair <CharacterSet *, Node *> const & e){
                                return Pair < CharacterSet *, Node * >{e.getFirst()->copy(), e.getSecond()->copy()};
                            }).toLinkedList()
                    ){

            }

            inline auto operator = (Node const & pattern) noexcept -> Node & {
                if (this == & pattern) return * this;

                this->_isEndState = pattern._isEndState;
                this->_minRepCount = pattern._minRepCount;
                this->_maxRepCount = pattern._maxRepCount;
                this->_debugStateIndex = pattern._debugStateIndex;

                this->_nextStates = pattern._nextStates.sequence().map([](Pair < CharacterSet *, Node *> const & e){
                    return Pair < CharacterSet *, Node * > ( e.getFirst()->copy(), e.getSecond()->copy() );
                }).toLinkedList();

                return * this;
            }

            [[nodiscard]] constexpr auto nextStates () const noexcept -> LinkedList < Pair < CharacterSet *, Node * > > const & { return this->_nextStates; }
            [[nodiscard]] constexpr auto nextStates () noexcept -> LinkedList < Pair < CharacterSet *, Node * > > & { return this->_nextStates; }

            [[nodiscard]] constexpr auto minRepCount () const noexcept -> Size { return this->_minRepCount; }
            [[nodiscard]] constexpr auto minRepCount () noexcept -> Size & { return this->_minRepCount; }

            [[nodiscard]] constexpr auto maxRepCount () const noexcept -> Size { return this->_maxRepCount; }
            [[nodiscard]] constexpr auto maxRepCount () noexcept -> Size & { return this->_maxRepCount; }

            [[nodiscard]] constexpr auto endState () const noexcept -> bool { return this->_isEndState; }
            [[nodiscard]] constexpr auto endState () noexcept -> bool & { return this->_isEndState; }

            [[nodiscard]] constexpr auto stateIndex () const noexcept -> Index { return this->_debugStateIndex; }
            [[nodiscard]] constexpr auto stateIndex () noexcept -> Index & { return this->_debugStateIndex; }

            [[nodiscard]] inline auto repCounts () const noexcept -> Pair < Size, Size > {
                return { this->_minRepCount, this->_maxRepCount };
            }

            constexpr auto setMinRepCount (Size repCount) noexcept -> Node & { this->_minRepCount = repCount; return * this; }
            constexpr auto setMaxRepCount (Size repCount) noexcept -> Node & { this->_maxRepCount = repCount; return * this; }

            constexpr auto setEndState (bool toggle) noexcept -> Node & { this->_isEndState = toggle; return * this; }
            constexpr auto makeEndState () noexcept -> Node & { return this->setEndState(true); }
            constexpr auto unmakeEndState () noexcept -> Node & { return this->setEndState(false); }

            constexpr auto setStateIndex (Index index) noexcept -> Node & { this->_debugStateIndex = index; return * this; }

            inline auto addState (CharacterSet const & characterSet, Node const & pattern) noexcept -> Node & {
                return this->addState (characterSet, pattern.copy());
            }

            inline auto addState (CharacterSet const & characterSet, Node * pPattern) noexcept -> Node & {
                this->_nextStates.add({characterSet.copy(), pPattern->copy()});
                return * this;
            }

            [[nodiscard]] inline auto getState (char c) const noexcept -> Node const * {
                for (auto const & e : this->_nextStates)
                    if (e.getFirst()->contains(c))
                        return e.getSecond();

                return nullptr;
            }

            [[nodiscard]] inline auto setRepCount ( Pair < Size, Size > const & sizePair ) noexcept -> Node & {
                return this->setMinRepCount(sizePair.getFirst()).setMaxRepCount(sizePair.getSecond());
            }

            [[nodiscard]] inline auto copy () const noexcept -> Node * override {
                return new Node (*this);
            }

            [[nodiscard]] inline auto outgoingCharacterSet () const noexcept -> CharacterSet {
                return this->_nextStates.sequence()
                    .fold(CharacterSet(), [](CharacterSet const & a, Pair < CharacterSet *, Node * > const & p){
                        CharacterSet r = a;

                        for ( char c = 0; c < 127; c++ )
                            if ( p.getFirst()->contains(c) )
                                r.add(c);

                        return r;
                    });
            }

            [[nodiscard]] inline auto toString () const noexcept -> String override {
                return "Regex::CompiledPattern::Node "_s +
                    ", outgoingCharacterSet = " + this->outgoingCharacterSet() +
                    ", outgoingNodes = " + this->_nextStates.sequence()
                        .map([](Pair < CharacterSet *, Node *>const & p){ return p.toString(); }).toLinkedList().toString() +
                    ", repCount = " + this->repCounts().toString() +
                    ", isEndState = " + (this->endState() ? "true" : "false") +
                    " }";
            }
        };

        Node * _head {nullptr};
        Pattern _originalPattern;

    private:
        inline auto parse () noexcept -> CompiledPattern & {

            return * this;
        }

    public:
        explicit CompiledPattern(Pattern const & pattern) noexcept :
                _originalPattern(pattern) {
            this->parse();
        }

        auto clear () noexcept -> CompiledPattern & {
            this->_originalPattern.clear();

            UnorderedSet < Node * > cleared;

            Node * current = this->_head;
            while (current != nullptr) {
                for ( auto & e : current->nextStates() ) {
                    delete e.getFirst();
                    
                }
            }

            return * this;
        }

        static inline auto compile (String const & pattern) noexcept -> CompiledPattern {
            return CompiledPattern(pattern);
        }
    };

    Flags  _flags  { Regex::_globalFlags };

    Pattern _pattern;

public:
    Regex () noexcept = default;
    Regex (Regex const &) noexcept = default;

    ~Regex() noexcept override = default;

    auto operator = (Regex const &) noexcept -> Regex &;

    [[nodiscard]] static auto compile (Pattern const &, Flags = Regex::FlagBit::NONE) noexcept(false) -> Regex;
    [[nodiscard]] static auto search (Pattern const &, String const &, Flags = Regex::FlagBit::NONE) noexcept(false) -> Match;
    [[nodiscard]] static auto match (Pattern const &, String const &, Flags = Regex::FlagBit::NONE) noexcept(false) -> Match;
    [[nodiscard]] static auto fullMatch (Pattern const &, String const &, Flags = Regex::FlagBit::NONE) noexcept(false) -> Match;
    [[nodiscard]] static auto split (Pattern const &, String const &, Size = 0, Flags = Regex::FlagBit::NONE) noexcept(false) -> LinkedList < String >;

    [[nodiscard]] static auto findAll (Pattern const &, String const &, Flags = Regex::FlagBit::NONE) noexcept(false) -> LinkedList < Match >;

    [[nodiscard]] static auto sub (Pattern const &, String const &, String const &, Size = 0, Flags = Regex::FlagBit::NONE) noexcept(false) -> String;
    [[nodiscard]] static auto subn (Pattern const &, String const &, String const &, Size = 0, Flags = Regex::FlagBit::NONE) noexcept(false) -> Pair < String, Size >;
    [[nodiscard]] static auto escape (String const &) noexcept -> String;

    [[nodiscard]] auto search (String const &, Index = String::INVALID_POS, Index = String::INVALID_POS) const noexcept -> Match;
    [[nodiscard]] auto match (String const &, Index = String::INVALID_POS, Index = String::INVALID_POS) const noexcept -> Match;
    [[nodiscard]] auto fullMatch (String const &, Index = String::INVALID_POS, Index = String::INVALID_POS) const noexcept -> Match;
    [[nodiscard]] auto split (String const &, Size = 0) const noexcept -> LinkedList < String >;
    [[nodiscard]] auto findAll (String const &, Index = String::INVALID_POS, Index = String::INVALID_POS) const noexcept -> LinkedList < Match >;
    [[nodiscard]] auto sub (String const &, String const &, Size = 0) const noexcept -> String;
    [[nodiscard]] auto subn (String const &, String const &, Size = 0) const noexcept -> Pair < String, Size >;

    [[nodiscard]] inline auto static globalFlags () noexcept -> Flags { return Regex::_globalFlags; }
    [[nodiscard]] inline auto static globalFormat () noexcept -> Format { return Regex::_globalFormat; }

    inline auto static setGlobalFlags ( Flags newFlags ) noexcept -> void { Regex::_globalFlags = newFlags & Regex::_flagMask; }
    inline auto static setGlobalFormat ( Format newFormat ) noexcept -> void { Regex::_globalFormat = newFormat; }

    inline auto static setGlobalFlagBit ( FlagBit flagBit, bool enable = true ) noexcept -> void { enable ? Regex::enableGlobalFlagBit(flagBit) : Regex::disableGlobalFlagBit(flagBit); }

    inline auto static enableGlobalFlagBit ( FlagBit flagBit ) noexcept -> void { Regex::_globalFlags |= flagBit & Regex::_flagMask; }
    inline auto static disableGlobalFlagBit ( FlagBit flagBit ) noexcept -> void { Regex::_globalFlags &= ~ (flagBit & Regex::_flagMask); }

    [[nodiscard]] constexpr auto flags () const noexcept -> Flags { return this->_flags; }
    [[nodiscard]] constexpr auto flags () noexcept -> Flags & { return this->_flags; }

    constexpr auto setFlags ( Flags newFlags ) noexcept -> Regex & { this->_flags = newFlags & Regex::_flagMask; return * this; }

    constexpr auto setFlagBit ( FlagBit flagBit, bool enable = true ) noexcept -> Regex & { return enable ? this->enableFlagBit (flagBit) : this->disableFlagBit(flagBit); }

    constexpr auto enableFlagBit ( FlagBit flagBit ) noexcept -> Regex & { this->_flags |= flagBit & Regex::_flagMask; return * this; }
    constexpr auto disableFlagBit ( FlagBit flagBit ) noexcept -> Regex & { this->_flags &= ~ (flagBit & Regex::_flagMask); return * this; }

    [[nodiscard]] constexpr static auto cache () noexcept -> Regex::Cache & { return Regex::_cache; }

    constexpr static auto enableCache () noexcept -> void { Regex::cache().enable(); }
    constexpr static auto enableCache (Size cacheSize) noexcept -> void { Regex::cache().enable().size() = cacheSize; }

    constexpr static auto disableCache () noexcept -> void { Regex::cache().disable(); }

    constexpr static auto setCacheSize (Size newSize) noexcept -> void { if ( Regex::cache().enabled() ) Regex::cache().size() = newSize; }
    constexpr static auto cacheEnabled () noexcept -> bool { return Regex::cache().enabled(); }

    inline static auto purge () noexcept -> void { Regex::cache().purge(); }
    inline static auto purgeCache () noexcept -> void { Regex::purge(); }

    [[nodiscard]] constexpr auto pattern () const noexcept -> Pattern const & { return this->_pattern; }

    class RegexError : public std::exception {
    private:
        String _message;

    public:
        RegexError (
                String const & errorMessage,
                Pattern const & pattern,
                Index position = -1,
                Index lineNumber = -1,
                Index columnNumber = -1
        ) noexcept :
                std::exception () {
            this->_message = "<Placeholder, Replace please!>";
        }

        [[nodiscard]] constexpr auto what () const noexcept -> StringLiteral override {
            return this->_message.cStr();
        }
    };
};

#endif //CDS_REGEX_HPP
