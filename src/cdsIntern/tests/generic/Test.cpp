/*
 * Created by loghin on 05.04.2021.
 */

#include "Test.h"
#include <CDS/Pair>

#include <iostream>
#include <cstdio>
#include <cstdarg>
#include <CDS/threading/Mutex>

namespace {
    using glob::Test;
    using cds::Pair;
    using cds::HashMap;
    using cds::String;

    Pair < Test :: TerminalColor :: Modifier, int > p;

    Test::TerminalColor testOK ( Test::TerminalColor::Modifier::FOREGROUND_GREEN | Test::TerminalColor::Modifier::ENABLE_BOLD );
    Test::TerminalColor testWarn ( Test::TerminalColor::Modifier::FOREGROUND_YELLOW );
    Test::TerminalColor subtestOK ( Test::TerminalColor::Modifier::FOREGROUND_GREEN );
    Test::TerminalColor testNOK ( Test::TerminalColor::Modifier::FOREGROUND_RED | Test::TerminalColor::Modifier::ENABLE_BOLD );
    Test::TerminalColor bold (Test::TerminalColor::Modifier::ENABLE_BOLD );

    cds::Mutex printLock;
}

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

auto Test::log(const String & text) const noexcept -> void {
    if(_disableLogActual) {return;}
    printLock.lock();
    std::cout << Test::TerminalColor::clear << this->getDepthString() << text << '\n';
    printLock.unlock();
}

auto Test::log(const char * format, ...) const noexcept -> void {
  if(_disableLogActual) {return;}
    printLock.lock();
    va_list args;
    va_start(args, format);
#if !defined(_WIN32)
    ::printf("\033[%sm", TerminalColor::asList(Test::TerminalColor::clear.format()).cStr());
#endif
    ::printf("%s", this->getDepthString().cStr());
    ::vprintf(format, args);
    ::printf("\n");
    va_end(args);
    printLock.unlock();
}

auto Test::logBold(const String & text) const noexcept -> void {
  if(_disableLogActual) {return;}
    printLock.lock();
    std::cout << this->getDepthString() << bold << text << TerminalColor::clear << '\n';
    printLock.unlock();
}

auto Test::logBold(const char * format, ...) const noexcept -> void {
  if(_disableLogActual) {return;}
    printLock.lock();
    va_list args;
    va_start(args, format);
#if !defined(_WIN32)
    ::printf("\033[%sm", TerminalColor::asList(bold.format()).cStr());
#endif
    ::printf("%s", this->getDepthString().cStr());
    ::vprintf(format, args);
#if !defined(_WIN32)
    ::printf("\033[%sm", TerminalColor::asList(Test::TerminalColor::clear.format()).cStr());
#endif
    ::printf("\n");
    va_end(args);
    printLock.unlock();
}

auto Test::logOK(const String & text) const noexcept -> void {
  if(_disableLogActual) {return;}
    printLock.lock();
    std::cout << this->getDepthString() << testOK << text << TerminalColor::clear << '\n';
    printLock.unlock();
}

auto Test::logOK(const char * format, ...) const noexcept -> void {
  if(_disableLogActual) {return;}
    printLock.lock();
    va_list args;
    va_start(args, format);
#if !defined(_WIN32)
    ::printf("\033[%sm", TerminalColor::asList(testOK.format()).cStr());
#endif
    ::printf("%s", this->getDepthString().cStr());
    ::vprintf(format, args);
#if !defined(_WIN32)
    ::printf("\033[%sm", TerminalColor::asList(Test::TerminalColor::clear.format()).cStr());
#endif
    ::printf("\n");
    va_end(args);
    printLock.unlock();
}


auto Test::logWarning(const String & text) const noexcept -> void {
  if(_disableLogActual) {return;}
    printLock.lock();
    std::cout << this->getDepthString() << testWarn << text << TerminalColor::clear << '\n';
    printLock.unlock();
}

auto Test::logWarning(const char * format, ...) const noexcept -> void {
  if(_disableLogActual) {return;}
    printLock.lock();
    va_list args;
    va_start(args, format);
#if !defined(_WIN32)
    ::printf("\033[%sm", TerminalColor::asList(testWarn.format()).cStr());
#endif
    ::printf("%s", this->getDepthString().cStr());
    ::vprintf(format, args);
#if !defined(_WIN32)
    ::printf("\033[%sm", TerminalColor::asList(Test::TerminalColor::clear.format()).cStr());
#endif
    ::printf("\n");
    va_end(args);
    printLock.unlock();
}



auto Test::logError(const String & text) const noexcept -> void {
  if(_disableLogActual) {return;}
    printLock.lock();
    std::cout << this->getDepthString() << testNOK << text << TerminalColor::clear << '\n';
    printLock.unlock();
}

auto Test::logError(const char * format, ...) const noexcept -> void {
  if(_disableLogActual) {return;}
    printLock.lock();
    va_list args;
    va_start(args, format);
#if !defined(_WIN32)
    ::printf("\033[%sm", TerminalColor::asList(testNOK.format()).cStr());
#endif
    ::printf("%s", this->getDepthString().cStr());
    ::vprintf(format, args);
#if !defined(_WIN32)
    ::printf("\033[%sm", TerminalColor::asList(Test::TerminalColor::clear.format()).cStr());
#endif
    ::printf("\n");
    va_end(args);
    printLock.unlock();
}
