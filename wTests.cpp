#include <iostream>
#include <CDS/Array>

int main () {

	using namespace cds;

	auto arr = cds::arrayOf(1, 2, 3, 4, 5);

	std::cout << arr << '\n';

	return 0;
}