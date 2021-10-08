
#include <CDS/Pointer>
#include <CDS/Traits>
#include <CDS/Socket>
#include <CDS/Integer>

int v = 014;

struct A {
public:
    A() {std::cout << "C\n";}
    void f() {}
    ~A() {std::cout << "D\n";}

};

int main () {
    Socket s;

    s.connect (Socket::LOCALHOST, 34000);

    s.writeInt (5);

    int v = s.readInt();
    String buffer(70000, 'b');
    s.writeString (buffer);

    buffer = std::move(s.readString());

    if ( ! buffer.all([](auto c) { return c == 'c'; }) )
        std::cout << "nok";

    std::cout << buffer << '\n';

    std::cout << v << '\n';

    s.close();

    return 0;
}