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

public:
    class CharacterSet : public Object {
    public:
        class Range : public Object {
        private:
            char _lower = 0;
            char _upper = 0;

        public:
            Range() noexcept = default;
            Range(Range const &) noexcept = default;
            Range(char l, char u) noexcept : _lower(l), _upper(u) {}
            explicit Range(char c) noexcept : Range(c, c) {}

            ~Range() noexcept override = default;

            [[nodiscard]] constexpr auto single () const noexcept -> bool { return this->_lower == this->_upper; }

            [[nodiscard]] constexpr auto lower () const noexcept -> char { return this->_lower; }
            [[nodiscard]] constexpr auto upper () const noexcept -> char { return this->_upper; }

            constexpr auto setLower (char lower) noexcept -> void { this->_lower = lower; }
            constexpr auto setUpper (char upper) noexcept -> void { this->_upper = upper; }

            constexpr auto operator == (Range const & set) const noexcept -> bool {
                return this->_lower == set._lower && this->_upper == set._upper;
            }

            constexpr auto operator < (Range const & range) const noexcept -> bool {
                return this->_lower < range._lower;
            }

            [[nodiscard]] constexpr auto contains (char c) const noexcept -> bool { return this->_lower <= c && c <= this->_upper; }
            [[nodiscard]] constexpr auto contains (Range const & r) const noexcept -> bool { return this->contains(r.lower()) && this->contains(r.upper()); }
            [[nodiscard]] constexpr auto leftOf (Range const & r) const noexcept -> bool { return r.lower() > this->upper() + 1; }
            [[nodiscard]] constexpr auto rightOf (Range const & r) const noexcept -> bool { return r.upper() + 1 < this->lower(); }

            [[nodiscard]] inline auto toString () const noexcept -> String override {
                return this->single() ? ""_s + this->_lower : ""_s + this->_lower + "-" + this->_upper;
            }
        };

    private:
        mutable OrderedSet < Range > _ranges;

    public:
        explicit CharacterSet(String const & str) noexcept {
            int rangeState = -1;

            char left;

            for (auto c : str) {
                if ( String::isAlpha(c) ) {
                    if (rangeState == 0)
                        this->_ranges.add(Range(left));
                    else if (rangeState == 1) {
                        this->_ranges.add(Range(left, c));
                        rangeState = -1;
                        continue;
                    }

                    rangeState = 0;
                    left = c;
                } else if ( c == '-' && rangeState == 0 ) rangeState = 1;
                else this->_ranges.add(Range(c));
            }

            if ( rangeState != -1 ) this->add(str.back());
        }

        [[nodiscard]] inline auto contains (char c) const noexcept -> bool {
            return this->_ranges.any([& c](auto & r){
                return r.contains(c);
            });
        }

        static auto compile (String const & s) noexcept -> CharacterSet { return CharacterSet(s); }

        inline auto add (char c) noexcept -> void {
            this->add(Range(c));
        }

        inline auto add (char l, char u) noexcept -> void {
            this->add(Range(l, u));
        }

        inline auto add (Range const & r) noexcept -> void {
            this->_ranges.add(r);
        }

        inline auto shrink () const noexcept -> void {
            char freq[255];
            std::memset(freq, 0, 255);

            this->_ranges.forEach([& freq](auto & r){std::memset(freq + r.lower(), 1, r.upper() - r.lower() + 1 );});
            this->_ranges.clear();

            Range r(1, 0);

            if ( freq[0] == 1 ) r.setLower(0);

            for (sint8 i = 0; i < 127; i++) {
                if(freq[i] == 1) r.setUpper(i);
                else {
                    if ( r.lower() <= r.upper() )
                        this->_ranges.add(r);
                    r.setLower(i + 1);
                }
            }
        }

        [[nodiscard]] inline auto toString () const noexcept -> String override {
            this->shrink();
            return this->_ranges.sequence().fold("["_s, [](String const & s, Range const & r){return s + r;}).append("]");
        }
    };

private:

    class CompiledPattern : public Object {
    private:
        class Node {

        };

    public:

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
