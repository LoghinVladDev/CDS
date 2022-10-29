#include <CDS/Array>
#include <CDS/Sequence>


template < typename t >
class A {
public:
    A () {
        std :: cout << "ctor\n";
    }

    ~A() {
        std :: cout << "dtor\n";
    }

    template < typename y >
    auto f () -> A <y> {
        return A<y> ();
    }
};

auto main () -> int {
    using namespace cds;

    A <int> ().f <float> ().f <double> ();

    Function < int (String const &) > f = [](String s) { return s.length(); };

    std :: cout << f ("ABCDE");

    return 0;
}