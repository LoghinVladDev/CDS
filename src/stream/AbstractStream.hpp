//
// Created by loghin on 19.04.2021.
//

#ifndef CDS_ABSTRACTSTREAM_HPP
#define CDS_ABSTRACTSTREAM_HPP

#include <CDS/Object>

#if defined(__linux) || defined(__APPLE__)

#include <unistd.h>

#elif defined(__WIN32)
#else
#endif

namespace cds {

    class AbstractStream : public Object {
    public:
        class UnopenedStream : public std::exception {
        public:
            [[nodiscard]] auto what() const noexcept -> StringLiteral override {
                return "Tried Writing on Unopened Stream";
            }
        };

        class StreamError : public std::exception {
        public:
            [[nodiscard]] auto what() const noexcept -> StringLiteral override = 0;
        };

        class WriteError : public AbstractStream::StreamError {
        public:
            [[nodiscard]] auto what() const noexcept -> StringLiteral override {
                return "Write error";
            }
        };

        class ReadError : public AbstractStream::StreamError {
        public:
            [[nodiscard]] auto what() const noexcept -> StringLiteral override {
                return "Read error";
            }
        };

        class ReadClosed : public AbstractStream::StreamError {
        public:
            [[nodiscard]] auto what () const noexcept -> StringLiteral override {
                return "Read channel closed/disconnected";
            }
        };

        enum Flag : uint8 {
            NONE        = 0x00,
            BINARY      = 0x01,
            APPEND      = 0x02,
            TRUNCATE    = 0x04,
            CREATE      = 0x08,
            INPUT       = 0x16,
            OUTPUT      = 0x32
        };

        using Flags = uint8;

    protected:

        constexpr static Flags flagMask =
                NONE | BINARY | APPEND | TRUNCATE | CREATE | INPUT | OUTPUT;

        Flags flags;

    #if defined(__linux) || defined(__APPLE__)

        using Handle = int;

        constexpr static Handle NULL_HANDLE = -1;
        constexpr static int PRIMITIVE_ERROR = -1;
        constexpr static int PRIMITIVE_DISCONNECT = 0;

        Handle handle {NULL_HANDLE};

        auto validateHandle () const noexcept(false) -> void {
            if ( this->handle == NULL_HANDLE ) throw UnopenedStream();
        }

        inline auto primitiveRead ( Handle h, void * p, Size s ) noexcept(false) -> Size {
            this->validateHandle();

            auto r = ::read(h, p, s);
            if ( r == PRIMITIVE_ERROR ) throw ReadError();
            if ( r == PRIMITIVE_DISCONNECT ) throw ReadClosed();

            return r;
        }

        inline auto primitiveWrite ( Handle h, void const * p, Size s ) noexcept(false) -> Size {
            this->validateHandle();

            auto r = ::write(h, p, s);
            if ( r == PRIMITIVE_ERROR ) throw WriteError();

            return r;
        }

    #elif defined(__WIN32)
    #else
    #error Unsupported : OutputStream
    #endif

        AbstractStream () noexcept = default;
        AbstractStream (AbstractStream const &) noexcept = default;
        AbstractStream (AbstractStream &&) noexcept = default;
        ~AbstractStream() noexcept override = default;

        [[nodiscard]] auto toString() const noexcept -> String override {
            return "";
        }
    };

}

#endif //CDS_ABSTRACTSTREAM_HPP
