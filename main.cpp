//#include <CDS/Function>
//#include <CDS/Pointer>
//#include <CDS/LinkedList>
//#include <CDS/Array>
//#include <CDS/Memory>
//
//template < typename F >
//auto i ( F const & f ) {
//    return Function < bool ( Integer const & ) > ( f );
//}
//
//template < typename T, EnableIf < std :: is_same < T, int > :: value > = 0 >
//auto f ( T var ){
//
//}


//#include <CDS/Async>
#include <CDS/Array>
#include <CDS/allocators/LeakDetectionAllocator>
#include <iostream>

class A {
public:
    A() noexcept { std :: cout << "Create\n"; }
    ~A() noexcept { std :: cout << "Delete\n"; }
};

int main () {

    delete Memory::instance().replaceAllocator(new Memory::LeakDetectionAllocator());

//
//    Boolean b{false};
//    b.copy();
//
//    try {
//        Memory::instance().create<A>();
//    } catch ( Exception const & e ) {
//        std::cout << e.toString() << '\n';
//    }
//    A * a = new A[10];
//    delete [] a;

//    A * pArray = Memory::instance().createArray < A > (10);
//    Memory::instance().destroyArray ( pArray );
}