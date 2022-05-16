#include <iostream>
#include <fstream>
#include <string>
#include <utility>
#include <set>
#include <queue>

int ctr = 0;

void f ( int n, int i, int j ) {
    if ( i <= n /2 ) {
        if ( j <= n - 1 ) {
            ctr ++;
            f(n, i, j + 1);
        } else {
            ctr ++;
            f(n, i + 1, i + 2);
        }
    }
}

int main () {
    f(7, 2, 4);
std :: cout << ctr << '\n';

    return 0;
}