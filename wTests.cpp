#include <iostream>
#include <list>

struct Test {
    int x;

    void modifyX () {
        this->x = 5;
    }
};

void modifyXFromTest (Test * pThis) {
    pThis->x = 5;
}

void modifyX (int & x) {
    x = 5;
}

int main () {
    Test t;

//    modifyXFromTest(& t);
    modifyX(t.x);
//0x62fe1c, 0x62fe1c
    std::cout << t.x << '\n';
}