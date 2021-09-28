#include <iostream>
#include <list>


#include <CDS/LinkedList>
#include <CDS/Pointer>
#include <CDS/Array>


int main () {
//    LinkedList < int > list;
    Array < UniquePointer < int > > pointers;

    pointers.add(new int(3));

    std::cout << pointers << '\n';
}