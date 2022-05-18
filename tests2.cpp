#include <CDS/Thread>
#include <CDS/smartPointers/UniquePointer>
#include <CDS/experimental/Traits>

using namespace cds :: experimental;

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

template < typename T, EnableIf < std :: is_same_v < T, bool > > = 0 >
void f () {
    std :: cout << "bool\n";
}

template < typename T, EnableIf < ! std :: is_same_v < T, bool > > = 0 >
void f () {
    std :: cout << "not bool\n";
}

int main () {

    f <int>();
    f <bool>();

    Conditional < true, int, float > v1 = 1;
    Conditional < false, int, float > v2 = 1.5f;

    std :: cout << v1 << '\n' << v2 << '\n';

    std :: cout << isSame < float, int > << '\n';
    std :: cout << isSame < int, int > << '\n';

    std :: cout << lessThanPossible < int *, int * > << '\n';

//    std :: cout << isMemberFunctionPointer < decltype ( & A :: x ), A > :: value << '\n';
//    std :: cout << isMemberFunctionPointer < decltype ( & A :: f ), B > :: value << '\n';
//    std :: cout << isMemberFunctionPointer < decltype ( g ), A > :: value << '\n';
//    std :: cout << isMemberFunctionPointer < decltype ( y ), A > :: value << '\n';

    return 0;
}