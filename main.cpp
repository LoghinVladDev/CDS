

#include <iostream>
#include <CDS/Object>
#include <CDS/Traits>
#include <CDS/DoubleLinkedList>

using namespace cds;

class A{
public:
    UniquePointer < DoubleLinkedList < int > > p;

    A() noexcept : p(new DoubleLinkedList<int>()) {

    }
};

int main () {

//    auto l = []( String const & s, auto i ){ return s + i; };
//    ArgumentsOf < decltype( l ) > v;-
//    l(""_s, 4);
//    decltype(*((decltype(l) *)(0x10)->operator())) v;

//    functionUtility :: returnOf < decltype ( l ) > t;
//    std :: cout << FunctionOver < decltype ( l ), returnOf < decltype ( l ) >, String, int >;

}