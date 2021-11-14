#include <iostream>

struct Test {
    unsigned char x : 3; // valori pana la 8 excl.
    unsigned char y : 2; // valori pana la 4 excl.
    unsigned char z : 4;
};

struct ErGrp {
    bool p0 : 1;
    bool p1 : 1;
    bool p2 : 1;
    bool p3 : 1;
    bool p4 : 1;
    bool p5 : 1;
    bool p6 : 1;
    bool p7 : 1;
};

ErGrp er[10000];

struct structura{
    /// 0
    char b;
    /// 1
    unsigned char f:2;
    /// 1 + 2b -> 4B
    unsigned int c:7;
    /// 1B + 9b
    unsigned int d:2;
    /// 1B + 11b ( 5B + 3b ) -> 8B
    double e;
    /// 16 B
    unsigned long long a:5;
    /// 16 + 5b -> 24B
};

#include <CDS/Async>
#include <CDS/Array>
#include <CDS/Sequence>

using namespace cds;

int main () {

    Array < int > a { 1 };
    std :: cout << a.sequence().fold(""_s, [](String const & s, int t){ return s + t; }) << '\n';

    return 0;
}