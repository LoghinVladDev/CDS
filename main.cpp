#include <CDS/experimental/JSON>

using namespace cds;

class A {
public:
    A () {
        std :: cout << "Constructed\n";
    }

    ~A () {
        std :: cout << "Destructed\n";
    }
};

auto f () {
    obj = HashMap < int, UniquePointer < A > > {
            { 1, makeUnique < A > () },
            { 2, makeUnique < A > () }
    };
}

auto f2 () {

}

int main () {

}