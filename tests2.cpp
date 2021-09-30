#include <iostream>
#include <list>


//#include <CDS/LinkedList>
//#include <CDS/Pointer>
//#include <CDS/Array>

#define CDS_DEBUG
#define CDS_PTR_DEBUG

#include <CDS/Pair>
#include <CDS/Range>
#include <CDS/Reference>

struct A : public Object {
    A () {
        std::cout << "ctor\n";
    }

    ~A () {
        std::cout << "dtor\n";
    }

    String toString() const noexcept override {
        return "A Object";
    }
};

int main () {
    SharedPointer p (new A());

    auto f = [p] {
        return p.copy();
    };

    auto x = f();
    delete x;

//    constexpr Pair p = {1, 5};
//
//    std::cout << p << '\n';
//
//
//    constexpr auto f = [p] {
//        int s = 0;
//        for ( auto i : Range(p) )
//            s += i;
//
//        return s;
//    };
//
//    std::cout << f() << '\n';


//    LinkedList < int > list;
//    Array < UniquePointer < int > > pointers;
//
//    pointers.add(new int(3));
//
//    std::cout << pointers << '\n';
}