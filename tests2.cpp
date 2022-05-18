#include <CDS/Thread>
#include <CDS/smartPointers/UniquePointer>
#include <CDS/experimental/meta/TypeTraits>
#include <CDS/experimental/meta/FunctionTraits>
#include <CDS/experimental/Tuple>
using namespace cds :: experimental;

template < typename T, typename = void >
struct isMemberFunctionPointer : std :: false_type { };

template < typename R, typename C >
struct isMemberFunctionPointer < R C :: *, C > : std :: is_function < R > { };

class B {
public:
    int f();
};

class A {
public:
    int x;
    int f();
};

void g();
int y;

template < typename T, meta :: EnableIf < std :: is_same_v < T, bool > > = 0 >
void f () {
    std :: cout << "bool\n";
}

template < typename T, meta :: EnableIf < ! std :: is_same_v < T, bool > > = 0 >
void f () {
    std :: cout << "not bool\n";
}

namespace details {
    template <typename B>
    std::true_type test_pre_ptr_convertible(const volatile B*);
    template <typename>
    std::false_type test_pre_ptr_convertible(const volatile void*);

    template <typename, typename>
    auto test_pre_is_base_of(...) -> std::true_type;
    template <typename B, typename D>
    auto test_pre_is_base_of(int) ->
    decltype(test_pre_ptr_convertible<B>(static_cast<D*>(nullptr)));
}

template <typename Base, typename Derived>
struct is_base_of :
        std::integral_constant<
                bool,
                std::is_class<Base>::value && std::is_class<Derived>::value &&
                decltype(details::test_pre_is_base_of<Base, Derived>(0))::value
        > { };

int main () {
//

    auto t = Tuple <int, int, int> ( 3, 4, 5 );
////    Tuple <int,int,int> t;
    Tuple <int,int,int> t2 ( t );
//
    Tuple <int, float> t3;

    auto t4 = Tuple < int, std :: string > ( 3, "ana" );
    auto t5 = std :: move ( t4 );

    f <int>();
    f <bool>();

    class A{};
    class B:  A{};

    std :: cout << meta :: Type < A > :: isBaseFor < B > () << '\n';

    meta :: Conditional < true, int, float > v1 = 1;
    meta :: Conditional < false, int, float > v2 = 1.5f;

    std :: cout << v1 << '\n' << v2 << '\n';

    std :: cout << meta :: isSame < float, int > () << '\n';
    std :: cout << meta :: isSame < int, int > () << '\n';

    std :: cout << meta :: lessThanPossible < int *, int * > () << '\n';

    std :: cout << meta :: Type < void * > :: hasEqualTo () << '\n';

    std :: cout << meta :: impl :: IsPrintable < void * > :: value << '\n';
    std :: cout << meta :: impl :: IsPrintable < void > :: value << '\n';

//    std :: cout << isMemberFunctionPointer < decltype ( & A :: x ), A > :: value << '\n';
//    std :: cout << isMemberFunctionPointer < decltype ( & A :: f ), B > :: value << '\n';
//    std :: cout << isMemberFunctionPointer < decltype ( g ), A > :: value << '\n';
//    std :: cout << isMemberFunctionPointer < decltype ( y ), A > :: value << '\n';

    return 0;
}