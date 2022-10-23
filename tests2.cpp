#include <CDS/LinkedHashMap>
#include <CDS/HashMap>
#include <CDS/HashSet>
#include <CDS/LinkedHashSet>
#include <CDS/Array>
#include <CDS/LinkedList>
#include <CDS/threading/Atomic>
#include <CDS/threading/Mutex>
#include <CDS/threading/Lock>
#include <mutex>

int main () {

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

    return 0;
}