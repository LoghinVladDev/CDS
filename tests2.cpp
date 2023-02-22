#include <CDS/TreeMap>
#include <CDS/TreeSet>
#include <CDS/StaticArray>
#include <CDS/memory/UniquePointer>
#include <CDS/Queue>

using namespace std;

template <std::string * temp> //pointer to object
void f()
{
    cout << *temp << endl;
}

template <std::string & temp> //reference to object
void g()
{
    cout << temp << endl;
    temp += "...appended some string";
}

std::string s; //must not be local as it must have external linkage!

using namespace cds;
#include <array>
#include <CDS/Array>

int main() {

    Array < int > a1;

    TreeSet <int> ts = {1, 2, 3};
    TreeMap <int, int> tm = {{1, 1}, {2, 2}, {3, 3}};

    class A {
        A () = delete;
    };

    struct B {
        B () {
            std :: cout << "test\n";
        }
    };

//    B ba[100];


    StaticArray <int, 5> a;
    StaticArray <int, 512> b;

    std :: array < int, 5 > a2 = {1, 2};
    std :: array < int, 5 > a3;
    a2 = a3;


    std :: cout << a2.size() << '\n';



    return 0;
}