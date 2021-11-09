//
// Created by vladl on 17/04/2021.
//

#ifndef CDS_OUTPUTSTREAM_HPP
#define CDS_OUTPUTSTREAM_HPP

#include <CDS/AbstractStream>

namespace cds {

    class OutputStream : virtual public AbstractStream {
    private:
        bool _incompleteWriteExceptionEnabled { false };

    public:

        class IncompleteWrite : public AbstractStream::StreamError {
        private:
            String message;
        public:
            IncompleteWrite() noexcept {
                this->message = "Write Incomplete";
            }

            IncompleteWrite(Size desired, Size resulted) noexcept {
                this->message = String("Write incomplete, requested : ").append(desired).append(", resulted : ").append(resulted);
            }

            [[nodiscard]] auto what() const noexcept -> StringLiteral override {
                return this->message.cStr();
            }
        };

    protected:
        OutputStream () noexcept = default;
        OutputStream (OutputStream const &) noexcept = default;
        OutputStream (OutputStream &&) noexcept = default;
        ~OutputStream() noexcept override = default;

    public:
        virtual auto writeBytes ( void const * p, Size s ) noexcept(false) -> Size {
            return AbstractStream::primitiveWrite( this->handle, p, s );
        }

        template < typename T >
        inline auto write ( T const & v ) noexcept(false) -> void {
            Size written;

            if (( this->flags & BINARY ) == BINARY) {
                written = this->writeBytes( reinterpret_cast < void const * > ( & v ), sizeof (T) );

                if ( this->_incompleteWriteExceptionEnabled && written != sizeof(T) )
                    throw IncompleteWrite(sizeof(T), written);
            } else {
                auto s = String().append(v);
                written = this->writeBytes( reinterpret_cast < void const * > ( s.cStr() ), s.length());

                if ( this->_incompleteWriteExceptionEnabled && written != s.length() )
                    throw IncompleteWrite(s.length(), written);
            }
        }

        inline auto write ( Object const & obj ) noexcept (false) -> void {
            Size written;

            if (( this->flags & BINARY ) == BINARY) {
                written = this->writeBytes( reinterpret_cast < void const * > ( & obj ), sizeof ( obj ) );
            } else {
                auto s = obj.toString();
                written = this->writeBytes(reinterpret_cast < void const * > ( s.cStr()), s.length());
            }

            if ( this->_incompleteWriteExceptionEnabled && written != sizeof(obj) )
                throw IncompleteWrite(sizeof(obj), written);
        }

        auto setIncompleteWriteException (bool v) noexcept -> void { this->_incompleteWriteExceptionEnabled = v; }
        auto enableIncompleteWriteException () noexcept -> void { return this->setIncompleteWriteException(true); }
        auto disableIncompleteWriteException () noexcept -> void { return this->setIncompleteWriteException(false); }

    };

}

#endif //CDS_OUTPUTSTREAM_HPP
