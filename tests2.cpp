
#include <CDS/Pointer>
#include <CDS/Traits>
#include <CDS/Socket>
#include <CDS/Integer>


int main () {
    Socket socket(Socket::LOCALHOST, 34000, Socket::ProtocolVersion::IPV4);

    socket.writeInt ( 5);
    int value = socket.readInt();

    String buffer(70000, 'b');
    socket.writeString ( buffer);

    buffer = socket.readString();

    if ( ! buffer.all([](auto c) { return c == 'c'; }) )
        std::cout << "nok";

    std::cout << buffer << "\n" << value << '\n';

    socket.close();

    return 0;
}