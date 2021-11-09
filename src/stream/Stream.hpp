//
// Created by vladl on 17/04/2021.
//

#ifndef CDS_STREAM_HPP
#define CDS_STREAM_HPP

#include <CDS/InputStream>
#include <CDS/OutputStream>

namespace cds {

    class Stream : public InputStream, public OutputStream {
    private:
        class Console;

    public:
        static Console console;
    };

    class Stream::Console : public Stream {
    private:
        friend class Stream;

        Console() noexcept : Stream() {
            this->flags = INPUT | OUTPUT;
            this->handle = Stream::Console::CONSOLE_HANDLE;
        }

        Console (Console const & o) noexcept = default;
        Console (Console && o) noexcept = default;
        ~Console () noexcept override = default;

        constexpr static Handle in = 0;
        constexpr static Handle out = 1;

        constexpr static Handle CONSOLE_HANDLE = -2;

    public:

        inline auto readLine (String const & sep = "\n") noexcept (false) -> String override {
            this->handle = in;
            auto s = InputStream::readLine(sep);
            this->handle = CONSOLE_HANDLE;

            return s;
        }

        auto writeBytes ( void const * p, Size s ) noexcept(false) -> Size override {
            return AbstractStream::primitiveWrite( Console::out, p, s );
        }

        auto readBytes ( void * p, Size s ) noexcept(false) -> Size override {
            return AbstractStream::primitiveRead( Console::in, p, s );
        }

        auto toString () const noexcept -> String override {
            return "";
        }
    };

    inline Stream::Console Stream::console;

}

#endif //CDS_STREAM_HPP
