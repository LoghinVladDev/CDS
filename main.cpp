#include <CDS/Function>
#include <CDS/Pointer>
#include <CDS/LinkedList>
#include <CDS/Array>

template < typename F >
auto i ( F const & f ) {
    return Function < bool ( Integer const & ) > ( f );
}

template < typename T, EnableIf < std :: is_same < T, int > :: value > = 0 >
auto f ( T var ){

}

#include <CDS/Async>

int main () {


    Array < int > list;

    std :: cout << i (Int::isEven)(5) << '\n';

    Function < int (int) noexcept > f2 = [](int a) noexcept { return a * 2; };

    std :: cout << f2(3) << '\n';
}