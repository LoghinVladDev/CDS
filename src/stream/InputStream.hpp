//
// Created by vladl on 17/04/2021.
//

#ifndef CDS_INPUTSTREAM_HPP
#define CDS_INPUTSTREAM_HPP

#include <CDS/AbstractStream>
#include <type_traits>

#include <CDS/Boolean>
#include <CDS/Double>
#include <CDS/Float>
#include <CDS/Integer>
#include <CDS/Long>

class InputStream : virtual public AbstractStream {
private:
    bool _incompleteWriteExceptionEnabled { false };
    bool _bufferEnded {false};

public:

    class IncompleteRead : public AbstractStream::StreamError {
    private:
        String message;

    public:
        IncompleteRead() noexcept {
            this->message = "Read Incomplete";
        }

        IncompleteRead(Size desired, Size resulted) noexcept {
            this->message = String("Read Incomplete, requested : ").append(desired).append(", resulted : ").append(resulted);
        }

        [[nodiscard]] auto what() const noexcept -> StringLiteral override {
            return this->message.cStr();
        }
    };

    class OutOfBounds : public AbstractStream::StreamError {
    public:
        [[nodiscard]] auto what() const noexcept -> StringLiteral override {
            return "Nothing left to read";
        }
    };

    class ConversionError : public AbstractStream::StreamError {
    private:
        String message;

    public:
        ConversionError() noexcept {
            this->message = "Input Conversion Error";
        }

        ConversionError(String const & from, String const & to) noexcept {
            this->message = String("Input Conversion Error from ").append(from).append(" to ").append(to);
        }

        [[nodiscard]] auto what () const noexcept -> StringLiteral override {
            return this->message.cStr();
        }
    };

protected:
    InputStream() noexcept = default;
    InputStream(InputStream const &) noexcept = default;
    InputStream(InputStream &&) noexcept = default;
    ~InputStream() noexcept override = default;

public:

    virtual auto readBytes ( void * p, Size s ) noexcept(false) -> Size {
        return AbstractStream::primitiveRead( this->handle, p, s );
    }

    inline auto endOfFile () const noexcept -> bool { return this->_bufferEnded; }

    virtual auto readString () noexcept (false) -> String {
        return this->readLine(" \t\n\r");
    }

    virtual auto getChar () noexcept(false) -> char {
        if ( this->_bufferEnded )
            throw OutOfBounds();

        char c;

        try {
            this->readBytes(&c, 1);
        } catch ( InputStream::ReadError const & ) {
            c = EOF;
        }

        if ( c == EOF )
            this->_bufferEnded = true;

        return c;
    }

    virtual auto readLine (String const & sep = "\n") noexcept (false) -> String {
        String current;

        while (!this->endOfFile()) {
            auto c = this->getChar();

            if ( sep.contains(c) || c == EOF )
                return current;

            current += c;
        }

        return current;
    }

    inline auto readInt () noexcept (false) -> Integer {
        return Integer::parse(this->readString());
    }

    inline auto readLong () noexcept (false) -> Long {
        return Long::parse(this->readString());
    }

    inline auto readBoolean () noexcept(false) -> Boolean {
        return Boolean::parse(this->readString());
    }

    inline auto readFloat () noexcept(false) -> Float {
        return Float::parse(this->readString());
    }

    inline auto readDouble () noexcept(false) -> Double {
        return Double::parse(this->readString());
    }
};


#endif //CDS_INPUTSTREAM_HPP
