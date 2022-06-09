//
// Created by loghin on 5/18/22.
//

#include "TupleTest.h"
#include <CDS/Tuple>

using namespace cds;

bool TupleTest :: execute () noexcept {


    auto t = Tuple <int, int, int> ( 3, 4, 5 );

    Tuple <int,int,int> t2 ( t );

    Tuple <int, float> t3;

    auto t4 = Tuple < int, std :: string > ( 3, "ana" );
    auto t5 = std :: move ( t4 );

    std :: cout << t5.get < 0 > () << '\n';
    t5.get <1> ()= "mara";
    std :: cout << t4.get < 1 > () << '\n';
    std :: cout << t5.get < 1 > () << '\n';

    auto t6 = t5;

    std :: cout << t6.get <1> () << '\n';

    Tuple < int, float > t7 = {1, 3.5f};

    t7 = { 1, 3.9f };

    Tuple < int > t8 = 3;

    std :: cout << t7.get<1>() << '\n';
    std :: cout << t8.get<0>() << '\n';

    Tuple < Tuple < Tuple < int, float > > > t10 = Tuple < int, float > { 1, 4.5f };

    std :: cout << t10.get<0>().get<0>().get<0>() << '\n';

    auto t11 = t7;
    std :: cout << (t7 == t11) << '\n';
    t11.get<0>() = 3;
    std :: cout << (t7 == t11) << '\n';

    std :: cout << t6 << '\n';

    return true;
}