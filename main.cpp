#include <iostream>
#include <cstring>
#include <exception>

#include <CDS/Reference>

using namespace std;

class FirstException : public std::exception {
public:
//    FirstException() noexcept = default; la absenta acestuia, se creeaza automat
//    FirstException() noexcept : std::exception() { } asta este = default

    const char * what() const noexcept override {
        return "First Exception";
    }
};

class SecondException : public std::exception {
public:
    const char * what() const noexcept override {
        return "Second Exception";
    }
};

void f(int x) noexcept(false) {
    if (x % 3 == 0)
        throw FirstException();
    else if (x % 3 == 1)
        throw SecondException();
}

int main() {
    return 0;
}