#include <iostream>

#include <CDS/experimental/Array>
#include "src/experimental/collection_new_iterable_model/shared/iterator/IteratorSort.hpp"
#include "src/experimental/collection_new_iterable_model/shared/iterator/impl/IteratorSort.hpp"

int main () {

    using namespace cds :: experimental;

    Array < int > a = { 9, 1, 2, 7, 4, 5, 8, 1 ,2 ,8 ,9, 7, 0, 4, 5, 1, 2 };
    heapSort (
            a.data(),
            a.data() + a.size()
    );

    std :: cout << a << '\n';

    return 0;
}