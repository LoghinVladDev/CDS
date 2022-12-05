#include <iostream>

void f() {
	std::cout << "test\n";
}

class T {
public:
	void f() {
		std::cout << "test\n";
	}
};

class G {
public:
	void f() {
		std::cout << "test2\n";
	}
};

union {
	void* pfnAsPure;
	void (T ::* orig) (void);
	void (G ::* casted) (void);
} FuckYouMicrosoft;

class B : T {
public:
	void f() {

	}
public:
	int g() {
		return 0;
	}
};

int main () {

	// void* pfn = &T::f; this does not work
	FuckYouMicrosoft.orig = &T::f;
	(G().*FuckYouMicrosoft.casted)();

	void(G :: * f)(int) = (void (G::*)(int)) & B::f;

	void (B :: * f2) (void) = (void (B::*)(void)) & B::g;

	return 0;
}