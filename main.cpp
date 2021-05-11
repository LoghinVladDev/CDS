#include <iostream>
#include <cstring>
#include <exception>

#include <CDS/Path>
//#include <unistd.h>
int main() {
    for ( auto & e : Path().walk() ) {
        std::cout << e.root() << " : Files = " << e.files() << ", Dirs : " << e.directories() << '\n';
    }
}