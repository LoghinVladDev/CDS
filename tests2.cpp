#include <CDS/Thread>
#include <CDS/smartPointers/UniquePointer>

using namespace cds;

template < typename T, typename = void >
struct isMemberFunctionPointer : std :: false_type { };

template < typename R, typename C >
struct isMemberFunctionPointer < R C :: *, C > : std :: is_function < R > { };

class B {
public:
    int f();
};

class A {
public:
    int x;
    int f();
};

void g();
int y;

int main () {

    std :: cout << isMemberFunctionPointer < decltype ( & A :: x ), A > :: value << '\n';
    std :: cout << isMemberFunctionPointer < decltype ( & A :: f ), B > :: value << '\n';
    std :: cout << isMemberFunctionPointer < decltype ( g ), A > :: value << '\n';
    std :: cout << isMemberFunctionPointer < decltype ( y ), A > :: value << '\n';

    return 0;
}