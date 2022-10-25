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


    std :: function <float(int)> * f123 = new std :: function ( [](int a) { return a + 0.5f; } );
    auto f234 = * f123;
    delete f123;

    class A {
    public:
        A() noexcept = default;
        auto operator ()(int a) {return a * 2.5f;}
    };

    A * a341515 = new A();
    std :: function f65 = * a341515;
    delete a341515;

    std :: cout << f234(5) << '\n';
    std :: cout << f65(3) << '\n';

    return 0;
}