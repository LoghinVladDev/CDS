//
// Created by loghin on 05.04.2021.
//

#ifndef CDS_TEST_H
#define CDS_TEST_H

#include <HashMap.hpp>

#define FLAG(i) 1u << i ## u
#define FOREACH_FLAG(_min, _max, _dt, _v) for ( _dt _v = FLAG(_min); _v != FLAG(_max); _v = _v << 1 )

class Test {
public:
    class TerminalColor {
    public:
        enum Modifier : CDS_uint32 {
            RESET = FLAG(0),

            ENABLE_BOLD = FLAG(1),
            ENABLE_UNDERLINE = FLAG(2),
            ENABLE_INVERSE_COLOR = FLAG(3),

            DISABLE_BOLD = FLAG(4),
            DISABLE_UNDERLINE = FLAG(5),
            DISABLE_INVERSE_COLOR = FLAG(6),

            FOREGROUND_BLACK = FLAG(14),
            FOREGROUND_RED = FLAG(15),
            FOREGROUND_GREEN = FLAG(16),
            FOREGROUND_YELLOW = FLAG(17),
            FOREGROUND_BLUE = FLAG(18),
            FOREGROUND_MAGENTA = FLAG(19),
            FOREGROUND_CYAN = FLAG(20),
            FOREGROUND_WHITE = FLAG(21),
            FOREGROUND_DEFAULT = FLAG(22),

            BACKGROUND_BLACK = FLAG(23),
            BACKGROUND_RED = FLAG(24),
            BACKGROUND_GREEN = FLAG(25),
            BACKGROUND_YELLOW = FLAG(26),
            BACKGROUND_BLUE = FLAG(27),
            BACKGROUND_MAGENTA = FLAG(28),
            BACKGROUND_CYAN = FLAG(29),
            BACKGROUND_WHITE = FLAG(30),
            BACKGROUND_DEFAULT = FLAG(31),
        };

    public:
        typedef CDS_uint32 Flags;
    private:

        static HashMap < Modifier, int > colorMap;
        Flags f = FOREGROUND_DEFAULT | BACKGROUND_DEFAULT;
    public:
        [[nodiscard]] auto format () const noexcept -> Flags { return this->f; }

        constexpr explicit TerminalColor ( Flags f ) noexcept : f(f) {}
        constexpr TerminalColor ( TerminalColor const & ) noexcept = default;
        static auto asList ( Flags f ) noexcept -> String {
#if defined(_WIN32)
            return "";
#endif

            String res;
            FOREACH_FLAG(0, 31, CDS_uint32, i ) {
                if ( colorMap.containsKey( static_cast<Modifier>(i) ) && ( f & i ) ) {
                    res.append( colorMap.get( static_cast<Modifier>(i) ) ).append(";");
                }
            }
            return res.rtrim(';');
        }

        friend std::ostream & operator << ( std::ostream & o, TerminalColor const & c ) {
#if defined(_WIN32)
            return o;
#else
            o << "\033[" << asList(c.f) << "m";
#endif
            return o;
        }

        static TerminalColor clear;
    };

private:
    Size logDepth = 0;

protected:
    [[nodiscard]] auto inline getDepthString() const noexcept -> String {
        return String("\t") * this->logDepth;
    }

public:
    virtual auto execute () noexcept -> bool = 0;

    template < typename Function >
    auto executeSubtest ( String const & title, Function const & subtest ) noexcept -> void {
        this->logDepth++;
        this->logBold("-----Start of subtest '%s'-----", title.cStr());
        this->logDepth++;
        subtest();
        this->logDepth--;
        this->logBold("-----End of subtest '%s'-----", title.cStr());
        this->logDepth--;
    }

    auto logOK ( String const & ) noexcept -> void;
    auto logError (String const &) noexcept -> void;
    auto logWarning (String const &) noexcept -> void;
    auto log(String const &) noexcept -> void;
    auto logBold(String const &) noexcept -> void;

    auto logOK ( const char *, ... ) noexcept -> void;
    auto logError ( const char *, ... ) noexcept -> void;
    auto logWarning ( const char *, ... ) noexcept -> void;
    auto log( const char *, ... ) noexcept -> void;
    auto logBold( const char *, ... ) noexcept -> void;
};

#undef FLAG
#undef FOREACH_FLAG

#endif //CDS_TEST_H
