#include <iostream>
#include <threading/Atomic.hpp>
#include <threading/Thread.hpp>
#include <CDS/Range>
#include <CDS/Integer>
#include <crypto/primitives/Block.hpp>

void testAtomic ();
void testCrypto();
void testView();

int main () {

    testView();
    testCrypto();
    testAtomic();

}

#include "primitive/View.hpp"
void testView () {

    String s2 = "Ana are mere, dar are Gigel bere?";

    String("ABCDADABC").view()
            .map(String::lowerChar)
            .filter(String::isConsonant)
            .filter(String::isLowerChar)
            .distinct()
            .sorted()
            .map(String::upperChar)
            .forEach([](auto c){std::cout << c;});

//    std::cout << chr << '\n';
//        .forEach([](auto c){
//        std::cout << c;});

    exit(0);
}

void testCrypto () {

//    constexpr auto & size = crypto::size::SIZE_128;
//    std::cout << size.bytes() << '\n';

    auto block = crypto::Block < crypto::BlockSize::Value::BITS_128 >::fromBinary("1011110110110");

    std::cout << block.toHex() << '\n';

    exit(0);
}

void testAtomic () {
    //    Integer::Atomic y;

    constexpr static CDS_uint32 runCnt = 10000;
    CDS_sint32 x = 0;
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