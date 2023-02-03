#include <CDS/experimental/TreeMap>
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

int main() {
    s = "can assign values locally";
    f<&s>();
    g<s>();
    cout << s << endl;
    return 0;
}