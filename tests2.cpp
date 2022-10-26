#include <CDS/LinkedHashMap>
#include <CDS/HashMap>
#include <CDS/HashSet>
#include <CDS/LinkedHashSet>
#include <CDS/Array>
#include <CDS/LinkedList>
#include <CDS/threading/Atomic>
#include <CDS/threading/Mutex>
#include <CDS/threading/Lock>
#include <CDS/threading/Thread>
#include <mutex>
#include <thread>
#include <pthread.h>
#include <functional>
#include "src/functional/FunctionalInterface.hpp"

template < typename F >
auto timed ( cds :: String const & message, F const & block ) {

    auto start = std :: chrono :: high_resolution_clock :: now ();
    block ();
    auto end = std :: chrono :: high_resolution_clock :: now ();
    auto duration = std :: chrono :: duration_cast < std :: chrono :: milliseconds > ( end - start ).count();

    std :: cout << "Operation '" << message << "' lasted " << duration << "ms\n";
}
int f2(int a) {return a * 2;}
int main () {

std::stop_token stopToken;
    using namespace cds;

    AtomicFlag f;

    std :: cout << f << '\n';
    f.set();
    std :: cout << f << '\n';
    f.clear();
    std :: cout << f << '\n';
    f.set();
    std :: cout << f.get() << '\n';
    f.clear();
    std :: cout << f.get() << '\n';

    Atomic < int > adef;
    Atomic cdef = 5;
    std :: cout << adef << '\n';
    std :: cout << cdef << '\n';

    Atomic c1def (cdef, AtomicMemoryOrder::SequentiallyConsistent);
    Atomic c2def (cdef, AtomicMemoryOrder::SequentiallyConsistent, AtomicMemoryOrder::SequentiallyConsistent);
    std :: cout << c1def << '\n';
    std :: cout << c2def << '\n';
    Atomic c3def (c1def);
    std :: cout << c3def << '\n';
    c1def = 3;
    std :: cout << c1def << '\n';
    c2def = c1def;
    std :: cout << c2def << '\n';
    std :: cout << c2def.get() << '\n';
    std :: cout << c2def.get(AtomicMemoryOrder::SequentiallyConsistent) << '\n';
    c2def.set(7);
    std :: cout << c2def << '\n';
    c2def.set(9, AtomicMemoryOrder::SequentiallyConsistent);
    std :: cout << c2def << '\n';
    std :: cout << c2def.exchange (1) << '\n';
    std :: cout << c2def << '\n';
    std :: cout << c2def.exchange (3, AtomicMemoryOrder::SequentiallyConsistent) << '\n';
    std :: cout << c2def << '\n';
    std :: cout << c2def.getThenAdd(15) << '\n';
    std :: cout << c2def << '\n';
    std :: cout << c2def.getThenBitwiseAnd(16) << '\n';
    std :: cout << c2def << '\n';
    std :: cout << c2def.hash() << '\n';

    Mutex m;
    m.lock();
    m.unlock();

    {
        Lock l (m);
    }

    {
        Lock l (m);
    }

    {
        DeferredLock l (m);
    }

    {
        DeferredLock l (m);
        l.lock();
        l.unlock();
    }

    {
        DeferredLock l (m);
        l.lock();
    }

    Mutex m1;
    Mutex m2;
    Mutex m3;

    {
        GroupLock g (m1, m2);
    }

    {
        GroupLock g (m1, m2, m3);
    }

    Runnable run1 = []{
        std :: cout << "test\n";
        sleep(1);
        std :: cout << "test2\n";
    };

    run1.start();
    run1.join();

    using namespace cds;

    int index = 0;
    Array <Runnable <Function <void()>>> threads;
    threads.pushBackAll (
            [&cout = m1, i = ++ index]{ GroupLock l(cout); std :: cout << "Thread " << i << '\n'; },
            [&cout = m1, i = ++ index]{ GroupLock l(cout); std :: cout << "Thread " << i << '\n'; },
            [&cout = m1, i = ++ index]{ GroupLock l(cout); std :: cout << "Thread " << i << '\n'; },
            [&cout = m1, i = ++ index]{ GroupLock l(cout); std :: cout << "Thread " << i << '\n'; },
            [&cout = m1, i = ++ index]{ GroupLock l(cout); std :: cout << "Thread " << i << '\n'; },
            [&cout = m1, i = ++ index]{ GroupLock l(cout); std :: cout << "Thread " << i << '\n'; },
            [&cout = m1, i = ++ index]{ GroupLock l(cout); std :: cout << "Thread " << i << '\n'; },
            [&cout = m1, i = ++ index]{ GroupLock l(cout); std :: cout << "Thread " << i << '\n'; },
            [&cout = m1, i = ++ index]{ GroupLock l(cout); std :: cout << "Thread " << i << '\n'; },
            [&cout = m1, i = ++ index]{ GroupLock l(cout); std :: cout << "Thread " << i << '\n'; },
            [&cout = m1, i = ++ index]{ GroupLock l(cout); std :: cout << "Thread " << i << '\n'; },
            [&cout = m1, i = ++ index]{ GroupLock l(cout); std :: cout << "Thread " << i << '\n'; },
            [&cout = m1, i = ++ index]{ GroupLock l(cout); std :: cout << "Thread " << i << '\n'; },
            [&cout = m1, i = ++ index]{ GroupLock l(cout); std :: cout << "Thread " << i << '\n'; },
            [&cout = m1, i = ++ index]{ GroupLock l(cout); std :: cout << "Thread " << i << '\n'; },
            [&cout = m1, i = ++ index]{ GroupLock l(cout); std :: cout << "Thread " << i << '\n'; },
            [&cout = m1, i = ++ index]{ GroupLock l(cout); std :: cout << "Thread " << i << '\n'; },
            [&cout = m1, i = ++ index]{ GroupLock l(cout); std :: cout << "Thread " << i << '\n'; },
            [&cout = m1, i = ++ index]{ GroupLock l(cout); std :: cout << "Thread " << i << '\n'; },
            [&cout = m1, i = ++ index]{ GroupLock l(cout); std :: cout << "Thread " << i << '\n'; },
            [&cout = m1, i = ++ index]{ GroupLock l(cout); std :: cout << "Thread " << i << '\n'; },
            [&cout = m1, i = ++ index]{ GroupLock l(cout); std :: cout << "Thread " << i << '\n'; },
            [&cout = m1, i = ++ index]{ GroupLock l(cout); std :: cout << "Thread " << i << '\n'; }
    );

    threads.forEach([](auto & th) {th.start();});
    threads.forEach([](auto & th) {th.join();});


    std :: function <float(int)> * f123 = new std :: function ( [](int a) { return a + 0.5f; } );
    cds :: Function <float(int)> * f123c = new cds :: Function ( [](int a) { return a + 0.5f; } );
    auto f234 = * f123;
    auto f234c = * f123c;
    delete f123;
    delete f123c;

    class A {
    public:
        A() noexcept = default;
        A(A const&) noexcept = default;
        A(A &&) noexcept = delete;
        auto operator ()(int a) const {return a * 2.5f;}
    };

    A b123;

    A * a341515 = new A();
    std :: function f65 = * a341515;
    cds :: Function f65c = * a341515;
    delete a341515;

    std :: cout << f234(5) << '\n';
    std :: cout << f65(3) << '\n';
    std :: cout << f234c(5) << '\n';
    std :: cout << f65c(3) << '\n';

    cds :: meta :: Decay < int(float) > pfn;

    long long calls = 1'000'000'000;

    timed( "std::function", [calls] {
        std :: function < int(int) > f = f2;
        volatile int s = 0;
        for (long long i = 0; i < calls; ++ i) {
            s += f(i);
        }
        (void) s;
    });

    timed( "cds::Function", [calls] {
        cds :: Function < int(int) > f = f2;
        volatile int s = 0;
        for (long long i = 0; i < calls; ++ i) {
            s += f(i);
        }
        (void) s;
    });

    timed( "standard", [calls] {
        volatile int s = 0;
        for (long long i = 0; i < calls; ++ i) {
            s += f2(i);
        }
        (void) s;
    });

    auto fact = [n=10]{
        cds :: Function <int(int)> fac = [&](int n){
            if ( n == 0 ) return 1;
            return n * fac(n-1);
        };

        return fac(n);
    };

    std :: cout << fact () << '\n';

    using namespace cds :: functional;

    Supplier < int > sint = []() { return 5; };
    Predicate < int > isEven = [](int e) { return e % 2 == 0; };
    Predicate < int, int, int, int > all4Even = [](
            int a, int b,
            int c, int d
    ) {
        return
                a % 2 == 0 && b % 2 == 0 &&
                c % 2 == 0 && d % 2 == 0;
    };

    Mapper < int, double > intToDoubleAndTimes3half = [] (int a) {
        return a * 3.5;
    };

    Mapper < String, int, int, int > int3ToString  = [] (int a, int b, int c) {
        return String() + a + b + c;
    };

    Consumer < int > intPrinter = [](int a) { std :: cout << a << '\n'; };

    std :: cout << sint() << '\n';
    std :: cout << isEven(3) << '\n';
    std :: cout << isEven(4) << '\n';
    std :: cout << all4Even(1, 1, 1, 1) << '\n';
    std :: cout << all4Even(2, 1, 1, 1) << '\n';
    std :: cout << all4Even(1, 2, 1, 1) << '\n';
    std :: cout << all4Even(1, 1, 2, 1) << '\n';
    std :: cout << all4Even(1, 1, 1, 2) << '\n';
    std :: cout << all4Even(2, 2, 2, 2) << '\n';
    std :: cout << intToDoubleAndTimes3half(3) << '\n';
    std :: cout << int3ToString(3, 4, 5) << '\n';

    intPrinter (4);

//    std :: function <float(A)> f0 = [](A a) { return a(3); };

    return 0;
}