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
//    Async async < int (int) > ( Function < int (int) > ( [](int v){return v * 2;} ) );
//    auto retVal = async(4);

//    Array < int > list;

//    std :: cout << i (Int::isEven)(5) << '\n';

    Function f2 = [](int a) {
        for ( auto i : Range(100) ) {
            std :: cout << i << '\n';
        }

        return 10;
    };

//    std :: cout << f2(3) << '\n';

    Async < int ( int ) > async ( f2 );
    auto retVal = async(4);

    for ( auto i : Range(150) ) {
        std :: cout << "Main : " << i << '\n';
    }

    std :: cout << "Await\n";

    std :: cout << retVal.get();
}