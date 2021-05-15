#include <iostream>
#include <cstring>
#include <exception>

#include <CDS/File>
#include <unistd.h>
int main() {
    std::cout << File::platformTypeFlagsToString(File::platformFileType("/")) << '\n';
    std::cout << File::platformPermissionFlagsToStringList ( File::PlatformPermissionFlag::PPF_EXECUTE | File::PPF_READ ) << '\n';
    std::cout << File::platformUserFlagsToString ( File::PUF_USER | File::PUF_OTHER ) << '\n';

//    std::cout << File::platformPermissionsGrouped ("/") << '\n';
    try {
        File::platformPermissionsGrouped("/home/loghin/work/dataStructures/main.cpp").forEach([](auto &p) {
            std::cout << File::platformUserFlagToString(p.getFirst()) << " : "
                      << File::platformPermissionFlagsToString(p.getSecond()) << '\n';
        });

        auto file = File::LinuxDirectory("/home/loghin");
        file.directories().forEach([](auto * d){
            std::cout << File::platformTypeFlagsToStringList (d->linuxFileType()) << " : " << d->name() << '\n';
            d->entries().forEach([](auto * e){
                std::cout << "\t" << File::platformTypeFlagsToStringList (e->linuxFileType()) << " : " << e->name() << ", size = " << e->linuxTotalSize() << '\n';
            });
        });


    } catch (std::exception const & e) {
        std::cout << e.what() << ", path hardcoded for testing purposes\n";
    }
}