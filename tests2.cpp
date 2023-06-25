#include "src/primitive/Tuple.hpp"
#include <CDS/Tuple>
#include <CDS/Array>
#include <tuple>

#include <CDS/Function>

template <typename...Outputs>
typename cds::meta::All <cds::meta::Bind <cds::meta::IsConvertible, cds::meta::Ph<>, std::ostream&>::Type, Outputs...>::value v;

template <typename T>
using ConvertibleToStdOstreamRef =
    cds::meta::Bind <cds::meta::IsConvertible, cds::meta::Ph<1>, std::ostream&>::Type<T>;

#include <CDS/LinkedHashSet>
#include <CDS/LinkedList>
#include <unordered_map>
#include <CDS/LinkedHashSet>
#include <CDS/HashSet>
#include <CDS/TreeSet>
#include <CDS/HashMap>
#include <CDS/TreeMap>
#include <CDS/LinkedHashMap>
#include <CDS/util/JSON>

int main () {

  cds::json::JsonObject const o;
  o.getJson("abc");
  o.get("abc");

  cds::Array <int> a24124;
  a24124.removeAllThat ([](auto e) {return e == 2;});
  a24124.removeAllOf ({1, 2, 3});
  a24124.removeAllOf (cds::arrayOf(1, 2, 3));
  cds::LinkedList <int> ll24124;
  ll24124.removeAllThat ([](auto e) {return e == 2;});
  ll24124.removeAllOf ({1, 2, 3});
  ll24124.removeAllOf (cds::arrayOf(1, 2, 3));

  cds::HashSet <int> hs;
  hs.removeAllThat ([](auto e) {return e == 2;});
  hs.removeAllOf ({1, 2, 3});
  hs.removeAllOf (cds::arrayOf(1, 2, 3));
  cds::LinkedHashSet <int> lh1s;
  lh1s.removeAllThat ([](auto e) {return e == 2;});
  lh1s.removeAllOf ({1, 2, 3});
  lh1s.removeAllOf (cds::arrayOf(1, 2, 3));
  cds::TreeSet <int> ts;
  ts.removeAllThat ([](auto e) {return e == 2;});
  ts.removeAllOf ({1, 2, 3});
  ts.removeAllOf (cds::arrayOf(1, 2, 3));

  cds::HashMap <int, int> hm;
  hm.removeAllThat ([](auto e) {return e.key() == 2;});
  hm.removeAllOf ({{1, 1}});
  hm.removeAllOf (cds::arrayOf(cds::MapEntry{1, 1}));
  cds::LinkedHashMap <int, int> lhm;
  lhm.removeAllThat ([](auto e) {return e.key() == 2;});
  lhm.removeAllOf ({{1, 1}});
  lhm.removeAllOf (cds::arrayOf(cds::MapEntry{1, 1}));
  cds::TreeMap <int, int> tm;
  tm.removeAllThat ([](auto e) {return e.key() == 2;});
  tm.removeAllOf ({{1, 1}});
  tm.removeAllOf (cds::arrayOf(cds::MapEntry{1, 1}));

  using cds::LinkedHashSet;
  using cds::String;

  cds::uint64 sh = 1u << 33u;
  cds :: LinkedHashSet < String > intSetUnderTest;
  cds :: Set < String > & underTest = intSetUnderTest;
  intSetUnderTest = { 1, 1 };
  std::cout << intSetUnderTest << '\n';


  return 0;
std::cout << cds::String("test") << '\n';
std::cout << cds::String("test") << '\n';
std::cout << cds::String("test") << '\n';

cds::Array aOfInt = cds::arrayOf (1, 2, 3, 4);
cds::Array aOfIntToIns = cds::arrayOf (5, 6, 7, 8);
auto const& aRef = aOfIntToIns;
aOfInt.insertAllOfBefore (aOfInt.begin(), aRef);

  cds::LinkedHashSet<int> lhs;
  lhs.begin();
//  cds::Array <char const> a2;
//  *a2.begin() = 2;
  cds::Array <int> a;
  a.pushBack(1);
  a.pushBack(1);
  a.pushBack(1);
  a.pushBack(1);
  a.pushBack(1);
  a.pushBack(1);
  a.pushBack(1);
  a.pushBack(1);
  a.pushBack(1);
  a.pushFront(1);
  a.pushFront(1);
  a.pushFront(1);
  a.pushFront(1);
  a.pushFront(1);
  a.pushFront(1);
  a.pushFront(1);
  a.pushFront(1);
  a.pushFront(1);
  a.pushFront(1);
  a.pushFront(1);
  return 0;
//
//  std::stringstream oss;
//  std::cout << ConvertibleToStdOstreamRef<decltype(oss)>::value << '\n';
//  return 0;
////            cds::meta::All <cds::meta::Bind <cds::meta::IsConvertible, cds::meta::Ph<>, int>, float, int>::value;
//
//    using cds::Tuple;
//    using cds::Array;
//
//
//    using cds::Size;
//    using cds::makeTuple;
//
//    auto t1 = makeTuple <Size, Size, Size> (3, 4, 5);
//
//    Size a = 3, b = 4, c = 5;
//
//    auto t2 = makeTuple (a, b, c);
//    t2.get<0>() = 1;
//
//    cds::Function <bool(int)> f = [](int x){return x == 2;};
//
//    int x = 5;
//    Size s = 3;
//    Array a213 (s, x);

//    std::cout << cds::meta::All <int, float, int> :: test < cds::meta::IsSame, int > ();
//  std::cout << IsIntImpl<int>::Type<> ::value << '\n';
//  std::cout << IsIntImpl<double>::Type<> ::value << '\n';
//  std::cout << IsDouble<double> ::value << '\n';/

//  using cds::meta::Ph;
//  using cds::meta::Bind;
  using cds::meta::All;
  using cds::meta::Ph;
  using cds::meta::Bind;

//  using namespace cds::meta::__impl::__bindImpl;

//  __PackPop <__Pack <int, Ph<>>> ::

//  Bind <cds::meta::IsSame, int, Ph<>> :: Type <int>::value;

  std::cout << "Inplace\n";
  std::cout << All < Bind <cds::meta::IsSame, int, Ph<1>>::Type, int, int, int > :: value << '\n';
  std::cout << All < Bind <cds::meta::IsSame, int, Ph<>>::Type, int, double, int > :: value << '\n';
  std::cout << All < Bind <cds::meta::IsSame, int, Ph<1>>::Type, int, int, double > :: value << '\n';
  std::cout << All < Bind <cds::meta::IsSame, int, Ph<1>>::Type, double, int, int > :: value << '\n';
  std::cout << All < Bind <cds::meta::IsSame, Ph<1>, Ph<1>>::Type, float, double > :: value << '\n';

  std::cout << "Meta\n";
  std::cout << cds::meta::All < cds::meta::Bind <cds::meta::IsSame, int, cds::meta::Ph<1>>::Type, int, int, int > :: value << '\n';
  std::cout << cds::meta::All < cds::meta::Bind <cds::meta::IsSame, int, cds::meta::Ph<>>::Type, int, double, int > :: value << '\n';
  std::cout << cds::meta::All < cds::meta::Bind <cds::meta::IsSame, int, cds::meta::Ph<1>>::Type, int, int, double > :: value << '\n';
  std::cout << cds::meta::All < cds::meta::Bind <cds::meta::IsSame, int, cds::meta::Ph<1>>::Type, double, int, int > :: value << '\n';
//  cds::meta::Bind <cds::meta::IsSame, cds::meta::Ph<1>, cds::meta::Ph<1>>:: Type<float> :: value;

  std::cout << cds::meta::All < cds::meta::Bind <cds::meta::IsSame, cds::meta::Ph<1>, cds::meta::Ph<1>>::Type, float, double > :: value << '\n';

//  Bind <cds::meta::Common, Ph<>, Ph<>, int, Ph<>>::Type <float, double, cds::String> :: Type s;
  Bind <cds::meta::IsSame, int, Ph<1>>::Type <int> v123;
  Bind <cds::meta::Common, int, float, Ph<>, Ph<>>::Type <float, cds::String> s1 = "Abc";
  cds::String wtfTest;
  wtfTest = "test";
  s1 = wtfTest;
  s1 = "test";
//  Bind <cds::meta::Common, int, float, Ph<1>, Ph<1>>::Type <float> s2;

  cds::meta::__impl::__Common <int, float>::Type f12312;
  f12312 = 3;

//  s1 = 3;
  std::cout << v123.value << '\n';
}
