#include <CDS/Array>
#include "src/experimental/cds_69_modernize_sequence/Sequence.hpp"

int main () {


    using namespace cds;


    auto array = cds :: arrayOf ( 1, 2, 3, 4, 5 );
    std :: cout << array << '\n';

    using namespace cds :: __hidden :: __impl;

    std::function <bool(int const &)> f2 = [](auto e) {return e % 2 == 1;};
    f2 (3);
    Function <bool(int const &)> f = [](auto e ){ return e % 2 == 1;};
    f( 3);

//    Function <bool(int const &)> f3 = /**/3;

    __LazySequence < int > ls ( array );
    for ( auto e : ls
            .filter ([](auto e){return e % 2 == 1;})
            .filter([](int const & e){return e != 5;})) {
        std :: cout << e << '\n';
    }
//    std :: cout << ls << '\n';

    return 0;
}