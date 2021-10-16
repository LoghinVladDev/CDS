//#include <iostream>
////#include <CDS/Random>
////#include <CDS/Integer>
//
//int heap [100001], heapLen = 0;
//
//int heap_empty () {
//    return heapLen == 0;
//}
//
//int heap_remove () {
//    int retVal = heap [1];
//
//    heap[1] = heap[heapLen--];
//
//    int current = 1;
//
//    while ( true ) {
//        int smallest = current;
//        int leftChild = current * 2;
//        int rightChild = current * 2 + 1;
//
//        if ( leftChild <= heapLen && heap[leftChild] < heap[smallest] )
//            smallest = leftChild;
//
//        if ( rightChild <= heapLen && heap[rightChild] < heap[smallest] )
//            smallest = rightChild;
//
//        if ( current == smallest ) break;
//
//        std :: swap ( heap[smallest], heap[current] );
//        current = smallest;
//    }
//
//    return retVal;
//}
//
//void heap_insert (int e) {
//    heap[ ++ heapLen ] = e;
//
//    int current = heapLen;
//    int parent = current / 2;
//
//    while ( current != 1 && heap [parent] > heap [current] ) {
//        std :: swap ( heap[parent], heap[current] );
//
//        current = parent;
//        parent = current / 2;
//    }
//}
//
//void make_heap (int * v, int l) {
//    for (int i = 0; i < l; ++i)
//        heap_insert(v[i]);
//}
//
//#include <chrono>
////#include <CDS/Array>
//
//int main () {
//    int v[100000], l;
//
//    l = 100000;
//    for ( int i = 0; i < l; ++ i )
//        v[i] = Int::random();
//
//    auto begin = std :: chrono :: high_resolution_clock :: now();
//
//    make_heap(v, l);
//
//    while ( ! heap_empty() )
//        heap_remove();
//
//    auto end = std :: chrono :: high_resolution_clock :: now();
//
//    auto diff = std :: chrono :: duration_cast < std :: chrono::milliseconds > ( end - begin );
//
//    std :: cout << diff.count() << '\n';
//
////    Array <int> a;
////    for ( int i = 0; i < l; ++ i )
////        a.pushBack(v[i]);
//
//    begin = std :: chrono :: high_resolution_clock :: now();
//
//    for ( int i = 0; i < l - 1; ++ i )
//        for ( int j = i + 1; j < l; ++ j )
//            if ( v[i] > v[j] )
//                std::swap(v[i], v[j]);
//
//    end = std :: chrono :: high_resolution_clock :: now();
//
//    diff = std :: chrono ::duration_cast < std :: chrono::milliseconds >( end - begin );
//
//    std :: cout << diff.count() << '\n';
//
////    begin = std :: chrono :: high_resolution_clock :: now();
//
////    a.sort([](int a, int b) { return a < b; });
//
////    end = std :: chrono :: high_resolution_clock :: now();
//
////    diff = std :: chrono ::duration_cast < std :: chrono::milliseconds >( end - begin );
//
////    std :: cout << diff.count() << '\n';
//
//}

#include <CDS/Utility>
#include <CDS/LinkedList>
#include <CDS/String>
#include <CDS/Union>

Union < int, String > f ( int x ) {
    if ( x % 2 == 0 ) return String::f("Numarul %d este impar", x);
    return x;
}

int main () {

    String s = f(12);
    std :: cout << s << '\n';


}