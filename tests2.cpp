#include <CDS/TreeMap>
#include <CDS/TreeSet>

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

int main() {

    TreeSet <int> ts = {1, 2, 3};
    TreeMap <int, int> tm = {{1, 1}, {2, 2}, {3, 3}};

    return 0;
}