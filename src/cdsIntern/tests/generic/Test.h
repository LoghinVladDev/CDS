/*
 * Created by loghin on 05.04.2021.
 */

#ifndef CDS_TEST_H
#define CDS_TEST_H

#include <CDS/Compiler>
#include <CDS/HashMap>

#include <chrono>
#include <cmath>
#include <functional>

namespace glob {
    template <typename F>
    constexpr static auto flag (F shiftSize) noexcept -> cds::uint64 {
        return 1U << static_cast <cds::uint64> (shiftSize);
    }

    template <typename Functor>
    inline static auto foreach_flag (std::tuple <cds::uint64, cds::uint64> const & range, Functor const & called) noexcept -> void {
        auto const fShiftEndVal = std::get<1> (range);
        for (auto fShiftVal = std::get<0> (range); fShiftVal < fShiftEndVal; ++ fShiftVal) {
            called (flag (fShiftVal));
        }
    }
} /* namespace glob */

#if defined(WIN32)
#undef FOREGROUND_RED
#undef FOREGROUND_GREEN
#undef FOREGROUND_BLUE

#undef BACKGROUND_RED
#undef BACKGROUND_GREEN
#undef BACKGROUND_BLUE
#endif

class Test {
public:
    class TerminalColor {
    public:
        enum Modifier : cds :: uint32 {
            RESET = glob::flag(0),

            ENABLE_BOLD = glob::flag(1),
            ENABLE_UNDERLINE = glob::flag(2),
            ENABLE_INVERSE_COLOR = glob::flag(3),

            DISABLE_BOLD = glob::flag(4),
            DISABLE_UNDERLINE = glob::flag(5),
            DISABLE_INVERSE_COLOR = glob::flag(6),

            FOREGROUND_BLACK = glob::flag(14),
            FOREGROUND_RED = glob::flag(15),
            FOREGROUND_GREEN = glob::flag(16),
            FOREGROUND_YELLOW = glob::flag(17),
            FOREGROUND_BLUE = glob::flag(18),
            FOREGROUND_MAGENTA = glob::flag(19),
            FOREGROUND_CYAN = glob::flag(20),
            FOREGROUND_WHITE = glob::flag(21),
            FOREGROUND_DEFAULT = glob::flag(22),

            BACKGROUND_BLACK = glob::flag(23),
            BACKGROUND_RED = glob::flag(24),
            BACKGROUND_GREEN = glob::flag(25),
            BACKGROUND_YELLOW = glob::flag(26),
            BACKGROUND_BLUE = glob::flag(27),
            BACKGROUND_MAGENTA = glob::flag(28),
            BACKGROUND_CYAN = glob::flag(29),
            BACKGROUND_WHITE = glob::flag(30),
            BACKGROUND_DEFAULT = glob::flag(31),
        };

    public:
        typedef cds :: uint32 Flags;
    private:

        static cds :: HashMap < Modifier, int > colorMap;
        Flags f = FOREGROUND_DEFAULT | BACKGROUND_DEFAULT;
    public:
        [[nodiscard]] auto format () const noexcept -> Flags { return this->f; }

        constexpr explicit TerminalColor ( Flags f ) noexcept : f(f) {}
        constexpr TerminalColor ( TerminalColor const & ) noexcept = default;
        static auto asList ( Flags f ) noexcept -> cds :: String {
#if defined(_WIN32)
            return "";
#endif

            cds :: String res;
            auto const flagLimit = 60U;

            glob::foreach_flag(std::make_tuple(0, flagLimit), [& res, f](cds::uint64 presentFlag){

                __CDS_WarningSuppression_UseScopedEnum_SuppressEnable

                if ( colorMap.containsKey( static_cast<Modifier>(presentFlag) ) && (( f & presentFlag ) != 0U) ) {
                    res.append( colorMap.get( static_cast<Modifier>(presentFlag) ) ).append(";");
                }

                __CDS_WarningSuppression_UseScopedEnum_SuppressDisable

            });

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
    cds :: Size logDepth = 0;

protected:
    [[nodiscard]] auto inline getDepthString() const noexcept -> cds :: String {
        return cds :: String("\t") * this->logDepth;
    }

public:
    virtual auto execute () noexcept -> bool = 0;
    auto start (cds :: String const & testName) noexcept -> bool {
        auto start = std::chrono::high_resolution_clock::now();

        this->logBold("Start of test '%s', on platform : '%s', compiler : '%s', version : '%s', cpp standard : '%s'",
            testName.cStr(),
            __CDS_Platform,
            __CDS_compiler_name,
            cds :: utility :: __CDS_compilerVersionString(),
            __CDS_cpplang_core_version_name
        );

        bool ok = this->execute();

        ok ?
            this->logOK("'%s' test OK, on platform : '%s', compiler : '%s', version : '%s', cpp standard : '%s'",
                testName.cStr(),
                __CDS_Platform,
                __CDS_compiler_name,
                cds :: utility :: __CDS_compilerVersionString(),
                __CDS_cpplang_core_version_name
            ):
            this->logError("'%s' test Not OK, on platform : '%s', on compiler : '%s', version : '%s', cpp standard : '%s'",
                testName.cStr(),
                __CDS_Platform,
                __CDS_compiler_name,
                cds :: utility :: __CDS_compilerVersionString(),
                __CDS_cpplang_core_version_name
            );

        auto end = std::chrono::high_resolution_clock::now();

        auto diff = std::chrono::duration_cast < std::chrono::nanoseconds > ( (end - start) );

        double power = std::pow(10, 9);
        std::cout << "Test Lasted " << diff.count() << " nanoseconds ( " << static_cast < double > (diff.count()) / power << " seconds )" << '\n';
        return ok;
    }

    template < typename Function >
    auto executeSubtest ( cds :: String const & title, Function const & subtest ) noexcept -> void {
        this->logDepth++;
        this->logBold("-----Start of test group '%s'-----", title.cStr());
        this->logDepth++;
        subtest();
        this->logDepth--;
        this->logBold("-----End of test group '%s'-----", title.cStr());
        this->logDepth--;
    }

    auto logOK ( cds :: String const & ) noexcept -> void;
    auto logError ( cds :: String const &) noexcept -> void;
    auto logWarning ( cds :: String const &) noexcept -> void;
    auto log( cds :: String const &) noexcept -> void;
    auto logBold( cds :: String const &) noexcept -> void;

    auto logOK ( const char *, ... ) noexcept -> void;
    auto logError ( const char *, ... ) noexcept -> void;
    auto logWarning ( const char *, ... ) noexcept -> void;
    auto log( const char *, ... ) noexcept -> void;
    auto logBold( const char *, ... ) noexcept -> void;

    virtual ~Test() noexcept = default;
};

#endif /* CDS_TEST_H */
