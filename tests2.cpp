#include "src/primitive/Tuple.hpp"
#include <CDS/Tuple>
#include <CDS/Array>
#include <tuple>

#include <CDS/Function>

int main () {

    using cds::Tuple;
    using cds::Array;


    using cds::Size;
    using cds::makeTuple;

    auto t1 = makeTuple <Size, Size, Size> (3, 4, 5);

    Size a = 3, b = 4, c = 5;

    auto t2 = makeTuple (a, b, c);
    t2.get<0>() = 1;

    cds::Function <bool(int)> f = [](int x){return x == 2;};
}
