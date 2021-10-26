//
// Created by loghin on 07.10.2021.
//

#ifndef CDS_SOCKET_HPP
#define CDS_SOCKET_HPP

#include <CDS/Platform>

#if defined(__CDS_Platform_Linux)

#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#elif defined(__CDS_Platform_Microsoft_Windows)

#include <cstdio>
#include <winsock2.h>
#include <windows.h>
#include <ws2tcpip.h>

#else

#error Not Implemented : CDS Socket Header

#endif

#include <CDS/Object>
#include <CDS/Exception>
#include <CDS/Pair>
#include <CDS/LinkedList>
#include <CDS/Utility>

class SocketException : public Exception {
public:
    __CDS_OptimalInline explicit SocketException(String const & message) noexcept : Exception(message) { }
    __CDS_OptimalInline SocketException () noexcept : SocketException ("Unspecified Socket Exception") { }
};

class SocketDisconnect : public SocketException {
public:
    __CDS_OptimalInline SocketDisconnect () noexcept : SocketException ("Socket Disconnected") { }
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
        FORCE_IPV6 __CDS_MaybeUnused = INTERNET_PROTOCOL_VERSION_6_FORCED
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

    constexpr static bool socketDuplicateExceptSpec = true;

#elif defined(__CDS_Platform_Microsoft_Windows)

    using PlatformSocket = SOCKET;

    constexpr static PlatformSocket WIN32_INVALID_PLATFORM_SOCKET = INVALID_SOCKET;
    constexpr static int WIN32_SOCKET_FUNCTION_ERROR = SOCKET_ERROR;
    constexpr static int WIN32_SOCKET_DISCONNECT = 0;

    constexpr static Size PLATFORM_DEFAULT_PACKET_SIZE = 1024U;
    constexpr static Size PLATFORM_DEFAULT_CLIENT_QUEUE_SIZE = 256U;
    constexpr static Size PLATFORM_DEFAULT_PACKET_SYNC_COUNT = 4U;

    constexpr static bool socketDuplicateExceptSpec = false;

    struct Win32WSAContainerType {
    public:
        WSADATA windowsSocketsApplicationLibraryData {};

        __CDS_OptimalInline Win32WSAContainerType () noexcept (false) {
            if ( WSAStartup ( MAKEWORD(2, 2), & this->windowsSocketsApplicationLibraryData ) != 0 )
                throw SocketException ( "Win32 Exception : WinSock2 Failed to Load, WSALastError : "_s + WSAGetLastError() );
        }

        __CDS_OptimalInline ~Win32WSAContainerType () noexcept {
            WSACleanup();
        }

        __CDS_OptionalInline static auto lastWSAError () noexcept -> StringLiteral {
            switch (WSAGetLastError()) {
                case WSAEINTR:                  return "WSAEINTR";
                case WSAEBADF:                  return "WSAEBADF";
                case WSAEACCES:                 return "WSAEACCES";
                case WSAEFAULT:                 return "WSAEFAULT";
                case WSAEINVAL:                 return "WSAEINVAL";
                case WSAEMFILE:                 return "WSAEMFILE";
                case WSAEWOULDBLOCK:            return "WSAEWOULDBLOCK";
                case WSAEINPROGRESS:            return "WSAEINPROGRESS";
                case WSAEALREADY:               return "WSAEALREADY";
                case WSAENOTSOCK:               return "WSAENOTSOCK";
                case WSAEDESTADDRREQ:           return "WSAEDESTADDRREQ";
                case WSAEMSGSIZE:               return "WSAEMSGSIZE";
                case WSAEPROTOTYPE:             return "WSAEPROTOTYPE";
                case WSAENOPROTOOPT:            return "WSAENOPROTOOPT";
                case WSAEPROTONOSUPPORT:        return "WSAEPROTONOSUPPORT";
                case WSAESOCKTNOSUPPORT:        return "WSAESOCKTNOSUPPORT";
                case WSAEOPNOTSUPP:             return "WSAEOPNOTSUPP";
                case WSAEPFNOSUPPORT:           return "WSAEPFNOSUPPORT";
                case WSAEAFNOSUPPORT:           return "WSAEAFNOSUPPORT";
                case WSAEADDRINUSE:             return "WSAEADDRINUSE";
                case WSAEADDRNOTAVAIL:          return "WSAEADDRNOTAVAIL";
                case WSAENETDOWN:               return "WSAENETDOWN";
                case WSAENETUNREACH:            return "WSAENETUNREACH";
                case WSAENETRESET:              return "WSAENETRESET";
                case WSAECONNABORTED:           return "WSAECONNABORTED";
                case WSAECONNRESET:             return "WSAECONNRESET";
                case WSAENOBUFS:                return "WSAENOBUFS";
                case WSAEISCONN:                return "WSAEISCONN";
                case WSAENOTCONN:               return "WSAENOTCONN";
                case WSAESHUTDOWN:              return "WSAESHUTDOWN";
                case WSAETOOMANYREFS:           return "WSAETOOMANYREFS";
                case WSAETIMEDOUT:              return "WSAETIMEDOUT";
                case WSAECONNREFUSED:           return "WSAECONNREFUSED";
                case WSAELOOP:                  return "WSAELOOP";
                case WSAENAMETOOLONG:           return "WSAENAMETOOLONG";
                case WSAEHOSTDOWN:              return "WSAEHOSTDOWN";
                case WSAEHOSTUNREACH:           return "WSAEHOSTUNREACH";
                case WSAENOTEMPTY:              return "WSAENOTEMPTY";
                case WSAEPROCLIM:               return "WSAEPROCLIM";
                case WSAEUSERS:                 return "WSAEUSERS";
                case WSAEDQUOT:                 return "WSAEDQUOT";
                case WSAESTALE:                 return "WSAESTALE";
                case WSAEREMOTE:                return "WSAEREMOTE";
                case WSASYSNOTREADY:            return "WSASYSNOTREADY";
                case WSAVERNOTSUPPORTED:        return "WSAVERNOTSUPPORTED";
                case WSANOTINITIALISED:         return "WSANOTINITIALISED";
                case WSAEDISCON:                return "WSAEDISCON";
                case WSAENOMORE:                return "WSAENOMORE";
                case WSAECANCELLED:             return "WSAECANCELLED";
                case WSAEINVALIDPROCTABLE:      return "WSAEINVALIDPROCTABLE";
                case WSAEINVALIDPROVIDER:       return "WSAEINVALIDPROVIDER";
                case WSAEPROVIDERFAILEDINIT:    return "WSAEPROVIDERFAILEDINIT";
                case WSASYSCALLFAILURE:         return "WSASYSCALLFAILURE";
                case WSASERVICE_NOT_FOUND:      return "WSASERVICE_NOT_FOUND";
                case WSATYPE_NOT_FOUND:         return "WSATYPE_NOT_FOUND";
                case WSA_E_NO_MORE:             return "WSA_E_NO_MORE";
                case WSA_E_CANCELLED:           return "WSA_E_CANCELLED";
                case WSAEREFUSED:               return "WSAEREFUSED";
                case WSAHOST_NOT_FOUND:         return "WSAHOST_NOT_FOUND";
                case WSATRY_AGAIN:              return "WSATRY_AGAIN";
                case WSANO_RECOVERY:            return "WSANO_RECOVERY";
                case WSANO_DATA:                return "WSANO_DATA";
                case WSA_QOS_RECEIVERS:         return "WSA_QOS_RECEIVERS";
                case WSA_QOS_SENDERS:           return "WSA_QOS_SENDERS";
                case WSA_QOS_NO_RECEIVERS:      return "WSA_QOS_NO_RECEIVERS";
                case WSA_QOS_NO_SENDERS:        return "WSA_QOS_NO_SENDERS";
                case WSA_QOS_REQUEST_CONFIRMED: return "WSA_QOS_REQUEST_CONFIRMED";
                case WSA_QOS_ADMISSION_FAILURE: return "WSA_QOS_ADMISSION_FAILURE";
                case WSA_QOS_POLICY_FAILURE:    return "WSA_QOS_POLICY_FAILURE";
                case WSA_QOS_BAD_STYLE:         return "WSA_QOS_BAD_STYLE";
                case WSA_QOS_BAD_OBJECT:        return "WSA_QOS_BAD_OBJECT";
                case WSA_QOS_TRAFFIC_CTRL_ERROR:return "WSA_QOS_TRAFFIC_CTRL_ERROR";
                case WSA_QOS_GENERIC_ERROR:     return "WSA_QOS_GENERIC_ERROR";
                case WSA_QOS_ESERVICETYPE:      return "WSA_QOS_ESERVICETYPE";
                case WSA_QOS_EFLOWSPEC:         return "WSA_QOS_EFLOWSPEC";
                case WSA_QOS_EPROVSPECBUF:      return "WSA_QOS_EPROVSPECBUF";
                case WSA_QOS_EFILTERSTYLE:      return "WSA_QOS_EFILTERSTYLE";
                case WSA_QOS_EFILTERTYPE:       return "WSA_QOS_EFILTERTYPE";
                case WSA_QOS_EFILTERCOUNT:      return "WSA_QOS_EFILTERCOUNT";
                case WSA_QOS_EOBJLENGTH:        return "WSA_QOS_EOBJLENGTH";
                case WSA_QOS_EFLOWCOUNT:        return "WSA_QOS_EFLOWCOUNT";
                case WSA_QOS_EUNKNOWNPSOBJ:     return "WSA_QOS_EUNKNOWNPSOBJ";
//                case WSA_QOS_EUNKOWNPSOBJ:      return "WSA_QOS_EUNKOWNPSOBJ";
                case WSA_QOS_EPOLICYOBJ:        return "WSA_QOS_EPOLICYOBJ";
                case WSA_QOS_EFLOWDESC:         return "WSA_QOS_EFLOWDESC";
                case WSA_QOS_EPSFLOWSPEC:       return "WSA_QOS_EPSFLOWSPEC";
                case WSA_QOS_EPSFILTERSPEC:     return "WSA_QOS_EPSFILTERSPEC";
                case WSA_QOS_ESDMODEOBJ:        return "WSA_QOS_ESDMODEOBJ";
                case WSA_QOS_ESHAPERATEOBJ:     return "WSA_QOS_ESHAPERATEOBJ";
                case WSA_QOS_RESERVED_PETYPE:   return "WSA_QOS_RESERVED_PETYPE";

                default:                        return "WSA Unknown Error";
            }
        }
    };

    PlatformSocket _platformSocket { Socket::WIN32_INVALID_PLATFORM_SOCKET };

#else

#error Object-Socket Not Implemented

#endif

    constexpr static Size DEFAULT_PACKET_SIZE = Socket::PLATFORM_DEFAULT_PACKET_SIZE;
    constexpr static Size DEFAULT_CLIENT_QUEUE_SIZE = Socket::PLATFORM_DEFAULT_CLIENT_QUEUE_SIZE;
    constexpr static uint16 DEFAULT_PORT = 8080;
    constexpr static Size DEFAULT_PACKET_SYNC_COUNT = Socket::PLATFORM_DEFAULT_PACKET_SYNC_COUNT;

    Size            _packetSize         { Socket::DEFAULT_PACKET_SIZE };
    Size            _packetSyncCount    { Socket::DEFAULT_PACKET_SYNC_COUNT };

    bool            _synchronizeSettingsAtConnectionStartup { true };


    Size            _port               { Socket::DEFAULT_PORT };
    ProtocolVersion _protocolVersion    { Socket::ProtocolVersion::IPV4 };

public:

    __CDS_NoDiscard constexpr auto isOpen () const noexcept -> bool {

#if defined(__CDS_Platform_Linux)

        return this->_platformSocket != Socket::UNIX_INVALID_PLATFORM_SOCKET;

#elif defined(__CDS_Platform_Microsoft_Windows)

        return this->_platformSocket != Socket::WIN32_INVALID_PLATFORM_SOCKET;

#else

#error Socket::isOpen Not Implemented

#endif

    }


    __CDS_OptionalInline auto open () noexcept (false) -> Socket & {

#if defined(__CDS_Platform_Microsoft_Windows)

        static Win32WSAContainerType container;

#endif

        if ( this->isOpen() ) return * this;

        switch ( this->_protocolVersion ) {

            case ProtocolVersion::INTERNET_PROTOCOL_NONE_SPECIFIED:
            case ProtocolVersion::INTERNET_PROTOCOL_VERSION_6:
            case ProtocolVersion::INTERNET_PROTOCOL_VERSION_6_FORCED:

                if ( this->_protocolVersion == ProtocolVersion::AUTO )
                    this->_protocolVersion = ProtocolVersion::INTERNET_PROTOCOL_VERSION_6;

#if defined(__CDS_Platform_Linux)

                this->_platformSocket = :: socket( AF_INET6, SOCK_STREAM, IPPROTO_TCP);

                if ( this->_platformSocket != Socket::UNIX_SOCKET_FUNCTION_ERROR )
                    return * this;

                if ( this->_protocolVersion == ProtocolVersion::INTERNET_PROTOCOL_VERSION_6_FORCED )
                    throw SocketException ( "Unable to open Socket on IPV6");

#elif defined(__CDS_Platform_Microsoft_Windows)

                this->_platformSocket = :: socket ( AF_INET6, SOCK_STREAM, IPPROTO_TCP );

                if ( this->_platformSocket != Socket::WIN32_INVALID_PLATFORM_SOCKET )
                    return * this;

                if ( this->_protocolVersion == ProtocolVersion::INTERNET_PROTOCOL_VERSION_6_FORCED )
                    throw SocketException ( "Unable to open Socket on IPV6, WSALastError : "_s + WSAGetLastError() + ", name = " + Socket::Win32WSAContainerType::lastWSAError() );

#else

#error Socket::open Not Implemented

#endif

                this->close();

            case ProtocolVersion::INTERNET_PROTOCOL_VERSION_4:

#if defined(__CDS_Platform_Linux)

                this->_platformSocket = socket( AF_INET, SOCK_STREAM, IPPROTO_TCP);

                if ( this->_platformSocket != Socket::UNIX_SOCKET_FUNCTION_ERROR )
                    return * this;

                throw SocketException ( "Unable to open Socket on IPV4" );

#elif defined(__CDS_Platform_Microsoft_Windows)

                this->_platformSocket = :: socket ( AF_INET, SOCK_STREAM, 0 );

                if ( this->_platformSocket != Socket::WIN32_INVALID_PLATFORM_SOCKET )
                    return * this;

                throw SocketException ( "Unable to open Socket on IPV4, WSALastError : "_s + WSAGetLastError() + ", name = " + Socket::Win32WSAContainerType::lastWSAError() );

#else

#error Socket::open Unimplemented

#endif

        }

        return * this;
    }

    __CDS_OptimalInline explicit Socket ( ProtocolVersion protocolVersion = ProtocolVersion::IPV4 ) noexcept (false) :
            _protocolVersion( protocolVersion) {

        this->open();
    }

    constexpr explicit Socket ( PlatformSocket const & platformSocket ) noexcept : _platformSocket( platformSocket) {

    }

    __CDS_OptimalInline explicit Socket ( String const & address, ProtocolVersion protocolVersion = ProtocolVersion::IPV4 ) noexcept (false) :
            _protocolVersion(protocolVersion) {

        this->open().connect( this->extractAddress (  address ) );
    }

    __CDS_OptimalInline explicit Socket ( String const & address, uint16 port, ProtocolVersion protocolVersion = ProtocolVersion::IPV4 ) noexcept (false) :
            _protocolVersion(protocolVersion),
            _port(port) {

        this->open().connect( this->extractAddress ( address ) );
    }

    __CDS_OptimalInline auto connect ( String const & address ) noexcept (false) -> Socket & {
        return this->connect( this->extractAddress(  address ) );
    }

    __CDS_OptimalInline auto connect ( String const & address, uint16 port ) noexcept (false) -> Socket & { // NOLINT(misc-no-recursion)
        this->_port = port;
        return this->connect( Pair < String, uint16 > ( std::move(this->extractAddress(address).first()), port ) );
    }

private:
    __CDS_OptionalInline auto connect ( Pair < String, uint16 > const & pack ) noexcept(false) -> Socket & { // NOLINT(misc-no-recursion)

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

#elif defined(__CDS_Platform_Microsoft_Windows)

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
                    throw SocketException("Unable to connect to address through IPV6. WSALastError : "_s + WSAGetLastError() + ", name = " + Socket::Win32WSAContainerType::lastWSAError());

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

                if ( retVal < 0 )
                    throw SocketException("Unable to connect to address through IPV4. WSALastError : "_s + WSAGetLastError() + ", name = " + Socket::Win32WSAContainerType::lastWSAError());

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
    __CDS_OptionalInline static auto convertIPV4ToIPV6(List < String > const & addressSegments) noexcept(false) -> String {
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

    __CDS_OptionalInline auto extractAddress ( String const & address ) noexcept(false) -> Pair < String, uint16 > {
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
                        .fold(addressBits.size() < 8 ? ":" : ""_s, [](String const & s, String const & p){
                            return s + ":" + p;
                        });
            }
        }

        return Pair < String, uint16 > { std :: move ( finalAddress ), port };
    }

public:

    __CDS_OptimalInline auto close () noexcept (false) -> Socket & {

        if ( ! this->isOpen() )
            return * this;

#if defined(__CDS_Platform_Linux)

        auto retVal = ::close ( Utility::exchange ( this->_platformSocket, Socket::UNIX_INVALID_PLATFORM_SOCKET ) );
        if ( retVal == Socket::UNIX_SOCKET_FUNCTION_ERROR )
            throw SocketException("Socket Close Exception");

        this->_platformSocket = Socket::UNIX_INVALID_PLATFORM_SOCKET;

#elif defined(__CDS_Platform_Microsoft_Windows)

        auto retVal = :: closesocket ( this->_platformSocket );
        if ( retVal != 0 )
            throw SocketException ("Socket Close Exception");

        this->_platformSocket = Socket::WIN32_INVALID_PLATFORM_SOCKET;

#else

#error Socket::close Unimplemented

#endif

        return * this;
    }

    __CDS_OptionalInline auto bind ( uint16 port = 0 ) noexcept (false) -> Socket & {

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

                sockaddr_in ipv4AddressInfo {};

                ipv4AddressInfo.sin_family = AF_INET;
                ipv4AddressInfo.sin_addr.s_addr = htonl(INADDR_ANY);
                ipv4AddressInfo.sin_port = htons(this->_port);

                retVal = :: bind (
                        this->_platformSocket,
                        reinterpret_cast < sockaddr * > ( & ipv4AddressInfo ),
                        sizeof ( ipv4AddressInfo )
                );

                if ( retVal == Socket::UNIX_SOCKET_FUNCTION_ERROR )
                    throw SocketException("Bind Exception on IPV4");

                return * this;
            }
        }

#elif defined(__CDS_Platform_Microsoft_Windows)

        switch ( this->_protocolVersion ) {
            case ProtocolVersion::INTERNET_PROTOCOL_NONE_SPECIFIED:
            case ProtocolVersion::INTERNET_PROTOCOL_VERSION_6:
            case ProtocolVersion::INTERNET_PROTOCOL_VERSION_6_FORCED: {

                int flag = 0x01;
                int retVal = :: setsockopt (
                        this->_platformSocket,
                        SOL_SOCKET,
                        SO_REUSEADDR,
                        reinterpret_cast < char * > (& flag),
                        sizeof ( flag )
                );

                if ( retVal == Socket::WIN32_SOCKET_FUNCTION_ERROR ) {
                    if ( this->_protocolVersion == Socket::ProtocolVersion::INTERNET_PROTOCOL_VERSION_6_FORCED )
                        throw SocketException("Bind Exception on IPV6 : SetSocketOption Error. WSALastError : "_s + WSAGetLastError() + ", name = " + Socket::Win32WSAContainerType::lastWSAError());

                    this->_protocolVersion = Socket::ProtocolVersion::INTERNET_PROTOCOL_VERSION_4;
                    return this->close().open().bind();
                }

                flag = 0x00;

                retVal = :: setsockopt (
                    this->_platformSocket,
                    SOL_SOCKET,
                    IPV6_V6ONLY,
                    reinterpret_cast < char * > ( & flag ),
                    sizeof ( flag )
                );

                sockaddr_in6 ipv6AddressInfo {};

                ipv6AddressInfo.sin6_family = AF_INET6;
                ipv6AddressInfo.sin6_addr = in6addr_any;
                ipv6AddressInfo.sin6_port = htons(this->_port);

                retVal = :: bind (
                        this->_platformSocket,
                        reinterpret_cast < sockaddr * > ( & ipv6AddressInfo ),
                        sizeof ( ipv6AddressInfo )
                );

                if ( retVal == Socket::WIN32_SOCKET_FUNCTION_ERROR ) {
                    if ( this->_protocolVersion == Socket::ProtocolVersion::INTERNET_PROTOCOL_VERSION_6_FORCED )
                        throw SocketException("Bind Exception on IPV6. WSALastError : "_s + WSAGetLastError() + ", name = " + Socket::Win32WSAContainerType::lastWSAError());

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
                        reinterpret_cast < char * > ( & flag ),
                        sizeof ( flag )
                );

                if ( retVal == Socket::WIN32_SOCKET_FUNCTION_ERROR )
                    throw SocketException("Bind Exception on IPV4 : SetSocketOption Error. WSALastError : "_s + WSAGetLastError() + ", name = " + Socket::Win32WSAContainerType::lastWSAError());

                sockaddr_in ipv4AddressInfo {};

                ipv4AddressInfo.sin_family = AF_INET;
                ipv4AddressInfo.sin_addr.s_addr = htonl(INADDR_ANY);
                ipv4AddressInfo.sin_port = htons(this->_port);

                retVal = :: bind (
                        this->_platformSocket,
                        reinterpret_cast < sockaddr * > ( & ipv4AddressInfo ),
                        sizeof ( ipv4AddressInfo )
                );

                if ( retVal == Socket::WIN32_SOCKET_FUNCTION_ERROR )
                    throw SocketException("Bind Exception on IPV4. WSALastError : "_s + WSAGetLastError() + ", name = " + Socket::Win32WSAContainerType::lastWSAError());

                return * this;
            }
        }

#else

#error Socket::bind Unimplemented

#endif

        return * this;

    }

    __CDS_OptionalInline auto listen ( int queueSize = 0 ) noexcept (false) -> Socket & { // NOLINT(misc-no-recursion)
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

#elif defined(__CDS_Platform_Microsoft_Windows)

        if ( Socket::WIN32_SOCKET_FUNCTION_ERROR == :: listen ( this->_platformSocket, queueSize ) ) {
            if ( this->_protocolVersion == Socket::ProtocolVersion::INTERNET_PROTOCOL_VERSION_6_FORCED )
                throw SocketException("Listen Exception on IPV6. WSALastError : "_s + WSAGetLastError() + ", name = " + Socket::Win32WSAContainerType::lastWSAError());
            if ( this->_protocolVersion == Socket::ProtocolVersion::INTERNET_PROTOCOL_VERSION_4 )
                throw SocketException("Listen Exception on IPV4. WSALastError : "_s + WSAGetLastError() + ", name = " + Socket::Win32WSAContainerType::lastWSAError());

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

        __CDS_OptimalInline LastAddressContainer() noexcept = default;

        __CDS_OptimalInline ~LastAddressContainer() noexcept {
            delete this->pLastSocketAddress;
        }

        __CDS_OptionalInline auto specifyType ( ProtocolVersion protocolVersion ) noexcept -> void {
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
                delete Utility::exchange(this->pLastSocketAddress, nullptr);

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

#elif defined(__CDS_Platform_Microsoft_Windows)

    struct LastAddressContainer {
    public:
        sockaddr * pLastSocketAddress { nullptr };
        socklen_t lastSocketAddressSize { 0 };
        ProtocolVersion lastProtocolType { ProtocolVersion::INTERNET_PROTOCOL_NONE_SPECIFIED };

        __CDS_OptimalInline LastAddressContainer() noexcept = default;

        __CDS_OptimalInline ~LastAddressContainer() noexcept {
            delete this->pLastSocketAddress;
        }

        __CDS_OptionalInline auto specifyType ( ProtocolVersion protocolVersion ) noexcept -> void {
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
                delete Utility::exchange(this->pLastSocketAddress, nullptr);

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
    __CDS_OptionalInline auto accept () noexcept (false) -> Socket {

#if defined(__CDS_Platform_Linux)

        static LastAddressContainer lastAddressContainer;
        lastAddressContainer.specifyType (this->_protocolVersion);

        if ( this->pLastAddressObtainedContainer == nullptr )
            this->pLastAddressObtainedContainer = & lastAddressContainer;

        PlatformSocket retVal = :: accept (
            this->_platformSocket,
            lastAddressContainer.pLastSocketAddress,
            & lastAddressContainer.lastSocketAddressSize
        );

        if ( retVal == Socket::UNIX_INVALID_PLATFORM_SOCKET )
            throw SocketException( "Accept Exception." );

#elif defined(__CDS_Platform_Microsoft_Windows)

        static LastAddressContainer lastAddressContainer;
        lastAddressContainer.specifyType (this->_protocolVersion);

        if ( this->pLastAddressObtainedContainer == nullptr )
            this->pLastAddressObtainedContainer = & lastAddressContainer;

        PlatformSocket retVal = :: accept (
                this->_platformSocket,
                lastAddressContainer.pLastSocketAddress,
                & lastAddressContainer.lastSocketAddressSize
        );

        if ( retVal == Socket::WIN32_INVALID_PLATFORM_SOCKET )
            throw SocketException( "Accept Exception. WSALastError : "_s + WSAGetLastError() + ", name = " + Socket::Win32WSAContainerType::lastWSAError() );

#else

#error Socket::accept Unimplemented

#endif

        auto clientSocket = Socket(retVal);

        if ( this->_synchronizeSettingsAtConnectionStartup ) {

            int acknowledge;

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

    __CDS_MaybeUnused __CDS_OptimalInline auto writeBytes ( Byte const * pBuffer, Size count ) noexcept (false) -> Socket & {

#if defined(__CDS_Platform_Linux)

        auto written = :: write ( this->_platformSocket, pBuffer, count );

        if ( Socket::UNIX_SOCKET_FUNCTION_ERROR == written )
            throw SocketException("Socket writeBytes Exception");
        if ( written != count )
            throw SocketException(String::f("Unable to completely write message : intended : %d, sent : %d", count, written) );

        return * this;

#elif defined(__CDS_Platform_Microsoft_Windows)

        auto written = :: send ( this->_platformSocket, reinterpret_cast < char const * > ( pBuffer ), static_cast < int > ( count ), 0u );

        if ( written < 0 )
            throw SocketException("Socket writeBytes Exception");
        if ( written != count )
            throw SocketException(String::f("Unable to completely write message : intended : %d, sent : %d", count, written) );

        return * this;

#else

#error Socket::writeBytes Unimplemented

#endif

    }

    __CDS_MaybeUnused __CDS_OptimalInline auto readBytes ( Byte * pBuffer, Size intendedForRead ) noexcept (false) -> Socket & {

#if defined(__CDS_Platform_Linux)

        auto read = :: read ( this->_platformSocket, pBuffer, intendedForRead );

        if ( Socket::UNIX_SOCKET_FUNCTION_ERROR == read )
            throw SocketException("Socket readBytes Exception");

        if ( Socket::UNIX_SOCKET_READ_DISCONNECT == read )
            throw SocketDisconnect();

        if ( read != intendedForRead )
            throw SocketException ("Read Bytes count Different from Intended Count");

        return * this;

#elif defined(__CDS_Platform_Microsoft_Windows)

        auto read = :: recv ( this->_platformSocket, reinterpret_cast < char * > (pBuffer), static_cast < int > ( intendedForRead ), 0 );

        if ( Socket::WIN32_SOCKET_FUNCTION_ERROR == read )
            throw SocketException("Socket readBytes Exception");

        if ( Socket::WIN32_SOCKET_DISCONNECT == read )
            throw SocketDisconnect();

        if ( read != intendedForRead )
            throw SocketException ("Read Bytes count Different from Intended Count");

        return * this;

#else

#error Socket::readBytes Unimplemented

#endif

    }


    __CDS_MaybeUnused __CDS_OptimalInline auto writeInt8 ( sint8 value ) noexcept (false) -> Socket & {
        return this->writeBytes( reinterpret_cast < Byte const * > ( & value ), sizeof (value) );
    }

    __CDS_MaybeUnused __CDS_OptimalInline auto writeInt16 ( sint16 value ) noexcept (false) -> Socket & {
        return this->writeBytes( reinterpret_cast < Byte const * > ( & value ), sizeof (value) );
    }

    __CDS_MaybeUnused __CDS_OptimalInline auto writeInt32 ( sint32 value ) noexcept (false) -> Socket & {
        return this->writeBytes( reinterpret_cast < Byte const * > ( & value ), sizeof (value) );
    }

    __CDS_MaybeUnused __CDS_OptimalInline auto writeInt64 ( sint64 value ) noexcept (false) -> Socket & {
        return this->writeBytes( reinterpret_cast < Byte const * > ( & value ), sizeof (value) );
    }

    __CDS_MaybeUnused __CDS_OptimalInline auto writeUInt8 ( uint8 value ) noexcept (false) -> Socket & {
        return this->writeBytes( reinterpret_cast < Byte const * > ( & value ), sizeof (value) );
    }

    __CDS_MaybeUnused __CDS_OptimalInline auto writeUInt16 ( uint16 value ) noexcept (false) -> Socket & {
        return this->writeBytes( reinterpret_cast < Byte const * > ( & value ), sizeof (value) );
    }

    __CDS_MaybeUnused __CDS_OptimalInline auto writeUInt32 ( uint32 value ) noexcept (false) -> Socket & {
        return this->writeBytes( reinterpret_cast < Byte const * > ( & value ), sizeof (value) );
    }

    __CDS_MaybeUnused __CDS_OptimalInline auto writeUInt64 ( uint64 value ) noexcept (false) -> Socket & {
        return this->writeBytes( reinterpret_cast < Byte const * > ( & value ), sizeof (value) );
    }


    __CDS_MaybeUnused __CDS_OptimalInline auto writeInt ( int value ) noexcept (false) -> Socket & {
        return this->writeInt32( value );
    }

    __CDS_MaybeUnused __CDS_OptimalInline auto writeSize ( Size value ) noexcept (false) -> Socket & {
        return this->writeUInt64 (value);
    }

    __CDS_MaybeUnused __CDS_OptionalInline auto writeString ( String const & string ) noexcept (false) -> Socket & {
        auto packetCount = string.size() / this->_packetSize;
        if ( string.size() % this->_packetSize != 0 )
            ++ packetCount;

        this->writeSize ( string.size() );

        Size offset = 0U;

        for ( Size i = 0; i < packetCount; ++ i ) {
            this->writeBytes (
                reinterpret_cast < Byte const * > ( string.cStr() ) + offset,
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


    __CDS_NoDiscard __CDS_MaybeUnused __CDS_OptimalInline auto readInt8 () noexcept(false) -> sint8 {
        sint8 value;
        this->readBytes(reinterpret_cast < Byte * > ( & value ), sizeof(value));
        return value;
    }

    __CDS_NoDiscard __CDS_MaybeUnused __CDS_OptimalInline auto readInt16 () noexcept(false) -> sint16 {
        sint16 value;
        this->readBytes(reinterpret_cast < Byte * > ( & value ), sizeof(value));
        return value;
    }

    __CDS_NoDiscard __CDS_MaybeUnused __CDS_OptimalInline auto readInt32 () noexcept(false) -> sint32 {
        sint32 value;
        this->readBytes(reinterpret_cast < Byte * > ( & value ), sizeof(value));
        return value;
    }

    __CDS_NoDiscard __CDS_MaybeUnused __CDS_OptimalInline auto readInt64 () noexcept(false) -> sint64 {
        sint64 value;
        this->readBytes(reinterpret_cast < Byte * > ( & value ), sizeof(value));
        return value;
    }

    __CDS_NoDiscard __CDS_MaybeUnused __CDS_OptimalInline auto readUInt8 () noexcept(false) -> uint8 {
        uint8 value;
        this->readBytes(reinterpret_cast < Byte * > ( & value ), sizeof(value));
        return value;
    }

    __CDS_NoDiscard __CDS_MaybeUnused __CDS_OptimalInline auto readUInt16 () noexcept(false) -> uint16 {
        uint16 value;
        this->readBytes(reinterpret_cast < Byte * > ( & value ), sizeof(value));
        return value;
    }

    __CDS_NoDiscard __CDS_MaybeUnused __CDS_OptimalInline auto readUInt32 () noexcept(false) -> uint32 {
        uint32 value;
        this->readBytes(reinterpret_cast < Byte * > ( & value ), sizeof(value));
        return value;
    }

    __CDS_NoDiscard __CDS_MaybeUnused __CDS_OptimalInline auto readUInt64 () noexcept(false) -> uint64 {
        uint64 value;
        this->readBytes(reinterpret_cast < Byte * > ( & value ), sizeof(value));
        return value;
    }


    __CDS_NoDiscard __CDS_MaybeUnused __CDS_OptimalInline auto readInt () noexcept (false) -> int {
        return this->readInt32();
    }

    __CDS_NoDiscard __CDS_MaybeUnused __CDS_OptimalInline auto readSize () noexcept (false) -> Size {
        return this->readUInt64();
    }

    __CDS_NoDiscard __CDS_MaybeUnused __CDS_OptionalInline auto readString () noexcept (false) -> String {
        Size originalSize = this->readSize(), offset = 0U;
        Size packetCount = originalSize / this->_packetSize;

        if ( originalSize % this->_packetSize != 0 )
            ++ packetCount;

        String buffer;
        buffer.resize(originalSize);
        buffer._l = originalSize;

        for ( Size i = 0; i < packetCount; ++ i ) {
            this->readBytes (
                reinterpret_cast < Byte * > (buffer.data()) + offset,
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

#elif defined(__CDS_Platform_Microsoft_Windows)

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

#elif defined(__CDS_Platform_Microsoft_Windows)

        return dataTypes::hash<Size> ( reinterpret_cast < Size >( this->_platformSocket ) );

#else

#error Socket::hash Unimplemented

#endif
    }

    __CDS_NoDiscard __CDS_OptionalInline auto copy () const noexcept -> Socket * override {

#if defined (__CDS_Platform_Linux)

        return new Socket(dup(this->_platformSocket));

#elif defined(__CDS_Platform_Microsoft_Windows)

        WSAPROTOCOL_INFO wsaProtocolInfo;

        if ( 0 != WSADuplicateSocket(this->_platformSocket, GetCurrentProcessId(), & wsaProtocolInfo) ) {
            return nullptr;
        }

        PlatformSocket platformSocket = WSASocket(
                wsaProtocolInfo.iAddressFamily,
                wsaProtocolInfo.iSocketType,
                wsaProtocolInfo.iProtocol,
                & wsaProtocolInfo,
                0,
                0
        );

        if ( this->_platformSocket == Socket::WIN32_INVALID_PLATFORM_SOCKET ) {
            return nullptr;
        }

        return new Socket(platformSocket);

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

#elif defined(__CDS_Platform_Microsoft_Windows)

        return this->_platformSocket == p->_platformSocket;

#else

#error Socket::equals Unimplemented

#endif
    }

    __CDS_OptimalInline ~Socket () noexcept override {
        this->close();
    }

    Socket(Socket const & socket) noexcept (Socket::socketDuplicateExceptSpec) :

#if defined(__CDS_Platform_Linux)

            _platformSocket(dup(socket._platformSocket)),

#elif defined(__CDS_Platform_Microsoft_Windows)

//            moved to ctor body due to structure instantiation creation
//            _platformSocket(WSADuplicateSocket(socket._platformSocket, GetCurrentProcessId(), & wsaProtocolInfo)),

#else

#error Socket::CopyConstructor Undefined

#endif

            _port(socket._port),
            _packetSize(socket._packetSize),
            _protocolVersion(socket._protocolVersion),
            _packetSyncCount(socket._packetSyncCount),
            _synchronizeSettingsAtConnectionStartup(socket._synchronizeSettingsAtConnectionStartup) {

#if defined(__CDS_Platform_Microsoft_Windows)

        WSAPROTOCOL_INFO wsaProtocolInfo;
        int retVal;

        if ( 0 != ( retVal = WSADuplicateSocket(socket._platformSocket, GetCurrentProcessId(), & wsaProtocolInfo) ) ) {
            throw SocketException( "Socket Copy Failure. WSADuplicateSocket : "_s + retVal );
        }

        this->_platformSocket = WSASocket(
            wsaProtocolInfo.iAddressFamily,
            wsaProtocolInfo.iSocketType,
            wsaProtocolInfo.iProtocol,
            & wsaProtocolInfo,
            0,
            0
        );

        if ( this->_platformSocket == Socket::WIN32_INVALID_PLATFORM_SOCKET ) {
            throw SocketException ( "Socket Creation Failure at Socket Copy. WSALastError : "_s + WSAGetLastError() + ", name = " + Socket::Win32WSAContainerType::lastWSAError() );
        }

#endif

    }

    auto operator = (Socket const & socket) noexcept (Socket::socketDuplicateExceptSpec) -> Socket & {
        if ( & socket == this ) return * this;

        this->close();

#if defined(__CDS_Platform_Linux)

            this->_platformSocket = dup(socket._platformSocket);

#elif defined(__CDS_Platform_Microsoft_Windows)

        WSAPROTOCOL_INFO wsaProtocolInfo;
        int retVal;

        if ( 0 != ( retVal = WSADuplicateSocket(socket._platformSocket, GetCurrentProcessId(), & wsaProtocolInfo) ) ) {
            throw SocketException( "Socket Copy Failure. WSADuplicateSocket : "_s + retVal );
        }

        this->_platformSocket = WSASocket(
            wsaProtocolInfo.iAddressFamily,
            wsaProtocolInfo.iSocketType,
            wsaProtocolInfo.iProtocol,
            & wsaProtocolInfo,
            0,
            0
        );

        if ( this->_platformSocket == Socket::WIN32_INVALID_PLATFORM_SOCKET ) {
            throw SocketException ( "Socket Creation Failure at Socket Copy. WSALastError : "_s + WSAGetLastError() + ", name = " + Socket::Win32WSAContainerType::lastWSAError() );
        }

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

            _platformSocket(Utility::exchange(socket._platformSocket, Socket::UNIX_INVALID_PLATFORM_SOCKET)),

#elif defined(__CDS_Platform_Microsoft_Windows)

            _platformSocket(Utility::exchange(socket._platformSocket, Socket::WIN32_INVALID_PLATFORM_SOCKET)),

#else

#error Socket::MoveConstructor Undefined

#endif

            _port(Utility::exchange(socket._port, Socket::DEFAULT_PORT)),
            _packetSize(Utility::exchange(socket._packetSize, Socket::DEFAULT_PACKET_SIZE)),
            _protocolVersion(Utility::exchange(socket._protocolVersion, Socket::ProtocolVersion::AUTO)),
            _packetSyncCount(Utility::exchange(socket._packetSyncCount, Socket::DEFAULT_PACKET_SYNC_COUNT)),
            _synchronizeSettingsAtConnectionStartup(Utility::exchange(socket._synchronizeSettingsAtConnectionStartup, true)) {

    }

    auto operator = (Socket && socket) noexcept -> Socket & {
        if ( & socket == this ) return * this;

        this->close();

#if defined(__CDS_Platform_Linux)

        this->_platformSocket = Utility::exchange(socket._platformSocket, Socket::UNIX_INVALID_PLATFORM_SOCKET);

#elif defined(__CDS_Platform_Microsoft_Windows)

        this->_platformSocket = Utility::exchange(socket._platformSocket, Socket::WIN32_INVALID_PLATFORM_SOCKET);

#else

#error Socket::MoveOperator Undefined

#endif

        this->_port = Utility::exchange(socket._port, Socket::DEFAULT_PORT);
        this->_packetSize = Utility::exchange(socket._packetSize, Socket::DEFAULT_PACKET_SIZE);
        this->_protocolVersion = Utility::exchange(socket._protocolVersion, Socket::ProtocolVersion::AUTO);
        this->_packetSyncCount = Utility::exchange(socket._packetSyncCount, Socket::DEFAULT_PACKET_SYNC_COUNT);
        this->_synchronizeSettingsAtConnectionStartup = Utility::exchange(socket._synchronizeSettingsAtConnectionStartup, true);

        return * this;
    }
};

class ServerSocket : public Socket {
public:
    explicit ServerSocket ( uint16 port, ProtocolVersion protocolVersion = Socket::ProtocolVersion::AUTO ) noexcept (false) : Socket(protocolVersion) {
        this->bind (port).listen ();
    }
};

__CDS_RegisterParseType(Socket)
__CDS_RegisterParseType(ServerSocket)

#endif //CDS_SOCKET_HPP
