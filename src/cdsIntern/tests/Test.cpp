//
// Created by loghin on 05.04.2021.
//

#include "Test.h"

Test::TerminalColor Test::TerminalColor::clear(DISABLE_INVERSE_COLOR | DISABLE_UNDERLINE | DISABLE_BOLD | RESET );

HashMap < Test::TerminalColor::Modifier, int > Test::TerminalColor::colorMap = {
        {RESET, 0},
        {ENABLE_BOLD, 1},
        {ENABLE_UNDERLINE, 4},
        {ENABLE_INVERSE_COLOR, 7},
        {DISABLE_BOLD, 21},
        {DISABLE_UNDERLINE, 24},
        {DISABLE_INVERSE_COLOR, 27},

        {FOREGROUND_BLACK, 30},
        {FOREGROUND_RED, 31},
        {FOREGROUND_GREEN, 32},
        {FOREGROUND_YELLOW, 33},
        {FOREGROUND_BLUE, 34},
        {FOREGROUND_MAGENTA, 35},
        {FOREGROUND_CYAN, 36},
        {FOREGROUND_WHITE, 37},

        {BACKGROUND_BLACK, 40},
        {BACKGROUND_RED, 41},
        {BACKGROUND_GREEN, 42},
        {BACKGROUND_YELLOW, 43},
        {BACKGROUND_BLUE, 44},
        {BACKGROUND_MAGENTA, 45},
        {BACKGROUND_CYAN, 46},
        {BACKGROUND_WHITE, 47}
};

static Test::TerminalColor testOK ( Test::TerminalColor::Modifier::FOREGROUND_GREEN | Test::TerminalColor::Modifier::ENABLE_BOLD );
static Test::TerminalColor testWarn ( Test::TerminalColor::Modifier::FOREGROUND_YELLOW );
static Test::TerminalColor subtestOK ( Test::TerminalColor::Modifier::FOREGROUND_GREEN );
static Test::TerminalColor testNOK ( Test::TerminalColor::Modifier::FOREGROUND_RED | Test::TerminalColor::Modifier::ENABLE_BOLD );
static Test::TerminalColor bold (Test::TerminalColor::Modifier::ENABLE_BOLD );

#include <iostream>
#include <cstdio>
#include <cstdarg>

auto Test::log(const String & text) noexcept -> void {
    std::cout << Test::TerminalColor::clear << text << '\n';
}

auto Test::log(const char * format, ...) noexcept -> void {
    va_list args;
    va_start(args, format);
    printf("\033[%sm", TerminalColor::asList(Test::TerminalColor::clear.format()).cStr());
    vprintf(format, args);
    printf("\n");
    va_end(args);
}

auto Test::logBold(const String & text) noexcept -> void {
    std::cout << bold << text << TerminalColor::clear << '\n';
}

auto Test::logBold(const char * format, ...) noexcept -> void {
    va_list args;
    va_start(args, format);
    printf("\033[%sm", TerminalColor::asList(bold.format()).cStr());
    vprintf(format, args);
    printf("\033[%sm", TerminalColor::asList(Test::TerminalColor::clear.format()).cStr());
    printf("\n");
    va_end(args);
}

auto Test::logOK(const String & text) noexcept -> void {
    std::cout << testOK << text << TerminalColor::clear << '\n';
}

auto Test::logOK(const char * format, ...) noexcept -> void {
    va_list args;
    va_start(args, format);
    printf("\033[%sm", TerminalColor::asList(testOK.format()).cStr());
    vprintf(format, args);
    printf("\033[%sm", TerminalColor::asList(Test::TerminalColor::clear.format()).cStr());
    printf("\n");
    va_end(args);
}


auto Test::logWarning(const String & text) noexcept -> void {
    std::cout << testWarn << text << TerminalColor::clear << '\n';
}

auto Test::logWarning(const char * format, ...) noexcept -> void {
    va_list args;
    va_start(args, format);
    printf("\033[%sm", TerminalColor::asList(testWarn.format()).cStr());
    vprintf(format, args);
    printf("\033[%sm", TerminalColor::asList(Test::TerminalColor::clear.format()).cStr());
    printf("\n");
    va_end(args);
}



auto Test::logError(const String & text) noexcept -> void {
    std::cout << testNOK << text << TerminalColor::clear << '\n';
}

auto Test::logError(const char * format, ...) noexcept -> void {
    va_list args;
    va_start(args, format);
    printf("\033[%sm", TerminalColor::asList(testNOK.format()).cStr());
    vprintf(format, args);
    printf("\033[%sm", TerminalColor::asList(Test::TerminalColor::clear.format()).cStr());
    printf("\n");
    va_end(args);
}
