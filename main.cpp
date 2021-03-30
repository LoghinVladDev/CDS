#include <iostream>
#include <CDS/LinkedList>
#include <CDS/String>
#include <CDS/HashMap>
#include <CDS/UnorderedSet>
#include <CDS/OrderedSet>
#include <CDS/Pointer>
#include <CDS/Reference>
#include <CDS/Optional>
#include <CDS/Range>

//Whenever I have the time

#define FLAG(i) 1u << i ## u
#define FOREACH_FLAG(_min, _max, _dt, _v) for ( _dt _v = FLAG(_min); _v != FLAG(_max); _v = _v << 1 )

class TerminalColor {
public:
    enum Modifier : CDS_uint32 {
        RESET = FLAG(0),

        ENABLE_BOLD = FLAG(1),
        ENABLE_UNDERLINE = FLAG(2),
        ENABLE_INVERSE_COLOR = FLAG(3),

        DISABLE_BOLD = FLAG(4),
        DISABLE_UNDERLINE = FLAG(5),
        DISABLE_INVERSE_COLOR = FLAG(6),

        FOREGROUND_BLACK = FLAG(14),
        FOREGROUND_RED = FLAG(15),
        FOREGROUND_GREEN = FLAG(16),
        FOREGROUND_YELLOW = FLAG(17),
        FOREGROUND_BLUE = FLAG(18),
        FOREGROUND_MAGENTA = FLAG(19),
        FOREGROUND_CYAN = FLAG(20),
        FOREGROUND_WHITE = FLAG(21),
        FOREGROUND_DEFAULT = FLAG(22),

        BACKGROUND_BLACK = FLAG(23),
        BACKGROUND_RED = FLAG(24),
        BACKGROUND_GREEN = FLAG(25),
        BACKGROUND_YELLOW = FLAG(26),
        BACKGROUND_BLUE = FLAG(27),
        BACKGROUND_MAGENTA = FLAG(28),
        BACKGROUND_CYAN = FLAG(29),
        BACKGROUND_WHITE = FLAG(30),
        BACKGROUND_DEFAULT = FLAG(31),
    };

public:
    typedef CDS_uint32 Flags;
private:

    static HashMap < Modifier, int > colorMap;
    Flags f = FOREGROUND_DEFAULT | BACKGROUND_DEFAULT;
public:

    constexpr explicit TerminalColor ( Flags f ) noexcept : f(f) {}
    constexpr TerminalColor ( TerminalColor const & ) noexcept = default;
    static auto asList ( Flags f ) noexcept -> String {
        String res;
        FOREACH_FLAG(0, 31, CDS_uint32, i ) {
            if ( colorMap.containsKey( static_cast<Modifier>(i) ) && ( f & i ) ) {
                res.append( colorMap.get( static_cast<Modifier>(i) ) ).append(";");
            }
        }
        return res.rtrim(';');
    }

    friend std::ostream & operator << ( std::ostream & o, TerminalColor const & c ) {
        o << "\033[" << asList(c.f) << "m";
        return o;
    }

    static TerminalColor clear;
};

TerminalColor TerminalColor::clear(DISABLE_INVERSE_COLOR | DISABLE_UNDERLINE | DISABLE_BOLD | RESET );

HashMap < TerminalColor::Modifier, int > TerminalColor::colorMap = {
        {RESET, 0},
        {ENABLE_BOLD, 1},
        {ENABLE_UNDERLINE, 4},
        {ENABLE_INVERSE_COLOR, 7},
        {DISABLE_BOLD, 21},
        {DISABLE_UNDERLINE, 24},
        {DISABLE_INVERSE_COLOR, 27},

        {FOREGROUND_BLACK, 30},
        {FOREGROUND_RED, 31},
        {FOREGROUND_GREEN, 32},
        {FOREGROUND_YELLOW, 33},
        {FOREGROUND_BLUE, 34},
        {FOREGROUND_MAGENTA, 35},
        {FOREGROUND_CYAN, 36},
        {FOREGROUND_WHITE, 37},

        {BACKGROUND_BLACK, 40},
        {BACKGROUND_RED, 41},
        {BACKGROUND_GREEN, 42},
        {BACKGROUND_YELLOW, 43},
        {BACKGROUND_BLUE, 44},
        {BACKGROUND_MAGENTA, 45},
        {BACKGROUND_CYAN, 46},
        {BACKGROUND_WHITE, 47}
};

TerminalColor testOK ( TerminalColor::Modifier::FOREGROUND_GREEN | TerminalColor::Modifier::ENABLE_BOLD | TerminalColor::Modifier::ENABLE_UNDERLINE );
TerminalColor subtestOK ( TerminalColor::Modifier::FOREGROUND_GREEN );
TerminalColor testNOK ( TerminalColor::Modifier::FOREGROUND_RED | TerminalColor::Modifier::ENABLE_BOLD );



void testThread();
void testList ();
void testString ();
void testMap ();
void testSet ();
void testPointer ();
void testReference ();
void testOptional ();
void testRange ();
void testPrimitives();
void testJSON();
void testArray();
void testRandom();

int main() {

//    testRandom();
    testThread();

    testArray();

    testPrimitives();
    testJSON();

    testList();
    testString();
    testMap();
    testSet();
    testPointer();
    testReference();
    testOptional();
    testRange();

    return 0;
}

#include <functional/Random.hpp>
void testRandom () {
//    std::random_device d;
//    std::mt19937 tw(d());
//    Random::Int<int, std::uniform_int_distribution<int>> dist(0, 5);
    Random::Int dist(2, 5);
    Random::Long distLong((CDS_sint64)INT32_MAX + 1, INT64_MAX - 1);
    Random::Float distFloat(1.0f, 2.0f);
    Random::Double distDouble(0.0f, 1.0f);

    Random::UnsignedInt rUint;

//    distFloat.seed(10);

//    rUint.seed(10);

    std::random_device d;
    std::mt19937 tw(d());
    std::uniform_int_distribution<int> di(0, 10);

//    std::mt19937 ::default_seed
//    std::mt19937 ::result_type

    for ( auto i : Range(0, dist.get()) )
        std::cout << dist() << '\n';

    for ( auto i : Range(0, dist.get()) )
        std::cout << distLong() << '\n';

    for ( auto i : Range(0, dist.get()) )
        std::cout << distFloat() << '\n';

    for ( auto i : Range(0, dist.get()) )
        std::cout << distDouble() << '\n';

    for ( auto i : Range(0, dist.get()) )
        std::cout << rUint() << '\n';

    exit(0);
}

//#define MUTEX_IMPLEMENTATION_WINAPI_MUTEX
#include <CDS/Thread>
#include <CDS/Mutex>
#include <threading/Semaphore.hpp>
#include <functional/Generator.hpp>
#include <chrono>

class IntGenerator : public Generator<int, int> {
    auto task(int startPoint) noexcept -> int override {
        int i = 5;
        while( i < 15 ) {
            this->yield(i++);
        }

        return i;
    }
};

#if defined(__linux)
#include <unistd.h>
#endif
#include <primitive/Tuple.hpp>
#include <threading/Timer.hpp>

void testThread () {

    for ( auto i : Range(0, 10) ) {
        Timer t;
        t.setInterval(550 );

        t.start( [] () { std::cout << "Test\n"; std::cout.flush(); } );
        sleep(1);
        t.pause();
        sleep(2);
        t.unpause();
        sleep(1);

        t.stop();

        std::cout << "Stopped\n";
    }

    exit(0);
//    Tuple < double, int > tuple = { 3.4, 5 };
////    std::cout << tuple_impl::get<0>(tuple) << '\n';
////    std::cout << tuple_impl::get<1>(tuple) << '\n';
//    std::cout << tuple.get<0>() << '\n';
//    std::cout << tuple.get<1>() << '\n';
//
//    Tuple < double, int > tuple2 = {3.4, 5};
//
//    Tuple tuple3 = {4, 5.4f, String("Ana are mere"), 'c'};
//
//    std::cout << (tuple == tuple2) << '\n';
//    std::cout << tuple3.size() << '\n';
//
////    Tuple t4 = tuple3;
////
////    std::cout << t4.get<2>() << '\n';
////
////    exit(0);
//
//    IntGenerator g;
//
//    std::cout << g(5) << '\n';
//
//    for ( auto o : g(5) ) {
//        std::cout << o << '\n';
//    }
//
//    class StringReader : public Generator < char, String const & > {
//    public:
//        auto task (String const & o) noexcept -> char override {
//            for ( auto c : o )
//                this->yield(c);
//            return '\0';
//        }
//    };
//
//    class Test : public Generator < String > {
//    public:
//        auto task () noexcept -> String override {
//            int rep = 10;
//            while ( rep -- ) {
//                yield(this->toString());
//            }
//
//            return this->toString();
//        }
//    };
//
//    StringReader sr;
//
//    for ( auto c : sr("Ana are mere") ) {
//        std::cout << c;
//    }
//
//    Test test;
//
//    for ( auto e : test() )
//        std::cout << e << '\n';
//
//    std::cout << "Loop End------------------------------\n";
//
//    std::cout << test.toString() << '\n';
//
//    test.restart();
//
//    for ( auto e : test() )
//        std::cout << e << '\n';
//
//    std::cout << "Loop End------------------------------\n";
//
//    std::cout << test.toString() << '\n';
//
//    class Rng : public Generator < float > {
//        auto task () noexcept -> float override {
//            Random::Float floatGen;
//
//            while(true)
//                yield(floatGen.get());
//
//            return floatGen.get();
//        }
//    };
//
//    Rng rng;
//
//    for ( auto x : rng() ) {
//        std::cout << x << '\n';
//    }
//
//    exit(0);
    Semaphore s;
    Semaphore s2;
    Semaphore s3;

    constexpr static int repCountAll = 100000;

    float t = 0.5f;
    Runnable x( [ &t, &s, &s3 ](){
        int repCount = repCountAll;
        while ( repCount > 0 ) {
            t = t + 1.0f;
//            std::cout << "Thread 1 Modified y = " << t << '\n';
            repCount --;
            s.notify();
            s3.wait();
        }
    });
    Runnable y([ &t, &s, &s2 ]() {
        int repCount = repCountAll;

        while ( repCount > 0 ) {
            s.wait();

            t = t - .3f;

//            std::cout << "Thread 2 Modified y = " << t << '\n';
            repCount --;

            s2.notify();
        }
    });

    Runnable z( [&t, &s2, &s3]() {
        int repCount = repCountAll;

        while ( repCount > 0 ) {
            s2.wait();

            t += .7f;

//            std::cout << "Thread 3 Modified y = " << t << '\n';
            repCount--;

            s3.notify();
        }
    });

    auto start = std::chrono::high_resolution_clock::now();

    z.start();
    x.start();
    y.start();

    z.join();
    x.join();
    y.join();

    auto end = std::chrono::high_resolution_clock::now();

//    std::cout << t << '\n';
    std::cout
        << "Result : " << t << "\n"
        << "Thread Loops : " << repCountAll << "\n"
        << "Elapsed Time : " << (end - start).count() / std::pow(10, 9) << "\n"
        << "Thread Impl" << Runnable([](){}).toString() << "\n"
        << "Mutex Impl" << Mutex().toString() << "\n";

//    Runnable a (
//        [] () {
//            int x = 500;
//            while(x > 0) {
//                std::cout << x << ' ';
//                x--;
//            }
//        }
//    );
//
//    a.start();
//    a.join();

    exit(0);
}


#include <CDS/Array>
void testArray () {
    Array<float> a = {1.2f, 5.1f, 412.3f};

    std::cout << a << '\n';

    a.pushBack( 4.3f );

    std::cout << a << '\n';

    a.pushFront( 6.12f );

    std::cout << a << '\n';

    a.popFront();

    std::cout << a << '\n';

    a.popFront();

    std::cout << a << '\n';

    a.popBack();

    std::cout << a << '\n';

    a.popBack();

    std::cout << a << '\n';

    a.pushFront(6.1f);
    a.pushFront(3.1f);
    a.pushFront(7.1f);

    std::cout << a << '\n';

#if defined(__cpp_concepts) && !defined(_MSC_VER)
    a.sort ( [](auto & a, auto & b){return a < b;} );
#endif

    std::cout << a <<'\n';

#if defined(__cpp_concepts) && !defined(_MSC_VER)
    std::cout << a.count([](auto & e){return e > 5.0f;}) << '\n';
#endif

//    exit(0);
}

#include <CDS/Integer>
#include <CDS/Long>
#include <CDS/Float>
#include <CDS/Boolean>
#include <CDS/Double>
void testPrimitives() {
    Integer x = 3;

    std::cout << Integer::parse("1234") + 5 << '\n';

    Long l = 5;

    std::cout << Long::parse("231421512123252") + l << "\n";

    Float f = 5.54f;

    std::cout << Float::parse("13442.2453f") + f << "\n";

    Boolean b = false;

    std::cout << ( Boolean::parse("true") && b ) << '\n';

    Double d = 5.5;

    std::cout << Double::parse("123141.1254123") + d << '\n';

//    exit(0);
}
#include <CDS/JSON>
void testJSON () {
    try {
//        auto test = JSON::Node();
//
//        test.setLabel("test1");
//        test.put(true);
//        std::cout << test.toString() << "\n";
//
//        test.put(3.4);
//        std::cout << test.toString() << "\n";
//
//        test.put(3.5f);
//        std::cout << test.toString() << "\n";
//
////        test.put('z');
//        test.put("test");
//        std::cout << test.toString() << "\n";
//
//        test.put(3);
//        std::cout << test.toString() << "\n";
//
//        test.put(5000000000000ll);
//        std::cout << test.toString() << "\n";
//
//        test.put("test");
//        std::cout << test.toString() << "\n";

    } catch (std::exception &e) {
        std::cout << e.what();
    }

    auto array = JSON::Array();
    array.put(2, 1);
    std::cout << array.toString() << '\n';
    array.put(3, 20.5f);
    std::cout << array.toString() << '\n';
    array.put(0, "test");
    std::cout << array.toString() << '\n';

    JSON o;
    o.put("ex1", 1);
    o.put("ex2", 1.5);
    o.put("ex3", 1.4f);
    o.put("ex4", true);
    o.put("ex5", "test2");
    o.put("ex6", array);

    JSON o2;

    o2.put("sub1", array);
    o2.put("sub2", "test3");

    o.put("ex7", o2);

    std::cout << o.toString() << '\n';
    std::cout << o.getJSON("ex7").toString() << '\n';
    std::cout << o.getArray("ex6").toString() << '\n';
    std::cout << o.getString("ex5") << '\n';
    std::cout << o.getFloat("ex3") << '\n';
    std::cout << o.getArray("ex6").getString(0) << '\n';

    String str = R"({"ex1" : 1, "ex2" : 1.500000, "ex3" : 1.400000, "ex4" :true, "ex5" : "test2", "ex6" : ["test", 1, 20.500000], "ex7" : {"sub1" : ["test", 1, 20.500000], "sub2" : "pana mea"}})";

    auto parsed = JSON::parse(str);

    std::cout << parsed.toString() << '\n';
    std::cout << parsed.getString("ex5") << '\n';
    std::cout << parsed.getArray("ex6").getInt(1) << '\n';
    std::cout << parsed.getJSON("ex7").getString("sub2") << '\n';
    std::cout << parsed.getJSON("ex7").getArray("sub1").getString(0) << '\n';

//    exit(0);
}

void markTestStart (StringLiteral testName) {
    std::cout << "-----Test '" << testName << "'-----\n\n";
}

void markTestEnd (StringLiteral testName = nullptr) {
    std::cout << "-----EndOfTest" << (testName == nullptr ? String("") : (String("'") + testName + "'")) << "-----\n\n";
}

#define COMMA ,

void testList_DoubleLinkedList() {
    markTestStart("DoubleLinkedList");

    try {
        std::cout << testOK;

#define DLL_TEST_SUITE(dType, vName, initializer) \
        DoubleLinkedList<dType> vName = initializer; \
        std::cout << subtestOK << "Created DLL of " #dType << " : " << vName.toString() << '\n'; \
        std::cout << "Pop of Front : " << vName.popFront() << '\n';\
        std::cout << "Pop of Back : " << vName.popBack() << '\n';\
        std::cout << TerminalColor::clear;

        DLL_TEST_SUITE(int, intList, {1 COMMA 2 COMMA 3 COMMA 4 COMMA 5 COMMA 1 COMMA 3})
        DLL_TEST_SUITE(float, floatList, {0.1f COMMA 0.2f COMMA 0.3f COMMA 0.4f COMMA 0.5f COMMA 0.6f COMMA 0.3f COMMA 0.4f})
        DLL_TEST_SUITE(double, doubleList, {0.7 COMMA  0.9 COMMA  1.1 COMMA  1.5 COMMA  1.5 COMMA  2.7 COMMA  0.9})
        DLL_TEST_SUITE(bool, boolList, {false COMMA  true COMMA  true COMMA  false})
//        DLL_TEST_SUITE(UniquePointer<int>, upList, {
//                UniquePointer<int>(new int(1)) COMMA
//                UniquePointer<int>(new int(2)) COMMA
//                UniquePointer<int>(new int(3)) COMMA
//                UniquePointer<int>(new int(4)) COMMA
//                UniquePointer<int>(new int(5)) COMMA
//                UniquePointer<int>(new int(1)) COMMA
//                UniquePointer<int>(new int(3)) COMMA
//                UniquePointer<int>(new int(1)) COMMA
//        })
        DLL_TEST_SUITE(Reference<int>, refList, {
                Reference<int>(intList[0]) COMMA
                Reference<int>(intList[1]) COMMA
                Reference<int>(intList[2]) COMMA
                Reference<int>(intList[3]) COMMA
                Reference<int>(intList[4]) COMMA
                Reference<int>(intList[5]) COMMA
                Reference<int>(intList[6]) COMMA
                Reference<int>(intList[7])
        })
        DLL_TEST_SUITE(String, stringList, {"Ana" COMMA  "are" COMMA  "mere" COMMA  "merele" COMMA  "o" COMMA  "au" COMMA  "pe" COMMA  "Ana"})
        DLL_TEST_SUITE(Optional<int>, optionalList, { {} COMMA  {1} COMMA  {2} COMMA  {5} COMMA  {1} COMMA  {} COMMA  {2} COMMA  {} COMMA  {1} COMMA  {} })
        DLL_TEST_SUITE(Pair<int COMMA  int>, pairList, {
                {1 COMMA  2} COMMA
                {4 COMMA  3} COMMA
                {5 COMMA  7} COMMA
                {1 COMMA  2} COMMA
                {2 COMMA  5} COMMA
                {3 COMMA  4} COMMA
                {6 COMMA  6} COMMA
                {7 COMMA  5} COMMA
                {4 COMMA  3} COMMA
                {3 COMMA  1} COMMA
                {2 COMMA  2} COMMA
                {5 COMMA  6} COMMA
                {1 COMMA  8}
        })
    } catch ( std::exception const & e ) {
        std::cout << testNOK << "Test Not OK : " << e.what() << '\n';
        std::cout << TerminalColor::clear;
    }

    std::cout << testOK << "Test OK\n";
    std::cout << TerminalColor::clear;

    markTestEnd("DoubleLinkedList");
}

void testList () {
    markTestStart("List");

    testList_DoubleLinkedList();

    markTestEnd("List");
}

void testString () {

}

void testMap () {

}

void testSet () {

}

void testPointer () {

}

void testReference () {

}

void testOptional () {

}

void testRange () {

}

