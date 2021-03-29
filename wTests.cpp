#include <CDS/LinkedList>
#include <iostream>

//#include <unistd.h>
#include <windows.h>

#include <threading/Timer.hpp>
#include <CDS/Range>

int main () {
    try {
        for ( auto i : Range (0, 500) ) {
            Timer t;

            t.setInterval(20);
            t.start([]() { std::cout << "Period\n"; });


            Sleep(100);
//            sleep(1);

            t.stop();

            std::cout << "Stop\n";
        }
    } catch ( std::exception const & e ) {
        std::cout << e.what() << '\n';
    }

    return 0;
}