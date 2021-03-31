#include <iostream>
#include <threading/Atomic.hpp>
#include <threading/Thread.hpp>
#include <CDS/Range>
#include <CDS/Integer>
//#include <crypto/primitives/Block.hpp>

void testAtomic ();
void testCrypto();

int main () {

    testCrypto();
    testAtomic();

}

void testCrypto () {

//    constexpr auto & size = crypto::size::SIZE_128;
//    std::cout << size.bytes() << '\n';

//    auto block = crypto::Block < size >::fromBinary("1011110110110");

//    std::cout << block.toHex() << '\n';

//    exit(0);
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