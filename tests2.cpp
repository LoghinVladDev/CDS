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
#include <CDS/util/JSON>
#include <mutex>
#include <thread>
#include <functional>
#include "src/functional/FunctionalInterface.hpp"
#include <variant>
#include <CDS/filesystem/Path>
#include <CDS/filesystem/Walk>
#include <memory>
#include <CDS/memory/UniquePointer>
#include <CDS/memory/SharedPointer>
#include <CDS/memory/RawPointer>
#include <CDS/memory/WeakPointer>
#include <CDS/memory/Reference>
#include <CDS/Optional>
#include <CDS/exception/ArithmeticException>
#include <CDS/exception/RuntimeException>
#include <CDS/exception/Exception>
#include <CDS/exception/DivideByZeroException>
#include <CDS/exception/IllegalArgumentException>
#include <CDS/exception/KeyException>
#include <CDS/exception/TypeException>
#include <CDS/exception/UnsupportedOperationException>
#include <CDS/exception/OutOfBoundsException>
#include <CDS/exception/NullPointerException>
#include <CDS/exception/NotImplementedException>
#include <CDS/exception/FormatException>
#include <CDS/exception/NoSuchElementException>
#include <CDS/Union>


template < typename F >
auto timed ( cds :: String const & message, F const & block ) {

    auto start = std :: chrono :: high_resolution_clock :: now ();
    block ();
    auto end = std :: chrono :: high_resolution_clock :: now ();
    auto duration = std :: chrono :: duration_cast < std :: chrono :: milliseconds > ( end - start ).count();

    std :: cout << "Operation '" << message << "' lasted " << duration << "ms\n";
}

void f2( ) {

    std::variant<std::string> v31231;
    std::string strstr;
    (void) std::make_shared<int>(3);
    std::shared_ptr <int> p24121;
    p24121.~shared_ptr();
    using namespace cds;
    using namespace cds :: json;
    using namespace cds :: literals;
    using namespace cds :: filesystem;

    HashMap < int, int > m;
    class  T1: HashMap < int, int > {} m2;
    T1 m3;

    JsonArray arr;

    JsonObject json;
    json.put ( "test1", 2 );
    json.put ( "test2", 4.3f );
    json.put ( "test3", "test" );
    json.put ( "test1", "test2"_s );
    json.at ( "test1" ) = "test2"_s;
    json.get ( "test3" ) = 5;
    StringView sv = "test";
    String path = "test";
    filesystem :: Path p = sv;
    filesystem :: Path p2 ( "test2" );
    filesystem :: Path p3 = path;

    p3 /= "test";
    p3 = "test";

    std :: cout << json << '\n';
    for ( auto & e : filesystem :: walk ( Path(__FILE__).parent() / "src" ) ) {
        std :: cout << e << '\n';
    }

    UniquePointer <int> p54 = new int (3);
    UniquePointer <int[]> p64 = new int [5];
    SharedPointer <int> s54 = new int (3);
    SharedPointer <int[]> s64 = new int[5];

    auto sp5 = s54;
    std :: cout << * sp5 << '\n';
    std :: cout << sp5 << '\n';
    auto sp6 = s54;
    auto sp7 = sp6;
    std :: cout << sp6 << '\n';
    std :: cout << sp7 << '\n';

    constexpr int thCount = 2;
    SharedPointer < Atomic < int > > sp = new Atomic <int> (0);
    cds :: Function threadFunc = [tsp = sp]{
        cds :: Function innerThreadFunc = [itsp = tsp]{
            cds :: Function innerInnerThreadFunc = [iitsp = itsp]{
                cds :: Function innerInnerInnerThreadFunc = [iiitsp = iitsp]{
                    cds :: Function innerInnerInnerInnerThreadFunc = [iiiitsp = iiitsp]{
                        ++ * iiiitsp;
                    };

                    cds :: Array < cds :: UniquePointer < cds :: Thread > > threads;
                    for ( int i = 0; i < thCount; ++ i ) { threads.emplaceBack ( new Runnable ( innerInnerInnerInnerThreadFunc ) ); }
                    threads.forEach ([](auto & th){th->start();});
                    -- * iiitsp;
                    threads.forEach ([](auto & th){th->join();});
                };

                cds :: Array < cds :: UniquePointer < cds :: Thread > > threads;
                for ( int i = 0; i < thCount; ++ i ) { threads.emplaceBack ( new Runnable ( innerInnerInnerThreadFunc ) ); }
                threads.forEach ([](auto & th){th->start();});
                ++ * iitsp;
                threads.forEach ([](auto & th){th->join();});
            };

            cds :: Array < cds :: UniquePointer < cds :: Thread > > threads;
            for ( int i = 0; i < thCount; ++ i ) { threads.emplaceBack ( new Runnable ( innerInnerThreadFunc ) ); }
            threads.forEach ([](auto & th){th->start();});
            -- * itsp;
            threads.forEach ([](auto & th){th->join();});
        };

        cds :: Array < cds :: UniquePointer < cds :: Thread > > threads;
        for ( int i = 0; i < thCount; ++ i ) { threads.emplaceBack ( new Runnable ( innerThreadFunc ) ); }
        threads.forEach ([](auto & th){th->start();});
        -- * tsp;
        threads.forEach ([](auto & th){th->join();});
    };

    cds :: Array < cds :: UniquePointer < cds :: Thread > > threads;
    for ( int i = 0; i < thCount; ++ i ) { threads.emplaceBack ( new Runnable ( threadFunc ) ); }
    threads.forEach ([](auto & th){th->start();});
    threads.forEach ([](auto & th){th->join();});
    std :: cout << * sp << '\n';

    auto f = []{
        SharedPointer < int > intSP = new int(3);
        WeakPointer < int > intWP = intSP;
        WeakPointer < int > intWP2 = intWP;

        if ( auto intSP2 = intWP2.acquire() ) {
            std :: cout << * intSP2 << '\n';
        } else {
            std :: cout << "Expired\n";
        }

        intSP.reset();

        if ( auto intSP3 = intWP.acquire() ) {
            std :: cout << * intSP3 << '\n';
        } else {
            std :: cout << "Expired\n";
        }

        if ( auto intSP2 = intWP2.acquire() ) {
            std :: cout << * intSP2 << '\n';
        } else {
            std :: cout << "Expired\n";
        }
    };

    f();

    auto g = []{
        return UniquePointer <int> (new int (3));
    };

    auto h = []{
        auto h1 = []{
            return UniquePointer <int> (new int (5));
        };

        return h1();
    };

    std :: cout << *g() + *h() << '\n';

    auto gs = []{
        return SharedPointer <int> (new int (3));
    };

    auto hs = []{
        auto h1 = []{
            return SharedPointer <int> (new int (5));
        };

        return h1();
    };

    std :: cout << *gs() + *hs() << '\n';

    auto ptr1 = cds :: makeUnique <int> ( 3 );
    auto ptr2 = cds :: makeUnique <int[]> ( 5 );
    auto sptr1 = cds :: makeShared <int> ( 3 );
    auto sptr2 = cds :: makeShared <int[]> ( 5 );

    auto wptr2 = sptr2.observe();
    auto sptr3 = wptr2.acquire();

    Tuple t = {1, 3.4f, String ("test"), false, String ("test2")};
    Tuple t2 = t;

    std :: cout << t << '\n' << t2 << '\n';
    Tuple t3 = std :: move (t2);
    std :: cout << t << '\n' << t2 << '\n' << t3 << '\n';


    Optional < int > o1;
    std :: cout << o1 << '\n';
    o1 = 3;
    std :: cout << o1 << '\n';

    Optional < int > o2;
    o1 = o2;
    std :: cout << o1 << '\n';

    Optional < int > o3 = 4;
    o1 = std :: move ( o3 );

    std :: cout << o1 << '\n';
    std :: cout << o3 << '\n';

    Function < int(int) > f123 = [](int x) { return x * 2; };
    Reference < Function < int(int) > > fref = f123;

    int x123;
    Reference < int > refx123 = x123;

    auto opt123 = cds :: makeOptional < int > ( 3 );

    class B {
    private:
        int y;
    };

    class Test : public Object, public B {
    public:
        int x;
        size_t y = reinterpret_cast < size_t > ( static_cast < B * > ( this ) );
        size_t t = reinterpret_cast < size_t > ( static_cast < Test * > ( static_cast < B * > ( this ) ) );
//        size_t z = reinterpret_cast < size_t > ( reinterpret_cast < B * > ( this ) );
    };

    Test test123;
    std :: cout << & test123 << '\n';
    std :: cout << static_cast < B * > ( & test123 ) << '\n';
    std :: cout << & test123.x << '\n';
    std :: cout << std :: hex << test123.y << '\n';
//    std :: cout << std :: hex << test123.z << '\n';
    std :: cout << std :: hex << test123.t << '\n';


    std :: cout << cds :: meta :: isConvertible < char const *, int > () << '\n';
//    using t4124512 = cds :: __hidden :: __impl :: __UnionInitTraits < char const *, int, float, double, String >;
//    std :: cout << t4124512 :: __directInit << '\n';
//    std :: cout << t4124512 :: __convertInit << '\n';
//    std :: cout << t4124512 :: __directInitIndex << '\n';
//    std :: cout << t4124512 :: __convertInitIndex << '\n';
//    std :: cout << t4124512 :: __NextEntryTraits :: __directInitIndex << '\n';
//    std :: cout << t4124512 :: __NextEntryTraits :: __NextEntryTraits :: __directInitIndex << '\n';
//    std :: cout << t4124512 :: __NextEntryTraits :: __NextEntryTraits :: __NextEntryTraits :: __directInitIndex << '\n';
//    std :: cout << t4124512 :: __NextEntryTraits :: __NextEntryTraits :: __NextEntryTraits :: __NextEntryTraits :: __directInitIndex << '\n';
//    std :: variant < int, float, double, String > var3241234;
}

void unionDebugF();

int main () {

    using namespace cds;



    Union < int, float, String > u1 = "123";
    Union < int, float, String > u2 = StringView ( "123" );
    Union < int, float, String > u3 = String ( "123" );

    Union < int, float, String > u4 = u3;
    Union < int, float, UniquePointer <int> > u5 = new int (3);
    Union < int, float, UniquePointer <int> > u6 = std :: move ( u5 );

    std :: variant < String, Tuple <int, float >> v1 = "test";
    std :: variant < String, Tuple <int, float >> v2 = Tuple {1, 4.3f};

    v1 = v2;

    u2 = u3;
    u1 = std :: move (u3);

    Union <int, float, String > u7 = 4.5f;
    Union <int, float, String > u8 = 4;
    u1 = std :: move ( u7 );
    u1 = u2;
    u1 = u3;
    u1 = std :: move ( u3 );
    u1 = u8;
    u1 = 3;
    u1 = 4.5f;
    u1 = "abc";
    u1 = StringView("123");
    u1 = std :: move ( String ( "123" ) );

    u5 = new int(3);
//    u5 = "abc";

//    u5 = u6;

    u7.emplace < String > ( 5, 'e' );
    u7.emplace < String > ( {'a', 'b', 'c'} );
//    u7.emplace < StringView > ( "abc" );

    std :: cout << u5.get <2> () << '\n';
    std :: cout << u5.get < UniquePointer < int > > () << '\n';
    std :: cout << u7.get <2> () << '\n';
    std :: cout << u7.get < String > () << '\n';

    Union <int, float, String> const & u7c = u7;
    std :: cout << u7c.get <2> () << '\n';
    std :: cout << u7c.get <String> () << '\n';

    try {
        std :: cout << u7.get <int> () << '\n';
    } catch ( Exception const & e ) {
        std :: cout << e.message() << '\n';
    }

    try {
        std :: cout << u7c.get <int> () << '\n';
    } catch ( Exception const & e ) {
        std :: cout << e.message() << '\n';
    }

    try {
        std :: cout << u5.get <int> () << '\n';
    } catch ( Exception const & e ) {
        std :: cout << e.message() << '\n';
    }

    std :: cout << u5.getPointer <2> () << " : " << * u5.getPointer <2> () << '\n';
    std :: cout << u5.getPointer <UniquePointer <int>> () << " : " << * u5.getPointer <UniquePointer <int>> () << '\n';
    std :: cout << u5.getPointer <0> () << '\n';
    std :: cout << u5.getPointer <int> () << '\n';

    std :: cout << u7c.getPointer <2> () << " : " << * u7c.getPointer <2> () << '\n';
    std :: cout << u7c.getPointer <String> () << " : " << * u7c.getPointer <String> () << '\n';
    std :: cout << u7c.getPointer <0> () << '\n';
    std :: cout << u7c.getPointer <int> () << '\n';

    std :: cout << "if is : \n";
    u5.ifIs <0> ( [](auto & e) {
        std :: cout << e << '\n';
    });

    u5.ifIs <int> ( [](auto & e) {
        std :: cout << e << '\n';
    });

    u5.ifIs <2> ( [](auto & e) {
        std :: cout << e << '\n';
    });

    u5.ifIs <UniquePointer < int >> ( [](auto & e) {
        std :: cout << e << '\n';
    });

    u7c.ifIs <String> ([](auto & e){
        std :: cout << e << '\n';
    });

//    u7c.ifIs <String> ([](auto & e){
//        e = "abc";
//    });


//    std :: cout << u5.get<double>() << '\n';

unionDebugF();

    std :: cout << u7 << '\n';
    std :: cout << u7c << '\n';
    std :: cout << u5 << '\n';
    std :: cout << u1 << '\n';
    std :: cout << u3 << '\n';

    std :: cout << ( u7 == 3 ) << '\n';
//    std :: cout << ( u7 == 3.5 ) << '\n';
    std :: cout << ( u7 == String("abc") ) << '\n';
    std :: cout << ( u7 == String("Abc") ) << '\n';

    class A {
    public:
        void f ();
    };

    std :: cout << cds :: meta :: isFunction < decltype ( & A :: f ) > () << '\n';

    return 0;
}


//template < typename t >
//void printUnionTraits () {
//
//    std :: cout << "Direct Init :           " << t :: __directInit << '\n';
//    std :: cout << "Direct Init Index :     " << t :: __directInitIndex << '\n';
//    std :: cout << "Convert Init :          " << t :: __convertInit << '\n';
//    std :: cout << "Convert Init Index :    " << t :: __convertInitIndex << '\n';
//    std :: cout << '\n';
//};

void unionDebugF () {

//    using t4124512 = cds :: __hidden :: __impl :: __UnionInitTraits < char const *, int, float, double, cds :: String >;
//    printUnionTraits < t4124512 > ();
//    printUnionTraits < t4124512 :: __NextEntryTraits > ();
//    printUnionTraits < t4124512 :: __NextEntryTraits :: __NextEntryTraits > ();
//    printUnionTraits < t4124512 :: __NextEntryTraits :: __NextEntryTraits :: __NextEntryTraits > ();
//    printUnionTraits < t4124512 :: __NextEntryTraits :: __NextEntryTraits :: __NextEntryTraits :: __NextEntryTraits > ();
}