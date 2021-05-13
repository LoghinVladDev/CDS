#include <iostream>
#include <cstring>
#include <exception>

#include <CDS/File>
//#include <unistd.h>
int main() {
    std::cout << File::platformFileTypeFlagsToString(File::platformFileType("/")) << '\n';
}