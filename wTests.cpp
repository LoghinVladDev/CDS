#include <iostream>
#include <CDS/Array>

class T {
public:
	void f();
};

template < typename t, typename = void >
struct has : cds :: meta :: FalseType {};

template < typename t >
struct has < t, cds :: meta :: Void < decltype ( & t :: operator () ) > > : cds :: meta :: TrueType {};

int main () {

	auto predanon = [](auto e) {return e % 2 == 1; };
	auto pred = [](int e) {return e % 2 == 1; };

	std::cout << has<decltype(predanon)>::value << '\n';
	std::cout << cds::meta::isFunction<decltype(predanon)>() << '\n';
	std::cout << cds::meta::isCallable<decltype(predanon)>() << '\n';
	std::cout << cds::meta::isCallable<decltype(pred)>() << '\n';
	std::cout << cds::meta::isCallable <decltype(&T::f)>() << '\n';
	using namespace cds;

	auto arr = cds::arrayOf(1, 2, 3, 4, 5);

	std::cout << arr << '\n';
	std::cout << *arr.findFirstThat([](auto e) {return e % 2 == 1; }) << '\n';
	std::cout << arr.any([](auto e) {return e % 2 == 1; }) << '\n';
	//std::cout << arr.count([](auto e) {return e % 2 == 1; }) << '\n';

	std::cout << sizeof(meta::Iterator) << '\n';
	std::cout << sizeof(meta::ForwardIterator) << '\n';
	std::cout << sizeof(meta::BidirectionalIterator) << '\n';
	std::cout << sizeof(meta::RandomAccessIterator) << '\n';
	std::cout << sizeof(cds::AddressIterator<int>) << '\n';
	std::cout << sizeof(cds::__hidden::__impl::__ForwardDelegateWrapperIterator<int>) << '\n';

	Collection<int>& c = arr;
	auto it = c.begin();
	c.remove(it);

	std::cout<<sizeof(cds::AddressIterator<int const>)<<'\n';
	std::cout << arr << '\n';

	return 0;
}