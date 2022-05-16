#include <CDS/Thread>
#include <CDS/smartPointers/UniquePointer>

using namespace cds;

int main () {

    UniquePointer < Thread > t = new Runnable ( [& t]{

        uint32 repeats = 10;

        for ( uint32 i = 0; i < repeats; ++ i ) {
            (void) t->sleep ( 500 );
            std :: cout << "Slept for 500ms" << '\n';
        }
    });

    t->start();
    t->join();
    return 0;
}