#include <iostream>
#include <CDS/Atomic>
#include <CDS/Thread>
#include <CDS/Range>
#include <CDS/Integer>
#include <crypto/primitives/Block.hpp>

void testAtomic ();
void testCrypto();
void testView();

#include <CDS/Timer>
#include <Tuple.hpp>
#include <CDS/HashMap>
int z = 5;

#include <Sequence.hpp>

void testView () {
    UniquePointer < List < int > > p ( new LinkedList < int > {1, 2, 3, 4} );
    std::cout << (*p) << '\n';

    String s = "Ana are mere";



//    Tuple t1 = {3, 5, 9.3f, String("ana are mere")};
//    std::cout << t1.get<3>() << '\n';
//
//    Tuple t2 = {
//            LinkedList<int>  {1, 3, 2},
//            UnorderedSet <float > {3.4f, 5.6f},
//            HashMap<int, int> {{2, 3}, {6, 4}},
//            String("Hello")
//    };
//
//    t2.get<2>().values().forEach([](Reference<int> i){i.get() = i.get() * 2;});
//    std::cout << t2.get<2>().values() << '\n';
//
//    exit(0);


    Timer t;
    int x = 3, y = 7;
    t.setInterval(100);
    t.start([& x, & y] {
        static int repCount = 0;
        std::cout << x << ", " << y << ", " << repCount ++ << "\n";
        std::cout.flush();
    });

//    Sleep(5010);

    t.stop();
}

template < typename K >
static auto hsh (K const &) -> Index { return 0; }
template <> auto hsh < String > ( String const & s ) -> Index { return s.length(); }
template <> auto hsh < int > ( int const & s ) -> Index { return s; }

template < typename Key >
struct Hasher {
    auto operator () (Key const & v) const noexcept -> Index {
        return hsh(v);
    }
};

template < typename Key, typename Value, typename Hash = Hasher<Key> >
class OurMap {
private:
    Hash h;

public:
    Size size {256};

    OurMap() noexcept = default;

    explicit OurMap ( Hash const & h ) noexcept {
        this->h = h;
    }

    auto getKeyHash (Key const & k) {
        return this->h(k) % this->size;
    }
};

int main () {
    Sequence s ( DoubleLinkedList<int>{1, 2, 3, 4} );

    for ( auto e : s ) {
        std::cout << e << '\n';
    }

    return 0;

    OurMap < String, int > m;
    std::cout << m.getKeyHash("Ana are mere");
    OurMap < int, String > m2;
    std::cout << m2.getKeyHash(294);
    exit(0);















//    testView();
//    testCrypto();
//    testAtomic();

}
//
////#include "primitive/View.hpp"
//#include <CDS/Array>
//#include <CDS/HashMap>
//#include <Tuple.hpp>
//void testView () {
//
//
////    LinkedList < int > numere = {5, 1, 2, 9, 6, 4};
////    numere.sort([](auto a, auto b){return a < b;});
////    std::cout << numere;
//
//
////
////
////    String x = "Ana are mere";
////
////    std::cout << x.cStr() << '\n';
////    std::cout << x << '\n';
////
////    std::string str = x.cStr();
////
////    exit(0);
//
//
////    int n = 5;
////    int s = 4;
//
////    Array < Pair < Pair < int, int >, int > > edges = {
////            { {1, 3}, 1 },
////            { {2, 1}, 2 },
////            { {4, 2}, 1 },
////            { {4, 3}, 8 },
////            { {5, 3}, 5 },
////            { {5, 4}, 2 }
////    };
////
////    HashMap < int, LinkedList < Pair < int, int > > > neighbours;
////    edges.forEach([&neighbours](auto p){neighbours[p.getFirst().getFirst()].pushBack({p.getFirst().getSecond(), p.getSecond()});});
//
////    HashMap < int, int > distances;
////    Range(1, n + 1).view().forEach([& distances](auto i){distances[i] = INT32_MAX;});
////    distances[s] = 0;
////    auto q = Range(1, n + 1).view().toSet();
//
////    while ( ! q.empty() ) {
////        int shortestDistNode = 1;
////        q.forEach([&shortestDistNode, &distances](auto i){if (distances[i] < distances[shortestDistNode]) shortestDistNode = i;});
////        q.remove(shortestDistNode);
////
////        neighbours[shortestDistNode].forEach([&distances, &shortestDistNode](auto & i){
////            int alt = i.getSecond() + distances[shortestDistNode];
////            if ( alt < distances[i.getFirst()] )
////                distances[i.getFirst()] = alt;
////        });
////    }
////
////    distances.forEach([](auto i){std::cout << i << ' ';});
//
//    std::cout << String ("abcd").view()
//        .filter(String::isVowel)
//        .findFirst().orElse('x') << '\n';
//
//
//    String s2 = "Ana are mere, dar are Gigel bere?";
//
//    String("ABCDADABC").view()
//            .map(String::lowerChar)
//            .filter(String::isConsonant)
//            .filter(String::isLowerChar)
//            .distinct()
//            .sorted()
//            .map(String::upperChar)
//            .forEach([](auto c){std::cout << c;});
//
//    std::cout << '\n';
//
//    s2.view()
//        .map(String::upperChar)
//        .filter([](auto c){return c >= 'A' && c <= 'G';})
//        .map(String::lowerChar)
//        .filter(String::isConsonant)
//        .map([](auto c){return c + 1;})
//        .forEach([](auto c){std::cout << c;});
//
//    std::cout << '\n';
//
//    Range(0, 10).view()
//        .filter([](auto e){return e % 2 == 1;})
//        .map([](auto e){return e * e;})
//        .sorted([](auto a, auto b){return a > b;})
//        .forEach([](auto e){std::cout << e << ' ';});
//
//    std::cout << '\n';
//
//    std::cout << View(Range(0, 15)).average() << '\n';
//
//    Array < float > arr = { 5.4f, 1.2f, 9.6f, 7.65f };
//
//    arr.view()
//        .sorted()
//        .forEach([](auto e){std::cout << e << ' ';});
//
//    std::cout << "\n";
//
//    std::cout << View (arr).average() << '\n';
//
//    LinkedList < float > ll = {1.3f, 94.5f, 105.4f, 47.0f};
//
//    ll.view().forEach([](auto e){std::cout << e << ' ';});
//    std::cout << '\n';
//
//    HashMap < String, int > { {"Ana", 1}, {"Are", 4}, {"Bere", 3} }.view()
//        .filter([](auto e){return e.getSecond() % 2 == 1;})
//        .forEach([](auto e){std::cout << e << ' ';});
//
//    std::cout << "\n";
//
//    Array < Array < int > > matrix = {
//            {3, 1 ,2},
//            {5, 7, 9},
//            {8, 0 ,6}
//    };
//
//    matrix.view()
//        .filter([](auto & row){return row.any([](auto e){return e % 2 == 0;});})
//        .sorted([](auto & rowA, auto & rowB){
//            auto sumA = 0, sumB = 0;
//            rowA.forEach([&sumA](auto e){return sumA += e;});
//            rowB.forEach([&sumB](auto e){return sumB += e;});
//            return sumA > sumB;
//        })
//        .forEach([](auto & row){
//            std::cout << "Row : ";
//            row.view()
//                .map([](auto & e){return e * 2;})
//                .sorted()
//                .forEach([](auto & e){std::cout << e << ' ';});
//            std::cout << "\n";
//        });
//
////    Range(0, 10).view().toMap<int, int>();
//
//    Pair p = {3, 4};
//
////    std::cout << hasFirstGetter<decltype(p)>::value << '\n';
//    std::cout << isPair<decltype(p)>::value << '\n';
//    std::cout << isPair<int>::value << '\n';
//
//    auto m = LinkedList <Pair<int, int>> { {1, 2}, {4, 3}, {5, 6} }.view().toMap();
//
//    std::cout << m << '\n';
//
//    try {
//        std::cout << Range(0, 10).view().toMap();
//    } catch ( std::exception const & e ) {
//        std::cout << e.what() << '\n';
//    }
//
//
////    std::cout << String("ABCDEFABCaaabccddsf").view()
////        .filter(String::isVowel)
////        .map(String::toLowerChar)
////        .distinct()
////        .sorted([](auto a, auto b){return a > b;})
////        .toList();
////        .count([](auto a){return a == 'a';});
//
////    auto set = Range(0, 10).view().toOrderedSet();
////
////    std::cout << set << '\n';
//
////    View(h)
////        .filter([](auto e){return e.getSecond() % 2 == 1;})
////        .forEach([](auto e){std::cout << e << ' ';});
////    std::cout << '\n';
//
////    std::cout << chr << '\n';
////        .forEach([](auto c){
////        std::cout << c;});
//
//    exit(0);
//}

void testCrypto () {

//    constexpr auto & size = crypto::size::SIZE_128;
//    std::cout << size.bytes() << '\n';

    auto block = crypto::Block < crypto::BlockSize::Value::BITS_128 >::fromBinary("1011110110110");

    std::cout << block.toHex() << '\n';

    exit(0);
}

void testAtomic () {
    //    Integer::Atomic y;

    constexpr static uint32 runCnt = 10000;
    sint32 x = 0;
    Integer::Atomic xAtomic = 0;

    Runnable a ([&x, &xAtomic](){
        for(auto _ : Range(runCnt)) {
            x++;
            xAtomic++;
        }
    });

    Runnable b ([&x, &xAtomic](){
        for (auto _ : Range(runCnt)) {
            x--;
            xAtomic--;
        }
    });

    Runnable c ( [&x, &xAtomic]() {
        for (auto _ : Range(runCnt)) {
            x++;
            xAtomic++;
        }
    });

    Runnable d ( [&x, &xAtomic]() {
        for (auto _ : Range(runCnt)) {
            x++;
            xAtomic++;
        }
    });

    a.start();
    b.start();
    c.start();
    d.start();

    a.join();
    b.join();
    c.join();
    d.join();

    std::cout << "No Atomic : " << x << '\n';
    std::cout << "Atomic : " << xAtomic.get() << '\n';
    std::cout << "Correct Value : " << 2 * runCnt << '\n';

    xAtomic = 7;
    xAtomic = Integer(5);

    std::cout << 22 % xAtomic << '\n';
    std::cout << xAtomic % 4 << '\n';
    std::cout << (xAtomic > 4) << '\n';
}