#include <CDS/Function>
#include <CDS/Pointer>
#include <CDS/LinkedList>

template < typename F >
auto i ( F const & f ) {
    return Function < bool ( Integer const & ) > ( f );
}

int main () {


    std :: cout << i (Int::isEven)(5) << '\n';

    Function < int (int) noexcept > f2 = [](int a) noexcept { return a * 2; };

    std :: cout << f2(3) << '\n';
}