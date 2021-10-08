//
// Created by loghin on 07.10.2021.
//

#ifndef CDS_SOCKET_HPP
#define CDS_SOCKET_HPP

#include <CDS/Object>
#include <CDS/Exception>
#include <CDS/Pair>
#include <CDS/LinkedList>
#include <CDS/Utility>

#if defined(__CDS_Platform_Linux)

#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#else

#error "Unimplemented : Socket Header"

#endif

class SocketException : public Exception {
public:
    inline explicit SocketException(String const & message) noexcept : Exception(message) { }
    inline SocketException () noexcept : SocketException ("Unspecified Socket Exception") { }
};

class SocketDisconnect : public SocketException {
public:
    inline SocketDisconnect () noexcept : SocketException ("Socket Disconnected") { }
};

class Socket : public Object {

public:

    constexpr static StringLiteral LOCALHOST = "127.0.0.1";

    enum class ProtocolVersion {
        INTERNET_PROTOCOL_NONE_SPECIFIED = 0x00,

        INTERNET_PROTOCOL_VERSION_4 = 0x01,
        INTERNET_PROTOCOL_VERSION_6 = 0x02,
        INTERNET_PROTOCOL_VERSION_6_FORCED = 0x04,

        AUTO = INTERNET_PROTOCOL_NONE_SPECIFIED,
        IPV4 = INTERNET_PROTOCOL_VERSION_4,
        IPV6 = INTERNET_PROTOCOL_VERSION_6,
        FORCE_IPV6 = INTERNET_PROTOCOL_VERSION_6_FORCED
    };

private:

#if defined(__CDS_Platform_Linux)

    using PlatformSocket = int;

    constexpr static PlatformSocket UNIX_INVALID_PLATFORM_SOCKET = -1;
    constexpr static PlatformSocket UNIX_SOCKET_FUNCTION_ERROR = -1;
    constexpr static PlatformSocket UNIX_SOCKET_READ_DISCONNECT = 0;
    constexpr static Size PLATFORM_DEFAULT_PACKET_SIZE = 1024U;
    constexpr static Size PLATFORM_DEFAULT_CLIENT_QUEUE_SIZE = 256U;
    constexpr static Size PLATFORM_DEFAULT_PACKET_SYNC_COUNT = 4U;

    PlatformSocket _platformSocket { Socket::UNIX_INVALID_PLATFORM_SOCKET };

#else

#error "Unimplemented : Object-Socket"

#endif

    constexpr static Size DEFAULT_PACKET_SIZE = Socket::PLATFORM_DEFAULT_PACKET_SIZE;
    constexpr static Size DEFAULT_CLIENT_QUEUE_SIZE = Socket::PLATFORM_DEFAULT_CLIENT_QUEUE_SIZE;
    constexpr static uint16 DEFAULT_PORT = 8080;
    constexpr static Size DEFAULT_PACKET_SYNC_COUNT = Socket::PLATFORM_DEFAULT_PACKET_SYNC_COUNT;

    Size            _packetSize         { Socket::DEFAULT_PACKET_SIZE };
    Size            _packetSyncCount    { Socket::DEFAULT_PACKET_SYNC_COUNT };

    bool            _synchronizeSettingsAtConnectionStartup { true };


    Size            _port               { Socket::DEFAULT_PORT };
    ProtocolVersion _protocolVersion    { Socket::ProtocolVersion::AUTO };

public:

    __CDS_NoDiscard constexpr auto isOpen () const noexcept -> bool {

#if defined(__CDS_Platform_Linux)

        return this->_platformSocket != Socket::UNIX_INVALID_PLATFORM_SOCKET;

#else

#error "Unimplemented : Socket::isOpen()"

#endif

    }


    inline auto open () noexcept (false) -> Socket & {
        if ( this->isOpen() ) return * this;

        switch ( this->_protocolVersion ) {

            case ProtocolVersion::INTERNET_PROTOCOL_NONE_SPECIFIED:
            case ProtocolVersion::INTERNET_PROTOCOL_VERSION_6:
            case ProtocolVersion::INTERNET_PROTOCOL_VERSION_6_FORCED:

#if defined(__CDS_Platform_Linux)

                if ( this->_protocolVersion == ProtocolVersion::AUTO )
                    this->_protocolVersion = ProtocolVersion::INTERNET_PROTOCOL_VERSION_6;

                this->_platformSocket = socket( AF_INET6, SOCK_STREAM, IPPROTO_TCP);

                if ( this->_platformSocket != Socket::UNIX_SOCKET_FUNCTION_ERROR )
                    return * this;

                if ( this->_protocolVersion == ProtocolVersion::INTERNET_PROTOCOL_VERSION_6_FORCED )
                    throw SocketException ( "Unable to open Socket on IPV6" );

                this->close();

#endif

            case ProtocolVersion::INTERNET_PROTOCOL_VERSION_4:

#if defined(__CDS_Platform_Linux)

                this->_platformSocket = socket( AF_INET, SOCK_STREAM, IPPROTO_TCP);

                if ( this->_platformSocket != Socket::UNIX_SOCKET_FUNCTION_ERROR )
                    return * this;

                throw SocketException ( "Unable to open Socket on IPV4" );

#else

#error Socket::open Unimplemented

#endif

        }

        return * this;
    }

    inline explicit Socket ( ProtocolVersion protocolVersion = ProtocolVersion::AUTO ) noexcept (false) :
            _protocolVersion( protocolVersion) {

        this->open();
    }

    constexpr explicit Socket ( PlatformSocket const & platformSocket ) noexcept : _platformSocket( platformSocket) {

    }

    inline explicit Socket ( String const & address, ProtocolVersion protocolVersion = ProtocolVersion::AUTO ) noexcept (false) :
            _protocolVersion(protocolVersion) {

        this->open().connect( this->extractAddress (  address ) );
    }

    inline auto connect ( String const & address ) noexcept (false) -> Socket & {
        return this->connect( this->extractAddress(  address ) );
    }

    inline auto connect ( String const & address, uint16 port ) noexcept (false) -> Socket & { // NOLINT(misc-no-recursion)
        this->_port = port;
        return this->connect( Pair < String, uint16 > ( std::move(this->extractAddress(address).first()), port ) );
    }

private:
    inline auto connect ( Pair < String, uint16 > const & pack ) noexcept(false) -> Socket & { // NOLINT(misc-no-recursion)

#if defined(__CDS_Platform_Linux)

        switch ( this->_protocolVersion ) {
            case ProtocolVersion::INTERNET_PROTOCOL_NONE_SPECIFIED:
            case ProtocolVersion::INTERNET_PROTOCOL_VERSION_6:
            case ProtocolVersion::INTERNET_PROTOCOL_VERSION_6_FORCED: {

                sockaddr_in6 ipv6AddressData {};

                int retVal = inet_pton(AF_INET6, pack.first().cStr(), & ipv6AddressData.sin6_addr);
                if ( retVal == 0 ) throw SocketException("IPV6 Address Format Error : "_s + pack.first());
                if ( retVal == 1 ) {
                    ipv6AddressData.sin6_port = htons(pack.second());
                    ipv6AddressData.sin6_family = AF_INET6;

                    retVal = ::connect(
                        this->_platformSocket,
                        reinterpret_cast < sockaddr * > (& ipv6AddressData),
                        sizeof ( ipv6AddressData )
                    );

                    if ( retVal == 0 )
                        break;
                }

                if ( this->_protocolVersion == Socket::ProtocolVersion::INTERNET_PROTOCOL_VERSION_6_FORCED )
                    throw SocketException("Unable to connect to address through IPV6");

                this->_protocolVersion = ProtocolVersion::INTERNET_PROTOCOL_VERSION_4;
                this->close().open().connect(pack.first(), pack.second());

            } case ProtocolVersion::INTERNET_PROTOCOL_VERSION_4: {

                sockaddr_in ipv4AddressData{};

                ipv4AddressData.sin_addr.s_addr = inet_addr ( pack.first ().cStr () );
                ipv4AddressData.sin_port = htons ( pack.second () );
                ipv4AddressData.sin_family = AF_INET;

                int retVal = :: connect (
                    this->_platformSocket,
                    reinterpret_cast < sockaddr * > ( & ipv4AddressData ),
                    sizeof ( ipv4AddressData )
                );

                if ( retVal == Socket::UNIX_SOCKET_FUNCTION_ERROR )
                    throw SocketException("Unable to connect to address through IPV4");

                break;
            }
        }

#else

#error Socket::connect Unimplemented

#endif

        if ( this->_synchronizeSettingsAtConnectionStartup ) {

            try {

                this->_packetSize = this->readSize ();
                this->_packetSyncCount = this->readSize ();

                this->writeInt(1);

            } catch ( Exception const & e ) {
                throw SocketException ( "Synchronization of settings at connect initialization not acknowledged : "_s + e );
            }

        }

        return * this;
    }

private:
    inline static auto convertIPV4ToIPV6(List < String > const & addressSegments) noexcept(false) -> String {
        auto addressBits = Array < String > ( addressSegments );
        auto isBigEndian = []{ return htonl(47) == 47; };

        String const ipv4Identifier = "FFFF";

        auto idIndex = addressBits.index( ipv4Identifier );
        if ( idIndex != -1 )
            addressBits = addressBits.sub<Array<String>>(idIndex + 1);
        else
            addressBits.remove("", 2);

        if ( addressBits.size () > 3 )
            throw IllegalArgumentException ( "IPV6 Address conversion failed : "_s + addressBits.toString () +
                                             ", assumed format : ::IPV4Address[:port]" );

        if ( addressBits.size() == 1 ) {
            if ( addressBits[ 0 ].count ( '.' ) != 3 || addressBits[ 0 ].findFirstNotOf ( ".0123456789" ) != String::INVALID_POS )
                throw IllegalArgumentException ( "IPV6 Address conversion failed : "_s + addressBits.toString () +
                                                 ", assumed format : ::IPV4Address" );

            return addressBits[20];
        }

        if ( addressBits.size() == 2 ) {
            if ( addressBits[ 0 ].count ('.') == 0 ) {
                if ( addressBits[ 0 ].size() > 4 || addressBits[ 1 ].size() > 4 )
                    throw IllegalArgumentException ( "IPV6 Address conversion failed : "_s + addressBits.toString() +
                                                    ", assumed format : ::IPV4-1..2hex::IPV4-3..4hex -> to IPV4");

                union {
                    struct { uint16 first32, second32; };
                    struct { uint8 l1, l2, l3, l4; };
                } address { };

                address.first32 = (uint16)(int)Int::parse(addressBits[ 0 ], 16);
                address.second32 = (uint16)(int)Int::parse(addressBits[ 1 ], 16);

                if ( isBigEndian() )
                    return String::f("%d.%d.%d.%d", address.l1, address.l2, address.l3, address.l4);
                return String::f("%d.%d.%d.%d", address.l2, address.l1, address.l4, address.l3);
            }

            if ( addressBits[ 0 ].count ('.') != 3 || addressBits[ 0 ].findFirstNotOf ( ".0123456789" ) != String::INVALID_POS )
                throw IllegalArgumentException( "IPV6 Address conversion failed : "_s + addressBits.toString() +
                                                ", assumed format : ::IPV4:port");

            return String::f("%s:%s", addressBits[0].cStr(), addressBits[1].cStr());
        }

        if ( addressBits.size() == 3 ) {
            if ( addressBits[ 0 ].count ('.') == 0 ) {
                if ( addressBits[ 0 ].size() > 4 || addressBits[ 1 ].size() > 4 )
                    throw IllegalArgumentException ( "IPV6 Address conversion failed : "_s + addressBits.toString() +
                                                     ", assumed format : ::IPV4-1..2hex::IPV4-3..4hex -> to IPV4");

                union {
                    struct { uint16 first32, second32; };
                    struct { uint8 l1, l2, l3, l4; };
                } address {};

                address.first32 = (uint16)(int)Int::parse(addressBits[ 0 ], 16);
                address.second32 = (uint16)(int)Int::parse(addressBits[ 1 ], 16);

                if ( isBigEndian() )
                    return String::f("%d.%d.%d.%d:%s", address.l1, address.l2, address.l3, address.l4, addressBits[ 2 ].cStr());
                return String::f("%d.%d.%d.%d:%s", address.l2, address.l1, address.l4, address.l3, addressBits[ 2 ].cStr());
            }
        }

        throw IllegalArgumentException("IPV6 Address Conversion failed : "_s + addressBits.toString() + ", unknown format");
    }

    inline auto extractAddress ( String const & address ) noexcept(false) -> Pair < String, uint16 > {
        auto addressBits = address.split(':');
        String finalAddress;
        uint16 port = this->_port;

        if ( this->_protocolVersion == ProtocolVersion::INTERNET_PROTOCOL_VERSION_4 ) {
            if ( address.count(':') > 1 ) {
                finalAddress = std::move ( Socket::convertIPV4ToIPV6 ( addressBits ) );
                Index indexOfPortSeparator = finalAddress.findFirst (':');
                if ( indexOfPortSeparator != String::INVALID_POS ) {
                    finalAddress = std::move ( finalAddress.split ( ':' )[ 0 ] );
                    port = (uint16)(int)Int::parse(finalAddress.split (':')[1]);
                }
            } else if ( address.count(':') > 0 ) {
                auto unverifiedPort = Int::parse(addressBits.back());
                if ( unverifiedPort > Limits::U16_MAX )
                    throw IllegalArgumentException ( "Invalid TCP/IP Port : "_s + unverifiedPort.toString() );

                port = (uint16)(int)unverifiedPort;
                finalAddress = std :: move ( addressBits.front() );
            } else
                finalAddress = std :: move(addressBits.front());
        } else {
            if( ! addressBits.empty() && addressBits.size() <= 2 && addressBits[0].count ('.') == 3 ) {
                finalAddress = std::move(String::f("::FFFF:%s%s:%s%s",
                    Int::parse(addressBits[0].split ('.')[0]).toString(16).ljust(2, '0').cStr(),
                    Int::parse(addressBits[0].split ('.')[1]).toString(16).ljust(2, '0').cStr(),
                    Int::parse(addressBits[0].split ('.')[2]).toString(16).ljust(2, '0').cStr(),
                    Int::parse(addressBits[0].split ('.')[3]).toString(16).ljust(2, '0').cStr()
                ));

                if ( addressBits.size() == 2 )
                    port = (int) Int::parse(addressBits[1]);
            } else {
                finalAddress = addressBits
                        .sequence()
                        .fold(addressBits.size() < 8 ? ":" : ""_s, [](String const & s, String const & p){ return s + ":" + p; });
            }
        }

        return Pair < String, uint16 > { std :: move ( finalAddress ), port };
    }

public:

    inline auto close () noexcept (false) -> Socket & {

        if ( ! this->isOpen() )
            return * this;

#if defined(__CDS_Platform_Linux)

        auto retVal = ::close ( exchange ( this->_platformSocket, Socket::UNIX_INVALID_PLATFORM_SOCKET ) );
        if ( retVal == Socket::UNIX_SOCKET_FUNCTION_ERROR )
            throw SocketException("Socket Close Exception");

#else

#error Socket::close Unimplemented

#endif

        return * this;
    }

    inline auto bind ( uint16 port = 0 ) noexcept (false) -> Socket & {

        if ( port != 0 )
            this->_port = port;

#if defined(__CDS_Platform_Linux)

        switch ( this->_protocolVersion ) {
            case ProtocolVersion::INTERNET_PROTOCOL_NONE_SPECIFIED:
            case ProtocolVersion::INTERNET_PROTOCOL_VERSION_6:
            case ProtocolVersion::INTERNET_PROTOCOL_VERSION_6_FORCED: {

                int flag = 0x01;
                int retVal = :: setsockopt (
                        this->_platformSocket,
                        SOL_SOCKET,
                        SO_REUSEADDR,
                        & flag,
                        sizeof ( flag )
                );

                if ( retVal == Socket::UNIX_SOCKET_FUNCTION_ERROR ) {
                    if ( this->_protocolVersion == Socket::ProtocolVersion::INTERNET_PROTOCOL_VERSION_6_FORCED )
                        throw SocketException("Bind Exception on IPV6 : SetSocketOption Error");

                    this->_protocolVersion = Socket::ProtocolVersion::INTERNET_PROTOCOL_VERSION_4;
                    return this->close().open().bind();
                }

                sockaddr_in6 ipv6AddressInfo {};

                ipv6AddressInfo.sin6_family = AF_INET6;
                ipv6AddressInfo.sin6_addr = in6addr_any;
                ipv6AddressInfo.sin6_port = htons(this->_port);

                retVal = :: bind (
                    this->_platformSocket,
                    reinterpret_cast < sockaddr * > ( & ipv6AddressInfo ),
                    sizeof ( ipv6AddressInfo )
                );

                if ( retVal == Socket::UNIX_SOCKET_FUNCTION_ERROR ) {
                    if ( this->_protocolVersion == Socket::ProtocolVersion::INTERNET_PROTOCOL_VERSION_6_FORCED )
                        throw SocketException("Bind Exception on IPV6");

                    this->_protocolVersion = Socket::ProtocolVersion::INTERNET_PROTOCOL_VERSION_4;
                    return this->close().open().bind();
                }

                return * this;

            } case ProtocolVersion::INTERNET_PROTOCOL_VERSION_4: {

                int flag = 0x01;
                int retVal = :: setsockopt (
                        this->_platformSocket,
                        SOL_SOCKET,
                        SO_REUSEADDR,
                        & flag,
                        sizeof ( flag )
                );

                if ( retVal == Socket::UNIX_SOCKET_FUNCTION_ERROR )
                    throw SocketException("Bind Exception on IPV4 : SetSocketOption Error");

                sockaddr_in ipv6AddressInfo {};

                ipv6AddressInfo.sin_family = AF_INET;
                ipv6AddressInfo.sin_addr.s_addr = htonl(INADDR_ANY);
                ipv6AddressInfo.sin_port = htons(this->_port);

                retVal = :: bind (
                        this->_platformSocket,
                        reinterpret_cast < sockaddr * > ( & ipv6AddressInfo ),
                        sizeof ( ipv6AddressInfo )
                );

                if ( retVal == Socket::UNIX_SOCKET_FUNCTION_ERROR )
                    throw SocketException("Bind Exception on IPV4");

                return * this;
            }
        }

#else

#error Socket::bind Unimplemented

#endif

    }

    inline auto listen ( int queueSize = 0 ) noexcept (false) -> Socket & { // NOLINT(misc-no-recursion)
        if ( queueSize == 0 ) queueSize = Socket::DEFAULT_CLIENT_QUEUE_SIZE;

#if defined(__CDS_Platform_Linux)

        if ( Socket::UNIX_SOCKET_FUNCTION_ERROR == :: listen ( this->_platformSocket, queueSize ) ) {
            if ( this->_protocolVersion == Socket::ProtocolVersion::INTERNET_PROTOCOL_VERSION_6_FORCED )
                throw SocketException("Listen Exception on IPV6");
            if ( this->_protocolVersion == Socket::ProtocolVersion::INTERNET_PROTOCOL_VERSION_4 )
                throw SocketException("Listen Exception on IPV4");

            this->_protocolVersion = Socket::ProtocolVersion::INTERNET_PROTOCOL_VERSION_4;
            return this->close().open().bind (this->_port).listen (queueSize);
        }

        return * this;

#else

#error Socket::listen Unimplemented

#endif

    }

private:

#if defined(__CDS_Platform_Linux)

    struct LastAddressContainer {
    public:
        sockaddr * pLastSocketAddress { nullptr };
        socklen_t lastSocketAddressSize { 0 };
        ProtocolVersion lastProtocolType { ProtocolVersion::INTERNET_PROTOCOL_NONE_SPECIFIED };

        inline LastAddressContainer() noexcept = default;

        inline ~LastAddressContainer() noexcept {
            delete this->pLastSocketAddress;
        }

        inline auto specifyType ( ProtocolVersion protocolVersion ) noexcept -> void {
            switch ( protocolVersion ) {
                case ProtocolVersion::INTERNET_PROTOCOL_NONE_SPECIFIED:
                case ProtocolVersion::INTERNET_PROTOCOL_VERSION_6:
                case ProtocolVersion::INTERNET_PROTOCOL_VERSION_6_FORCED:
                    if ( this->lastProtocolType == ProtocolVersion::IPV6 )
                        return;

                case ProtocolVersion::INTERNET_PROTOCOL_VERSION_4:
                    if ( this->lastProtocolType == ProtocolVersion::IPV4 )
                        return;
            }

            if ( this->pLastSocketAddress != nullptr )
                delete exchange(this->pLastSocketAddress, nullptr);

            switch ( protocolVersion ) {
                case ProtocolVersion::INTERNET_PROTOCOL_NONE_SPECIFIED:
                case ProtocolVersion::INTERNET_PROTOCOL_VERSION_6:
                case ProtocolVersion::INTERNET_PROTOCOL_VERSION_6_FORCED:
                    this->pLastSocketAddress = reinterpret_cast < sockaddr * > (new sockaddr_in6);
                    this->lastSocketAddressSize = sizeof ( sockaddr_in6 );
                    this->lastProtocolType = ProtocolVersion::IPV6;

                    return;
                case ProtocolVersion::INTERNET_PROTOCOL_VERSION_4:

                    this->pLastSocketAddress = reinterpret_cast < sockaddr * > (new sockaddr_in);
                    this->lastSocketAddressSize = sizeof ( sockaddr_in );
                    this->lastProtocolType = ProtocolVersion::IPV4;
            }
        }
    };

    LastAddressContainer * pLastAddressObtainedContainer { nullptr };

#else

#error Socket::LastAddressContainer Unimplemented

#endif

public:
    inline auto accept () noexcept (false) -> Socket {

#if defined(__CDS_Platform_Linux)

        static LastAddressContainer lastAddressContainer;
        lastAddressContainer.specifyType (this->_protocolVersion);

        if ( this->pLastAddressObtainedContainer == nullptr )
            this->pLastAddressObtainedContainer = & lastAddressContainer;

        int retVal = :: accept (
            this->_platformSocket,
            lastAddressContainer.pLastSocketAddress,
            & lastAddressContainer.lastSocketAddressSize
        );

        if ( retVal == Socket::UNIX_SOCKET_FUNCTION_ERROR )
            throw SocketException( "Accept Exception." );

#else

#error Socket::accept Unimplemented

#endif

        auto clientSocket = Socket(retVal);

        if ( this->_synchronizeSettingsAtConnectionStartup ) {

            int acknowledge = 0;

            try {
                clientSocket.writeSize ( this->_packetSize );
                clientSocket.writeSize ( this->_packetSyncCount );

                acknowledge = clientSocket.readInt ();
            } catch ( Exception const & e ) {
                throw SocketException("Synchronization of settings at connect initialization not acknowledged : "_s + e);
            }

            if ( acknowledge != 1 )
                throw SocketException("Synchronization of settings at connect initialization not acknowledged : Client Response Not OK");

        }

        return std::move(clientSocket);
    }

    __CDS_MaybeUnused inline auto writeBytes ( byte const * pBuffer, Size count ) noexcept (false) -> Socket & {

#if defined(__CDS_Platform_Linux)

        auto written = :: write ( this->_platformSocket, pBuffer, count );

        if ( Socket::UNIX_SOCKET_FUNCTION_ERROR == written )
            throw SocketException("Socket writeBytes Exception");
        if ( written != count )
            throw SocketException(String::f("Unable to completely write message : intended : %d, sent : %d", count, written) );

        return * this;

#else

#error Socket::writeBytes Unimplemented

#endif

    }

    __CDS_MaybeUnused inline auto readBytes ( byte * pBuffer, Size intendedForRead ) noexcept (false) -> Socket & {

#if defined(__CDS_Platform_Linux)

        auto read = :: read ( this->_platformSocket, pBuffer, intendedForRead );

        if ( Socket::UNIX_SOCKET_FUNCTION_ERROR == read )
            throw SocketException("Socket readBytes Exception");

        if ( Socket::UNIX_SOCKET_READ_DISCONNECT == read )
            throw SocketDisconnect();

        if ( read != intendedForRead )
            throw SocketException ("Read Bytes count Different from Intended Count");

        return * this;

#else

#error Socket::readBytes Unimplemented

#endif

    }


    __CDS_MaybeUnused inline auto writeInt8 ( sint8 value ) noexcept (false) -> Socket & {
        return this->writeBytes( reinterpret_cast < byte const * > ( & value ), sizeof (value) );
    }

    __CDS_MaybeUnused inline auto writeInt16 ( sint16 value ) noexcept (false) -> Socket & {
        return this->writeBytes( reinterpret_cast < byte const * > ( & value ), sizeof (value) );
    }

    __CDS_MaybeUnused inline auto writeInt32 ( sint32 value ) noexcept (false) -> Socket & {
        return this->writeBytes( reinterpret_cast < byte const * > ( & value ), sizeof (value) );
    }

    __CDS_MaybeUnused inline auto writeInt64 ( sint64 value ) noexcept (false) -> Socket & {
        return this->writeBytes( reinterpret_cast < byte const * > ( & value ), sizeof (value) );
    }

    __CDS_MaybeUnused inline auto writeUInt8 ( uint8 value ) noexcept (false) -> Socket & {
        return this->writeBytes( reinterpret_cast < byte const * > ( & value ), sizeof (value) );
    }

    __CDS_MaybeUnused inline auto writeUInt16 ( uint16 value ) noexcept (false) -> Socket & {
        return this->writeBytes( reinterpret_cast < byte const * > ( & value ), sizeof (value) );
    }

    __CDS_MaybeUnused inline auto writeUInt32 ( uint32 value ) noexcept (false) -> Socket & {
        return this->writeBytes( reinterpret_cast < byte const * > ( & value ), sizeof (value) );
    }

    __CDS_MaybeUnused inline auto writeUInt64 ( uint64 value ) noexcept (false) -> Socket & {
        return this->writeBytes( reinterpret_cast < byte const * > ( & value ), sizeof (value) );
    }


    __CDS_MaybeUnused inline auto writeInt ( int value ) noexcept (false) -> Socket & {
        return this->writeInt32( value );
    }

    __CDS_MaybeUnused inline auto writeSize ( Size value ) noexcept (false) -> Socket & {
        return this->writeUInt64 (value);
    }

    __CDS_MaybeUnused inline auto writeString ( String const & string ) noexcept (false) -> Socket & {
        auto packetCount = string.size() / this->_packetSize;
        if ( string.size() % this->_packetSize != 0 )
            ++ packetCount;

        this->writeSize ( string.size() );

        Size offset = 0U;

        for ( Size i = 0; i < packetCount; ++ i ) {
            this->writeBytes (
                reinterpret_cast < byte const * > ( string.cStr() ) + offset,
                std::min ( this->_packetSize, string.size() - offset)
            );

            offset += this->_packetSize;

            if ( ( i + 1 ) % this->_packetSyncCount == 0 ) {
                int ack = this->readInt();
                if ( ack != 1 ) throw SocketException("Large Data Write Synchronize Error");
            }
        }

        return * this;
    }


    __CDS_NoDiscard __CDS_MaybeUnused auto readInt8 () noexcept(false) -> sint8 {
        sint8 value;
        this->readBytes(reinterpret_cast < byte * > ( & value ), sizeof(value));
        return value;
    }

    __CDS_NoDiscard __CDS_MaybeUnused auto readInt16 () noexcept(false) -> sint16 {
        sint16 value;
        this->readBytes(reinterpret_cast < byte * > ( & value ), sizeof(value));
        return value;
    }

    __CDS_NoDiscard __CDS_MaybeUnused auto readInt32 () noexcept(false) -> sint32 {
        sint32 value;
        this->readBytes(reinterpret_cast < byte * > ( & value ), sizeof(value));
        return value;
    }

    __CDS_NoDiscard __CDS_MaybeUnused auto readInt64 () noexcept(false) -> sint64 {
        sint64 value;
        this->readBytes(reinterpret_cast < byte * > ( & value ), sizeof(value));
        return value;
    }

    __CDS_NoDiscard __CDS_MaybeUnused auto readUInt8 () noexcept(false) -> uint8 {
        uint8 value;
        this->readBytes(reinterpret_cast < byte * > ( & value ), sizeof(value));
        return value;
    }

    __CDS_NoDiscard __CDS_MaybeUnused auto readUInt16 () noexcept(false) -> uint16 {
        uint16 value;
        this->readBytes(reinterpret_cast < byte * > ( & value ), sizeof(value));
        return value;
    }

    __CDS_NoDiscard __CDS_MaybeUnused auto readUInt32 () noexcept(false) -> uint32 {
        uint32 value;
        this->readBytes(reinterpret_cast < byte * > ( & value ), sizeof(value));
        return value;
    }

    __CDS_NoDiscard __CDS_MaybeUnused auto readUInt64 () noexcept(false) -> uint64 {
        uint64 value;
        this->readBytes(reinterpret_cast < byte * > ( & value ), sizeof(value));
        return value;
    }


    __CDS_NoDiscard __CDS_MaybeUnused auto readInt () noexcept (false) -> int {
        return this->readInt32();
    }

    __CDS_NoDiscard __CDS_MaybeUnused auto readSize () noexcept (false) -> Size {
        return this->readUInt64();
    }

    __CDS_NoDiscard __CDS_MaybeUnused auto readString () noexcept (false) -> String {
        Size originalSize = this->readSize(), offset = 0U;
        Size packetCount = originalSize / this->_packetSize;

        if ( originalSize % this->_packetSize != 0 )
            ++ packetCount;

        String buffer;
        buffer.resize(originalSize);
        buffer._l = originalSize;

        for ( Size i = 0; i < packetCount; ++ i ) {
            this->readBytes (
                reinterpret_cast < byte * > (buffer.data()) + offset,
                std::min(this->_packetSize, originalSize - offset)
            );

            offset += this->_packetSize;

            if ( (i + 1) % this->_packetSyncCount == 0 ) {
                this->writeInt(1);
            }
        }

        return std :: move ( buffer );
    }

    __CDS_NoDiscard constexpr static auto protocolVersionToString (ProtocolVersion protocolVersion) noexcept -> StringLiteral {
        switch ( protocolVersion ) {
            case ProtocolVersion::INTERNET_PROTOCOL_NONE_SPECIFIED:     return "Protocol Version Automatic Detection";
            case ProtocolVersion::INTERNET_PROTOCOL_VERSION_4:          return "Internet Protocol Version 4 (IPV4, Preferred)";
            case ProtocolVersion::INTERNET_PROTOCOL_VERSION_6:          return "Internet Protocol Version 6 (IPV6, Preferred)";
            case ProtocolVersion::INTERNET_PROTOCOL_VERSION_6_FORCED:   return "Internet Protocol Version 6 (IPV6, Forced)";
            default:                                                    return "Unknown Protocol Version Handler";
        }
    }

    __CDS_NoDiscard __CDS_cpplang_ConstexprDestructor auto toString () const noexcept -> String override {
        return "Socket "_s +

#if defined(__CDS_Platform_Linux)

            "{ platformSocket = " + this->_platformSocket +
            ", platform = " + __CDS_Platform +

#else

#warning Socket::toString Missing Platform Specific Settings

#endif

            ", internetProtocolVersion = " + Socket::protocolVersionToString (this->_protocolVersion) +
            ", usedPort = " + this->_port +
            ", settings " +
            "{ packetSize = " + this->_packetSize +
            ", packetSyncCountLargeData = " + this->_packetSyncCount +
            ", syncAtConnectOrAccept = " + (this->_synchronizeSettingsAtConnectionStartup ? "true" : "false") +
            " }" +
            " }";
    }

    __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto hash() const noexcept -> Index override {

#if defined (__CDS_Platform_Linux)

        return dataTypes::hash<int> ( this->_platformSocket );

#else

#error Socket::hash Unimplemented

#endif
    }

    __CDS_NoDiscard inline auto copy () const noexcept -> Socket * override {

#if defined (__CDS_Platform_Linux)

        return new Socket(dup(this->_platformSocket));

#else

#error Socket::copy Unimplemented

#endif

    }

    __CDS_NoDiscard auto equals(Object const & o) const noexcept -> bool override {
        if ( this == & o ) return true;
        auto p = dynamic_cast < decltype (this) > ( & o );
        if ( p == nullptr ) return false;

#if defined(__CDS_Platform_Linux)

        return this->_platformSocket == p->_platformSocket;

#else

#error Socket::equals Unimplemented

#endif
    }

    inline ~Socket () noexcept override {
        this->close();
    }

    Socket(Socket const & socket) noexcept :

#if defined(__CDS_Platform_Linux)

            _platformSocket(dup(socket._platformSocket)),

#else

#error Socket::CopyConstructor Undefined

#endif

            _port(socket._port),
            _packetSize(socket._packetSize),
            _protocolVersion(socket._protocolVersion),
            _packetSyncCount(socket._packetSyncCount),
            _synchronizeSettingsAtConnectionStartup(socket._synchronizeSettingsAtConnectionStartup) {

    }

    auto operator = (Socket const & socket) noexcept -> Socket & {
        if ( & socket == this ) return * this;

        this->close();

#if defined(__CDS_Platform_Linux)

            this->_platformSocket = dup(socket._platformSocket);

#else

#error Socket::CopyOperator Undefined

#endif

            this->_port = socket._port;
            this->_packetSize = socket._packetSize;
            this->_protocolVersion = socket._protocolVersion;
            this->_packetSyncCount = socket._packetSyncCount;
            this->_synchronizeSettingsAtConnectionStartup = socket._synchronizeSettingsAtConnectionStartup;

            return * this;
    }


    Socket(Socket && socket) noexcept :

#if defined(__CDS_Platform_Linux)

            _platformSocket(exchange(socket._platformSocket, Socket::UNIX_INVALID_PLATFORM_SOCKET)),

#else

#error Socket::MoveConstructor Undefined

#endif

            _port(exchange(socket._port, Socket::DEFAULT_PORT)),
            _packetSize(exchange(socket._packetSize, Socket::DEFAULT_PACKET_SIZE)),
            _protocolVersion(exchange(socket._protocolVersion, Socket::ProtocolVersion::AUTO)),
            _packetSyncCount(exchange(socket._packetSyncCount, Socket::DEFAULT_PACKET_SYNC_COUNT)),
            _synchronizeSettingsAtConnectionStartup(exchange(socket._synchronizeSettingsAtConnectionStartup, true)) {

    }

    auto operator = (Socket && socket) noexcept -> Socket & {
        if ( & socket == this ) return * this;

        this->close();

#if defined(__CDS_Platform_Linux)

        this->_platformSocket = exchange(socket._platformSocket, Socket::UNIX_INVALID_PLATFORM_SOCKET);

#else

#error Socket::MoveOperator Undefined

#endif

        this->_port = exchange(socket._port, Socket::DEFAULT_PORT);
        this->_packetSize = exchange(socket._packetSize, Socket::DEFAULT_PACKET_SIZE);
        this->_protocolVersion = exchange(socket._protocolVersion, Socket::ProtocolVersion::AUTO);
        this->_packetSyncCount = exchange(socket._packetSyncCount, Socket::DEFAULT_PACKET_SYNC_COUNT);
        this->_synchronizeSettingsAtConnectionStartup = exchange(socket._synchronizeSettingsAtConnectionStartup, true);

        return * this;
    }
};

class ServerSocket : public Socket {
public:
    explicit ServerSocket ( uint16 port, ProtocolVersion protocolVersion = Socket::ProtocolVersion::AUTO ) noexcept (false) : Socket(protocolVersion) {
        this->bind (port).listen ();
    }
};

#endif //CDS_SOCKET_HPP
